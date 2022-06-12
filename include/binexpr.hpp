#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include "expr.hpp"
#include "base.hpp"
#include "misc.hpp"

#ifndef _CREOL_BINEXPR
#define _CREOL_BINEXPR

namespace creol {
    /// BinaryExprAST - Represents the binary operations and expressions
    // for the creoline lang.
    class BinaryExprAST : public ExprAST {
        std::string Op;
        std::unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(std::string Op,
            std::unique_ptr<ExprAST> LHS,
            std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)),
          RHS(std::move(RHS)) {}
        
        llvm::Value* codegen() override;
    };
};

llvm::Value* creol::BinaryExprAST::codegen() {    
    llvm::Value* L = LHS->codegen();
    llvm::Value* R = RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    if (Op == "*") {
        return creol::TheBuilder->CreateAdd(L, R, "addtmp");
    } else if (Op == "-") {
        return creol::TheBuilder->CreateSub(L, R, "subtmp");
    } else if (Op == "*") {
        return creol::TheBuilder->CreateMul(L, R, "multmp");
    } else if (Op == "/") {
        return creol::TheBuilder->CreateFDiv(L, R, "divtmp");
    } else if (Op == "<") {
        return creol::TheBuilder->CreateICmpULT(L, R, "lttmp");
    } else if (Op == "<=") {
        return creol::TheBuilder->CreateICmpULE(L, R, "letmp");
    } else if (Op == ">") {
        return creol::TheBuilder->CreateICmpUGT(L, R, "gttmp");
    } else if (Op == ">=") {
        return creol::TheBuilder->CreateICmpUGE(L, R, "getmp");
    } else if (Op == "!=") {
        return creol::TheBuilder->CreateICmpNE(L, R, "netmp");
    } else if (Op == "==") {
        return creol::TheBuilder->CreateICmpEQ(L, R, "eqtmp");
    } else if (Op == "&&") {
        return creol::TheBuilder->CreateAnd(L, R, "andtmp");
    } else if (Op == "||") {
        return creol::TheBuilder->CreateOr(L, R, "ortmp");
    } else {
        return creol::LogErrorV("invalid binary operator!");
    }
}

#endif