#include <iostream>
#include "ast.h"

using namespace creol;

const NodeType& NodeAST::GetType() const {
    return Type;
}