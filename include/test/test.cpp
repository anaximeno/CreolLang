#include "../creol.hpp"
#include "../base.hpp"
#include <llvm/IR/BasicBlock.h>
#include <iostream>
#include <memory>
#include <string>

// Compile using:
// $ clang++ `llvm-config --libs core --ldflags --cppflags --system-libs ` -std=c++17 -g test.cpp -o test
//
// !NOTE: llvm, clang and its basics modules must be installed first!

int main(int argc, char* argv[]) {
    creol::InitializeModule("Testing Module");
    
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

    llvm::BasicBlock* Block =llvm::BasicBlock::Create(
        *creol::Context, "test", testFun->codegen()
    );

    creol::Builder->SetInsertPoint(Block);

    creol::Module->print(llvm::dbgs(), nullptr);
}
