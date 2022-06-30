%{
    #include "include/creol.hh"

    #include <cstdio>
    #include <cstdlib>
    #include <iostream>
    #include <typeinfo>

    extern int yylex();
    void yyerror(const char* err);

    using namespace creol;

    creol::BlockSttmt* Program;
%}

%union {
    int token;
    std::string* integer;
    std::string* floatingpoint;
    std::string* boolean;
    std::string* string;
    creol::Expr* expr;
    creol::Sttmt* sttmt;
    creol::BlockSttmt* block;
    creol::VarDeclSttmt* vardecl;
    creol::FuncArgs* params;
    creol::FuncCallArgs* args;
}

/* terminal symbols */

%token<string> TIDENTIFIER
%token<integer> INTEGER
%token<floatingpoint> FLOAT
%token<boolean> BOOL
%token<token>  TPLUS TMINUS TMUL TDIV
%token<token>  TEQ  TNE  TLT TLE TGT TGE
%token<token>  TAND TOR
%token<string> TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_VOID
%token<token>  TDIVOLVI TDI TPUI
%token<token>  TINKUANTU TSI TSINON
%token<token> TPARA TCONTINUA

%type<expr> expression assignment_expression function_call primary_expression
            constant_expression constant logical_or_expressions logical_and_expressions
            equality_expression relational_expression additive_expression multiplicative_expression
            unary_expression initializer
%type<sttmt> expression_statement selection_statement iteration_statement
             jump_statement function_declaration declaration statement
%type<block> compound_statement statements
%type<string> declarator identifier type_specifier assignment_operator
%type<vardecl> init_declarator parameter_declaration
%type<params> parameter_list parameter_optional_list
%type<args> argument_list

%left TLT TGT TLE TGE TEQ TNE '='
%left TPLUS TMINUS
%left TMUL TDIV
%left UMINUS

%start program

%debug
%verbose


%%

/* non terminals */

program : statements { Program = $1; }
        ;

type_specifier : TYPE_INT
               | TYPE_FLOAT
               | TYPE_VOID
               | TYPE_BOOL
               ;

constant : INTEGER { $$ = new LiteralExpr("int", *$1); }
         | FLOAT { $$ = new LiteralExpr("float", *$1); }
         | BOOL { $$ = new LiteralExpr("int", *$1); }
         ;

identifier : TIDENTIFIER
           ;

// note: declator may be extended later
declarator : identifier
           ;

declaration : type_specifier init_declarator { $2->SetType(*$1); $$ = (Sttmt*) $2; }
            ;

init_declarator : declarator { $$ = new VarDeclSttmt("void", *$1, nullptr); }
                | declarator '=' initializer { $$ = new VarDeclSttmt("void", *$1, $3); }
                ;

// note: may be extended later
initializer : expression
            ;

expression : assignment_expression
           | function_call
           ;

constant_expression : logical_or_expressions
                    ;

logical_or_expressions : logical_and_expressions
                       | logical_or_expressions TOR logical_and_expressions { $$ = (Expr*) new BinExpr("||", $1, $3); }
                       ;

logical_and_expressions : equality_expression
                        | logical_and_expressions TAND equality_expression { $$ = (Expr*) new BinExpr("&&", $1, $3); }
                        ;

equality_expression : relational_expression
                    | equality_expression TEQ relational_expression { $$ = (Expr*) new BinExpr("==", $1, $3); }
                    | equality_expression TNE relational_expression { $$ = (Expr*) new BinExpr("!=", $1, $3); }
                    ;

relational_expression : additive_expression
                      | relational_expression TLT additive_expression { $$ = (Expr*) new BinExpr("<", $1, $3); }
                      | relational_expression TGT additive_expression { $$ = (Expr*) new BinExpr(">", $1, $3); }
                      | relational_expression TLE additive_expression { $$ = (Expr*) new BinExpr("<=", $1, $3); }
                      | relational_expression TGE additive_expression { $$ = (Expr*) new BinExpr(">=", $1, $3); }
                      ;

