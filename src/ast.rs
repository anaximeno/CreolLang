#[cxx::bridge(namespace = "creol::ast")]
pub mod ffi {
    unsafe extern "C++" {
        include!("creol/include/ast.hh");

        type BlockSttmt;
    }
}