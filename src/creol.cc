#include "../include/creol.hh"

std::string creol::Expr::CodeGen() {
    return "";
}

std::string creol::VarDeclSttmt::CodeGen() {
    std::string VarVal = Value ? " = " + Value->CodeGen() : "";
    return Type + ' ' + Name + VarVal;
}

void creol::VarDeclSttmt::SetType(std::string Type) {
    this->Type = Type;
}


void creol::BlockSttmt::AddSttmt(creol::Sttmt* sttmt) {
    SttmtList.push_back(sttmt);
}

std::string creol::BlockSttmt::CodeGen() {
    std::string block = "";

    for (auto& S : SttmtList) {
        block += S ? S->CodeGen() : "";
    };

    if (BracketsOn)
        block = "{" + block + "}";

    return block;
}

void creol::BlockSttmt::UseBrackets() {
    BracketsOn = true;
}

void creol::BlockSttmt::DontUseBrackets() {
    BracketsOn = false;
}

void creol::FuncArgs::AddArg(creol::VarDeclSttmt* Arg) {
    Args.push_back(Arg);
}

std::string creol::FuncArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string creol::FuncDeclSttmt::CodeGen() {
    return Type + " " + Name + " ( " + Args->CodeGen() + " ) " + Body->CodeGen();
}

std::string creol::IfSttmt::CodeGen() {
    auto E = Else ? " else " + Else->CodeGen() : "";
    return "if ( " + Cond->CodeGen() + " ) " + Then->CodeGen() + E;
}

std::string creol::WhileSttmt::CodeGen() {
    return "while ( " + Cond->CodeGen() + " )" + Do->CodeGen();
}

std::string creol::JumpSttmt::CodeGen() {
    return Name + ";";
}

std::string creol::ReturnSttmt::CodeGen() {
    auto R = ReturnValue ? ReturnValue->CodeGen() : "";
    return "return " + R + ";";
}

void creol::FuncCallArgs::AddArg(Expr* Arg) {
    Args.push_back(Arg);
}

std::string creol::FuncCallArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string creol::FunCallExpr::CodeGen() {
    auto A = Args ? Args->CodeGen() : "";
    return Name + "( " + A + " )";
}

std::string creol::BinExpr::CodeGen() {
    auto L = LHS ? LHS->CodeGen() : "";
    auto R = RHS ? RHS->CodeGen() : "";
    return L + " " + Op + " " + R;
}

std::string creol::LiteralExpr::CodeGen() {
    auto Prefix = AutoCast ? "(" + Type + ") " : "";
    return Prefix + Value;
}

void creol::LiteralExpr::ActivateAutoCast() {
    AutoCast = true;
}

void creol::LiteralExpr::DeactivateAutoCast() {
    AutoCast = false;
}

std::string creol::ExprSttmt::CodeGen() {
    return Expression ? Expression->CodeGen() + ";" : ";";
}

std::string creol::IdentExpr::CodeGen() {
    return Name;
}

std::string creol::ParExpr::CodeGen() {
    auto C = Content ? Content->CodeGen() : "";
    return "( " + C + " )";
}

std::string creol::AssignExpr::CodeGen() {
    return Assignee->CodeGen() + " = " + Assigned->CodeGen();
}

std::string creol::ForSttmt::CodeGen() {
    auto S = Start ? Start->CodeGen() : "";
    auto C = Cond ? Cond->CodeGen() : "";
    auto A = After ? After->CodeGen() : "";
    auto T = Then ? Then->CodeGen() : "";
    return "for (" + S + " ; " + C + " ; " + A + " ) " + T;
}