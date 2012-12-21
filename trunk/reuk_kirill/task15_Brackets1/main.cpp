#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
    int bal = 0;
    char ch;
    while (1)
    {
        scanf("%c", &ch);
        if ((ch != '(') && (ch != ')'))
            break;
        if (ch=='(')
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
