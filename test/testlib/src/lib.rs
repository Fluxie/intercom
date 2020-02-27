#![crate_type = "dylib"]
#![allow(clippy::match_bool)]

extern crate intercom;
use intercom::*;
extern crate chrono;
extern crate winapi;

pub mod alloc;
pub mod error_info;
pub mod interface_params;
pub mod nullable_parameters;
pub mod output_memory;
pub mod primitive;
pub mod result;
pub mod return_interfaces;
pub mod stateful;
pub mod strings;
pub mod struct_parameters;
pub mod type_system_callbacks;
pub mod unicode;
pub mod variant;

// Declare available COM classes.
com_library! {
    module return_interfaces,
    module nullable_parameters,

    class primitive::PrimitiveOperations,
    class return_interfaces::RefCountOperations,
    class return_interfaces::ClassCreator,
    class return_interfaces::CreatedClass,
    class stateful::StatefulOperations,
    class result::ResultOperations,
    class interface_params::SharedImplementation,
    class error_info::ErrorTests,
    class alloc::AllocTests,
    class strings::StringTests,
    class type_system_callbacks::TypeSystemCaller,
    class variant::VariantTests,
    class variant::VariantImpl,
    class unicode::UnicodeConversion,
    class output_memory::OutputMemoryTests,

    interface IOnlyInterface,

    // Ensure exporting interfaces that would otherwise be included as well
    // does not cause problem.

    class struct_parameters::StructParameterTests,
    user_type struct_parameters::BasicStruct,
    user_type struct_parameters::StringStruct,
    user_type struct_parameters::Rectangle,
    user_type struct_parameters::Point,
    interface interface_params::ISharedInterface,
}

#[com_interface]
pub trait IOnlyInterface
{
    fn method(&self) -> ComResult<u32>;
}
