#include<stdio.h>

int main()
{
	FILE *fp;
	fp = fopen("abc.txt", "w");
	fprintf(fp, "abcd");
	char *newline = "\r\n";
	fprintf(fp, "\r\n");
	fprintf(fp, "efgh");
	fclose(fp);
	return 0;
}