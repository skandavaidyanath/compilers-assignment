%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int yylex(void);
void yyerror(char *);
%}

%token GET
%token AND
%token OR
%token FROM
%token UPDATE
%token DELETE
%token RECORD
%token FIELD
%token FILENAME
%token IN
%token INTO
%token WHERE
%token SET
%token INSERT
%token CONSTANT
%token STRING_CONSTANT
%token TO


%%

STMTS: STMT STMTS |
       STMT
;
STMT: GET_STMT {printf("get\n");}| 
      INSERT_STMT {printf("insert\n");}| 
      UPDATE_STMT {printf("update\n");}| 
      DELETE_STMT {printf("delete\n");}
;
FIELD_LIST: FIELD_LIST ',' FIELD | 
            FIELD {printf("field_list\n");}
;
CONDITION: FIELD '=''=' CONSTANT | 
           FIELD '=''=' STRING_CONSTANT |
	       FIELD '!''=' CONSTANT | 
           FIELD '!''=' STRING_CONSTANT |
	       FIELD '>''=' CONSTANT | 
           FIELD '<''=' CONSTANT |
	       FIELD '>' CONSTANT | 
           FIELD '<' CONSTANT
;
CONDITION_LIST: CONDITION_LIST AND CONDITION | 
                CONDITION_LIST OR CONDITION| 
                CONDITION {printf("condition_list\n");}
;
GET_STMT: GET FIELD_LIST FROM FILENAME WHERE CONDITION_LIST';' | 
          GET FIELD_LIST FROM FILENAME';'
;
VALUE: CONSTANT | 
       STRING_CONSTANT
;
VALUE_LIST: VALUE_LIST ',' VALUE | 
            VALUE
;
INSERT_STMT: INSERT RECORD '('VALUE_LIST')' INTO FILENAME';'
;
UPDATE_STMT: UPDATE RECORD IN FILENAME SET FIELD TO VALUE';' | 
             UPDATE RECORD IN FILENAME SET FIELD TO VALUE WHERE CONDITION_LIST';'
;
DELETE_STMT: DELETE RECORD FROM FILENAME';' | 
             DELETE RECORD FROM FILENAME WHERE CONDITION_LIST';'
;

%%

int main(int argc, char *argv[])
{
	yyparse();
	if(!yyparse)
	{
		printf("Parse Error\n");

	return 0;

	}
}
