#include "../../include/creol/ast.hh"

using namespace creol;

std::string ast::Expr::CodeGen()
{
    return "";
}

std::string ast::VarDeclSttmt::CodeGen()
{
    std::string VarVal = Value ? " = " + Value->CodeGen() : "";
    return Type + ' ' + Name + VarVal;
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
        block = "{" + block + "}";

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
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string ast::FuncDeclSttmt::CodeGen()
{
    return Type + " " + Name + " ( " + Args->CodeGen() + " ) " + Body->CodeGen();
}

std::string ast::IfSttmt::CodeGen()
{
    auto E = Else ? " else " + Else->CodeGen() : "";
    return "if ( " + Cond->CodeGen() + " ) " + Then->CodeGen() + E;
}

std::string ast::WhileSttmt::CodeGen()
{
    return "while ( " + Cond->CodeGen() + " )" + Do->CodeGen();
}

std::string ast::JumpSttmt::CodeGen()
{
    return Name + ";";
}

std::string ast::ReturnSttmt::CodeGen()
{
    auto R = ReturnValue ? ReturnValue->CodeGen() : "";
    return "return " + R + ";";
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
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string ast::FunCallExpr::CodeGen()
{
    auto A = Args ? Args->CodeGen() : "";
    return Name + "( " + A + " )";
}

std::string ast::BinExpr::CodeGen()
{
    auto L = LHS ? LHS->CodeGen() : "";
    auto R = RHS ? RHS->CodeGen() : "";
    return L + " " + Op + " " + R;
}

std::string ast::LiteralExpr::CodeGen()
{
    auto Prefix = AutoCast ? "(" + Type + ") " : "";
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
    return Expression ? Expression->CodeGen() + ";" : ";";
}

std::string ast::IdentExpr::CodeGen()
{
    return Name;
}

std::string ast::ParExpr::CodeGen()
{
    auto C = Content ? Content->CodeGen() : "";
    return "( " + C + " )";
}

std::string ast::AssignExpr::CodeGen()
{
    return Assignee->CodeGen() + " = " + Assigned->CodeGen();
}

std::string ast::ForSttmt::CodeGen()
{
    auto S = Start ? Start->CodeGen() : "";
    auto C = Cond ? Cond->CodeGen() : "";
    auto A = After ? After->CodeGen() : "";
    auto T = Then ? Then->CodeGen() : "";
    return "for (" + S + " ; " + C + " ; " + A + " ) " + T;
}

std::string ast::ImportSttmt::CodeGen()
{
    return "#include " + Import + "\n";
}