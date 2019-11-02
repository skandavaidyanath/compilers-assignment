/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<ctype.h>
#include<strings.h>

int yylex(void);
void yyerror(char *);

typedef struct Employee{
    int eid;
    char ename[25];
    int eage;
    char eaddress[100];
    int salary;
    int deptno;
}Employee;

typedef struct Department{
    int dnum;
    char dname[50];
    char dlocation[50];
}Department;

void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

void remove_extra_line(char filename[])
{
    int chars_to_delete = 2;
    FILE *fp = fopen(filename, "r+");
    fseeko(fp, -chars_to_delete, SEEK_END);
    int position = ftello(fp);
    ftruncate(fileno(fp), position);
    fclose(fp);
}

bool isNumber(char s[])
{
    int i=0;
    while(s[i]!='\0')
    {
        if (isdigit(s[i]) == false)
            return false;
        i++;
    }
    return true;
}

void add_extra_line(char filename[])
{
    FILE *fp = fopen(filename, "a+");
    fprintf(fp, "\r\n");
    fclose(fp);
}

void d_evaluate(int results[], char condition[], Department records[], int num_records)
{
    int i = 0;
    int flag; //0 for ==, 1 for !=, 2 for >, 3 for <, 4 for >=, 5 for <=
    for(; i < strlen(condition); i++)
    {
        if(condition[i] == '!')
        {
            flag = 1;
            break;
        }
        if(condition[i] == '=')
        {
            flag = 0;
            break;
        }
        if(condition[i] == '>')
        {
            if(condition[i+1] == '=')
            {
                flag = 4;
                break;
            }
            flag = 2;
            break;
       }
       if(condition[i] == '<')
       {
            if(condition[i+1] == '=')
            {
                flag = 5;
                break;
            }
            flag = 3;
            break;
       }

    }
    char *field;
    char *string_value;
    int value;
    if(flag == 0)
    {
        field = strtok(condition, "=");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        if(string_value[0] != '"')
            value = atoi(string_value);
        remove_all_chars(string_value, '"');
    }
    if(flag == 1)
    {
        field = strtok(condition, "!");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        if(string_value[0] != '"')
            value = atoi(string_value);
        remove_all_chars(string_value, '"');
    }
    if(flag == 2)
    {
        field = strtok(condition, ">");
        string_value = strtok(NULL, ">");
		if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 3)
    {
        field = strtok(condition, "<");
        string_value = strtok(NULL, "<");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 4)
    {
        field = strtok(condition, ">");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 5)
    {
        field = strtok(condition, "<");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    for(i=0; i<num_records; i++)
    {
        switch(flag)
        {
            case 0:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum == value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "dname") == 0)
                {
                    if(strcasecmp(records[i].dname, string_value) == 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "dlocation") == 0)
                {
                    if(strcasecmp(records[i].dlocation, string_value) == 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
           case 1:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum != value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "dname") == 0)
                {
                    if(strcasecmp(records[i].dname, string_value) != 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "dlocation") == 0)
                {
                    if(strcasecmp(records[i].dlocation, string_value) != 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 2:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum > value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 3:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum < value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 4:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum >= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 5:
                if(strcmp(field, "dnum") == 0)
                {
                    if(records[i].dnum <= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
        }
    }
}

void e_evaluate(int results[], char condition[], Employee records[], int num_records)
{
    int i = 0;
    int flag; //0 for ==, 1 for !=, 2 for >, 3 for <, 4 for >=, 5 for <=
    for(; i < strlen(condition); i++)
    {
        if(condition[i] == '!')
        {
            flag = 1;
            break;
        }
        if(condition[i] == '=')
        {
            flag = 0;
            break;
        }
        if(condition[i] == '>')
        {
            if(condition[i+1] == '=')
            {
                flag = 4;
                break;
            }
            flag = 2;
            break;
       }
       if(condition[i] == '<')
       {
            if(condition[i+1] == '=')
            {
                flag = 5;
                break;
            }
            flag = 3;
            break;
       }
    }
    char *field;
    char *string_value;
    int value;
    if(flag == 0)
    {
        field = strtok(condition, "=");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        if(string_value[0] != '"')
            value = atoi(string_value);
        remove_all_chars(string_value, '"');
    }
    if(flag == 1)
    {
        field = strtok(condition, "!");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        if(string_value[0] != '"')
            value = atoi(string_value);
        remove_all_chars(string_value, '"');
    }
    if(flag == 2)
    {
        field = strtok(condition, ">");
        string_value = strtok(NULL, ">");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 3)
    {
        field = strtok(condition, "<");
        string_value = strtok(NULL, "<");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 4)
    {
        field = strtok(condition, ">");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    if(flag == 5)
    {
        field = strtok(condition, "<");
        string_value = strtok(NULL, "=");
        if(string_value[strlen(string_value)-1] == ';')
            string_value[strlen(string_value)-1] = '\0';
        value = atoi(string_value);
    }
    for(i=0; i<num_records; i++)
    {
        switch(flag)
        {
            case 0:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid == value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "ename") == 0)
                {
                    if(strcasecmp(records[i].ename, string_value) == 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage == value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eaddress") == 0)
                {
                    if(strcasecmp(records[i].eaddress, string_value) == 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary == value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno == value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;

           case 1:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid != value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "ename") == 0)
                {
                    if(strcasecmp(records[i].ename, string_value) != 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage != value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eaddress") == 0)
                {
                    if(strcasecmp(records[i].eaddress, string_value) != 0)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary != value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno != value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 2:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid > value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage > value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary > value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno > value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 3:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid < value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage < value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary < value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno < value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 4:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid >= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage >= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary >= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno >= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
            case 5:
                if(strcmp(field, "eid") == 0)
                {
                    if(records[i].eid <= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "eage") == 0)
                {
                    if(records[i].eage <= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "salary") == 0)
                {
                    if(records[i].salary <= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                if(strcmp(field, "deptno") == 0)
                {
                    if(records[i].deptno <= value)
                    {
                        continue;
                    }
                    results[i] = -1;
                }
                break;
        }
    }
}

int removeDuplicates(int arr[], int n)
{
    if (n==0 || n==1)
        return n;
    int temp[n];
    int j = 0;
    int i;
    for (i=0; i<n-1; i++)
        if (arr[i] != arr[i+1])
            temp[j++] = arr[i];
    temp[j++] = arr[n-1];
    for (i=0; i<j; i++)
        arr[i] = temp[i];
    return j;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

void insert(char command[])
{
    int commas = 0;
    int i=0;
	for(;i<strlen(command);i++)
	{
		if(command[i] == ',')
		{
			commas++;
		}
	}
	char *token = strtok(command, "(");
    char* record = strtok(NULL, ")");
    token = strtok(NULL, " ");
    char* file_name = strtok(NULL, " ");
    if(strcmp(file_name, "emp.txt;") == 0)
    {
        char fields[6][100];
        if(commas != 5)
            printf("Incorrect Record!");
        else
        {
            for(i = 0; i <= strlen(record); i++)
            {
                if(record[i] == ',')
                {
                    record[i] = ' ';
                }
            }
            remove_all_chars(record, '"');
            i=0;
            char *copyRecord;
            copyRecord = malloc(strlen(record)*sizeof(char)+1);
            strcpy(copyRecord, record);
            char myString[1000];
            char eids[100];
            FILE* fp;
            char c;
            int n = 0;
            fp = fopen("emp.txt" , "r");
            while(fgets(myString, 1000, fp) != NULL)
            {
                int jj = -1;
                while(++jj < strlen(myString))
                {
                    if ((c = myString[jj]) != ' ')
                        break;
                }
                eids[n]=c;
                n++;
            }
            eids[n]='\0';
            fclose(fp);
            int flag=0;
            for(i=0;i<strlen(eids);i++)
            {
                if(copyRecord[0]==eids[i])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
                printf("Eid already present!");
            else
            {
                char* field = strtok(record, " ");
                i=0;
                while(field != NULL)
                {
                    strcpy(fields[i++],field);
                    field = strtok(NULL, " ");
                }
                int num_fields = i;
                if(isNumber(fields[0])&&isNumber(fields[2])&&isNumber(fields[4])&&isNumber(fields[5]))
                {
                    FILE *fp = fopen("emp.txt", "a+");
                    fprintf(fp, "%s", copyRecord);
                    fprintf(fp, "\r\n");
                    fclose(fp);
                }
                else
                {
                    printf("Record entered in the wrong format!");
                }
            }
        }
    }
    else if(strcmp(file_name, "dept.txt;") == 0)
    {
        char fields[3][100];
        if(commas != 2)
            printf("Incorrect Record!");
        else
        {
            for(i = 0; i <= strlen(record); i++)
            {
                if(record[i] == ',')
                {
                    record[i] = ' ';
                }
            }
            remove_all_chars(record, '"');
            i=0;
            char *copyRecord;
            copyRecord = malloc(strlen(record)*sizeof(char)+1);
            strcpy(copyRecord, record);
			char myString[1000];
            char deptids[100];
            FILE* fp;
            char c;
            int n = 0;
            fp = fopen("dept.txt" , "r");
            while(fgets(myString, 1000, fp) != NULL)
            {
                int jj = -1;
                while(++jj < strlen(myString))
                {
                    if ((c = myString[jj]) != ' ')
                        break;
                }
                deptids[n]=c;
                n++;
            }
            deptids[n]='\0';
            fclose(fp);
            int flag=0;
            for(i=0;i<strlen(deptids);i++)
            {
                if(copyRecord[0]==deptids[i])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
                printf("Deptid already present!");
            else
            {
				char* field = strtok(record, " ");
				i=0;
				while(field != NULL)
				{
					strcpy(fields[i++],field);
					field = strtok(NULL, " ");
				}
				int num_fields = i;
				if(isNumber(fields[0]))
				{
					FILE *fp = fopen("dept.txt", "a+");
					fprintf(fp, "%s", copyRecord);
					fprintf(fp, "\r\n");
					fclose(fp);
				}
				else
				{
					printf("Record entered in the wrong format!");
				}
			}
		}
	}
}

void delete_record(char command[])
{
	char array[100][100];   //the command delimited by space, array[0] = DELETE RECORD FROM, array[1] = filename....
	int i = 0;
	char *token = strtok(command, " ");
	while(token != NULL)
	{
		strcpy(array[i++],token);
		token = strtok(NULL, " ");
	}
	int len_array = i;
	i=0;
	char flag;  //emp.txt or dept.txt
	char filename[20];
	if((strcasecmp(array[3], "emp.txt") == 0) || (strcasecmp(array[3], "emp.txt;") == 0))
	{
	    flag = 'e';
	    strcpy(filename,"emp.txt");
	}
	else if((strcasecmp(array[3], "dept.txt") == 0) || (strcasecmp(array[3], "dept.txt;") == 0))
	{
	    flag = 'd';
	    strcpy(filename,"dept.txt");
	}
	else
	{
	    printf("NO SUCH FILE\n");
	    exit(0);
	}
	int num_conditions = 0;
	char conditions[100][100];  // each row has a separate condition like a<100
	i = 0;
	int logicals[100];  // each entry has 1 for and, 0 for or
	int j = 0;
	int k = 5;
	if(strcasecmp(array[4], "where") == 0)
	{
	    while(k < len_array)
	    {
	        num_conditions++;
	        strcpy(conditions[i++], array[k++]);
	        if(strcasecmp(array[k], "and") == 0)
	        {
	            logicals[j++] = 1;
	            k++;
	        }
	        else if(strcasecmp(array[k], "or") == 0)
	        {
	            logicals[j++] = 0;
	            k++;
	        }
	    }
	}
	int num_logicals = j;
    char ch;
    int n=0;
    char line[300];
    if (flag == 'e')
    {
		remove_extra_line("emp.txt");
		FILE *fp = fopen(filename, "r");
        Employee records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
            if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					e_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        e_evaluate(current_results, conditions[s], records, num_records);
                        e_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
                Employee new_records[1000];
                t=0;
                int n=0;
                for(i=0;i<num_records;i++)
                {
                    if(i==final_results[t])
                    {
                        t++;
                        continue;
                    }
                    else
                    {
                    new_records[n] = records[i];
                    n++;
                    }
                }
            fclose(fp);
            FILE *fp = fopen(filename, "w");
            for(i=0;i<n;i++)
            {
                fprintf(fp, "%d ",new_records[i].eid);
                fprintf(fp, "%s ",new_records[i].ename);
                fprintf(fp, "%d ",new_records[i].eage);
                fprintf(fp, "%s ",new_records[i].eaddress);
                fprintf(fp, "%d ",new_records[i].salary);
                fprintf(fp, "%d",new_records[i].deptno);
                fprintf(fp, "\r\n");
            }
           fclose(fp);
        }
        else
        {
            fclose(fp);
            FILE *fp = fopen(filename, "w");
            fclose(fp);
        }
    }
    if (flag == 'd')
    {
		remove_extra_line("dept.txt");
		FILE *fp = fopen(filename, "r");
        Department records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
            if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					d_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        d_evaluate(current_results, conditions[s], records, num_records);
                        d_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
                Department new_records[1000];
                t=0;
                int n=0;
                for(i=0;i<num_records;i++)
                {
                    if(i==final_results[t])
                    {
                        t++;
                        continue;
                    }
                    else
                    {
                    new_records[n] = records[i];
                    n++;
                    }
                }
                fclose(fp);
                FILE *fp = fopen(filename, "w");
            for(i=0;i<n;i++)
            {
                fprintf(fp, "%d ",new_records[i].dnum);
                fprintf(fp, "%s ",new_records[i].dname);
                fprintf(fp, "%s",new_records[i].dlocation);
                fprintf(fp, "\r\n");
            }
           fclose(fp);
        }
        else
        {
            fclose(fp);
            FILE *fp = fopen(filename, "w");
            fclose(fp);
        }
    }
}

void get(char command[])
{
    int i = 0;
	int commas = 0;
	for(; i<strlen(command); i++)
	{
		if(command[i] == ',')
		{
			commas++;
		}
	}
	int num_fields = commas + 1;
	char fields[num_fields][25];   //fields to get, one field in a row
	char array[100][100];   //the command delimited by space, array[0] = GET, array[1] = field_list, array[2] = FROM....
	i = 0;
	char *token = strtok(command, " ");
	while(token != NULL)
	{
		strcpy(array[i++],token);
		token = strtok(NULL, " ");
	}
	int len_array = i;
	i = 0;
	char field_list[100];
	strcpy(field_list, array[1]);
	token = strtok(field_list, ",");
	while(token != NULL)
	{
		strcpy(fields[i++], token);
		token = strtok(NULL, ",");
	}
	int eid_flag = 0;
	int ename_flag = 0;
	int eage_flag = 0;
	int eaddress_flag = 0;
	int salary_flag = 0;
	int deptno_flag = 0;
	int dnum_flag = 0;
	int dname_flag = 0;
	int dlocation_flag = 0;
	for(i = 0; i < num_fields; i++)
	{
	    if(strcmp(fields[i], "eid") == 0)
        {
           eid_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "ename") == 0)
        {
           ename_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "eage") == 0)
        {
           eage_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "eaddress") == 0)
        {
           eaddress_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "salary") == 0)
        {
           salary_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "deptno") == 0)
        {
           deptno_flag = 1;
           continue;
        }
		if(strcmp(fields[i], "dnum") == 0)
        {
           dnum_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "dname") == 0)
        {
           dname_flag = 1;
           continue;
        }
        if(strcmp(fields[i], "dlocation") == 0)
        {
           dlocation_flag = 1;
           continue;
        }
   }
	char flag;  //emp.txt or dept.txt
	char filename[20];
	if((strcasecmp(array[3], "emp.txt") == 0) || (strcasecmp(array[3], "emp.txt;") == 0))
	{
	    flag = 'e';
	    strcpy(filename,"emp.txt");
	}
	else if((strcasecmp(array[3], "dept.txt") == 0) || (strcasecmp(array[3], "dept.txt;") == 0))
	{
	    flag = 'd';
	    strcpy(filename,"dept.txt");
	}
	else
	{
	    printf("NO SUCH FILE\n");
	    exit(0);
	}
	int num_conditions = 0;
	char conditions[100][100];  // each row has a separate condition like a<100
	i = 0;
	int logicals[100];  // each entry has 1 for and, 0 for or
	int j = 0;
	int k = 5;
	if(strcasecmp(array[4], "where") == 0)
	{
	    while(k < len_array)
	    {
	        num_conditions++;
	        strcpy(conditions[i++], array[k++]);
	        if(strcasecmp(array[k], "and") == 0)
	        {
	            logicals[j++] = 1;
	            k++;
	        }
	        else if(strcasecmp(array[k], "or") == 0)
	        {
	            logicals[j++] = 0;
	            k++;
	        }
	    }
	}
	int num_logicals = j;
    char ch;
    int n=0;
    char line[300];
    if (flag == 'e')
    {
		remove_extra_line("emp.txt");
		FILE *fp = fopen(filename, "r");
        Employee records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
            if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					e_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        e_evaluate(current_results, conditions[s], records, num_records);
                        e_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
               for(i=0; i < new_size; i++)
               {
                    if(eid_flag)
                        printf("%d ", records[final_results[i]].eid);
                    if(ename_flag)
                        printf("%s ",  records[final_results[i]].ename);
                    if(eage_flag)
                        printf("%d ", records[final_results[i]].eage);
                    if(eaddress_flag)
                        printf("%s ",  records[final_results[i]].eaddress);
                    if(salary_flag)
                        printf("%d ", records[final_results[i]].salary);
                    if(deptno_flag)
                        printf("%d ", records[final_results[i]].deptno);
                    printf("\n");
               }
            }
            else
            {
               for(i=0; i < num_records; i++)
               {
                    if(eid_flag)
                        printf("%d ", records[i].eid);
                    if(ename_flag)
                        printf("%s ",  records[i].ename);
                    if(eage_flag)
                        printf("%d ", records[i].eage);
                    if(eaddress_flag)
                        printf("%s ",  records[i].eaddress);
                    if(salary_flag)
                        printf("%d ", records[i].salary);
                    if(deptno_flag)
                        printf("%d ", records[i].deptno);
                    printf("\n");
               }
            }
            fclose(fp);
			add_extra_line("emp.txt");
        }
    if (flag == 'd')
    {
		remove_extra_line("dept.txt");
		FILE *fp = fopen(filename, "r");
        Department records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
		if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					d_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        d_evaluate(current_results, conditions[s], records, num_records);
                        d_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
               for(i=0; i < new_size; i++)
               {
                    if(dnum_flag)
                        printf("%d ", records[final_results[i]].dnum);
                    if(dname_flag)
                        printf("%s ",  records[final_results[i]].dname);
                    if(dlocation_flag)
                        printf("%s ", records[final_results[i]].dlocation);
                    printf("\n");
               }
            }
            else
            {
               for(i=0; i < num_records; i++)
               {
                    if(dnum_flag)
                        printf("%d ", records[i].dnum);
                    if(dname_flag)
                        printf("%s ",  records[i].dname);
                    if(dlocation_flag)
                        printf("%s ", records[i].dlocation);
                    printf("\n");
               }
            }
			fclose(fp);
			add_extra_line("dept.txt");
    }
}

void update(char command[])
{
    char array[100][100];
	int i = 0;
	char *token = strtok(command, " ");
	while(token != NULL)
	{
		strcpy(array[i++],token);
		token = strtok(NULL, " ");
	}
	int len_array = i;
	i=0;
	char flag;  //emp.txt or dept.txt
	char filename[20];
	if((strcasecmp(array[3], "emp.txt") == 0) || (strcasecmp(array[3], "emp.txt;") == 0))
	{
	    flag = 'e';
	    strcpy(filename,"emp.txt");
	}
	else if((strcasecmp(array[3], "dept.txt") == 0) || (strcasecmp(array[3], "dept.txt;") == 0))
	{
	    flag = 'd';
	    strcpy(filename,"dept.txt");
	}
	else
	{
	    printf("NO SUCH FILE\n");
	    exit(0);
	}
	int num_conditions = 0;
	char conditions[100][100];  // each row has a separate condition like a<100
	i = 0;
	int logicals[100];  // each entry has 1 for and, 0 for or
	int j = 0;
	int k = 9;
	char field[100];
	char newvalue[100];
	if(strcasecmp(array[4], "set") == 0)
        strcpy(field, array[5]);
    if(strcasecmp(array[6], "to") == 0)
        strcpy(newvalue, array[7]);
	if(strcasecmp(array[8], "where") == 0)
	{
	    while(k < len_array)
	    {
	        num_conditions++;
	        strcpy(conditions[i++], array[k++]);
	        if(strcasecmp(array[k], "and") == 0)
	        {
	            logicals[j++] = 1;
	            k++;
	        }
	        else if(strcasecmp(array[k], "or") == 0)
	        {
	            logicals[j++] = 0;
	            k++;
	        }
	    }
	}
	remove_all_chars(newvalue,';');
	int num_logicals = j;
    char ch;
    int n=0;
    char line[300];
    if (flag == 'e')
    {
		remove_extra_line("emp.txt");
		FILE *fp = fopen(filename, "r");
        Employee records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Employee ob;
            ob.eid = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.ename, p);
            p = strtok(NULL, " ");
            ob.eage = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.eaddress, p);
            p = strtok(NULL, " ");
            ob.salary = atoi(p);
            p = strtok(NULL, " ");
            ob.deptno = atoi(p);
            records[i++] = ob;
            Employee new_records[1000];
            if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					e_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        e_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        e_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        e_evaluate(current_results, conditions[s], records, num_records);
                        e_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						e_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
                t=0;
                for(i=0;i<num_records;i++)
                {
                    if(t>new_size)
                        new_records[i] = records[i];
                    else if(i==final_results[t])
                    {
                        if(strcmp(field, "eid") == 0)
                        {
                            new_records[i].eid = atoi(newvalue);
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "ename") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, newvalue);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "eage") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = atoi(newvalue);
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "eaddress") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, newvalue);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "salary") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress,records[i].eaddress);
                            new_records[i].salary= atoi(newvalue);
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "deptno") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress,records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = atoi(newvalue);
                        }
                        t++;
                    }
                    else
                        new_records[i] = records[i];
                }
            }
            else
            {
                for(i=0;i<num_records;i++)
                {
                        if(strcmp(field, "eid") == 0)
                        {
                            new_records[i].eid = atoi(newvalue);
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "ename") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, newvalue);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "eage") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = atoi(newvalue);
                            strcpy(new_records[i].eaddress, records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "eaddress") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress, newvalue);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "salary") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress,records[i].eaddress);
                            new_records[i].salary= atoi(newvalue);
                            new_records[i].deptno = records[i].deptno;
                        }
                        else if(strcmp(field, "deptno") == 0)
                        {
                            new_records[i].eid = records[i].eid;
                            strcpy(new_records[i].ename, records[i].ename);
                            new_records[i].eage = records[i].eage;
                            strcpy(new_records[i].eaddress,records[i].eaddress);
                            new_records[i].salary = records[i].salary;
                            new_records[i].deptno = atoi(newvalue);
                        }
                }
            }
            fclose(fp);
            fp = fopen(filename, "w");
            for(i=0;i<num_records;i++)
            {
                fprintf(fp, "%d ",new_records[i].eid);
                fprintf(fp, "%s ",new_records[i].ename);
                fprintf(fp, "%d ",new_records[i].eage);
                fprintf(fp, "%s ",new_records[i].eaddress);
                fprintf(fp, "%d ",new_records[i].salary);
                fprintf(fp, "%d",new_records[i].deptno);
                fprintf(fp, "\r\n");
            }
           fclose(fp);
    }
    if (flag == 'd')
    {
		remove_extra_line("dept.txt");
		FILE *fp = fopen(filename, "r");
        Department records[1000];
        int num_records = 0;
        int i = 0;
        while((ch = fgetc(fp)) != EOF)
        {
            if(ch!='\n')
            {
                line[n++] = ch;
                continue;
            }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
        }
            line[n]='\0';
            n = 0;
            num_records++;
            char *p = strtok (line, " ");
            Department ob;
            ob.dnum = atoi(p);
            p = strtok(NULL, " ");
            strcpy(ob.dname, p);
            p = strtok(NULL, " ");
            strcpy(ob.dlocation, p);
            p = strtok(NULL, " ");
            records[i++] = ob;
            Department new_records[1000];
            if(num_conditions)
            {
                int final_results[1000];
                int current_results[1000];
                int num_ors = 0;
                int t;
                for (t=0; t<num_logicals; t++)
                {
                    if(logicals[t] == 0)
                        num_ors++;
                }

                for(t = 0;t<num_records; t++)
                {
                    current_results[t] = t; // current results is initially all records
                }
                int index = 0;
                int s;
				if(num_logicals == 0)
				{
					d_evaluate(current_results, conditions[0], records, num_records);
					for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
				}
                for(s = 0; s<num_logicals; s++)
                {
                    if((num_logicals == 1) && (logicals[s] == 0))
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[1], records, num_records);
                        t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                    }
                    else if((s == 0) && (logicals[s] == 0)) // first op is OR(0)
                    {
                        d_evaluate(current_results, conditions[0], records, num_records);
                        int t;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];    //don't put the ones that don't satisfy the conditions in final results
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[1], records, num_records);
                    }
                    else if((s == num_logicals - 1) && logicals[s] == 0) // last op is OR
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
                        d_evaluate(current_results, conditions[num_logicals], records, num_records);
                    }
                    else if(logicals[s] == 1)
                    {
                        d_evaluate(current_results, conditions[s], records, num_records);
                        d_evaluate(current_results, conditions[s+1], records, num_records);
                        printf("\n");
                    }
                    else if(logicals[s] == 0)
                    {
                        int t = 0;
                        for(t = 0; t<num_records; t++)
                        {
                            if(current_results[t] != -1)
                                final_results[index++] = current_results[t];
                        }
                        for(t = 0;t<num_records; t++)
                        {
                            current_results[t] = t;
                        }
						d_evaluate(current_results, conditions[s+1], records, num_records);
                    }
               }
               for(t = 0; t<num_records; t++)
               {
                    if(current_results[t] != -1)
                    {
                        final_results[index++] = current_results[t];
                    }
               }
               bubbleSort(final_results, index);
               int new_size = removeDuplicates(final_results, index);
                t=0;
                for(i=0;i<num_records;i++)
                {
                    if(t>new_size)
                        new_records[i] = records[i];
                    else if(i==final_results[t])
                    {
                        if(strcmp(field, "dnum") == 0)
                        {
                            new_records[i].dnum = atoi(newvalue);
                            strcpy(new_records[i].dname, records[i].dname);
                            strcpy(new_records[i].dlocation, records[i].dlocation);
                        }
                        else if(strcmp(field, "dname") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].dnum = records[i].dnum;
                            strcpy(new_records[i].dname, newvalue);
                            strcpy(new_records[i].dlocation, records[i].dlocation);
                        }
                        else if(strcmp(field, "dlocation") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].dnum = records[i].dnum;
                            strcpy(new_records[i].dname, records[i].dname);
                            strcpy(new_records[i].dlocation, newvalue);
                        }
                        t++;
                    }
                    else
                        new_records[i] = records[i];
                }
            }
            else
            {
                for(i=0;i<num_records;i++)
                {
                        if(strcmp(field, "dnum") == 0)
                        {
                            new_records[i].dnum = atoi(newvalue);
                            strcpy(new_records[i].dname, records[i].dname);
                            strcpy(new_records[i].dlocation, records[i].dlocation);
                        }
                        else if(strcmp(field, "dname") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].dnum = records[i].dnum;
                            strcpy(new_records[i].dname, newvalue);
                            strcpy(new_records[i].dlocation, records[i].dlocation);
                        }
                        else if(strcmp(field, "dlocation") == 0)
                        {
                            remove_all_chars(newvalue, '"');
                            new_records[i].dnum = records[i].dnum;
                            strcpy(new_records[i].dname, records[i].dname);
                            strcpy(new_records[i].dlocation, newvalue);
                        }
                }
            }
            fclose(fp);
            fp = fopen(filename, "w");
            for(i=0;i<num_records;i++)
            {
                fprintf(fp, "%d ",new_records[i].dnum);
                fprintf(fp, "%s ",new_records[i].dname);
                fprintf(fp, "%s",new_records[i].dlocation);
                fprintf(fp, "\r\n");
            }
           fclose(fp);
    }
}


