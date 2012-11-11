#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int MAXN = 10000;

char** split(const char *str, const char *delim)
{
    int cnt = 0;
    char** buf;
    int lastdel = -strlen(delim);
    buf = new char*[strlen(str)];
    for (int i = 0; i < (signed)strlen(str); ++i)
        buf[i] = new char[strlen(str)];

    char* bufstring = (char*) calloc(MAXN, sizeof(char));
    char* cstring = (char*) calloc(MAXN, sizeof(char));

    for (int i = 0; i <= (signed)(strlen(str) - strlen(delim)); ++i)
    {
        bool flag = 1;
        for (int j = i; j < i + (signed)strlen(delim); ++j)
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
                strcpy(buf[cnt], bufstring);
                cnt++;
                strcpy(bufstring, "");
            }
            i += (strlen(delim) - 1);
            lastdel = i;
        }
        else
        {
            strcpy(cstring, "");
            cstring[0] = str[i];
            strcat(bufstring, cstring);
            //bufstring[strcount++] = str[i];
        }
    }
    for (int i = max((signed)(strlen(str) - strlen(delim)) + 1, lastdel + (signed)strlen(delim)); i < strlen(str); ++i)
    {
        strcpy(cstring, "");
        cstring[0] = str[i];
        strcat(bufstring, cstring);
    }
    if (strlen(bufstring)>0)
    {
        strcpy(buf[cnt], bufstring);
        cnt++;
    }
    buf[cnt] = NULL;
    return buf;
}

void delete_string_array(char **str)
{
    for (int i = 0; str[i] != NULL; ++i)
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
    for (int i = 0; res[i] != NULL; ++i)
    {
        printf("%s\n", res[i]);
    }

    delete_string_array(res);

    return 0;
}
