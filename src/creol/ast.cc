#include "../../include/creol/ast.hh"
#include "../../include/creol/cli.hh"

using namespace creol;

void ast::LocalContext::Initialize(std::string ModuleName) {
    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>(ModuleName, *TheContext);
    TheBuilder = std::make_unique<llvm::IRBuilder<>>(*TheContext);
}

static std::shared_ptr<ast::LocalContext> ast::LocalContext::New(std::string ModuleName) {
    std::shared_ptr<ast::LocalContext> LC = std::make_shared<ast::LocalContext>();
    LC->Initialize();
    return LC;
}

/// TODO: Implement in LLVM
std::string ast::Expr::CodeGen() {
    return "";
}

/// TODO: Implement in LLVM
std::string ast::VarDeclSttmt::CodeGen() {
    std::string VarVal = Value ? " = " + Value->CodeGen() : "";
    return Type + ' ' + Name + VarVal;
}

/// TODO: Implement in LLVM
void ast::VarDeclSttmt::SetType(std::string Type) {
    this->Type = Type;
}

/// TODO: Implement in LLVM
void ast::BlockSttmt::AddSttmt(ast::Sttmt* sttmt) {
    SttmtList.push_back(sttmt);
}

/// TODO: Implement in LLVM
std::string ast::BlockSttmt::CodeGen() {
    std::string block = "";

    for (auto& S : SttmtList) {
        block += S ? S->CodeGen() : "";
    };

    if (BracketsOn)
        block = "{" + block + "}";

    return block;
}

/// TODO: Implement in LLVM
void ast::BlockSttmt::UseBrackets() {
    BracketsOn = true;
}

/// TODO: Implement in LLVM
void ast::BlockSttmt::DontUseBrackets() {
    BracketsOn = false;
}

/// TODO: Implement in LLVM
void ast::FuncArgs::AddArg(ast::VarDeclSttmt* Arg) {
    Args.push_back(Arg);
}

/// TODO: Implement in LLVM
std::string ast::FuncArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

/// TODO: Implement in LLVM
std::string ast::FuncDeclSttmt::CodeGen() {
    return Type + " " + Name + " ( " + Args->CodeGen() + " ) " + Body->CodeGen();
}

/// TODO: Implement in LLVM
std::string ast::IfSttmt::CodeGen() {
    auto E = Else ? " else " + Else->CodeGen() : "";
    return "if ( " + Cond->CodeGen() + " ) " + Then->CodeGen() + E;
}

/// TODO: Implement in LLVM
std::string ast::WhileSttmt::CodeGen() {
    return "while ( " + Cond->CodeGen() + " )" + Do->CodeGen();
}

/// TODO: Implement in LLVM
std::string ast::JumpSttmt::CodeGen() {
    return Name + ";";
}

/// TODO: Implement in LLVM
std::string ast::ReturnSttmt::CodeGen() {
    auto R = ReturnValue ? ReturnValue->CodeGen() : "";
    return "return " + R + ";";
}

/// TODO: Implement in LLVM
void ast::FuncCallArgs::AddArg(Expr* Arg) {
    Args.push_back(Arg);
}

/// TODO: Implement in LLVM
std::string ast::FuncCallArgs::CodeGen() {
    std::string Arguments = "";

    for (int i = 0 ; i < (int) Args.size() ; ++i) {
        Arguments += Args[i] ? Args[i]->CodeGen() : "";
        if (Args[i] && i < (int) Args.size() - 1) {
            Arguments += " , ";
        }
    }

    return Arguments;
}

/// TODO: Implement in LLVM
std::string ast::FunCallExpr::CodeGen() {
    auto A = Args ? Args->CodeGen() : "";
    return Name + "( " + A + " )";
}

std::string ast::BinExpr::CodeGen(std::shared_ptr<ast::LocalContext> LC) {
    llvm::Value* L = LHS->CodeGen(LC);
    llvm::Value* R = RHS->CodeGen(LC);

    if (!L || !R) {
        cli::PrintErr("Error generating binary expr node.");
        return nullptr;
    }

    if (Op == "+") {
        return LC->TheBuilder->CreateAdd(L, R, "addtmp");
    } else if (Op == "-") {
        return LC->TheBuilder->CreateSub(L, R, "subtmp");
    } else if (Op == "*") {
        return LC->TheBuilder->CreateMul(L, R, "multmp");
    } else if (Op == "/") {
        return LC->TheBuilder->CreateFDiv(L, R, "divtmp");
    } else if (Op == "<") {
        return LC->TheBuilder->CreateICmpULT(L, R, "lttmp");
    } else if (Op == "<=") {
        return LC->TheBuilder->CreateICmpULE(L, R, "letmp");
    } else if (Op == ">") {
        return LC->TheBuilder->CreateICmpUGT(L, R, "gttmp");
    } else if (Op == ">=") {
        return LC->TheBuilder->CreateICmpUGE(L, R, "getmp");
    } else if (Op == "!=") {
        return LC->TheBuilder->CreateICmpNE(L, R, "netmp");
    } else if (Op == "==") {
        return LC->TheBuilder->CreateICmpEQ(L, R, "eqtmp");
    } else if (Op == "&&") {
        return LC->TheBuilder->CreateAnd(L, R, "andtmp");
    } else if (Op == "||") {
        return LC->TheBuilder->CreateOr(L, R, "ortmp");
    } else {
        cli::PrintErr("Operation " + Op + " is not yet supported as a binary operation!");
        return nullptr;
    }
}

/// TODO: Implement in LLVM
std::string ast::LiteralExpr::CodeGen() {
    auto Prefix = AutoCast ? "(" + Type + ") " : "";
    return Prefix + Value;
}

/// TODO: Implement in LLVM
void ast::LiteralExpr::ActivateAutoCast() {
    AutoCast = true;
}

/// TODO: Implement in LLVM
void ast::LiteralExpr::DeactivateAutoCast() {
    AutoCast = false;
}

/// TODO: Implement in LLVM
std::string ast::ExprSttmt::CodeGen() {
    return Expression ? Expression->CodeGen() + ";" : ";";
}

/// TODO: Implement in LLVM
std::string ast::IdentExpr::CodeGen() {
    return Name;
}

/// TODO: Implement in LLVM
std::string ast::ParExpr::CodeGen() {
    auto C = Content ? Content->CodeGen() : "";
    return "( " + C + " )";
}

/// TODO: Implement in LLVM
std::string ast::AssignExpr::CodeGen() {
    return Assignee->CodeGen() + " = " + Assigned->CodeGen();
}

/// TODO: Implement in LLVM
std::string ast::ForSttmt::CodeGen() {
    auto S = Start ? Start->CodeGen() : "";
    auto C = Cond ? Cond->CodeGen() : "";
    auto A = After ? After->CodeGen() : "";
    auto T = Then ? Then->CodeGen() : "";
    return "for (" + S + " ; " + C + " ; " + A + " ) " + T;
}

/// TODO: Implement in LLVM
std::string ast::ImportSttmt::CodeGen() {
    return "#include " + Import + "\n";
}