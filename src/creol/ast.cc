#include "../../include/creol/ast.hh"
#include "../../include/creol/cbinds.hh"

using namespace creol;

std::string ast::Expr::CodeGen()
{
    return "";
}

std::string ast::VarDeclSttmt::CodeGen()
{
    std::string Decl = Type + ' ' + Name;

    if (Value)
    {
        Decl = Decl + C_EQ + Value->CodeGen();
    }

    return Decl;
}

void ast::VarDeclSttmt::SetType(std::string Type)
{
    this->Type = Type;
}

void ast::BlockSttmt::AddSttmt(ast::Sttmt *sttmt)
{
    SttmtList.push_back(sttmt);
}

std::string ast::BlockSttmt::CodeGen()
{
    std::string block = "";

    for (auto &S : SttmtList)
    {
        block += S ? S->CodeGen() : "";
    };

    if (BracketsOn)
    {
        block = C_OPEN_CURLY + block + C_CLOSE_CURLY;
    }

    return block;
}

void ast::BlockSttmt::UseBrackets()
{
    BracketsOn = true;
}

void ast::BlockSttmt::DontUseBrackets()
{
    BracketsOn = false;
}

void ast::FuncArgs::AddArg(ast::VarDeclSttmt *Arg)
{
    Args.push_back(Arg);
}

std::string ast::FuncArgs::CodeGen()
{
    std::string Arguments = "";

    for (int i = 0; i < (int)Args.size(); ++i)
    {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";

        if (Args[i] && i < (int)Args.size() - 1)
        {
            Arguments += C_COMMA;
        }
    }

    return Arguments;
}

std::string ast::FuncDeclSttmt::CodeGen()
{
    return Type + " " + Name + C_OPEN_PAR + Args->CodeGen() + C_CLOSE_PAR + Body->CodeGen();
}

std::string ast::IfSttmt::CodeGen()
{
    std::string If_Code = C_IF + C_OPEN_PAR + Cond->CodeGen() + C_CLOSE_PAR + Then->CodeGen();

    if (Else)
    {
        If_Code = If_Code + " " + C_ELSE + " " + Else->CodeGen();
    }

    return If_Code;
}

std::string ast::WhileSttmt::CodeGen()
{
    return C_WHILE + C_OPEN_PAR + Cond->CodeGen() + C_CLOSE_PAR + Do->CodeGen();
}

std::string ast::JumpSttmt::CodeGen()
{
    return Name + C_SEMICOLON;
}

std::string ast::ReturnSttmt::CodeGen()
{
    std::string Value = "";

    if (ReturnValue)
    {
        Value = " " + ReturnValue->CodeGen();
    }

    return C_RETURN + Value + C_SEMICOLON;
}

void ast::FuncCallArgs::AddArg(Expr *Arg)
{
    Args.push_back(Arg);
}

std::string ast::FuncCallArgs::CodeGen()
{
    std::string Arguments = "";

    for (int i = 0; i < (int)Args.size(); ++i)
    {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int)Args.size() - 1)
        {
            Arguments += C_COMMA;
        }
    }

    return Arguments;
}

std::string ast::FunCallExpr::CodeGen()
{
    std::string Arguments = "";

    if (Args)
    {
        Arguments = Args->CodeGen();
    }

    return Name + C_OPEN_PAR + Arguments + C_CLOSE_PAR;
}

std::string ast::BinExpr::CodeGen()
{
    auto L = LHS ? LHS->CodeGen() : "";
    auto R = RHS ? RHS->CodeGen() : "";
    return L + " " + Op + " " + R;
}

std::string ast::LiteralExpr::CodeGen()
{
    std::string Prefix = "";

    if (AutoCast)
    {
        Prefix = C_OPEN_PAR + Type + C_CLOSE_PAR;
    }

    return Prefix + Value;
}

void ast::LiteralExpr::ActivateAutoCast()
{
    AutoCast = true;
}

void ast::LiteralExpr::DeactivateAutoCast()
{
    AutoCast = false;
}

std::string ast::ExprSttmt::CodeGen()
{
    return Expression ? Expression->CodeGen() + C_SEMICOLON : C_SEMICOLON;
}

std::string ast::IdentExpr::CodeGen()
{
    return Name;
}

std::string ast::ParExpr::CodeGen()
{
    auto C = Content ? Content->CodeGen() : "";
    return C_OPEN_PAR + C + C_CLOSE_PAR;
}

std::string ast::AssignExpr::CodeGen()
{
    return Assignee->CodeGen() + C_EQ + Assigned->CodeGen();
}

std::string ast::ForSttmt::CodeGen()
{
    auto S = Start ? Start->CodeGen() : "";
    auto C = Cond ? Cond->CodeGen() : "";
    auto A = After ? After->CodeGen() : "";
    auto T = Then ? Then->CodeGen() : "";
    return C_FOR + C_OPEN_PAR + S + C_SEMICOLON + C + C_SEMICOLON + A + C_CLOSE_PAR + T;
}

std::string ast::ImportSttmt::CodeGen()
{
    return C_IMPORT + " " + Import + "\n";
}