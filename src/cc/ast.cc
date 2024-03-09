#include "creol/include/ast.hh"

using namespace creol;

extern FILE* yyin;

extern int yyparse(void);

extern BlockSttmt* __KL_Program__BLOCK;


std::string Expr::CodeGen() {
    return "";
}

std::string VarDeclSttmt::CodeGen() {
    std::string VarVal = Value ? " = " + Value->CodeGen() : "";
    return Type + ' ' + Name + VarVal;
}

void VarDeclSttmt::SetType(std::string Type) {
    this->Type = Type;
}


void BlockSttmt::AddSttmt(Sttmt* sttmt) {
    SttmtList.push_back(sttmt);
}

std::string BlockSttmt::CodeGen() {
    std::string block = "";

    for (auto& S : SttmtList) {
        block += S ? S->CodeGen() : "";
    };

    if (BracketsOn)
        block = "{" + block + "}";

    return block;
}

void BlockSttmt::UseBrackets() {
    BracketsOn = true;
}

void BlockSttmt::DontUseBrackets() {
    BracketsOn = false;
}

void FuncArgs::AddArg(VarDeclSttmt* Arg) {
    Args.push_back(Arg);
}

std::string FuncArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string FuncDeclSttmt::CodeGen() {
    return Type + " " + Name + " ( " + Args->CodeGen() + " ) " + Body->CodeGen();
}

std::string IfSttmt::CodeGen() {
    auto E = Else ? " else " + Else->CodeGen() : "";
    return "if ( " + Cond->CodeGen() + " ) " + Then->CodeGen() + E;
}

std::string WhileSttmt::CodeGen() {
    return "while ( " + Cond->CodeGen() + " )" + Do->CodeGen();
}

std::string JumpSttmt::CodeGen() {
    return Name + ";";
}

std::string ReturnSttmt::CodeGen() {
    auto R = ReturnValue ? ReturnValue->CodeGen() : "";
    return "return " + R + ";";
}

void FuncCallArgs::AddArg(Expr* Arg) {
    Args.push_back(Arg);
}

std::string FuncCallArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

std::string FunCallExpr::CodeGen() {
    auto A = Args ? Args->CodeGen() : "";
    return Name + "( " + A + " )";
}

std::string BinExpr::CodeGen() {
    auto L = LHS ? LHS->CodeGen() : "";
    auto R = RHS ? RHS->CodeGen() : "";
    return L + " " + Op + " " + R;
}

std::string LiteralExpr::CodeGen() {
    auto Prefix = AutoCast ? "(" + Type + ") " : "";
    return Prefix + Value;
}

void LiteralExpr::ActivateAutoCast() {
    AutoCast = true;
}

void LiteralExpr::DeactivateAutoCast() {
    AutoCast = false;
}

std::string ExprSttmt::CodeGen() {
    return Expression ? Expression->CodeGen() + ";" : ";";
}

std::string IdentExpr::CodeGen() {
    return Name;
}

std::string ParExpr::CodeGen() {
    auto C = Content ? Content->CodeGen() : "";
    return "( " + C + " )";
}

std::string AssignExpr::CodeGen() {
    return Assignee->CodeGen() + " = " + Assigned->CodeGen();
}

std::string ForSttmt::CodeGen() {
    auto S = Start ? Start->CodeGen() : "";
    auto C = Cond ? Cond->CodeGen() : "";
    auto A = After ? After->CodeGen() : "";
    auto T = Then ? Then->CodeGen() : "";
    return "for (" + S + " ; " + C + " ; " + A + " ) " + T;
}

std::string ImportSttmt::CodeGen() {
    return "#include " + Import + "\n";
}

BlockSttmt* ParseFile(std::unique_ptr<std::string> filename) {
    FILE* file = fopen(filename.c_str(), "rt");

    // TODO: handle NULL pointer case maybe with better
    //       error reporting.

    // define the input file
    yyin = file;

    // parse the file
    yyparse();

    // close the file after the parsing
    fclose(file);

    // return the parsed program block
    return __KL_Program__BLOCK;
}