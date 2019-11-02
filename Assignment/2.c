#include<stdio.h>

int main()
{
	FILE *fp = fopen("abc.txt", "r");
	char ch;
	while((ch = fgetc(fp)) != EOF)
	{
		if(ch == '\r') printf("r\n");
		if(ch == '\n') printf("n\n");
	}
	fclose(fp);
	return 0;
}