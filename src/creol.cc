#include "../include/creol.hh"

std::string creol::Expr::CodeGen() {
    return "";
}

std::string creol::VarDeclSttmt::CodeGen() {
    std::string VarVal = Value ? " = " + Value->CodeGen() : "";
    return Type + ' ' + Name + VarVal;
}

void creol::BlockSttmt::AddSttmt(creol::Sttmt* sttmt) {
    SttmtList.push_back(sttmt);
}

std::string creol::BlockSttmt::CodeGen() {
    std::string block = "{";

    for (auto& S : SttmtList) {
        block += S ? S->CodeGen() : "";
    };

    return block + "}";
}

std::string creol::FuncDeclSttmt::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < Args.size() - 1) {
            Arguments += ',';
        }
    }

    return Arguments;
}

std::string creol::IfSttmt::CodeGen() {
    return "if ( " + Cond->CodeGen() + " ) " + Then->CodeGen() + " else " + Else->CodeGen();
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

std::string creol::FunCallExpr::CodeGen() {
    std::string Parameters = "";

    for (int i = 0 ; i < Params.size() ; ++i) {
        Parameters += Params[i] ? Params[i]->CodeGen() : "";
        if (Params[i] && i < Params.size() - 1) {
            Parameters += ',';
        }
    }

    return Name + "( " + Parameters + " )";
}

std::string creol::BinExpr::CodeGen() {
    auto L = LHS ? LHS->CodeGen() : "";
    auto R = RHS ? RHS->CodeGen() : "";
    return L + " " + Op + " " + R;
}

std::string creol::LiteralExpr::CodeGen() {
    return "(" + Type + ")" + " " + Value;
}

std::string creol::ExprSttmt::CodeGen() {
    return Expression ? Expression->CodeGen() + ";" : ";";
}