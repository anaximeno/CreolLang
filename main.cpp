#include "include/creol/cli.hh"

int main(int argc, const char* const* argv) {
    creol::cli::Compiler Comp("Creol", "Creol v1.2.1");

    Comp.Run(argc, argv);

    return 0;
}