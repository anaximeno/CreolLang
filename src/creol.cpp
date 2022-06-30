#include "../include/creol.hh"

#include <llvm/IR/Value.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>

#include <algorithm>
#include <string>
#include <vector>

std::unique_ptr<creol::ExprAST> creol::LogError(const std::string& Str) {
    fprintf(stderr, "Error: %s\n", Str.c_str());
    return nullptr;
}

llvm::Value* creol::LogErrorV(const std::string& Str) {
    LogError(Str);
    return nullptr;
}

llvm::Value* creol::BinaryExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
    std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
    std::unique_ptr<llvm::IRBuilder<>>& Builder
) {
    llvm::Value* L = LHS->codegen(Context, Module, NamedValues, Builder);
    llvm::Value* R = RHS->codegen(Context, Module, NamedValues, Builder);

    if (!L || !R) { return nullptr; }

    switch (Op)
    {
    case PLUS:
        return Builder->CreateAdd(L, R, "addtmp");
    case MINUS:
        return Builder->CreateSub(L, R, "subtmp");
    case TIMES:
        return Builder->CreateMul(L, R, "multmp");
    case DIV:
        return Builder->CreateFDiv(L, R, "divtmp");
    case LT:
        return Builder->CreateICmpULT(L, R, "lttmp");
    case LE:
        return Builder->CreateICmpULE(L, R, "letmp");
    case GT:
        return Builder->CreateICmpUGT(L, R, "gttmp");
    case GE:
        return Builder->CreateICmpUGE(L, R, "getmp");
    case NE:
        return Builder->CreateICmpNE(L, R, "netmp");
    case EQ:
        return Builder->CreateICmpEQ(L, R, "eqtmp");
    case AND:
        return Builder->CreateAnd(L, R, "andtmp");
    case OR:
        return Builder->CreateOr(L, R, "ortmp");

    default:
        return creol::LogErrorV("invalid binary operator!");
    }
}

llvm::Value* creol::BlockAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    llvm::Value* last = nullptr;
    for (auto& S : StatementList) {
        last = S->codegen(Context, Module, NamedValues, Builder);
    }
    return last;
}

void creol::BlockAST::AddStatement(StmtAST* stmt) {
    StatementList.push_back(std::unique_ptr<StmtAST>(stmt));
}

llvm::Value* creol::CallExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    llvm::Function* CalleeFun = Module->getFunction(Callee);

    if (!CalleeFun) {
        return creol::LogErrorV("Unknown function referenced!");
    } else if (CalleeFun->arg_size() != Args.size()) {
        return creol::LogErrorV("Incorrent number of arguments passed!");
    } else {
        std::vector<llvm::Value*> ArgsValues;

        for (unsigned i = 0 ; i < Args.size() ; ++i) {
            ArgsValues.push_back(Args[i]->codegen(Context, Module, NamedValues, Builder));

            if (!ArgsValues.back()) {
                return nullptr;
            }
        }

        return Builder->CreateCall(CalleeFun, ArgsValues, "calltmp");
    }
}

llvm::Function* creol::PrototypeAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    // info: Currently only integer types arguments are received by the funtions
    // TODO: divesify arguments
    std::vector<llvm::Type*> Arguments(
        Args.size(), llvm::Type::getInt32Ty(*Context)
    );

    llvm::FunctionType* FunType = nullptr;

    if (TypeName == "int") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(*Context), Arguments, false
        );
    } else if (TypeName == "float") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getFloatTy(*Context), Arguments, false
        );
    } else if (TypeName == "bool") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getInt1Ty(*Context), Arguments, false
        );
    } else if (TypeName == "void") {
        FunType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*Context), Arguments, false
        );
    } else {
        LogErrorV("Unknown function type!");
        return nullptr;
    }

    llvm::Function* Fun = llvm::Function::Create(
        FunType, llvm::Function::ExternalLinkage, Name, Module.get()
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

llvm::Function* creol::FunctionAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    llvm::Function* TheFunction = Module->getFunction(Proto->getName());

    TheFunction = TheFunction ? TheFunction : Proto->codegen(Context, Module, NamedValues, Builder);

    if (!TheFunction) {
        creol::LogErrorV("Function could not be defined");
        return nullptr;
    } else if (!TheFunction->empty()) {
        creol::LogErrorV("Function can not be redefined");
        return nullptr;
    }

    llvm::BasicBlock* BasicBlock = llvm::BasicBlock::Create(
        *Context, "entry", TheFunction
    );

    Builder->SetInsertPoint(BasicBlock);

    NamedValues.clear();

    for (auto& arg : TheFunction->args()) {
        NamedValues[arg.getName()] = &arg;
    }

    if (llvm::Value* RetVal = Body->codegen(Context, Module, NamedValues, Builder)) {
        // Add a return value to the function
        Builder->CreateRet(RetVal);
        llvm::verifyFunction(*TheFunction);
        return TheFunction;
    } else {
        TheFunction->eraseFromParent();
        creol::LogErrorV("Error reading the body of the funtion!");
        return nullptr;
    }
}

llvm::Value* creol::IfExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    llvm::Value* CondV = Cond->codegen(Context, Module, NamedValues, Builder);

    if (!CondV) {
        return nullptr;
    }

    CondV = Builder->CreateFCmpONE(
        CondV, llvm::ConstantFP::get(*Context, llvm::APFloat(0.0)), "ifcond"
    );

    llvm::Function* TheFunction = Builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* ThenBB = llvm::BasicBlock::Create(*Context, "then", TheFunction);
    llvm::BasicBlock* ElseBB = llvm::BasicBlock::Create(*Context, "else");
    llvm::BasicBlock* MergeBB = llvm::BasicBlock::Create(*Context, "ifcont");

    Builder->CreateCondBr(CondV, ThenBB, ElseBB);

    Builder->SetInsertPoint(ThenBB);

    llvm::Value* ThenV = Then->codegen(Context, Module, NamedValues, Builder);

    if (!ThenV)
        return nullptr;

    Builder->CreateBr(MergeBB);

    ThenBB = Builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(ElseBB);
    Builder->SetInsertPoint(ElseBB);

    llvm::Value* ElseV = Else->codegen(Context, Module, NamedValues, Builder);

    if (!ElseV)
        return nullptr;

    Builder->CreateBr(MergeBB);

    ElseBB = Builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);
    llvm::PHINode* PN = Builder->CreatePHI(llvm::Type::getDoubleTy(*Context), 2, "iftmp");

    PN ->addIncoming(ThenV, ThenBB);
    PN ->addIncoming(ElseV, ElseBB);

    return PN;
}

llvm::Value* creol::IntLiteralExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    return llvm::ConstantInt::get(*Context, llvm::APSInt(Val, false));
}

llvm::Value* creol::FloatLiteralExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    return llvm::ConstantFP::get(*Context, llvm::APFloat(Val));
}

llvm::Value* creol::BoolLiteralExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    return llvm::ConstantInt::get(*Context, llvm::APSInt(Val));
}

const std::string& creol::VariableExprAST::getName() const {
    return Name;
}

const std::string& creol::VariableExprAST::getTypeName() const {
    return TypeName;
}

llvm::Value* creol::VariableExprAST::codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) {
    llvm::Value* Value = NamedValues[Name];
    if (!Value)
        return creol::LogErrorV("Unknown variable name '" + Name + "'");
    return Value;
}
