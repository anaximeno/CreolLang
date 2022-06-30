#include "include/creol.hh"
#include "parser.hh"

#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>

extern FILE* yyin;
extern int yyparse(void);
extern creol::BlockSttmt* Program;

namespace fs = std::filesystem;

int main(int argc, const char* const* argv) {
    if (argc != 2) {
        std::cout << "Help Section: Execute using:" << std::endl;
        std::cout << "$ creol <filename.crl>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    if (!fs::exists(filename)) {
        std::cout << "File '" << filename
                  << "' was not found in the current dir!"
                  << std::endl;
        return 1;
    }

    FILE* file = fopen(filename, "r");

    if (!file) {
        std::cout << "Error opening the file '"
                  << filename << "'!" << std::endl;
        return 1;
    }

    yyin = file; yyparse();

    std::cout << Program->CodeGen() << std::endl;
}