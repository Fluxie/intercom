#![feature(use_extern_macros, attr_literals)]

extern crate intercom;
use intercom::*;

#[com_interface("00000000-0000-0000-0000-000000000000")]
pub trait Foo {
    fn static_method(a: u16, b: i16);

    fn simple_method(&self);

    fn arg_method(&self, a: u16);

    fn simple_result_method(&self) -> u16;
    fn com_result_method(&self) -> ComResult<u16>;
    fn rust_result_method(&self) -> Result<u16, i32>;

    fn complete_method(&mut self, a: u16, b: i16) -> ComResult<bool>;

    fn string_method(&self, msg: String) -> String;
    fn comitf_method(&self, itf: ComItf<Foo>) -> ComResult<ComItf<IUnknown>>;
}
