%{
    #include <cstdio>
    #include <cstdlib>
    #include <iostream>
    extern int yylex();
    void yyerror(const char* err);
%}

%union {
    std::string* string;
    long long integer;
    double number;
    int boolean;
    int token;
}

/* terminal symbols */
%token <string>  TIDENTIFIER
%token <integer> TINTEGER
%token <number>  TDOUBLE
%token <boolean> TBOOL
%token <token>  TPLUS TMINUS TMUL TDIV
%token <token>  TEQ  TNE  TLT TLE TGT TGE
%token <token>  TAND TOR
%token <token> TYPE_INT TYPE_DOUBLE TYPE_BOOL TYPE_VOID
%token <token> TDIVOLVI TDI TTI TPUI
%token <token> TINKUANTU TSI TSINON

%left TPLUS TMINUS
%left TMUL TDIV

%start Program
%debug
%verbose

/* non terminal symbols */

%%

Type : TYPE_INT
     | TYPE_DOUBLE
     | TYPE_VOID
     | TYPE_BOOL
     ;

Literal : TINTEGER
        | TDOUBLE
        | TBOOL
        ;

Identifier : TIDENTIFIER
           ;

BooleanOperator : TAND
                | TOR
                ;

AritmeticOperator : TPLUS
                  | TMINUS
                  | TMUL
                  | TDIV
                  ;

ComparativeOperator : TLT
                    | TLE
                    | TGT
                    | TGE
                    | TEQ
                    | TNE
                    ;

VariableDeclaration : Type Declarations
                    ;

Declarations : Declarations ',' Declaration
             | Declaration
             ;

Declaration : Identifier
            | Identifier '=' Expression
            ;

Expression : Expression AritmeticOperator Expression
           | Expression ComparativeOperator Expression
           | Expression BooleanOperator Expression
           | Identifier
           | Identifier '(' FunctionArguments ')'
           | Identifier '(' ')'
           | Literal
           ;

FunctionArguments : FunctionArguments ',' Expression
                  | Expression
                  ;

FunctionDeclaration : Type Identifier '(' FunctionParameters ')' Block
                    | Type Identifier '(' NoFunctionParameters ')'
                    ;

NoFunctionParameters : %empty
                     | TYPE_VOID
                     ;

FunctionParameters : FunctionParameters ',' Type Identifier
                   | Type Identifier
                   ;

Block : '{' Statements '}'
      | '{' Statements ReturnStatement '}'
      ;

ReturnStatement : TDIVOLVI Expression ';'
                | TDIVOLVI NoReturnValue ';'
                ;

NoReturnValue : NoFunctionParameters
              ;

Statements : Statements Statement
           | Statement
           ;

Statement : SingleLineStatement ';'
          | FunctionDeclaration
          | DiTiLoop
          | InkuantuLoop
          | SiStatement
          ;

SingleLineStatement : VariableDeclaration
                    | Declaration
                    | Expression
                    ;

DiTiLoop : TDI DiTiLoopInitStatement TTI Expression TPUI Declaration Block
         ;

DiTiLoopInitStatement : Type Identifier '=' Expression
                      | Identifier '=' Expression
                      ;

InkuantuLoop : TINKUANTU Expression Block
             ;

SiStatement : TSI Expression Block
            | TSI Expression TSINON Block
            | TSI Expression TSINON SiStatement
            ;

Program : %empty
        | Statements
        ;
%%

void yyerror(const char* err) {
    std::cerr << "Error: " << err << std::endl;
    std::exit(1);
}

