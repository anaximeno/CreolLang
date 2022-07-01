%option noyywrap yylineno

%{
    #include "include/creol.hh"

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

"mostra"        return TOKENIZE(TMOSTRA);
"impristan"     return TOKENIZE(TIMPRISTAN);


[ \t\n]         /* ignore */;
"si"            return TOKENIZE(TSI);
"sinon"         return TOKENIZE(TSINON);
"divolvi"       return TOKENIZE(TDIVOLVI);
"di"            return TOKENIZE(TDI);
"inkuantu"      return TOKENIZE(TINKUANTU);
"int"           SAVE_TOKEN;   return TYPE_INT;
"float"         SAVE_TOKEN;   return TYPE_FLOAT;
"void"          SAVE_TOKEN;   return TYPE_VOID;
"bool"          SAVE_TOKEN;   return TYPE_BOOL;
"sim"           SAVE_BOOLEAN; return BOOL;
"nau"           SAVE_BOOLEAN; return BOOL;
"para"          return TOKENIZE(TPARA);
"continua"      return TOKENIZE(TCONTINUA);
"+"             return TOKENIZE(TPLUS);
"-"             return TOKENIZE(TMINUS);
"*"             return TOKENIZE(TMUL);
"/"             return TOKENIZE(TDIV);
"("             return '(';
")"             return ')';
"."             return '.';
","             return ',';
";"             return ';';
"{"             return '{';
"}"             return '}';
"="             return '=';
"=="            return TOKENIZE(TEQ);
"!="            return TOKENIZE(TNE);
">"             return TOKENIZE(TGT);
">="            return TOKENIZE(TGE);
"<"             return TOKENIZE(TLT);
"<="            return TOKENIZE(TLE);
"ii"            return TOKENIZE(TAND);
"ou"            return TOKENIZE(TOR);
{INT}           SAVE_TOKEN;   return INTEGER;
{FLOAT}         SAVE_TOKEN;   return FLOAT;
{IDENT}         SAVE_TOKEN;   return TIDENTIFIER;
{STRING}        SAVE_TOKEN;   return STR;
.               printf("Creol: Error: line %d, Unknown token '%s'\n", yylineno, yytext); /* yyterminate(); */

%%
