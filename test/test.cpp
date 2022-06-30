#include "../include/creol.hh"

#include <llvm/IR/BasicBlock.h>

#include <iostream>
#include <memory>
#include <string>

// Compile using:
// $ clang++ `llvm-config --libs core --ldflags --cppflags --system-libs ` -std=c++17 -g test.cpp -o test
//
// !NOTE: llvm, clang and its basics modules must be installed first!

int main(int argc, char* argv[]) {
    static std::unique_ptr<llvm::LLVMContext> Context;
    static std::unique_ptr<llvm::Module> Module;
    static std::map<std::string, llvm::Value*> NamedValues;
    static std::unique_ptr<llvm::IRBuilder<>> Builder;
    Context = std::unique_ptr<llvm::LLVMContext>(new llvm::LLVMContext());
    Module = std::make_unique<llvm::Module>("Test", *Context);
    Builder = std::make_unique<llvm::IRBuilder<>>(*Context);

    std::unique_ptr<creol::PrototypeAST> Proto;
    std::unique_ptr<creol::ExprAST> Body;
    std::vector<std::string> Args;

    Args.push_back("a");
    Args.push_back("b");

    Proto = std::make_unique<creol::PrototypeAST>("int", "testFunc", Args);

    Body = std::unique_ptr<creol::ExprAST>(
        (creol::ExprAST*) new creol::IntLiteralExprAST(9)
    );

    std::unique_ptr<creol::FunctionAST> testFun = std::make_unique<creol::FunctionAST>(
        std::move(Proto), std::move(Body)
    );

    auto out = testFun->codegen(Context, Module, NamedValues, Builder);

    llvm::BasicBlock* Block = llvm::BasicBlock::Create(*Context, "test", out);

    Builder->SetInsertPoint(Block);

    Module->print(llvm::dbgs(), nullptr);
}
