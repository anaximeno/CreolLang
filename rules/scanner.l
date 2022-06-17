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

INT [+|-]?[0-9]+

FLOAT {INT}\.[0-9]+

/* Identifier RegEx */
IDF [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n]         /* ignore */;
"si"            return TOKENIZE(TSI);
"sinon"         return TOKENIZE(TSINON);
"divolvi"       return TOKENIZE(TDIVOLVI);
"di"            return TOKENIZE(TDI);
"pui"           return TOKENIZE(TPUI);
"inkuantu"      return TOKENIZE(TINKUANTU);
"int"           SAVE_TOKEN;   return TYPE_INT;
"float"         SAVE_TOKEN;   return TYPE_FLOAT;
"void"          SAVE_TOKEN;   return TYPE_VOID;
"bool"          SAVE_TOKEN;   return TYPE_BOOL;
"sim"           SAVE_BOOLEAN; return BOOL;
"nau"           SAVE_BOOLEAN; return BOOL;
"para"          return TOKENIZE(TPARA);
"continua"      return TOKENIZE(TCONTINUA);
{INT}           SAVE_INTEGER; return INTEGER;
{FLOAT}         SAVE_NUMBER;  return FLOAT;
{IDF}           SAVE_TOKEN;   return TIDENTIFIER;
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
.               printf("line %d, Unknown token %s !\n", yylineno, yytext); yyterminate();

%%
