#[cxx::bridge(namespace = "creol")]
pub mod ffi {
    unsafe extern "C++" {
        include!("creol/include/ast.hh");

        type BlockSttmt;

        fn ParseFile(filename: UniquePtr<CxxString>) -> &BlockSttmt;
    }
}

fn main() {
    let _program = kl::ffi::ParseFile("examples/example01.kl");
}
