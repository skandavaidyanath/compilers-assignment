%{
#include "y.tab.h"
#include<stdio.h>
%}


%%

[gG][eE][tT] {strcat(yylval.string, yytext); return GET;}
[aA][nN][dD] {strcat(yylval.string, yytext); return AND;}
[oO][rR] {strcat(yylval.string, yytext); return OR;}
[fF][rR][oO][mM] {strcat(yylval.string, yytext); return FROM;}
[uU][pP][dD][aA][tT][eE] {strcat(yylval.string, yytext); return UPDATE;}
[dD][eE][lL][eE][tT][eE] {strcat(yylval.string, yytext); return DELETE;}
[rR][eE][cC][oO][rR][dD] {strcat(yylval.string, yytext); return RECORD;}
[wW][hH][eE][rR][eE] {strcat(yylval.string, yytext); return WHERE;}
[iI][nN][sS][eE][rR][tT] {strcat(yylval.string, yytext); return INSERT;}
[sS][eE][tT] {strcat(yylval.string, yytext); return SET;}
[iI][nN] {strcat(yylval.string, yytext); return IN;}
[tT][oO] {strcat(yylval.string, yytext); return TO;}
[iI][nN][tT][oO] {strcat(yylval.string, yytext); return INTO;}
[A-Za-z_][a-zA-Z_0-9$]* {strcat(yylval.string, yytext); return FIELD;}
[A-Za-z_][a-zA-Z_0-9$]*".txt" {strcat(yylval.string, yytext); return FILENAME;}
\"(\\.|[^"\\])*\" {strcat(yylval.string, yytext); return STRING_CONSTANT;}
['-']?[0-9]+(['.'][0-9]+)? {strcat(yylval.string, yytext); return CONSTANT;}
[ ] {strcat(yylval.string, yytext);}
[\r\n\t] {}
[,<>=!;()] {strcat(yylval.string, yytext); return yytext[0];}
. {printf("LEXICAL ERROR. TERMINATING."); yyterminate();}

%%



