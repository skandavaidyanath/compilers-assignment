#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void remove_extra_line(char[] filename)
{
    int chars_to_delete = 2;
    FILE *fp = fopen(filename, "r+");
    fseeko(fp, -chars_to_delete, SEEK_END);
    int position = ftello(fp);
    ftruncate(fileno(fp), position);
    fclose(fp);
}
    
    
void add_extra_line(char[] filename)
{
    FILE *fp = fopen(filename, "a+");
    fprintf(fp, "\r\n");
    fclose(fp);
}

int main()
{
    //add_extra_line();
    remove_extra_line();
    return 0;
}