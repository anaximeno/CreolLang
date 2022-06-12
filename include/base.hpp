#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include <string>

#ifndef _CREOL_BASE
#define _CREOL_BASE

namespace creol {
    static std::unique_ptr<llvm::LLVMContext> TheContext;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::map<std::string, llvm::Value*> NamedValues;
    static std::unique_ptr<llvm::IRBuilder<>> TheBuilder;

    static void InitializeModule(const std::string& Name) {
        TheContext = std::make_unique<llvm::LLVMContext>();
        TheModule = std::make_unique<llvm::Module>(Name, *TheContext);
        TheBuilder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
    }
};

#endif