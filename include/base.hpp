#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>

namespace creol {
    static llvm::LLVMContext TheContext;
    static std::unique_ptr<llvm::Module> TheModule;
    static std::map<std::string, llvm::Value*> NamedValues;
    static llvm::IRBuilder<> TheBuilder(TheContext);
};