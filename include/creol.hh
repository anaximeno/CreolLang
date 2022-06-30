#ifndef _CREOL_INTERMEDIATE_AST_REPR
#define _CREOL_INTERMEDIATE_AST_REPR

#include <llvm/IR/Value.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/APSInt.h>
#include <llvm/IR/Constants.h>

#include <memory>
#include <vector>
#include <algorithm>

namespace creol {
    enum NodeType {
        // TODO
    };

    class NodeAST {
        public:
            virtual ~NodeAST() = default;
            virtual llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) = 0;
    };

    /** Represents a statement. */
    class StmtAST : public NodeAST {
        public:
            virtual ~StmtAST() = default;
            virtual llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
                std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
                std::unique_ptr<llvm::IRBuilder<>>& Builder
            ) = 0;
    };

    class ExprAST : public StmtAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) = 0;
    };

    class VariableExprAST : public ExprAST {
        std::string TypeName;
        std::string Name;

    public:
        VariableExprAST(const std::string& TypeName, const std::string& Name)
        : TypeName(TypeName), Name(Name) {}

        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;

        const std::string& getName() const;

        const std::string& getTypeName() const;
    };

    std::unique_ptr<ExprAST> LogError(const std::string& Str);

    llvm::Value* LogErrorV(const std::string& Str);

    class BlockAST : public ExprAST {
        std::vector<std::unique_ptr<StmtAST>> StatementList;
    public:
        void AddStatement(StmtAST* stmt);
        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    class VarAssignmetExprAST : public ExprAST {
        std::unique_ptr<VariableExprAST> lhs;
        std::unique_ptr<ExprAST> rhs;

    public:
        VarAssignmetExprAST(
            std::unique_ptr<VariableExprAST> lhs,
            std::unique_ptr<ExprAST> rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {  }

        virtual llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// Common binary operation's symbols
    enum OpSymbol {
        PLUS, MINUS, TIMES, DIV, LT,
        LE, GT, GE, NE, EQ, AND, OR
    };

    /// BinaryExprAST - Represents the binary operations and expressions
    /// for the creoline lang.
    class BinaryExprAST : public ExprAST {
        OpSymbol Op;
        std::unique_ptr<ExprAST> LHS, RHS;

    public:
        BinaryExprAST(OpSymbol Op,
            std::unique_ptr<ExprAST> LHS,
            std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)),
          RHS(std::move(RHS)) {}

        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// CallExprAST - represents the function call
    class CallExprAST : public ExprAST {
        std::string Callee;
        std::vector<std::unique_ptr<ExprAST>> Args;

    public:
        CallExprAST(const std::string& Callee, std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}

        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// PrototypeAST - This class represents the "prototype" for a function,
    /// which captures its name, and its arguments names.
    class PrototypeAST : public ExprAST {
        std::string TypeName;
        std::string Name;
        std::vector<std::string> Args;

    public:
        PrototypeAST(const std::string& TypeName, const std::string& Name, std::vector<std::string> Args)
        : TypeName(TypeName), Name(Name), Args(std::move(Args)) {}

        llvm::Function* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;

        const std::string& getName() const;
    };

    /// FunctionAST - This class represents a function definition itself.
    class FunctionAST : public ExprAST {
        std::unique_ptr<PrototypeAST> Proto;
        std::unique_ptr<ExprAST> Body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}

        llvm::Function* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder);
    };

     class IfExprAST : public ExprAST {
        std::unique_ptr<ExprAST> Cond, Then, Else;

    public:
        IfExprAST(std::unique_ptr<ExprAST> Cond, std::unique_ptr<ExprAST> Then,
            std::unique_ptr<ExprAST> Else)
        : Cond(std::move(Cond)), Then(std::move(Then)), Else(std::move(Else)) {}
        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// IntLiteralExprAST - represents an integer literal value
    class IntLiteralExprAST : public ExprAST {
        int Val;

    public:
        IntLiteralExprAST(int Val)
        : Val(Val) {}
        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// FloatLiteralExprAST - represents a floting point literal value
    class FloatLiteralExprAST : public ExprAST {
        double Val;

    public:
        FloatLiteralExprAST(double Val)
        : Val(Val) {}
        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };

    /// BoolLiteralExprAST - represents a boolean literal value
    class BoolLiteralExprAST : public ExprAST {
        unsigned short Val;

    public:
        BoolLiteralExprAST(unsigned short Val)
        : Val(Val) {}
        llvm::Value* codegen(std::unique_ptr<llvm::LLVMContext>& Context,
            std::unique_ptr<llvm::Module>& Module, std::map<std::string, llvm::Value*>& NamedValues,
            std::unique_ptr<llvm::IRBuilder<>>& Builder) override;
    };
};

#endif //_CREOL_INTERMEDIATE_AST_REPR
