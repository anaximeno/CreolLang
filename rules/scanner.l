%option noyywrap yylineno

%{
    #include "include/creol/ast.hh"

    #include <string>
    #include <cstdio>
    #include <iostream>
    #include <cstring>
    #include "parser.hh"

    #define YYERROR_VERBOSE 1

    #define SAVE_TOKEN     yylval.string  = new std::string(yytext, yyleng)
    #define SAVE_BOOLEAN   yylval.boolean = new std::string(strcmp(yytext, "sim") == 0 ? "1" : "0");
    #define TOKENIZE(sym) (yylval.token   = sym)

    int yyerror(char const*);
%}

INT [+|-]?[0-9]+

FLOAT {INT}\.[0-9]+

IDENT [a-zA-Z_][a-zA-Z0-9_]*

STRING ["]([^"\\\n]|\\.|\\\n)*["]

%%

[ \t\n]         /* ignore */;

"mostra"        return TOKENIZE(T_MOSTRA);
"impristan"     return TOKENIZE(T_IMPRISTAN);
"si"            return TOKENIZE(T_SI);
"sinon"         return TOKENIZE(T_SINON);
"divolvi"       return TOKENIZE(T_DIVOLVI);
"di"            return TOKENIZE(T_DI);
"nkuantu"       return TOKENIZE(T_NKUANTU);
"int"           SAVE_TOKEN;   return T_TYPE_INT;
"float"         SAVE_TOKEN;   return T_TYPE_FLOAT;
"void"          SAVE_TOKEN;   return T_TYPE_VOID;
"bool"          SAVE_TOKEN;   return T_TYPE_BOOL;
"sim"           SAVE_BOOLEAN; return T_BOOL_LIT;
"nau"           SAVE_BOOLEAN; return T_BOOL_LIT;
"para"          return TOKENIZE(T_PARA);
"continua"      return TOKENIZE(T_CONTINUA);
"+"             return TOKENIZE(T_PLUS);
"-"             return TOKENIZE(T_MINUS);
"*"             return TOKENIZE(T_MUL);
"/"             return TOKENIZE(T_DIV);
"("             return TOKENIZE(T_LPAR);
")"             return TOKENIZE(T_RPAR);
"."             return TOKENIZE(T_DOT);
","             return TOKENIZE(T_COMMA);
";"             return TOKENIZE(T_SEMIC);
"{"             return TOKENIZE(T_LCURLY);
"}"             return TOKENIZE(T_RCURLY);
"["             return TOKENIZE(T_LBRAC);
"]"             return TOKENIZE(T_RBRAC);
"="             return TOKENIZE(T_ASSIGN);
"=="            return TOKENIZE(T_EQ);
"!="            return TOKENIZE(T_NE);
">"             return TOKENIZE(T_GT);
">="            return TOKENIZE(T_GE);
"<"             return TOKENIZE(T_LT);
"<="            return TOKENIZE(T_LE);
"&&"            return TOKENIZE(T_AND);
"||"            return TOKENIZE(T_OR);

{INT}           SAVE_TOKEN;   return T_INT_LIT;
{FLOAT}         SAVE_TOKEN;   return T_FLOAT_LIT;
{IDENT}         SAVE_TOKEN;   return T_IDENT;
{STRING}        SAVE_TOKEN;   return T_STR_LIT;

. {
    printf("Creol: Error: line %d, Unknown token '%s'\n", yylineno, yytext);
    /* yyterminate(); */
}

%%
