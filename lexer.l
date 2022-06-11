%option noyywrap yylineno

%{
    #include <string>
    #include <cstdio>
    #include <iostream>
    #define YYERROR_VERBOSE 1
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define SAVE_INTEGER yylval.integer = std::stoll(std::string(yytext, yyleng))
    #define SAVE_NUMBER yylval.number = std::stod(std::string(yytext, yyleng))
    #define SAVE_BOOLEAN yylval.boolean = std::string(yytext, yyleng) == "true" ? 1 : 0
    #define TOKENIZE(sym) (yylval.token = sym)
    int yyerror(char const*);
%}

INTEGER [+|-]?[0-9]+

DOUBLE [+|-]?[0-9]+\.[0-9]+

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

%%

[ \t\n\r]       /* ignore */
"si"            return TOKENIZE(TSI);
"sinon"         return TOKENIZE(TSINON);
"divolvi"       return TOKENIZE(TDIVOLVI);
"di"            return TOKENIZE(TDI);
"ti"            return TOKENIZE(TTI);
"pui"           return TOKENIZE(TPUI);
"nkuantu"       return TOKENIZE(TNKUANTU);
"int"           return TOKENIZE(TYPE_INT);
"double"        return TOKENIZE(TYPE_DOUBLE);
"void"          return TOKENIZE(TYPE_VOID);
"bool"          return TOKENIZE(TYPE_BOOL);
"true"          SAVE_BOOLEAN; return TBOOL;
"false"         SAVE_BOOLEAN; return TBOOL;
{INTEGER}       SAVE_INTEGER; return TINTEGER;
{DOUBLE}        SAVE_NUMBER; return TFLOAT;
{IDENTIFIER}    SAVE_TOKEN; return TIDENTIFIER;
"+"             TOKENIZE_SYMBOL(PLUS); return TPLUS;
"-"             TOKENIZE_SYMBOL(MINUS); return TMINUS;
"*"             TOKENIZE_SYMBOL(MUL); return TMUL;
"/"             TOKENIZE_SYMBOL(DIV); return TDIV;
"("             return '(';
")"             return ')';
"."             return '.';
","             return ',';
"{"             return '{';
"}"             return '}';
"=="            return TOKENIZE(TEQ);
"!="            return TOKENIZE(TNE);
">"             return TOKENIZE(TGT);
">="            return TOKENIZE(TGE);
"<"             return TOKENIZE(TLT);
"<="            return TOKENIZE(TLE);
.               printf("line %d, len %d Unknown token %s !", yylineno, yyleng, yytext); yyterminate();

%%

int yyerror(const char* s) {
    printf("ERR %s in '%s' at line %d\n", s, yytext, yylineno);
    return 1;
}