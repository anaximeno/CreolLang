#include <memory>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::Value*> NamedValues;

class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen() = 0;
};

llvm::Value* LogErrorV(const char* str) {
    LogErrorV(str);
    return nullptr;
}

class FloatExprAST : public ExprAST {
    double Val;

    public:
        FloatExprAST(double Val)
        : Val(Val) {}
        llvm::Value* codegen() override;
};

class IntExprAST : public ExprAST {
    int Val;

    public:
        IntExprAST(int Val)
        : Val(Val) {}
        llvm::Value* codegen() override;
};

llvm::Value* FloatExprAST::codegen() {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(Val));
}

llvm::Value* IntExprAST::codegen() {
    return llvm::ConstantInt::get(TheContext, llvm::APSInt(Val, false));
}
