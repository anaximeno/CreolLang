#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include "expr.hpp"

#ifndef _CREOL_VARS
#define _CREOL_VARS

namespace creol {
    class VariableExprAST : public ExprAST {
        std::string TypeName;
        std::string Name;

    public:
        VariableExprAST(const std::string& TypeName, const std::string& Name)
        : TypeName(TypeName), Name(Name) {}

        llvm::Value* codegen() override;

        const std::string& getName() const;

        const std::string& getTypeName() const;
    };
};

const std::string& creol::VariableExprAST::getName() const {
    return Name;
}

const std::string& creol::VariableExprAST::getTypeName() const {
    return TypeName;
}

llvm::Value* creol::VariableExprAST::codegen() {
    llvm::Value* Value = NamedValues[Name];
    if (!Value)
        return creol::LogErrorV("Unknown variable name '" + Name + "'");
    return Value;
}

#endif
