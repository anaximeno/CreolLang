%{
    #include "include/creol/ast.hh"
    #include "include/creol/cli.hh"

    #include <cstdio>
    #include <cstdlib>
    #include <iostream>

    extern int yylex();
    void yyerror(const char* err);

    using namespace creol;

    ast::BlockSttmt* Program;
%}

%union {
    int token;
    std::string* integer;
    std::string* floatingpoint;
    std::string* boolean;
    std::string* string;
    creol::ast::Expr* expr;
    creol::ast::Sttmt* sttmt;
    creol::ast::BlockSttmt* block;
    creol::ast::VarDeclSttmt* vardecl;
    creol::ast::FuncArgs* params;
    creol::ast::FuncCallArgs* args;
    creol::ast::LiteralExpr* litexpr;
}

/* terminal symbols */

%token<string> IDENT STR_LIT MOSTRA
%token<integer> INT_LIT
%token<floatingpoint> FLOAT_LIT
%token<boolean> BOOL_LIT
%token<token>  PLUS MINUS MUL DIV
%token<token>  EQ  NE  LT LE GT GE
%token<token>  AND OR ASSIGN LCURLY RCURLY COMMA SEMIC LBRAC RBRAC
%token<string> TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_VOID
%token<token>  DIVOLVI DI STRUT
%token<token>  NKUANTU SI SINON IMPRISTAN
%token<token> PARA CONTINUA DOT RPAR LPAR

/* non terminal symbols */

%type<expr> expression assignment_expression function_call primary_expression
            constant_expression constant logical_or_expressions logical_and_expressions
            equality_expression relational_expression additive_expression multiplicative_expression
            unary_expression initializer mostra_func_call
%type<sttmt> expression_statement selection_statement iteration_statement jump_statement
             function_declaration declaration statement import_statement
%type<block> compound_statement statements else_then
%type<string> declarator identifier type_specifier assignment_operator single_import
%type<vardecl> init_declarator parameter_declaration
%type<params> parameter_list parameter_optional_list
%type<args> argument_list

%left LT GT LE GE EQ NE ASSIGN
%left PLUS MINUS
%left MUL DIV
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
               | TYPE_BOOL { $$ = new std::string("unsigned short"); }
               ;

constant : INT_LIT { $$ = new ast::LiteralExpr("int", *$1); $<litexpr>$->ActivateAutoCast(); }
         | FLOAT_LIT { $$ = new ast::LiteralExpr("float", *$1); $<litexpr>$->ActivateAutoCast(); }
         | BOOL_LIT { $$ = new ast::LiteralExpr("unsigned short", *$1); $<litexpr>$->ActivateAutoCast(); }
         | STR_LIT { $$ = new ast::LiteralExpr("char*", *$1); $<litexpr>$->DeactivateAutoCast(); }
         ;

identifier : IDENT
           ;

// note: declator may be extended later
declarator : identifier
           ;

declaration : type_specifier init_declarator { $2->SetType(*$1); $$ = $2; }
            ;

init_declarator : declarator { $$ = new ast::VarDeclSttmt("void", *$1, nullptr); }
                | declarator ASSIGN initializer { $$ = new ast::VarDeclSttmt("void", *$1, $3); }
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
                       | logical_or_expressions OR logical_and_expressions { $$ = new ast::BinExpr("||", $1, $3); }
                       ;

logical_and_expressions : equality_expression
                        | logical_and_expressions AND equality_expression { $$ = new ast::BinExpr("&&", $1, $3); }
                        ;

equality_expression : relational_expression
                    | equality_expression EQ relational_expression { $$ = new ast::BinExpr("==", $1, $3); }
                    | equality_expression NE relational_expression { $$ = new ast::BinExpr("!=", $1, $3); }
                    ;

relational_expression : additive_expression
                      | relational_expression LT additive_expression { $$ = new ast::BinExpr("<", $1, $3); }
                      | relational_expression GT additive_expression { $$ = new ast::BinExpr(">", $1, $3); }
                      | relational_expression LE additive_expression { $$ = new ast::BinExpr("<=", $1, $3); }
                      | relational_expression GE additive_expression { $$ = new ast::BinExpr(">=", $1, $3); }
                      ;

additive_expression : multiplicative_expression
                    | additive_expression PLUS multiplicative_expression { $$ = new ast::BinExpr("+", $1, $3); }
                    | additive_expression MINUS multiplicative_expression { $$ = new ast::BinExpr("-", $1, $3); }
                    ;

