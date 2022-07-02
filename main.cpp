#include "include/creol/cli.hh"

int main(int argc, const char* const* argv) {
    creol::cli::Compiler Comp("creol", "Creol v1.2.2");

    Comp.Run(argc, argv);

    return 0;
}