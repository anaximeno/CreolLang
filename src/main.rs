#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("creol/include/interop.hh");

        fn hello_world() -> ();
    }
}

fn main() {
    ffi::hello_world();
}
