%{
    #include "include/creol/ast.hh"

    #include <cstdio>
    #include <cstdlib>
    #include <iostream>

    extern int yylex();
    void yyerror(const char* err);

    using namespace creol;
    using namespace creol::ast;

    creol::ast::BlockSttmt* Program;
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

%token<string> T_IDENT T_STR_LIT T_MOSTRA
%token<integer> T_INT_LIT
%token<floatingpoint> T_FLOAT_LIT
%token<boolean> T_BOOL_LIT
%token<token>  T_PLUS T_MINUS T_MUL T_DIV
%token<token>  T_EQ  T_NE  T_LT T_LE T_GT T_GE
%token<token>  T_AND T_OR T_ASSIGN T_LCURLY T_RCURLY T_COMMA T_SEMIC T_LBRAC T_RBRAC
%token<string> T_TYPE_INT T_TYPE_FLOAT T_TYPE_BOOL T_TYPE_VOID
%token<token>  T_DIVOLVI T_DI T_STRUT
%token<token>  T_NKUANTU T_SI T_SINON T_IMPRISTAN
%token<token> T_PARA T_CONTINUA T_DOT T_RPAR T_LPAR

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

%left T_LT T_GT T_LE T_GE T_EQ T_NE T_ASSIGN
%left T_PLUS T_MINUS
%left T_MUL T_DIV
%left UMINUS

%start program

%debug
%verbose


%%

/* non terminals */

program : statements { Program = $1; }
        ;

type_specifier : T_TYPE_INT
               | T_TYPE_FLOAT
               | T_TYPE_VOID
               | T_TYPE_BOOL { $$ = new std::string("unsigned short"); }
               ;

constant : T_INT_LIT { $$ = new LiteralExpr("int", *$1); $<litexpr>$->ActivateAutoCast(); }
         | T_FLOAT_LIT { $$ = new LiteralExpr("float", *$1); $<litexpr>$->ActivateAutoCast(); }
         | T_BOOL_LIT { $$ = new LiteralExpr("unsigned short", *$1); $<litexpr>$->ActivateAutoCast(); }
         | T_STR_LIT { $$ = new LiteralExpr("char*", *$1); $<litexpr>$->DeactivateAutoCast(); }
         ;

identifier : T_IDENT
           ;

// note: declator may be extended later
declarator : identifier
           ;

declaration : type_specifier init_declarator { $2->SetType(*$1); $$ = $2; }
            ;

init_declarator : declarator { $$ = new VarDeclSttmt("void", *$1, nullptr); }
                | declarator T_ASSIGN initializer { $$ = new VarDeclSttmt("void", *$1, $3); }
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
                       | logical_or_expressions T_OR logical_and_expressions { $$ = new BinExpr("||", $1, $3); }
                       ;

logical_and_expressions : equality_expression
                        | logical_and_expressions T_AND equality_expression { $$ = new BinExpr("&&", $1, $3); }
                        ;

equality_expression : relational_expression
                    | equality_expression T_EQ relational_expression { $$ = new BinExpr("==", $1, $3); }
                    | equality_expression T_NE relational_expression { $$ = new BinExpr("!=", $1, $3); }
                    ;

relational_expression : additive_expression
                      | relational_expression T_LT additive_expression { $$ = new BinExpr("<", $1, $3); }
                      | relational_expression T_GT additive_expression { $$ = new BinExpr(">", $1, $3); }
                      | relational_expression T_LE additive_expression { $$ = new BinExpr("<=", $1, $3); }
                      | relational_expression T_GE additive_expression { $$ = new BinExpr(">=", $1, $3); }
                      ;

additive_expression : multiplicative_expression
                    | additive_expression T_PLUS multiplicative_expression { $$ = new BinExpr("+", $1, $3); }
                    | additive_expression T_MINUS multiplicative_expression { $$ = new BinExpr("-", $1, $3); }
                    ;

multiplicative_expression : unary_expression
                          | multiplicative_expression T_MUL primary_expression { $$ = new BinExpr("*", $1, $3); }
                          | multiplicative_expression T_DIV primary_expression { $$ = new BinExpr("/", $1, $3); }
                          ;

unary_expression : primary_expression
                 /* | TMINUS primary_expression %prec UMINUS */
                 ;

primary_expression : identifier { $$ = new IdentExpr(*$1); }
                   | constant
                   | T_LPAR expression T_RPAR { $$ = new ParExpr($2); }
                   ;

// todo: correct anomalies using semantic analysis
assignment_expression : constant_expression
                      | primary_expression assignment_operator assignment_expression { $$ = new AssignExpr(*$2, $1, $3); }
                      ;

// note: this may be extended later to support op assign
assignment_operator : T_ASSIGN { $$ = new std::string("=", 2); }
                    ;

function_declaration : type_specifier declarator T_LPAR parameter_optional_list T_RPAR compound_statement { $$ = new FuncDeclSttmt(*$1, *$2, $4, $6); }
                     ;

parameter_optional_list : parameter_list
                        | %empty { $$ = new FuncArgs(); }
                        ;

parameter_list : parameter_declaration { $$ = new FuncArgs(); $$->AddArg($1); }
               | parameter_list T_COMMA parameter_declaration { { $1->AddArg($3); } }
               ;

parameter_declaration : type_specifier declarator { $$ = new VarDeclSttmt(*$1, *$2, nullptr); }
                      ;

argument_list : argument_list T_COMMA expression { $1->AddArg($3); }
              | expression { $$ = new FuncCallArgs(); $$->AddArg($1);  }
              ;

function_call : identifier T_LPAR argument_list T_RPAR { $$ = new FunCallExpr(*$1, $3); }
              | identifier T_LPAR T_RPAR { $$ = new FunCallExpr(*$1, nullptr); }
              | mostra_func_call
              ;

mostra_func_call : T_MOSTRA T_LPAR argument_list T_RPAR { $$ = new MostraFunCallExpr($3); }
                 | T_MOSTRA T_LPAR T_RPAR { $$ = new MostraFunCallExpr(nullptr); }
                 ;

statements : statements statement { $1->AddSttmt($2); }
           | statement { $$ = new BlockSttmt(); $$->AddSttmt($1); }
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

import_statement : T_IMPRISTAN single_import { $$ = new ImportSttmt(*$2); }
                 ;

single_import : T_STR_LIT
              ;

expression_statement : expression T_SEMIC { $$ = new ExprSttmt($1); }
                     | T_SEMIC { $$ = new ExprSttmt(nullptr); }
                     ;

compound_statement : T_LCURLY statements T_RCURLY { $$ = $2; $$->UseBrackets(); }
                   | T_LCURLY T_RCURLY { $$ = new BlockSttmt(); $$->UseBrackets(); }
                   ;

selection_statement : T_SI expression compound_statement { $$ = new IfSttmt($2, $3, nullptr); }
                    /* | T_SI expression compound_statement T_SINON compound_statement { $$ = new IfSttmt($2, $3, $5); } */
                    | T_SI expression compound_statement T_SINON else_then { $$ = new IfSttmt($2, $3, $5); }
                    ;

else_then : compound_statement
          | selection_statement { $$ = new BlockSttmt(); $$->AddSttmt($1); }
          ;

iteration_statement : T_NKUANTU expression compound_statement { $$ = new WhileSttmt($2, $3); }
                    | T_DI expression T_SEMIC expression T_SEMIC expression compound_statement { $$ = new ForSttmt($2, $4, $6, $7); }
                    ;

jump_statement : T_PARA T_SEMIC { $$ = new JumpSttmt("break"); }
               | T_CONTINUA T_SEMIC { $$ = new JumpSttmt("continue"); }
               | T_DIVOLVI expression T_SEMIC { $$ = new ReturnSttmt($2); }
               | T_DIVOLVI T_SEMIC { $$ = new ReturnSttmt(nullptr); }
               ;
%%

void yyerror(const char* err) {
    fprintf(stderr, "Creol: Error: %s\n", err);
    std::exit(1);
}

