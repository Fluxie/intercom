
use std::io::Write;
use std::path::Path;

use super::GeneratorError;

use intercom_common::model;
use intercom_common::utils;

use handlebars::Handlebars;

#[derive(PartialEq, Debug, Serialize)]
pub struct ManifestModel {
    pub lib_name : String,
    pub lib_id : String,
    pub file_name : String,
    pub classes : Vec<ManifestCoClass>,
}

#[derive(PartialEq, Debug, Serialize)]
pub struct ManifestCoClass {
    pub name : String,
    pub clsid : String,
}

impl ManifestModel {

    /// Prints the manifest based on the parse result.
    fn from_crate(
        c : &model::ComCrate
    ) -> Result<ManifestModel, GeneratorError>
    {
        let lib = c.lib().as_ref().ok_or( GeneratorError::MissingLibrary )?;

        // Gather all the com classes. These need to be declared in the manifest.
        let classes = lib.coclasses().iter().map(|class_name| {

            let coclass = &c.structs()[ class_name.as_ref() ];
            let clsid = coclass.clsid().as_ref()
                    .ok_or_else( || GeneratorError::MissingClsid(
                                        coclass.name().to_string() ) )?;
            Ok( ManifestCoClass {
                name : coclass.name().to_string(),
                clsid : format!( "{}", clsid ),
            } )
        } ).collect::<Result<Vec<_>, GeneratorError>>()?;

        Ok( ManifestModel {
            lib_name : utils::pascal_case( lib.name() ),
            file_name : lib.name().to_owned(),
            lib_id : format!( "{}", lib.libid() ),
            classes : classes,
        } )
    }
}

/// Run the manifest sub-command.
#[allow(dead_code)]
pub fn write( path : &Path, out : &mut Write ) -> Result<(), GeneratorError> {

    // Parse the source files and emit the manifest.
    let krate = if path.is_file() {
            model::ComCrate::parse_cargo_toml( path )
        } else {
            model::ComCrate::parse_cargo_toml( &path.join( "Cargo.toml" ) )
        }.map_err( |_| GeneratorError::CrateParseError )?;

    let model = ManifestModel::from_crate( &krate )?;
    let mut reg = Handlebars::new();
    reg.register_template_string( "manifest", include_str!( "manifest.hbs" ) )
            .expect( "Error in the built-in Manifest template." );

    let rendered = reg
            .render( "manifest", &model )
            .expect( "Rendering a valid ComCrate to Manifest failed" );
    write!( out, "{}", rendered )?;

    Ok(())
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    pub fn crate_to_manifest() {

        let krate = model::ComCrate::parse( "com_library", &[ r#"
            #[com_library( "11112222-3333-4444-5555-666677778888", CoClass )]
            struct S;

            #[com_interface( "22223333-4444-5555-6666-777788889999", NO_BASE )]
            trait IInterface {
                fn method( &self, a : u32 ) -> ComResult<bool>;
            }

            #[com_class( "33334444-5555-6666-7777-888899990000", CoClass, IInterface )]
            struct CoClass;

            #[com_interface( "44445555-6666-7777-8888-99990000AAAA" )]
            #[com_impl]
            impl CoClass {
                pub fn new() -> CoClass { CoClass }
                pub fn com_method( &self, b : u32 ) {}
            }

            #[com_impl]
            impl IInterface for CoClass {
                fn method( &self, a : u32 ) -> ComResult<bool> { unreachable!() }
            }
        "# ] ).expect( "Could not parse test crate" );

        let expected_manifest = ManifestModel {
            lib_name : "ComLibrary".to_owned(),
            lib_id : "{11112222-3333-4444-5555-666677778888}".to_owned(),
            file_name : "com_library".to_owned(),
            classes : vec![
                ManifestCoClass {
                    name : "CoClass".to_owned(),
                    clsid : "{33334444-5555-6666-7777-888899990000}".to_owned(),
                }
            ],
        };

        let actual_manifest = ManifestModel::from_crate( &krate ).unwrap();

        assert_eq!( expected_manifest, actual_manifest );
    }
}
