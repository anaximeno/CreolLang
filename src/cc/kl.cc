#include <cstdlib>
#include <cstdio>
#include <string>
#include <memory>
#include <algorithm>

#include "creol/include/ast.hh"

using namespace creol;

extern FILE* yyin;

extern int yyparse(void);

extern ast::BlockSttmt* __KL_Program__BLOCK;


std::unique_ptr<ast::BlockSttmt> ParseFile(std::string filename) {
    FILE* file = fopen(filename.c_str(), "rt");

    // TODO: handle NULL pointer case maybe with better
    //       error reporting.

    // define the input file
    yyin = file;

    // parse the file
    yyparse();

    // close the file after the parsing
    fclose(file);

    // return the parsed program block
    return std::unique_ptr(__KL_Program__BLOCK);
}
