#include "include/creol.hh"
#include "parser.hh"

#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <cstdio>

#include "include/external/argparse.hpp"

extern FILE* yyin;
extern int yyparse(void);
extern creol::BlockSttmt* Program;

namespace fs = std::filesystem;

namespace ap = argparse;

#define COMPILER_NAME "creol"
#define VERSION_OF_THE_COMPILER "Creol Programming Language V1.1.5"
#define TYPE_OF_THE_COMPILER "traspiler"
#define TARGET_LANGUAGE "c"

/// Parses the arguments from the command line and then returns the parser object.
std::unique_ptr<ap::ArgumentParser> parseArguments(const int, const char* const*);

/// Self-explanatory
void printErrorMessage(const char*);

int main(int argc, const char* const* argv) {
    std::unique_ptr<ap::ArgumentParser> commandParser;

    try {
        commandParser = parseArguments(argc, argv);
    } catch(const std::exception& e) {
        printErrorMessage(e.what());
    }

    auto filename = commandParser->get<std::string>("file");

    if (!fs::exists(filename)) {
        printErrorMessage(("File '" + filename + "' does not exits!").c_str());
    }

    FILE* file = fopen(filename.c_str(), "r");

    if (file == NULL) {
        printErrorMessage(("Could not open '" + filename + "'!").c_str());
    }

    yyin = file; yyparse();

    std::cout << "Generated Code:\n" << std::endl;
    std::cout << Program->CodeGen() << std::endl;
}

std::unique_ptr<ap::ArgumentParser> parseArguments(const int argc, const char* const* argv) {
    auto CArgs = std::make_unique<ap::ArgumentParser>(COMPILER_NAME, VERSION_OF_THE_COMPILER);

    CArgs->add_argument("file")
          .help("Name of the target compilation file.")
          .required()
          .nargs(1);

    CArgs->add_argument("-o", "--output")
         .help("Option used to specify the name of the output file.")
         .nargs(1);

    CArgs->add_argument("-f", "--format")
         .help("With this option the code gets formatted before being returned or saved.")
         .default_value(false)
         .implicit_value(true);

    try {
        CArgs->parse_args(argc, argv);
    } catch (const std::exception& e) {
        printErrorMessage(e.what());
    }

    return std::move(CArgs);
}

void printErrorMessage(const char* message) {
    fprintf(stderr, "Creol: Error: %s\n", message);
    std::exit(1);
}