#line 2391 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    GET = 258,
    AND = 259,
    OR = 260,
    FROM = 261,
    UPDATE = 262,
    DELETE = 263,
    RECORD = 264,
    FIELD = 265,
    FILENAME = 266,
    IN = 267,
    INTO = 268,
    WHERE = 269,
    SET = 270,
    INSERT = 271,
    CONSTANT = 272,
    STRING_CONSTANT = 273,
    TO = 274
  };
#endif
/* Tokens.  */
#define GET 258
#define AND 259
#define OR 260
#define FROM 261
#define UPDATE 262
#define DELETE 263
#define RECORD 264
#define FIELD 265
#define FILENAME 266
#define IN 267
#define INTO 268
#define WHERE 269
#define SET 270
#define INSERT 271
#define CONSTANT 272
#define STRING_CONSTANT 273
#define TO 274

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 2326 "yacc.y" /* yacc.c:355  */

    char string[100];

#line 2473 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 2490 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   73

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  31
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  75

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   274

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,     2,     2,     2,     2,     2,
      26,    27,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      24,    21,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  2350,  2350,  2351,  2352,  2353,  2354,  2355,  2356,  2357,
    2358,  2359,  2360,  2361,  2362,  2363,  2364,  2365,  2366,  2367,
    2368,  2369,  2370,  2371,  2372,  2373,  2374,  2375,  2376,  2377,
    2378,  2379
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GET", "AND", "OR", "FROM", "UPDATE",
  "DELETE", "RECORD", "FIELD", "FILENAME", "IN", "INTO", "WHERE", "SET",
  "INSERT", "CONSTANT", "STRING_CONSTANT", "TO", "','", "'='", "'!'",
  "'>'", "'<'", "';'", "'('", "')'", "$accept", "STMTS", "STMT",
  "FIELD_LIST", "CONDITION", "CONDITION_LIST", "GET_STMT", "VALUE",
  "VALUE_LIST", "INSERT_STMT", "UPDATE_STMT", "DELETE_STMT", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      44,    61,    33,    62,    60,    59,    40,    41
};
# endif

