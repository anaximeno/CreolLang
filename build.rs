fn main() {
    cxx_build::bridge("src/main.rs")
        // .file("src/cc/kl.cc")
        .file("parser.cc")
        .file("scanner.cc")
        .file("src/cc/ast.cc")
        .compile("creol");

    print!("cargo:rerun-if-changed=src/main.rs");
    // print!("cargo:rerun-if-changed=src/cc/kl.cc");
    // print!("cargo:rerun-if-changed=include/kl.hh");
}