#include <stdio.h>
#include <string>

char** split(const char *str, const char *delim)
{   
    int len=strlen(str);
    char *temp=new char [len+2];
    const char *sd=strstr(str, delim);
    int i;
    for (i=0; str!=sd; ++i, ++str) 
    {
        temp[i]=*str;
    }
   temp[i]='\n';
   ++i;
   for (; i<=len; ++str, ++i)
    {
        temp[i]=*str;
    }
   temp[i]=0;
   return &temp;
}

int main()
{
    char str[10000];
    char delim[10000];
    scanf("%s",str);
    scanf("%s",delim);
    char **str2;
    str2=split(str,delim);
    printf("%s",*str2);
    return 0;
}