multiplicative_expression : unary_expression
                          | multiplicative_expression MUL primary_expression { $$ = new ast::BinExpr("*", $1, $3); }
                          | multiplicative_expression DIV primary_expression { $$ = new ast::BinExpr("/", $1, $3); }
                          ;

unary_expression : primary_expression
                 /* | TMINUS primary_expression %prec UMINUS */
                 ;

primary_expression : identifier { $$ = new ast::IdentExpr(*$1); }
                   | constant
                   | LPAR expression RPAR { $$ = new ast::ParExpr($2); }
                   ;

// todo: correct anomalies using semantic analysis
assignment_expression : constant_expression
                      | primary_expression assignment_operator assignment_expression { $$ = new ast::AssignExpr(*$2, $1, $3); }
                      ;

// note: this may be extended later to support op assign
assignment_operator : ASSIGN { $$ = new std::string("=", 2); }
                    ;

function_declaration : type_specifier declarator LPAR parameter_optional_list RPAR compound_statement { $$ = new ast::FuncDeclSttmt(*$1, *$2, $4, $6); }
                     ;

parameter_optional_list : parameter_list
                        | %empty { $$ = new ast::FuncArgs(); }
                        ;

parameter_list : parameter_declaration { $$ = new ast::FuncArgs(); $$->AddArg($1); }
               | parameter_list COMMA parameter_declaration { { $1->AddArg($3); } }
               ;

parameter_declaration : type_specifier declarator { $$ = new ast::VarDeclSttmt(*$1, *$2, nullptr); }
                      ;

argument_list : argument_list COMMA expression { $1->AddArg($3); }
              | expression { $$ = new ast::FuncCallArgs(); $$->AddArg($1);  }
              ;

function_call : identifier LPAR argument_list RPAR { $$ = new ast::FunCallExpr(*$1, $3); }
              | identifier LPAR RPAR { $$ = new ast::FunCallExpr(*$1, nullptr); }
              | mostra_func_call
              ;

mostra_func_call : MOSTRA LPAR argument_list RPAR { $$ = new ast::MostraFunCallExpr($3); }
                 | MOSTRA LPAR RPAR { $$ = new ast::MostraFunCallExpr(nullptr); }
                 ;

statements : statements statement { $1->AddSttmt($2); }
           | statement { $$ = new ast::BlockSttmt(); $$->AddSttmt($1); }
           ;

// todo: analyze the situation of
// functions declared inside other functions
// and the use of declarations in the global
// scope.
statement : expression_statement
          | compound_statement { $$ = $1; }
          | selection_statement
          | iteration_statement
          | jump_statement
          | function_declaration
          | declaration
          | import_statement { $$ = $1; }
          ;

import_statement : IMPRISTAN single_import { $$ = new ast::ImportSttmt(*$2); }
                 ;

single_import : STR_LIT
              ;

expression_statement : expression SEMIC { $$ = new ast::ExprSttmt($1); }
                     | SEMIC { $$ = new ast::ExprSttmt(nullptr); }
                     ;

compound_statement : LCURLY statements RCURLY { $$ = $2; $$->UseBrackets(); }
                   | LCURLY RCURLY { $$ = new ast::BlockSttmt(); $$->UseBrackets(); }
                   ;

selection_statement : SI expression compound_statement { $$ = new ast::IfSttmt($2, $3, nullptr); }
                    | SI expression compound_statement SINON else_then { $$ = new ast::IfSttmt($2, $3, $5); }
                    ;

else_then : compound_statement
          | selection_statement { $$ = new ast::BlockSttmt(); $$->AddSttmt($1); }
          ;

iteration_statement : NKUANTU expression compound_statement { $$ = new ast::WhileSttmt($2, $3); }
                    | DI expression SEMIC expression SEMIC expression compound_statement { $$ = new ast::ForSttmt($2, $4, $6, $7); }
                    ;

jump_statement : PARA SEMIC { $$ = new ast::JumpSttmt("break"); }
               | CONTINUA SEMIC { $$ = new ast::JumpSttmt("continue"); }
               | DIVOLVI expression SEMIC { $$ = new ast::ReturnSttmt($2); }
               | DIVOLVI SEMIC { $$ = new ast::ReturnSttmt(nullptr); }
               ;
%%

void yyerror(const char* err) {
    creol::cli::PrintErr(err, 1);
}

