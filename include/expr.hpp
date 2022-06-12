#include <llvm/IR/Value.h>

namespace creol {
    class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen(llvm::LLVMContext& TheContext) = 0;
    };
};