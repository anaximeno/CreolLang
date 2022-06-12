#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
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
        std::vector<std::string> Args;
    
    public:
        PrototypeAST(const std::string& Name, std::vector<std::string> Args)
        : Name(Name), Args(std::move(Args)) {}

        llvm::Function* codegen();

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