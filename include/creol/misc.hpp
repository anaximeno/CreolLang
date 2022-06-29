#include <llvm/IR/Value.h>
#include <cstdio>
#include <memory>
#include "expr.hpp"

#ifndef _CREOL_MISC
#define _CREOL_MISC

namespace creol {
    std::unique_ptr<ExprAST> LogError(const std::string& Str) {
        fprintf(stderr, "Error: %s\n", Str.c_str());
        return nullptr;
    }

    llvm::Value* LogErrorV(const std::string& Str) {
        LogError(Str);
        return nullptr;
    }
};

#endif
