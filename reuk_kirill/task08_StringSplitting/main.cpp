#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int MAXN = 10000;
int count = 0;

char** split(const char *str, const char *delim)
{
    char** buf;
    buf = new char*[strlen(str)];
    for (int i = 0; i < strlen(str); ++i)
        buf[i] = new char[strlen(str)];

    char* bufstring = (char*) calloc(MAXN, sizeof(char));
    char* cstring = (char*) calloc(MAXN, sizeof(char));

    for (int i = 0; i <= (strlen(str) - strlen(delim)); ++i)
    {
        bool flag = 1;
        for (int j = i; j < i + strlen(delim); ++j)
        {
            if (str[j] != delim[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            if (strlen(bufstring) > 0)
            {
                strcpy(buf[count], bufstring);
                count++;
                strcpy(bufstring, "");
            }
            i += (strlen(delim) - 1);
        }
        else
        {
            strcpy(cstring, "");
            cstring[0] = str[i];
            strcat(bufstring, cstring);
            //bufstring[strcount++] = str[i];
        }
    }
    for (int i = (strlen(str) - strlen(delim)) + 1; i < strlen(str); ++i)
    {
        strcpy(cstring, "");
        cstring[0] = str[i];
        strcat(bufstring, cstring);
    }
    if (strlen(bufstring)>0)
    {
        strcpy(buf[count], bufstring);
        count++;
    }

    return buf;
}

void delete_string_array(char **str)
{
    for (int i = 0; i < --count; ++i)
    {
        delete[] str[i];
    }
    delete[]str;
}

int main()
{
    char* str = (char*) malloc(MAXN * sizeof(char));
    char* delim = (char*) malloc(MAXN * sizeof(char));
    scanf("%s", str);
    scanf("%s", delim);

    char** res = split(str, delim);
    for (int i = 0; i < count; ++i)
    {
        printf("%s\n", res[i]);
    }

    delete_string_array(res);

    return 0;
}
