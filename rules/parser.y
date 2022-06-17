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
%token<integer> INTEGER
%token<floatingp> FLOAT
%token<boolean> BOOL
%token<token>  TPLUS TMINUS TMUL TDIV
%token<token>  TEQ  TNE  TLT TLE TGT TGE
%token<token>  TAND TOR
%token<string> TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_VOID
%token<token>  TDIVOLVI TDI TPUI
%token<token>  TINKUANTU TSI TSINON
%token<token> TPARA TCONTINUA

%right '='
%left TPLUS TMINUS
%left TMUL TDIV
%nonassoc UMINUS

%start program
%debug
%verbose

/* non terminal symbols */

%%

program : statements /* TODO: Handle Here */
        ;

type_specifier : TYPE_INT
               | TYPE_FLOAT
               | TYPE_VOID
               | TYPE_BOOL
               ;

constant : INTEGER /* TODO: Handle Here */
         | FLOAT /* TODO: Handle Here */
         | BOOL /* TODO: Handle Here */
         ;

identifier : TIDENTIFIER
           ;

// note: declator may be extended later
declarator : identifier ;

declaration : type_specifier init_declarator ;

init_declarator : declarator
                | declarator '=' initializer;

// note: may be extended later
initializer : expression ;

expression : constant_expression
           | function_call
           ;

constant_expression : logical_or_expressions ;

logical_or_expressions : logical_and_expressions
                       | logical_or_expressions TOR logical_and_expressions;

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

multiplicative_expression : primary_expression
                          | multiplicative_expression TMUL primary_expression
                          | multiplicative_expression TDIV primary_expression
                          ;

primary_expression : identifier
                   | constant
                   | '(' expression ')'
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

compound_statement : '{' declaration statement '}'
                   | '{' statement '}'
                   | '{' declaration '}'
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

int main(int argc, char** argv) {
    yyparse();
    return 0;
}