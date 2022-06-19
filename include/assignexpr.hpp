#include <llvm/IR/Value.h>
#include <expr.hpp>
#include <base.hpp>
#include <vars.hpp>

namespace creol {
    class VarAssignmetExprAST : public ExprAST {
        std::unique_ptr<VariableExprAST> lhs;
        std::unique_ptr<ExprAST> rhs;

    public:
        VarAssignmetExprAST(
            std::unique_ptr<VariableExprAST> lhs,
            std::unique_ptr<ExprAST> rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {  }

        virtual llvm::Value* codegen() override;
    };
};