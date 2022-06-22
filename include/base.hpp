#ifndef _CREOL_BASE
#define _CREOL_BASE

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include <string>

namespace creol {
    static std::unique_ptr<llvm::LLVMContext> Context;
    static std::unique_ptr<llvm::Module> Module;
    static std::map<std::string, llvm::Value*> NamedValues;
    static std::unique_ptr<llvm::IRBuilder<>> Builder;

    /// Creates the context, module and builder references
    void InitializeModule(const std::string& ModuleName) {
        Context = std::unique_ptr<llvm::LLVMContext>(new llvm::LLVMContext());
        Module = std::make_unique<llvm::Module>(ModuleName, *Context);
        Builder = std::make_unique<llvm::IRBuilder<>>(*Context);
    }
};


#endif