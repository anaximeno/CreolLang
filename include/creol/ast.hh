#ifndef _CREOL_AST_TRANSPILER_HEADER
#define _CREOL_AST_TRANSPILER_HEADER

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "./cbinds.hh"

namespace creol
{
    namespace ast
    {
        /// Represents a statement
        class Sttmt
        {
        public:
            virtual std::string CodeGen() = 0;
        };

        /// Represents an expression
        class Expr : public Sttmt
        {
        public:
            virtual std::string CodeGen() override;
        };

        /// Represents the declaration of a variable
        class VarDeclSttmt : public Sttmt
        {
        protected:
            std::string Type;
            std::string Name;
            Expr *Value;

        public:
            VarDeclSttmt(std::string Type, std::string Name, Expr *Value)
                : Type(Type), Name(Name), Value(Value) {}
            virtual std::string CodeGen() override;
            void SetType(std::string Type);
        };

        /// Represents a blockSttmt of code
        class BlockSttmt : public Sttmt
        {
        protected:
            std::vector<Sttmt *> SttmtList;
            bool BracketsOn = false;

        public:
            void AddSttmt(Sttmt *sttmt);
            void UseBrackets();
            void DontUseBrackets();
            virtual std::string CodeGen() override;
        };

        class FuncArgs
        {
        protected:
            std::vector<VarDeclSttmt *> Args;

        public:
            void AddArg(VarDeclSttmt *Arg);
            virtual std::string CodeGen();
        };

        /// Represents the declaration of a function
        class FuncDeclSttmt : public Sttmt
        {
        protected:
            std::string Type;
            std::string Name;
            FuncArgs *Args;
            BlockSttmt *Body;

        public:
            FuncDeclSttmt(std::string Type, std::string Name,
                          FuncArgs *Args, BlockSttmt *Body)
                : Type(Type), Name(Name), Args(Args), Body(Body) {}
            virtual std::string CodeGen() override;
        };

        /// Represents an if statement
        class IfSttmt : public Sttmt
        {
        protected:
            Expr *Cond;
            BlockSttmt *Then;
            BlockSttmt *Else;

        public:
            IfSttmt(Expr *Cond, BlockSttmt *Then, BlockSttmt *Else)
                : Cond(Cond), Then(Then), Else(Else) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a while loop
        class WhileSttmt : public Sttmt
        {
        protected:
            Expr *Cond;
            BlockSttmt *Do;

        public:
            WhileSttmt(Expr *Cond, BlockSttmt *Do)
                : Cond(Cond), Do(Do) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a jump statement
        class JumpSttmt : public Sttmt
        {
        protected:
            std::string Name;

        public:
            JumpSttmt(std::string Name)
                : Name(Name) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a return statement
        class ReturnSttmt : public JumpSttmt
        {
        protected:
            Expr *ReturnValue;

        public:
            ReturnSttmt(Expr *ReturnValue)
                : JumpSttmt(C_RETURN), ReturnValue(ReturnValue) {}
            virtual std::string CodeGen() override;
        };

        class FuncCallArgs
        {
        protected:
            std::vector<Expr *> Args;

        public:
            void AddArg(Expr *Arg);
            virtual std::string CodeGen();
        };

        /// Represents the function call
        class FunCallExpr : public Expr
        {
        protected:
            std::string Name;
            FuncCallArgs *Args;

        public:
            FunCallExpr(std::string Name, FuncCallArgs *Args)
                : Name(Name), Args(Args) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a binary expression
        class BinExpr : public Expr
        {
        protected:
            std::string Op;
            Expr *LHS;
            Expr *RHS;

        public:
            BinExpr(std::string Op, Expr *LHS, Expr *RHS)
                : Op(Op), LHS(LHS), RHS(RHS) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a literal (nt) expression
        class LiteralExpr : public Expr
        {
        protected:
            std::string Type;
            std::string Value;
            bool AutoCast = true;

        public:
            LiteralExpr(std::string Type, std::string Value)
                : Type(Type), Value(Value) {}
            virtual std::string CodeGen() override;
            void DeactivateAutoCast(void);
            void ActivateAutoCast(void);
        };

        /// An expression statement is an expression ending by a semicolon
        class ExprSttmt : public Expr
        {
        protected:
            Expr *Expression;

        public:
            ExprSttmt(Expr *Expression)
                : Expression(Expression) {}
            virtual std::string CodeGen() override;
        };

        /// Represents a identifier
        class IdentExpr : public Expr
        {
        protected:
            std::string Name;

        public:
            IdentExpr(std::string Name)
                : Name(Name) {}
            virtual std::string CodeGen() override;
        };

        /// Represents an expression sorrounded by parentheses
        class ParExpr : public Expr
        {
        protected:
            Expr *Content;

        public:
            ParExpr(Expr *Content)
                : Content(Content) {}
            virtual std::string CodeGen() override;
        };

        /// Represents an assignment to a variable
        class AssignExpr : public Expr
        {
        protected:
            std::string AssignOp;
            Expr *Assignee;
            Expr *Assigned;

        public:
            AssignExpr(std::string AssignOp, Expr *Assignee, Expr *Assigned)
                : AssignOp(AssignOp), Assignee(Assignee), Assigned(Assigned) {}
            virtual std::string CodeGen() override;
        };

        /// Represents the for statement
        class ForSttmt : public Sttmt
        {
        protected:
            Expr *Start;
            Expr *Cond;
            Expr *After;
            BlockSttmt *Then;

        public:
            ForSttmt(Expr *Start, Expr *Cond, Expr *After, BlockSttmt *Then)
                : Start(Start), Cond(Cond), After(After), Then(Then) {}
            virtual std::string CodeGen() override;
        };

        /// Maps the 'mostra' keyword to printf in C
        class MostraFunCallExpr : public FunCallExpr
        {
        public:
            MostraFunCallExpr(FuncCallArgs *Args)
                : FunCallExpr(C_PRINTF, Args) {}
        };

        /// Represents a library importation
        class ImportSttmt : public Sttmt
        {
        protected:
            std::string Import;

        public:
            ImportSttmt(std::string Import)
                : Import(Import) {}
            virtual std::string CodeGen() override;
        };
    };
};

#endif // _CREOL_AST_TRANSPILER_HEADER