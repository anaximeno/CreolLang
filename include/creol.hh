#ifndef _CREOL_MAIN_TRANPILER_HEADER
#define _CREOL_MAIN_TRANPILER_HEADER

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace creol {
/// Represents a statement
class Sttmt {
public:
    virtual std::string codegen() = 0;
};

/// Represents an expression
class Expr : public Sttmt {
public:
    virtual std::string codegen() = 0;
};

/// Represents the declaration of a variable
class VarDeclSttmt : public Sttmt {
protected:
    const std::string Type;
    const std::string Name;
    const Expr* Value;
public:
    VarDeclSttmt(std::string Type, std::string Name, Expr* Value)
    : Type(Type), Name(Name), Value(Value) {}
    virtual std::string codegen() override;
};

/// Represents a blockSttmt of code
class BlockSttmt : public Sttmt {
protected:
    std::vector<Sttmt*> SttmtList;
public:
    void AddSttmt(Sttmt* sttmt);
    virtual std::string codegen() override;
};

/// Represents the declaration of a function
class FuncDeclSttmt : public Sttmt {
protected:
    const std::string Type;
    const std::string Name;
    std::vector<VarDeclSttmt*> Args;
public:
    FuncDeclSttmt(std::string Type, std::string Name, std::vector<VarDeclSttmt*>)
    : Type(Type), Name(Name), Args(Args) {}
    virtual std::string codegen() override;
};

/// Represents an if statement
class IfSttmt : public Sttmt {
protected:
    const Expr* Cond;
    const BlockSttmt* Then;
    const BlockSttmt* Else;
public:
    IfSttmt(Expr* Cond, BlockSttmt* Then, BlockSttmt* Else)
    : Cond(Cond), Then(Then), Else(Else) {}
    virtual std::string codegen() override;
};

/// Represents a while loop
class WhileSttmt : public Sttmt {
protected:
    const Expr* Cond;
    const BlockSttmt* Do;
public:
    WhileSttmt(Expr* Cond, BlockSttmt* Do)
    : Cond(Cond), Do(Do) {}
    virtual std::string codegen() override;
};

/// Represents a jump statement
class JumpSttmt : public Sttmt {
protected:
    const std::string Name;
public:
    JumpSttmt(std::string Name)
    : Name(Name) {}
    virtual std::string codegen() override;
};

/// Represents a return statement
class ReturnSttmt : public JumpSttmt {
protected:
    const Expr* ReturnValue;
public:
    ReturnSttmt(Expr* ReturnValue)
    : JumpSttmt("return"), ReturnValue(ReturnValue) {}
    virtual std::string codegen() override;
};

/// Represents the function call
class FunCallExpr : public Expr {
protected:
    const std::string Name;
    std::vector<Expr*> Args;
public:
    FunCallExpr(std::string Name, std::vector<Expr*> Args)
    : Name(Name), Args(Args) {}
    virtual std::string codegen() override;
};

/// Represents a binary expression
class BinExpr : public Expr {
protected:
    const std::string Op;
    const std::string LHS, RHS;
public:
    BinExpr(std::string Op, std::string LHS, std::string RHS)
    : Op(Op), LHS(LHS), RHS(RHS) {  }
    virtual std::string codegen() override;
};

/// Represents a literal (constant) expression
class LiteralExpr : public Expr {
protected:
    const std::string Type;
    const std::string Value;
public:
    LiteralExpr(std::string Type, std::string Value)
    : Type(Type), Value(Value) {}
    virtual std::string codegen() override;
};
}


#endif // _CREOL_MAIN_TRANPILER_HEADER