#ifndef _CREOL_IF_AST
#define _CREOL_IF_AST

#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <memory>
#include <algorithm>
#include "expr.hpp"
#include "base.hpp"

namespace creol {
    class IfExprAST : public ExprAST {
        std::unique_ptr<ExprAST> Cond, Then, Else;

    public:
        IfExprAST(std::unique_ptr<ExprAST> Cond, std::unique_ptr<ExprAST> Then,
            std::unique_ptr<ExprAST> Else)
        : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}
        llvm::Value* codegen() override;
    };
};

llvm::Value* creol::IfExprAST::codegen() {
    llvm::Value* CondV = Cond->codegen();

    if (!CondV) {
        return nullptr;
    }

    CondV = creol::Builder->CreateFCmpONE(
        CondV, llvm::ConstantFP::get(*creol::Context, llvm::APFloat(0.0)), "ifcond"
    );

    llvm::Function* TheFunction = creol::Builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* ThenBB = llvm::BasicBlock::Create(*creol::Context, "then", TheFunction);
    llvm::BasicBlock* ElseBB = llvm::BasicBlock::Create(*creol::Context, "else");
    llvm::BasicBlock* MergeBB = llvm::BasicBlock::Create(*creol::Context, "ifcont");

    creol::Builder->CreateCondBr(CondV, ThenBB, ElseBB);

    creol::Builder->SetInsertPoint(ThenBB);

    llvm::Value* ThenV = Then->codegen();

    if (!ThenV)
        return nullptr;

    creol::Builder->CreateBr(MergeBB);

    ThenBB = creol::Builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(ElseBB);
    creol::Builder->SetInsertPoint(ElseBB);

    llvm::Value* ElseV = Else->codegen();

    if (!ElseV)
        return nullptr;

    creol::Builder->CreateBr(MergeBB);

    ElseBB = creol::Builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(MergeBB);
    creol::Builder->SetInsertPoint(MergeBB);
    llvm::PHINode* PN = creol::Builder->CreatePHI(llvm::Type::getDoubleTy(*creol::Context), 2, "iftmp");

    PN ->addIncoming(ThenV, ThenBB);
    PN ->addIncoming(ElseV, ElseBB);

    return PN;
}

#endif // _CREOL_IF_AST