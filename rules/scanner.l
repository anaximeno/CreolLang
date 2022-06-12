%option noyywrap yylineno

%{
    #include <string>
    #include <cstdio>
    #include <iostream>
    #include "parser.hh"
    #define YYERROR_VERBOSE 1
    #define SAVE_TOKEN     yylval.string  = new std::string(yytext, yyleng)
    #define SAVE_INTEGER   yylval.integer = std::stoll(std::string(yytext, yyleng))
    #define SAVE_NUMBER    yylval.floatingp  = std::stod(std::string(yytext, yyleng))
    #define SAVE_BOOLEAN   yylval.boolean = std::string(yytext, yyleng) == "sim" ? 1 : 0
    #define TOKENIZE(sym) (yylval.token   = sym)
    int yyerror(char const*);
%}

INTEGER [+|-]?[0-9]+

FLOAT [+|-]?[0-9]+\.[0-9]+

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n\r]       /* ignore */
"si"            return TOKENIZE(TSI);
"sinon"         return TOKENIZE(TSINON);
"divolvi"       return TOKENIZE(TDIVOLVI);
"di"            return TOKENIZE(TDI);
"pui"           return TOKENIZE(TPUI);
"inkuantu"      return TOKENIZE(TINKUANTU);
"int"           return TOKENIZE(TYPE_INT);
"float"         return TOKENIZE(TYPE_FLOAT);
"void"          return TOKENIZE(TYPE_VOID);
"bool"          return TOKENIZE(TYPE_BOOL);
"sim"           SAVE_BOOLEAN; return TBOOL;
"nau"           SAVE_BOOLEAN; return TBOOL;
{INTEGER}       SAVE_INTEGER; return TINTEGER;
{FLOAT}         SAVE_NUMBER; return TFLOAT;
{IDENTIFIER}    SAVE_TOKEN; return TIDENTIFIER;
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
.               printf("line %d, len %d Unknown token %s !", yylineno, yyleng, yytext); yyterminate();

%%