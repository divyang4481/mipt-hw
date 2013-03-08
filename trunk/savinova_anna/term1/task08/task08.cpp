// task08.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>

char** split(const char *str, const char *delim)
{
    int strl = strlen(str);
    char** a = new char*[strl];
    const char* p;
    p = strstr(str, delim);
    for (int i = 0; p; ++i)
    {
        strncpy(a[i], str, int(p-str));
        a[i][p-str+1]='';
        //*p=
        p=strstr(str, delim);
    }
    return a;
};

void delete_string_array(char **str);

using namespace std;
int main()
{         
    char s1[10000], s2[10000];

	return 0;
}

