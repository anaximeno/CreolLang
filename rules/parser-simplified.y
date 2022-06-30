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

    static creol::BlockAST* ProgramBlock;
%}

%union {
    int token;
    std::string* string;
    float floatingpoint;
    creol::BlockAST* block;
    creol::ExprAST* expr;
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

%left TLT TGT TLE TGE TEQ TNE '='
%left TPLUS TMINUS
%left TMUL TDIV
%left UMINUS

%start program

%debug
%verbose


%%

/* non terminals */

program : statements /* TODO: Handle Here */
        ;

type_specifier : TYPE_FLOAT
               ;

constant : FLOAT /* TODO: Handle Here */
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
initializer : expression ;

expression : assignment_expression
           | function_call
           ;

constant_expression : logical_or_expressions
                    ;

logical_or_expressions : logical_and_expressions
                       | logical_or_expressions TOR logical_and_expressions
                       ;

logical_and_expressions : equality_expression
                        | logical_and_expressions TAND equality_expression
                        ;

equality_expression : relational_expression
                    | equality_expression TEQ relational_expression
                    | equality_expression TNE relational_expression
                    ;

relational_expression : additive_expression
                      | relational_expression TLT additive_expression
                      | relational_expression TGT additive_expression
                      | relational_expression TLE additive_expression
                      | relational_expression TGE additive_expression
                      ;

additive_expression : multiplicative_expression
                    | additive_expression TPLUS multiplicative_expression
                    | additive_expression TMINUS multiplicative_expression
                    ;

multiplicative_expression : unary_expression
                          | multiplicative_expression TMUL primary_expression
                          | multiplicative_expression TDIV primary_expression
                          ;

unary_expression : primary_expression
                 | TMINUS primary_expression %prec UMINUS
                 ;

primary_expression : identifier
                   | constant
                   | '(' expression ')'
                   ;

// todo: correct anomalies using semantic analysis
assignment_expression : constant_expression
                      | primary_expression assignment_operator assignment_expression
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

function_call : identifier '(' argument_list ')' /* TODO: Handle Here */
              | identifier '(' ')' /* TODO: Handle Here */

statements : statements statement /* TODO: Handle Here */
           | statement /* TODO: Handle Here */
           ;

// todo: analyze the situation of
// functions declared inside other functions
// and the use of declarations in the global
// scope.
statement : expression_statement
          | compound_statement
          | selection_statement
          | iteration_statement
          | jump_statement
          | function_declaration
          | declaration
          ;

expression_statement : expression ';'
                     | ';'
                     ;

compound_statement : '{' statement '}'
                   | '{' '}'
                   ;

selection_statement : TSI expression compound_statement
                    | TSI expression compound_statement TSINON compound_statement
                    ; // TODO: Add else if

iteration_statement : TINKUANTU expression compound_statement
                    | TDI expression TINKUANTU expression TPUI expression compound_statement;

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
    return 0;
}