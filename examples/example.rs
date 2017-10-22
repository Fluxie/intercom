#![feature( plugin, custom_attribute )]
#![plugin( issue )]

#![decorator]  // Removing the '!' prevents the error.

fn main()
{
    method();  // Commenting out this line prevents the error.
}
