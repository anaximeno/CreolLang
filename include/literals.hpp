#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>
#include "expr.hpp"

namespace creol {
    /// IntLiteralExprAST - represents an integer literal value
    class IntLiteralExprAST : public ExprAST {
        int Val;

    public:
        IntLiteralExprAST(int Val)
        : Val(Val) {}
        llvm::Value* codegen(llvm::LLVMContext& TheContext) override;
    };

    /// FloatLiteralExprAST - represents a floting point literal value
    class FloatLiteralExprAST : public ExprAST {
        double Val;

    public:
        FloatLiteralExprAST(double Val)
        : Val(Val) {}
        llvm::Value* codegen(llvm::LLVMContext& TheContext) override;
    };

    /// BoolLiteralExprAST - represents a boolean literal value
    class BoolLiteralExprAST : public ExprAST {
        unsigned short Val;
    
    public:
        BoolLiteralExprAST(unsigned short Val)
        : Val(Val) {}
        llvm::Value* codegen(llvm::LLVMContext& TheContext) override;
    };
};

llvm::Value* creol::IntLiteralExprAST::codegen(llvm::LLVMContext& TheContext) {
    return llvm::ConstantInt::get(TheContext, llvm::APSInt(Val, false));
}

llvm::Value* creol::FloatLiteralExprAST::codegen(llvm::LLVMContext& TheContext) {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}

llvm::Value* creol::BoolLiteralExprAST::codegen(llvm::LLVMContext& TheContext) {
    return llvm::ConstantInt::get(TheContext, llvm::APSInt(Val));
}