
use super::common::*;
use crate::prelude::*;

use crate::idents;
use crate::model;
use crate::utils;
use std::iter::FromIterator;

use crate::tyhandlers::{ModelTypeSystem};
use syn::*;

struct Tokens
{
    tokens: proc_macro2::TokenStream
}

impl quote::ToTokens for Tokens
{
    fn to_tokens(
        &self,
        output: &mut proc_macro2::TokenStream
    ) {
        output.extend( self.tokens.clone() );
    }
}

/// Expands the `com_struct` attribute.
///
/// The attribute expansion results in the following items:
///
/// - #[repr(C)]
pub fn expand_com_struct(
    attr_tokens: TokenStreamNightly,
    item_tokens: TokenStreamNightly,
) -> core::result::Result<TokenStreamNightly, model::ParseError>
{
    // Parse the attribute.
    // let com_struct = model::ComStruct::parse(
    //         &lib_name(), attr_tokens.into(), &item_tokens.to_string() )?;
    // let struct_ident = com_struct.name();

    // output.push( quote!(

    //         #[repr(C)]
    //         #struct_ident {
    //             fir
    //         }
    // ) );

    // Ok( tokens_to_tokenstream( item_tokens, output ) )
    let input = Tokens { tokens: item_tokens.into() };
    let expanded = quote! {
            #[repr(C)]
            #input
        };
    Ok( expanded.into() )
}
