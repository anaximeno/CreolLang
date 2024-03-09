#ifndef _CREOL_KL_HEADER
#define _CREOL_KL_HEADER

#include <memory>
#include <algorithm>

#include "ast.hh"

namespace creol {
    std::unique_ptr<creol::BlockSttmt> ParseFile(std::string filename);
}

/** Parse a .kl file with creol lang code. */

#endif // _CREOL_KL_HEADER
