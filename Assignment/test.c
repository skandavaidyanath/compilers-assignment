#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdbool.h>
#include<ctype.h>
#include<strings.h>

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
/*
void remove_extra_line(char filename[])
{
    int chars_to_delete = 2;
    FILE *fp = fopen(filename, "r+");
    fseeko(fp, -chars_to_delete, SEEK_END);
    int position = ftello(fp);
    ftruncate(fileno(fp), position);
    fclose(fp);
}
*/
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
		//remove_extra_line("emp.txt");
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
		//remove_extra_line("dept.txt");
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
		//remove_extra_line("emp.txt");
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
		//remove_extra_line("dept.txt");
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
		//remove_extra_line("emp.txt");
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
		//remove_extra_line("dept.txt");
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

int main()
{
    char command[] = "GET ename,salary,deptno from emp.txt where salary<1000 and ename==\"deek\" or deptno==3;";
    //get(command);
    char command2[] = "INSERT RECORD (3,\"djhb\",54b,\"vghga\",800,4) INTO emp.txt;";
    //insert(command2);
    char command3[] = "DELETE RECORD from emp.txt where salary>=1000 or deptno==8;";
    //delete_record(command3);
    char command4[] = "UPDATE RECORD in emp.txt set salary to 100 where salary==10 and deptno==3;";
    update(command4);
    return 0;
}
