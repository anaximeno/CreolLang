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
    float floatingp;
    unsigned short boolean;
    int token;
}

/* terminal symbols */
%token<string> TIDENTIFIER
%token<integer> TINTEGER
%token<floatingp> TFLOAT
%token<boolean> TBOOL
%token<token>  TPLUS TMINUS TMUL TDIV
%token<token>  TEQ  TNE  TLT TLE TGT TGE
%token<token>  TAND TOR
%token<string> TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_VOID
%token<token>  TDIVOLVI TDI TPUI
%token<token>  TINKUANTU TSI TSINON

%right '='
%left TPLUS TMINUS
%left TMUL TDIV
%nonassoc UMINUS

%start Program
%debug
%verbose

/* non terminal symbols */

%%

program : statements /* TODO: Handle Here */
        ;

type : TYPE_INT
     | TYPE_FLOAT
     | TYPE_VOID
     | TYPE_BOOL
     ;

literal : TINTEGER /* TODO: Handle Here */
        | TFLOAT /* TODO: Handle Here */
        | TBOOL /* TODO: Handle Here */
        ;

identifier : TIDENTIFIER
           ;

boolean_operator : TAND
                | TOR
                ;

aritmetic_operator : TPLUS
                  | TMINUS
                  | TMUL
                  | TDIV
                  ;

comparative_operator : TLT
                    | TLE
                    | TGT
                    | TGE
                    | TEQ
                    | TNE
                    ;

/// Variables

variable_declaration : single_variable_declaration /* TODO: Handle Here */
                    | multiple_variables_declaration /* TODO: Handle Here */
                    ;

single_variable_declaration : type identifier /* TODO: Handle Here */
                          | type variable_assignment /* TODO: Handle Here */
                          ;

multiple_variables_declaration : type variables_list /* TODO: Handle Here */
                             ;

variables_list : variables_list ',' identifier /* TODO: Handle Here */
              | variables_list ',' variable_assignment /* TODO: Handle Here */
              | variable_assignment
              | identifier
              ;

variable_assignment : identifier '=' expression /* TODO: Handle Here */
                   ;

/// Expressions

expression : expression aritmetic_operator expression /* TODO: Handle Here */
           | expression comparative_operator expression /* TODO: Handle Here */
           | expression boolean_operator expression /* TODO: Handle Here */
           | function_call /* TODO: Handle Here */
           | identifier /* TODO: Handle Here */
           | literal /* TODO: Handle Here */
           ;

/// Functions

function_declaration : type identifier '(' function_parameters ')' block /* TODO: Handle Here */
                    | type identifier '(' empty_or_void ')' /* TODO: Handle Here */
                    ;

function_parameters : function_parameters ',' type identifier /* TODO: Handle Here */
                   | type identifier /* TODO: Handle Here */
                   ;

function_arguments : function_arguments ',' expression /* TODO: Handle Here */
                  | expression /* TODO: Handle Here */
                  ;

function_call : identifier '(' function_arguments ')' /* TODO: Handle Here */
             | identifier '(' ')' /* TODO: Handle Here */

/// General Statements

statements : statements Statement /* TODO: Handle Here */
           | Statement /* TODO: Handle Here */
           ;

Statement : single_line_statement /* TODO: Handle Here */
          | function_declaration /* TODO: Handle Here */
          | di_loop /* TODO: Handle Here */
          | inkuantu_loop /* TODO: Handle Here */
          | si_statement /* TODO: Handle Here */
          ;

single_line_statement : variable_declaration ';' /* TODO: Handle Here */
                    | variable_assignment ';' /* TODO: Handle Here */
                    | expression ';' /* TODO: Handle Here */
                    | ReturnStatement ';'/* TODO: Handle Here */
                    | %empty    /* TODO: Handle Here */ 
                    | ';'
                    ;

ReturnStatement : TDIVOLVI expression /* TODO: Handle Here */
                | TDIVOLVI /* TODO: Handle Here */
                ;

block : '{' statements '}' /* TODO: Handle Here */
      ;


/// Loops

di_loop : TDI di_loop_start TINKUANTU expression TPUI variable_assignment block /* TODO: Handle Here */
       ;

di_loop_start : single_variable_declaration
            | variable_assignment
            ;

inkuantu_loop : TINKUANTU expression block /* TODO: Handle Here */
             ;

si_statement : TSI expression block /* TODO: Handle Here */
            | TSI expression TSINON block /* TODO: Handle Here */
            | TSI expression TSINON si_statement /* TODO: Handle Here */
            ;

/// Other

empty_or_void : %empty
            | TYPE_VOID
            ;

%%

void yyerror(const char* err) {
    std::cerr << "Error: " << err << std::endl;
    std::exit(1);
}

int main(int argc, char** argv) {
    yyparse();
    return 0;
}