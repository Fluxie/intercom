use super::common::*;
use crate::prelude::*;

use crate::idents;
use crate::model;
use crate::utils;
use std::iter::FromIterator;

use syn::spanned::Spanned;

/// Expands the `com_library` macro.
///
/// The macro expansion results in the following items:
///
/// - `DllGetClassObject` extern function implementation.
/// - `IntercomListClassObjects` extern function implementation.
pub fn expand_com_module(
    arg_tokens: TokenStreamNightly,
    com_library: bool,
) -> Result<TokenStreamNightly, model::ParseError>
{
    let mut output = vec![];
    let lib = model::ComLibrary::parse(&lib_name(), arg_tokens.into())?;

    // Create the match-statmeent patterns for each supposedly visible COM class.
    let mut match_arms = vec![];
    for struct_path in &lib.coclasses {
        // Construct the match pattern.
        let clsid_path = idents::clsid_path(struct_path);
        match_arms.push(quote_spanned!(struct_path.span() =>
            #clsid_path =>
                return Some(intercom::ClassFactory::<#struct_path>::new(riid, pout))
        ));
    }

    let try_submodule_class_factory = lib.submodules.iter().map(|submod| {
        quote!(
            if let Some(hr) = #submod::__get_module_class_factory(rclsid, riid, pout) {
                return Some(hr);
            }
        )
    });

    // Implement the __get_module_class_factory function.
    output.push(quote!(
        #[allow(dead_code)]
        #[doc(hidden)]
        pub unsafe fn __get_module_class_factory(
            rclsid : intercom::REFCLSID,
            riid : intercom::REFIID,
            pout : *mut intercom::RawComPtr
        ) -> Option<intercom::raw::HRESULT>
        {
            // Create new class factory.
            // Specify a create function that is able to create all the
            // contained coclasses.
            match *rclsid {
                #( #match_arms, )*
                _ => {},
            };

            // Try each sub-module
            #( #try_submodule_class_factory )*

            None
        }
    ));

    // Implement DllGetClassObject.
    //
    // This is more or less the only symbolic entry point that the COM
    // infrastructure uses. The COM client uses this method to acquire
    // the IClassFactory interfaces that are then used to construct the
    // actual coclasses.
    if com_library {
        let dll_get_class_object = get_dll_get_class_object_function();
        output.push(dll_get_class_object);
    }

    // Implement get_intercom_typelib()
    output.push(create_gather_module_types(&lib).map_err(model::ParseError::ComLibrary)?);
    if com_library {
        output.push(create_get_typelib_function(&lib).map_err(model::ParseError::ComLibrary)?);
    }

    // Implement DllListClassObjects
    // DllListClassObjects returns all CLSIDs implemented in the crate.
    if com_library {
        let list_class_objects = get_intercom_list_class_objects_function();
        output.push(list_class_objects);
    }

    Ok(TokenStream::from_iter(output.into_iter()).into())
}

fn get_dll_get_class_object_function() -> TokenStream
{
    quote!(
        #[no_mangle]
        #[allow(non_snake_case)]
        #[allow(dead_code)]
        #[doc(hidden)]
        pub unsafe extern "system" fn DllGetClassObject(
            rclsid: intercom::REFCLSID,
            riid: intercom::REFIID,
            pout: *mut intercom::RawComPtr,
        ) -> intercom::raw::HRESULT
        {
            // Delegate to the module implementation.
            if let Some(hr) = __get_module_class_factory(rclsid, riid, pout) {
                return hr;
            }

            // Try intercom built in types.
            if let Some(hr) = intercom::__get_module_class_factory(rclsid, riid, pout) {
                return hr;
            }

            intercom::raw::E_CLASSNOTAVAILABLE
        }
    )
}

fn create_gather_module_types(lib: &model::ComLibrary) -> Result<TokenStream, String>
{
    let create_class_typeinfo = lib.coclasses.iter().map(|path| {
        quote!(
            <#path as intercom::attributes::HasTypeInfo>::gather_type_info()
        )
    });
    let gather_submodule_types = lib
        .submodules
        .iter()
        .map(|path| quote!( #path::__gather_module_types()));
    Ok(quote!(
        pub fn __gather_module_types() -> Vec<intercom::typelib::TypeInfo>
        {
            vec![
                #( #create_class_typeinfo, )*
                #( #gather_submodule_types, )*
            ]
            .into_iter()
            .flatten()
            .collect()
        }
    ))
}

fn create_get_typelib_function(lib: &model::ComLibrary) -> Result<TokenStream, String>
{
    let lib_name = lib_name();
    let libid = utils::get_guid_tokens(&lib.libid, Span::call_site());
    Ok(quote!(
        #[no_mangle]
        pub unsafe extern "system" fn IntercomTypeLib(
            type_system: intercom::type_system::TypeSystemName,
            out: *mut intercom::RawComPtr,
        ) -> intercom::raw::HRESULT
        {
            let mut tlib = intercom::ComBox::new(intercom::typelib::TypeLib::__new(
                    #lib_name.into(),
                    #libid,
                    "0.1".into(),
                    intercom::__gather_module_types()
                        .into_iter().chain(__gather_module_types())
                        .collect()
            ));
            let rc = intercom::ComRc::<intercom::typelib::IIntercomTypeLib>::from( &tlib );
            let itf = intercom::ComRc::detach(rc);
            *out = match type_system {
                intercom::type_system::TypeSystemName::Automation =>
                    intercom::ComItf::ptr::<intercom::type_system::AutomationTypeSystem>(&itf).ptr,
                intercom::type_system::TypeSystemName::Raw =>
                    intercom::ComItf::ptr::<intercom::type_system::RawTypeSystem>(&itf).ptr,
            };

            intercom::raw::S_OK
        }
    ))
}

fn get_intercom_list_class_objects_function() -> TokenStream
{
    quote!(
        #[no_mangle]
        #[allow(non_snake_case)]
        #[allow(dead_code)]
        #[doc(hidden)]
        pub unsafe extern "system" fn IntercomListClassObjects(
            pcount: *mut usize,
            pclsids: *mut *const intercom::CLSID,
        ) -> intercom::raw::HRESULT
        {
            // Do not crash due to invalid parameters.
            if pcount.is_null() {
                return intercom::raw::E_POINTER;
            }
            if pclsids.is_null() {
                return intercom::raw::E_POINTER;
            }

            // Store the available CLSID in a static variable so that we can
            // pass them as-is to the caller.
            static mut AVAILABLE_CLASSES: Option<Vec<intercom::CLSID>> = None;
            static INIT_AVAILABLE_CLASSES: std::sync::Once = std::sync::Once::new();
            INIT_AVAILABLE_CLASSES.call_once(|| unsafe {
                AVAILABLE_CLASSES = Some(
                    __gather_module_types()
                        .into_iter()
                        .chain(intercom::__gather_module_types())
                        .filter_map(|ty| match ty {
                            intercom::typelib::TypeInfo::Class(cls) => Some(cls.clsid.clone()),
                            _ => None,
                        })
                        .collect(),
                );
            });

            // com_struct will drop here and decrement the referenc ecount.
            // This is okay, as the query_interface incremented it, leaving
            // it at two at this point.
            let available_classes = AVAILABLE_CLASSES
                .as_ref()
                .expect("AVAILABLE_CLASSES was not initialized");
            *pcount = available_classes.len();
            *pclsids = available_classes.as_ptr();

            intercom::raw::S_OK
        }
    )
}
