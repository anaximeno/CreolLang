fn main() {
    cxx_build::bridge("src/main.rs")
        .file("src/creol/interop.cc")
        .compile("creol");

    print!("cargo:rerun-if-changed=src/main.rs");
    print!("cargo:rerun-if-changed=src/creol/rs-interop.cc");
    print!("cargo:rerun-if-changed=include/creol/rs-interop.cc");
}