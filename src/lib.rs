#![crate_type="dylib"]
#![feature(quote, plugin_registrar, rustc_private)]

extern crate syntax;
extern crate rustc_plugin;

use syntax::symbol::Symbol;
use syntax::codemap::Span;
use syntax::ext::base::{ExtCtxt, Annotatable};
use syntax::ext::base::SyntaxExtension::{MultiDecorator};
use syntax::ast::MetaItem;
use rustc_plugin::Registry;

pub fn expand(
    cx: &mut ExtCtxt,
    _sp: Span,
    _mi: &MetaItem,
    _item: &Annotatable,
    push: &mut FnMut( Annotatable )
) {
    push( Annotatable::Item( quote_item!( cx,
            pub fn method() { println!( "Hello world!" ); }).unwrap() ) );
}

#[plugin_registrar]
pub fn registrar( reg: &mut Registry ) {

    reg.register_syntax_extension(
            Symbol::intern("decorator"),
            MultiDecorator( Box::new( expand ) ) );
}