#define YYPACT_NINF -38

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-38)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,     6,    35,    36,    37,    47,    11,   -38,   -38,   -38,
     -38,   -38,     5,    38,    42,    23,   -38,   -38,    40,    43,
      41,    44,    14,    -5,   -38,    39,    -4,   -38,   -38,   -38,
     -12,    46,   -38,    48,    46,   -38,    14,    49,    17,   -38,
      -3,    45,    -1,   -38,    50,    51,    52,    12,    13,    46,
      46,   -38,    14,   -38,    32,    18,    25,   -38,    53,   -38,
      54,   -38,   -38,     3,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,    46,   -38,     1,   -38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     3,     4,     5,     6,
       7,     9,     0,     0,     0,     0,     1,     2,     0,     0,
       0,     0,     0,     0,     8,     0,     0,    23,    24,    26,
       0,     0,    22,     0,     0,    30,     0,     0,     0,    20,
       0,     0,     0,    25,     0,     0,     0,     0,     0,     0,
       0,    21,     0,    31,     0,     0,     0,    16,     0,    17,
       0,    18,    19,     0,    27,    10,    11,    12,    13,    14,
      15,     0,    28,     0,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -38,    57,   -38,   -38,   -37,   -34,   -38,   -29,   -38,   -38,
     -38,   -38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    12,    39,    40,     7,    29,    30,     8,
       9,    10
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      42,    49,    50,    49,    50,    49,    50,    43,    36,    31,
      34,    18,    61,    62,     1,    37,    11,    71,     2,     3,
      32,    35,    51,    63,    53,    19,    74,     4,    72,    57,
      59,    27,    28,    58,    60,    65,    66,    73,    45,    46,
      47,    48,    67,    68,    13,    14,    15,    16,    21,    22,
      20,    23,    25,    24,    33,    26,    38,    64,    41,     0,
       0,    54,    44,    17,    52,     0,     0,     0,     0,     0,
      69,    70,    55,    56
};

