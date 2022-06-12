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
%token <token> TDIVOLVI TDI TPUI
%token <token> TINKUANTU TSI TSINON

%left TPLUS TMINUS
%left TMUL TDIV

%start Program
%debug
%verbose

/* non terminal symbols */

%%

Program : %empty /* TODO: Handle Here */
        | Statements /* TODO: Handle Here */
        ;

Type : TYPE_INT
     | TYPE_DOUBLE
     | TYPE_VOID
     | TYPE_BOOL
     ;

Literal : TINTEGER /* TODO: Handle Here */
        | TDOUBLE /* TODO: Handle Here */
        | TBOOL /* TODO: Handle Here */
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

/// Variables

VariableDeclaration : SingleVariableDeclaration /* TODO: Handle Here */
                    | MultipleVariablesDeclaration /* TODO: Handle Here */
                    ;

SingleVariableDeclaration : Type Identifier /* TODO: Handle Here */
                          | Type VariableAssignment /* TODO: Handle Here */
                          ;

MultipleVariablesDeclaration : Type VariablesList /* TODO: Handle Here */
                             ;

VariablesList : VariablesList ',' Identifier /* TODO: Handle Here */
              | VariablesList ',' VariableAssignment /* TODO: Handle Here */
              | VariableAssignment
              | Identifier
              ;

VariableAssignment : Identifier '=' Expression /* TODO: Handle Here */
                   ;

/// Expressions

Expression : Expression AritmeticOperator Expression /* TODO: Handle Here */
           | Expression ComparativeOperator Expression /* TODO: Handle Here */
           | Expression BooleanOperator Expression /* TODO: Handle Here */
           | FunctionCall /* TODO: Handle Here */
           | Identifier /* TODO: Handle Here */
           | Literal /* TODO: Handle Here */
           ;

/// Functions

FunctionDeclaration : Type Identifier '(' FunctionParameters ')' Block /* TODO: Handle Here */
                    | Type Identifier '(' EmptyOrVoid ')' /* TODO: Handle Here */
                    ;

FunctionParameters : FunctionParameters ',' Type Identifier /* TODO: Handle Here */
                   | Type Identifier /* TODO: Handle Here */
                   ;

FunctionArguments : FunctionArguments ',' Expression /* TODO: Handle Here */
                  | Expression /* TODO: Handle Here */
                  ;

FunctionCall : Identifier '(' FunctionArguments ')' /* TODO: Handle Here */
             | Identifier '(' ')' /* TODO: Handle Here */

/// General Statements

Statements : Statements Statement /* TODO: Handle Here */
           | Statement /* TODO: Handle Here */
           ;

Statement : SingleLineStatement ';' /* TODO: Handle Here */
          | FunctionDeclaration /* TODO: Handle Here */
          | DiLoop /* TODO: Handle Here */
          | InkuantuLoop /* TODO: Handle Here */
          | SiStatement /* TODO: Handle Here */
          ;

SingleLineStatement : VariableDeclaration /* TODO: Handle Here */
                    | VariableAssignment /* TODO: Handle Here */
                    | Expression /* TODO: Handle Here */
                    | ReturnStatement /* TODO: Handle Here */
                    ;

ReturnStatement : TDIVOLVI Expression /* TODO: Handle Here */
                | TDIVOLVI /* TODO: Handle Here */
                ;

Block : '{' Statements '}' /* TODO: Handle Here */
      ;


/// Loops

DiLoop : TDI SingleVariableDeclaration TINKUANTU Expression TPUI VariableAssignment Block /* TODO: Handle Here */
         ;

InkuantuLoop : TINKUANTU Expression Block /* TODO: Handle Here */
             ;

SiStatement : TSI Expression Block /* TODO: Handle Here */
            | TSI Expression TSINON Block /* TODO: Handle Here */
            | TSI Expression TSINON SiStatement /* TODO: Handle Here */
            ;

/// Other

EmptyOrVoid : %empty
            | TYPE_VOID
            ;

%%

void yyerror(const char* err) {
    std::cerr << "Error: " << err << std::endl;
    std::exit(1);
}

