#ifndef _CREOL_EXPR
#define _CREOL_EXPR

#include <llvm/IR/Value.h>

namespace creol {
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen() = 0;
    };
};

#endif