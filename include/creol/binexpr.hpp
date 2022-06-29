#ifndef _CREOL_BINEXPR
#define _CREOL_BINEXPR

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include "expr.hpp"
#include "base.hpp"
#include "misc.hpp"

namespace creol {
    /// Common binary operation's symbols
    enum OpSymbol {
        PLUS, MINUS, TIMES, DIV, LT,
        LE, GT, GE, NE, EQ, AND, OR
    };

    /// BinaryExprAST - Represents the binary operations and expressions
    /// for the creoline lang.
    class BinaryExprAST : public ExprAST {
        OpSymbol Op;
        std::unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(OpSymbol Op,
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

    if (!L || !R) { return nullptr; }

    switch (Op)
    {
    case PLUS:
        return creol::Builder->CreateAdd(L, R, "addtmp");
    case MINUS:
        return creol::Builder->CreateSub(L, R, "subtmp");
    case TIMES:
        return creol::Builder->CreateMul(L, R, "multmp");
    case DIV:
        return creol::Builder->CreateFDiv(L, R, "divtmp");
    case LT:
        return creol::Builder->CreateICmpULT(L, R, "lttmp");
    case LE:
        return creol::Builder->CreateICmpULE(L, R, "letmp");
    case GT:
        return creol::Builder->CreateICmpUGT(L, R, "gttmp");
    case GE:
        return creol::Builder->CreateICmpUGE(L, R, "getmp");
    case NE:
        return creol::Builder->CreateICmpNE(L, R, "netmp");
    case EQ:
        return creol::Builder->CreateICmpEQ(L, R, "eqtmp");
    case AND:
        return creol::Builder->CreateAnd(L, R, "andtmp");
    case OR:
        return creol::Builder->CreateOr(L, R, "ortmp");

    default:
        return creol::LogErrorV("invalid binary operator!");
    }
}

#endif
