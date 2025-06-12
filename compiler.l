%{
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "compiler.tab.h"
extern int yylineno;
extern char currentLineText[1024];
extern int currentPos;

#define YY_USER_ACTION { \
    for (int i = 0; i < yyleng; i++) { \
        if (yytext[i] == '\n') { \
            currentLineText[currentPos] = '\0'; \
            currentPos = 0; \
        } else if (currentPos < 1023) { \
            currentLineText[currentPos++] = yytext[i]; \
            currentLineText[currentPos] = '\0'; \
        } \
    } \
}
%}

%%

"if"            { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return IF; }
"elif"          { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return ELIF; }
"else"          { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return ELSE; }
"while"         { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return WHILE; }
"return"        { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return RETURN; }
"pass"          { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return TOKEN_PASS; }
"is"            { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return IS; }
"and"           { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return AND; }
"or"            { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return OR; }
"not"           { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return NOT; }
"def"           { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return DEF; }
"print"         { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return PRINT; }
"__main__"      { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return MAIN_ID; }

"bool"|"int"|"string"|"float" {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return TOKEN_TYPE;
}

"True"|"False" {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return BOOL_LIT;
}

[0-9]+\.[0-9]+ {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return FLOAT_LIT;
}

0|[1-9][0-9]* {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return INT_LIT;
}

0[xX][0-9a-fA-F]+ {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return HEX_LIT;
}

\"[^"\n]*\" {
    currentPos += strlen(yytext);
    yylval.n = mknode(strdup(yytext), NULL, NULL);
    return STRING_LIT;
}

\'[^'\n]*\' {
    currentPos += strlen(yytext);
    yylval.n = mknode(strdup(yytext), NULL, NULL);
    return STRING_LIT;
}


[a-zA-Z][a-zA-Z0-9_]* {
    currentPos += strlen(yytext);
    yylval.n = mknode(strdup(yytext), NULL, NULL);
    return ID;
}

_[a-zA-Z0-9][a-zA-Z0-9_]* {
    currentPos += strlen(yytext);
    yylval.n = mknode(strdup(yytext), NULL, NULL);
    return ID;
}

__[a-zA-Z0-9][a-zA-Z0-9_]* {
    currentPos += strlen(yytext);
    yylval.n = mknode(strdup(yytext), NULL, NULL);
    return ID;
}

___[a-zA-Z0-9_]* {
    printf("Lexical error: invalid identifier starting with more than 2 underscores: %s\n", yytext);
    exit(1);
}

"=="|"!="|"<"|">"|"<="|">=" {
    currentPos += strlen(yytext); 
    yylval.n = mknode(strdup(yytext), NULL, NULL); 
    return REL_OP;
}

"**"            { currentPos += strlen(yytext); yylval.n = mknode(strdup(yytext), NULL, NULL); return POW; }
"+"             { currentPos += strlen(yytext); return '+'; }
"-"             { currentPos += strlen(yytext); return '-'; }
"*"             { currentPos += strlen(yytext); return '*'; }
"/"             { currentPos += strlen(yytext); return '/'; }

"->"            { currentPos += strlen(yytext); return ARROW; }
";"             { currentPos += strlen(yytext); return ';'; }
","             { currentPos += strlen(yytext); return ','; }
":"             { currentPos += strlen(yytext); return ':'; }
"="             { currentPos += strlen(yytext); return '='; }
"("             { currentPos += strlen(yytext); return '('; }
")"             { currentPos += strlen(yytext); return ')'; }
"["             { currentPos += strlen(yytext); return '['; }
"]"             { currentPos += strlen(yytext); return ']'; }
"{"             { currentPos += strlen(yytext); return '{'; }
"}"             { currentPos += strlen(yytext); return '}'; }

\#[^\n]*        { currentPos += strlen(yytext); }

[ \t\r]+        { currentPos += strlen(yytext); }

\n              { 
    yylineno++; 
    currentLineText[0] = '\0';
    currentPos = 0; 
}

. { 
    printf("Lexical error: invalid character '%c' at line %d, position %d\n", 
           yytext[0], yylineno, currentPos);
    exit(1); 
}

%%

int yywrap() { 
    return 1; 
}