static const yytype_int8 yycheck[] =
{
      34,     4,     5,     4,     5,     4,     5,    36,    20,    14,
      14,     6,    49,    50,     3,    27,    10,    14,     7,     8,
      25,    25,    25,    52,    25,    20,    25,    16,    25,    17,
      17,    17,    18,    21,    21,    17,    18,    71,    21,    22,
      23,    24,    17,    18,     9,     9,     9,     0,     6,    26,
      12,    11,    11,    10,    15,    11,    10,    25,    10,    -1,
      -1,    11,    13,     6,    19,    -1,    -1,    -1,    -1,    -1,
      17,    17,    21,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,     8,    16,    29,    30,    34,    37,    38,
      39,    10,    31,     9,     9,     9,     0,    29,     6,    20,
      12,     6,    26,    11,    10,    11,    11,    17,    18,    35,
      36,    14,    25,    15,    14,    25,    20,    27,    10,    32,
      33,    10,    33,    35,    13,    21,    22,    23,    24,     4,
       5,    25,    19,    25,    11,    21,    21,    17,    21,    17,
      21,    32,    32,    35,    25,    17,    18,    17,    18,    17,
      17,    14,    25,    33,    25
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    30,    30,    31,    31,
      32,    32,    32,    32,    32,    32,    32,    32,    33,    33,
      33,    34,    34,    35,    35,    36,    36,    37,    38,    38,
      39,    39
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     3,     1,
       4,     4,     4,     4,     4,     4,     3,     3,     3,     3,
       1,     7,     5,     1,     1,     3,     1,     8,     9,    11,
       5,     7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 2352 "yacc.y" /* yacc.c:1646  */
    {get(yylval.string);}
#line 3609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 2353 "yacc.y" /* yacc.c:1646  */
    {insert(yylval.string);}
#line 3615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 2354 "yacc.y" /* yacc.c:1646  */
    {update(yylval.string);}
#line 3621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 2355 "yacc.y" /* yacc.c:1646  */
    {delete_record(yylval.string);}
#line 3627 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3631 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2381 "yacc.y" /* yacc.c:1906  */


int main(int argc, char *argv[])
{
	yyparse();
	if(!yyparse)
	{
		printf("Parse Error\n");

	return 0;

	}
}





