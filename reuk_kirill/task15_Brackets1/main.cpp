#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


using namespace std;

int main()
{
    int bal = 0;
    char ch[10000];
    scanf("%s", ch);
    for (int i = 0; i < (signed)strlen(ch); ++i)
    {
        if (ch[i]=='(')
            bal++;
        else
            bal--;
        if (bal < 0)
        {
            printf("NO");
            return 0;
        }
    }
    if (bal != 0)
        printf("NO");
    else
        printf("YES");

    return 0;
}
