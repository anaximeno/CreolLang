#ifndef _CREOL_BLOCK
#define _CREOL_BLOCK

#include <llvm/IR/Value.h>
#include <vector>
#include "base.hpp"
#include "expr.hpp"
#include "stmts.hpp"

namespace creol {
    class BlockAST : public ExprAST {
        std::vector<std::unique_ptr<StmtAST>> StatementList;
    public:
        void AddStatement(StmtAST* stmt);
        llvm::Value* codegen() override;
    };
};

llvm::Value* creol::BlockAST::codegen() {
    llvm::Value* last = nullptr;
    for (auto& S : StatementList) {
        last = S->codegen();
    }
    return last;
}

void creol::BlockAST::AddStatement(StmtAST* stmt) {
    StatementList.push_back(std::unique_ptr<StmtAST>(stmt));
}

#endif