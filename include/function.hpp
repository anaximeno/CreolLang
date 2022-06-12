#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include "expr.hpp"
#include "misc.hpp"
#include "base.hpp"

namespace creol {
    /// CallExprAST - represents the function call
    class CallExprAST : public ExprAST {
        std::vector<std::unique_ptr<ExprAST>> Args;
        std::string Callee;
    
    public:
        CallExprAST(const std::string& Callee, std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}

        llvm::Value* codegen(llvm::LLVMContext& TheContext) override;
    };
    
    /// PrototypeAST - This class represents the "prototype" for a function,
    /// which captures its name, and its arguments names.
    class PrototypeAST : public ExprAST {
        std::string Name;
        std::string TypeName;
        std::vector<std::string> Args;
    
    public:
        PrototypeAST(const std::string& TypeName, const std::string& Name, std::vector<std::string> Args)
        : TypeName(TypeName), Name(Name), Args(std::move(Args)) {}

        llvm::Function* codegen(llvm::LLVMContext& TheContext) override;

        const std::string& getName() const;
    };
};

llvm::Value* creol::CallExprAST::codegen(llvm::LLVMContext& TheContext) {
    llvm::Function* CalleeFun = creol::TheModule->getFunction(Callee);

    if (!CalleeFun) {
        return creol::LogErrorV("Unknown function referenced!");
    } else if (CalleeFun->arg_size() != Args.size()) {
        return creol::LogErrorV("Incorrent number of arguments passed!");
    } else {
        std::vector<llvm::Value*> ArgsValues;

        for (unsigned i = 0 ; i < Args.size() ; ++i) {
            ArgsValues.push_back(Args[i]->codegen(TheContext));

            if (!ArgsValues.back()) {
                return nullptr;
            }
        }

        return creol::TheBuilder.CreateCall(CalleeFun, ArgsValues, "calltmp");
    }
}

llvm::Function* creol::PrototypeAST::codegen(llvm::LLVMContext& TheContext) {
    // info: Currently only integer types arguments are received by the funtions
    // TODO: divesify arguments
    std::vector<llvm::Type*> Arguments(Args.size(), llvm::Type::getInt32Ty(TheContext));

    llvm::FunctionType* FunType = nullptr;

    if (TypeName == "int") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(TheContext), Arguments, false
        );
    } else if (TypeName == "float") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getFloatTy(TheContext), Arguments, false
        );
    } else if (TypeName == "bool") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getInt1Ty(TheContext), Arguments, false
        );
    } else if (TypeName == "void") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(TheContext), Arguments, false
        );
    } else {
        LogErrorV("Unknown function type!");
        return nullptr;
    }

    llvm::Function* Fun = llvm::Function::Create(
        FunType, llvm::Function::ExternalLinkage, Name, creol::TheModule.get()
    );

    unsigned idx = 0;

    for (auto& arg : Fun->args()) {
        arg.setName(Args[idx++]);
    }

    return Fun;
}

const std::string& creol::PrototypeAST::getName() const {
    return Name;
}