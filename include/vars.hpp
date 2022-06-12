#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include "expr.hpp"

namespace creol {
    class VariableExprAST : public ExprAST {
        std::string Name;

    public:
        VariableExprAST(const std::string& Name)
        : Name(Name) {}
        llvm::Value* codegen(llvm::LLVMContext& TheContext) override;
    };
};