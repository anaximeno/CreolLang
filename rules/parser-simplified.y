%{
    #include <cstdio>
    #include <cstdlib>
    #include <iostream>
    #include <memory>
    #include <algorithm>
    #include "../include/creol.hh"
    extern int yylex();
    void yyerror(const char* err);

    using namespace creol;

    static creol::BlockAST* ProgramBlock = nullptr;
%}

%union {
    int token;
    std::string* string;
    double floatingpoint;
    creol::BlockAST* block;
    creol::ExprAST* expr;
    creol::BinaryExprAST* binexpr;
    creol::StmtAST* stmt;
    // std::vector<std::unique_ptr<ExprAST>> exprvec;
}

/* terminal symbols */

%token<string> TIDENTIFIER
%token<floatingpoint> FLOAT
%token<token>  TPLUS TMINUS TMUL TDIV
%token<token>  TEQ  TNE  TLT TLE TGT TGE
%token<token>  TAND TOR
%token<string> TYPE_FLOAT
%token<token>  TDIVOLVI TDI TPUI
%token<token>  TINKUANTU TSI TSINON
%token<token> TPARA TCONTINUA

%type<expr> assignment_expression /* function_call */ constant_expression primary_expression
            expression constant logical_and_expressions logical_or_expressions equality_expression
            relational_expression additive_expression multiplicative_expression unary_expression
%type<stmt> expression_statement selection_statement statement
            iteration_statement jump_statement function_declaration declaration
%type<string> identifier type_specifier
/* %type<exprvec> argument_list assignment_operator */
%type<block> statements compound_statement

%left TLT TGT TLE TGE TEQ TNE '='
%left TPLUS TMINUS
%left TMUL TDIV
%left UMINUS

%start program

%debug
%verbose


%%

/* non terminals */

program : statements { ProgramBlock = $1; }
        ;

type_specifier : TYPE_FLOAT
               ;

constant : FLOAT { $$ = (ExprAST*) new FloatLiteralExprAST($1); }
         ;

identifier : TIDENTIFIER
           ;

// note: declator may be extended later
declarator : identifier
           ;

declaration : type_specifier init_declarator
            ;

init_declarator : declarator
                | declarator '=' initializer
                ;

// note: may be extended later
initializer : expression
            ;

expression : assignment_expression { $$ = $1; }
           /* | function_call { $$ = $1; } */
           ;

constant_expression : logical_or_expressions { $$ = $1; }
                    ;

logical_or_expressions : logical_and_expressions { $$ = $1; }
                       | logical_or_expressions TOR logical_and_expressions { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::OR, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                       ;

logical_and_expressions : equality_expression { $$ = $1; }
                        | logical_and_expressions TAND equality_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::AND, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                        ;

equality_expression : relational_expression { $$ = $1; }
                    | equality_expression TEQ relational_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::EQ, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                    | equality_expression TNE relational_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::NE, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                    ;

relational_expression : additive_expression { $$ = $1; }
                      | relational_expression TLT additive_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::LT, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                      | relational_expression TGT additive_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::GT, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                      | relational_expression TLE additive_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::LE, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                      | relational_expression TGE additive_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::GE, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                      ;

additive_expression : multiplicative_expression { $$ = $1; }
                    | additive_expression TPLUS multiplicative_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::PLUS, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                    | additive_expression TMINUS multiplicative_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::MINUS, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                    ;

multiplicative_expression : unary_expression { $$ = $1; }
                          | multiplicative_expression TMUL primary_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::TIMES, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                          | multiplicative_expression TDIV primary_expression { $$ = (ExprAST*) new BinaryExprAST(OpSymbol::DIV, std::unique_ptr<ExprAST>($1), std::unique_ptr<ExprAST>($3)); }
                          ;

unary_expression : primary_expression { $$ = $1; }
                 | TMINUS primary_expression %prec UMINUS // TODO: Handle here!
                 ;

primary_expression : identifier // TODO: Handle here!
                   | constant { $$ = $1; }
                   | '(' expression ')' { $$ = $2; }
                   ;

// todo: correct anomalies using semantic analysis
assignment_expression : constant_expression { $$ = $1; }
                      | primary_expression assignment_operator assignment_expression { $$ = nullptr; } // TODO: Implement here!
                      ;

// note: this may be extended later to support op assign
assignment_operator : '='
                    ;

function_declaration : type_specifier declarator '(' parameter_optional_list ')' compound_statement
                     ;

parameter_optional_list : parameter_list
                        | %empty
                        ;

parameter_list : parameter_declaration
               | parameter_list ',' parameter_declaration
               ;

parameter_declaration : type_specifier declarator
                      ;

argument_list : argument_list ',' expression /* TODO: Handle Here */
              | expression /* TODO: Handle Here */
              ;

/* function_call : identifier '(' argument_list ')' { $$ = new CallExprAST($1, $3); }
              | identifier '(' ')' { std::vector<std::unique_ptr<ExprAST>> emptyVec; $$ = new CallExprAST($1, std::move(emptyVec)); } */

statements : statements statement { $1->AddStatement($2); }
           | statement { $$ = new BlockAST(); $$->AddStatement($1); }
           ;

// todo: analyze the situation of
// functions declared inside other functions
// and the use of declarations in the global
// scope.
statement : expression_statement { $$ = $1; }
          | compound_statement { $$ = (StmtAST*) $1; }
          | selection_statement { $$ = $1; }
          | iteration_statement { $$ = $1; }
          | jump_statement { $$ = $1; }
          | function_declaration { $$ = $1; }
          | declaration { $$ = $1; }
          ;

expression_statement : expression ';' { $$ = (StmtAST*) $1; }
                     | ';'
                     ;

compound_statement : '{' statements '}' { $$ = $2; }
                   | '{' '}'
                   ;

selection_statement : TSI expression compound_statement { $$ = (StmtAST*) new IfExprAST(std::unique_ptr<ExprAST>($2), std::unique_ptr<BlockAST>($3), std::make_unique<BlockAST>()); }
                    | TSI expression compound_statement TSINON compound_statement { $$ = (StmtAST*) new IfExprAST(std::unique_ptr<ExprAST>($2), std::unique_ptr<BlockAST>($3), std::unique_ptr<BlockAST>($5)); }
                    ; // TODO: Add else if

iteration_statement : TINKUANTU expression compound_statement /// TODO: Handle here
                    | TDI expression TINKUANTU expression TPUI expression compound_statement /// TODO: Handle here
                    ;

jump_statement : TPARA ';'
               | TCONTINUA ';'
               | TDIVOLVI expression ';'
               | TDIVOLVI ';'
               ;
%%

void yyerror(const char* err) {
    std::cerr << "Error: " << err << std::endl;
    std::exit(1);
}

int main(const int argc, const char* const* argv) {
    yyparse();
    if (ProgramBlock != nullptr)
        std::cout << "Not NULL!" << std::endl;
    return 0;
}
