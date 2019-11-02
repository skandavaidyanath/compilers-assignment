%{
#include<stdio.h>
#include "y.tab.h"
%}


%%

[gG][eE][tT] {return GET;}
[aA][nN][dD] {return AND;}
[oO][rR] {return OR;}
[fF][rR][oO][mM] {return FROM;}
[uU][pP][dD][aA][tT][eE] {return UPDATE;}
[dD][eE][lL][eE][tT][eE] {return DELETE;}
[rR][eE][cC][oO][rR][dD] {return RECORD;}
[wW][hH][eE][rR][eE] {return WHERE;}
[iI][nN][sS][eE][rR][tT] {return INSERT;}
[sS][eE][tT] {return SET;}
[iI][nN] {return IN;}
[tT][oO] {return TO;}
[iI][nN][tT][oO] {return INTO;}
[A-Za-z_][a-zA-Z_0-9$]* {return FIELD;}
[A-Za-z_][a-zA-Z_0-9$]*".txt" {return FILENAME;}
\"(\\.|[^"\\])*\" {return STRING_CONSTANT;}
['-']?[0-9]+(['.'][0-9]+)? {return CONSTANT;}
[ \n\t] {}
[,<>=!;()] {return yytext[0];}
. {printf("LEXICAL ERROR. TERMINATING."); yyterminate();}

%%