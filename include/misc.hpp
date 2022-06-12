#include <llvm/IR/Value.h>
#include <cstdio>
#include <memory>
#include "expr.hpp"

namespace creol {
    std::unique_ptr<ExprAST> LogError(const char *Str) {
        fprintf(stderr, "Error: %s", Str);
        return nullptr;
    }
    
    llvm::Value* LogErrorV(const char* Str) {
        LogError(Str);
        return nullptr;
    }
};