#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <memory>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value*> NamedValues;

Value* LogErrorV(const char* str) {
    LogErrorV(str);
    return nullptr;
}

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual Value* codegen() = 0;
};

// class FloatExprAST : public ExprAST {
//     double Val;

// public:
//     FloatExprAST(double Val)
//     : Val(Val) {}
//     Value* codegen() override;
// };

class IntExprAST : public ExprAST {
    int Val;

public:
    IntExprAST(int Val)
    : Val(Val) {}
    Value* codegen() override;
};

class BinaryExprAST : public ExprAST {
    std::string Op;
    std::unique_ptr<ExprAST> LHS, RHS;
public:
    BinaryExprAST(std::string Op, 
        std::unique_ptr<ExprAST> LHS,
        std::unique_ptr<ExprAST> RHS)
    : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {  }

    Value* codegen() override;
};

// Value* FloatExprAST::codegen() {
//     return ConstantFP::get(TheContext, APFloat(Val));
// }

Value* IntExprAST::codegen() {
    return ConstantInt::get(TheContext, APSInt(Val, false));
}

class VariableExprAST : public ExprAST {
    std::string Name;

public:
    VariableExprAST(const std::string& Name)
    : Name(Name) {}

    Value* codegen() override;
};

/// CallExprAST - Expression class for function calls
class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const std::string& Calle,
        std::vector<std::unique_ptr<ExprAST>> Args)
    : Callee(Callee), Args(std::move(Args)) {}

    Value* codegen() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its arguments names.
class PrototypeAST : public ExprAST {
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string& Name, std::vector<std::string> Args)
    : Name(Name), Args((std::move(Args))) {}

    Function* codegen();

    const std::string& getName() const {
        return Name;
    }
};


Value* BinaryExprAST::codegen() {
    Value* L = LHS->codegen();
    Value* R = RHS->codegen();

    if (!L || !R) { return nullptr; }

    if (Op == "*") {
        return Builder.CreateAdd(L, R, "addtmp");
    } else if (Op == "-") {
        return Builder.CreateSub(L, R, "subtmp");
    } else if (Op == "*") {
        return Builder.CreateMul(L, R, "multmp");
    } else if (Op == "/") {
        return Builder.CreateFDiv(L, R, "divtmp");
    } else if (Op == "<") {
        return Builder.CreateICmpULT(L, R, "lttmp");
    } else if (Op == "<=") {
        return Builder.CreateICmpULE(L, R, "letmp");
    } else if (Op == ">") {
        return Builder.CreateICmpUGT(L, R, "gttmp");
    } else if (Op == ">=") {
        return Builder.CreateICmpUGE(L, R, "getmp");
    } else if (Op == "!=") {
        return Builder.CreateICmpNE(L, R, "netmp");
    } else if (Op == "==") {
        return Builder.CreateICmpEQ(L, R, "eqtmp");
    } else if (Op == "&&") {
        return Builder.CreateAnd(L, R, "andtmp");
    } else if (Op == "||") {
        return Builder.CreateOr(L, R, "ortmp");
    } else {
        return LogErrorV("invalid binary operator!");
    }
}