additive_expression : multiplicative_expression
                    | additive_expression TPLUS multiplicative_expression { $$ = (Expr*) new BinExpr("+", $1, $3); }
                    | additive_expression TMINUS multiplicative_expression { $$ = (Expr*) new BinExpr("-", $1, $3); }
                    ;

multiplicative_expression : unary_expression
                          | multiplicative_expression TMUL primary_expression { $$ = (Expr*) new BinExpr("*", $1, $3); }
                          | multiplicative_expression TDIV primary_expression { $$ = (Expr*) new BinExpr("/", $1, $3); }
                          ;

unary_expression : primary_expression
                 /* | TMINUS primary_expression %prec UMINUS */
                 ;

primary_expression : identifier { $$ = (Expr*) new IdentExpr(*$1); }
                   | constant
                   | '(' expression ')' { $$ = (Expr*) new ParExpr($2); }
                   ;

// todo: correct anomalies using semantic analysis
assignment_expression : constant_expression
                      | primary_expression assignment_operator assignment_expression { $$ = (Expr*) new AssignExpr(*$2, $1, $3); }
                      ;

// note: this may be extended later to support op assign
assignment_operator : '=' { $$ = new std::string("=", 2); }
                    ;

function_declaration : type_specifier declarator '(' parameter_optional_list ')' compound_statement { $$ = (Sttmt*) new FuncDeclSttmt(*$1, *$2, $4, $6); }
                     ;

parameter_optional_list : parameter_list
                        | %empty { $$ = new FuncArgs(); }
                        ;

parameter_list : parameter_declaration { $$ = new FuncArgs(); $$->AddArg($1); }
               | parameter_list ',' parameter_declaration { { $1->AddArg($3); } }
               ;

parameter_declaration : type_specifier declarator { $$ = new VarDeclSttmt(*$1, *$2, nullptr); }
                      ;

argument_list : argument_list ',' expression { $1->AddArg($3); }
              | expression { $$ = new FuncCallArgs(); $$->AddArg($1);  }
              ;

function_call : identifier '(' argument_list ')' { $$ = new FunCallExpr(*$1, $3); }
              | identifier '(' ')' { $$ = new FunCallExpr(*$1, nullptr); }

statements : statements statement { $1->AddSttmt($2); }
           | statement { $$ = new BlockSttmt(); $$->AddSttmt($1); }
           ;

// todo: analyze the situation of
// functions declared inside other functions
// and the use of declarations in the global
// scope.
statement : expression_statement
          | compound_statement { $$ = (Sttmt*) $1; }
          | selection_statement
          | iteration_statement
          | jump_statement
          | function_declaration
          | declaration
          ;

expression_statement : expression ';' { $$ = new ExprSttmt($1); }
                     | ';' { $$ = new ExprSttmt(nullptr); }
                     ;

compound_statement : '{' statements '}' { $$ = $2; $$->UseBrackets(); }
                   | '{' '}' { $$ = new BlockSttmt(); $$->UseBrackets(); }
                   ;

selection_statement : TSI expression compound_statement { $$ = new IfSttmt($2, $3, nullptr); }
                    | TSI expression compound_statement TSINON compound_statement { $$ = new IfSttmt($2, $3, $5); }
                    ; // TODO: Add else if

iteration_statement : TINKUANTU expression compound_statement { $$ = new WhileSttmt($2, $3); }
                    /* | TDI expression TINKUANTU expression TPUI expression compound_statement */
                    ;

jump_statement : TPARA ';' { $$ = new JumpSttmt("break"); }
               | TCONTINUA ';' { $$ = new JumpSttmt("continue"); }
               | TDIVOLVI expression ';' { $$ = new ReturnSttmt($2); }
               | TDIVOLVI ';' { $$ = new ReturnSttmt(nullptr); }
               ;
%%

void yyerror(const char* err) {
    std::cerr << "Error: " << err << std::endl;
    std::exit(1);
}

int main(const int argc, const char* const* argv) {
    yyparse();

    if (Program)
        std::cout << Program->CodeGen() << std::endl;

    return 0;
}
