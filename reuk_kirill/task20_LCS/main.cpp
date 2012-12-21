#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//using namespace std;

int main()
{
    char a[100];
    char b[100];
    scanf("%s", a);
    scanf("%s", b);
    int tab [100][100];
    int dir [100][100];
    for(int i = 0; i < 100; ++i)
    {
        tab[0][i] = 0;
        tab[i][0] = 0;
    }
    for(int i = 1; i <= (signed)strlen(a); ++i)
        for(int j = 1; j <= (signed)strlen(b); ++j)
        {
            if (a[i-1] == b[j-1])
            {
                tab[i][j] = tab[i-1][j-1] + 1;
                dir[i][j] = 2;
            }
            else
            {
                if ((tab[i][j-1])>(tab[i-1][j]))
                {
                    tab[i][j] = tab[i][j-1];
                    dir[i][j] = 1;
                }
                else
                {
                    tab[i][j] = tab[i-1][j];
                    dir[i][j] = 0;
                }
            }
        }
    printf("%d ", tab[strlen(a)][strlen(b)]);
    int posx = strlen(a), posy = strlen(b);
    char res [100];
    strcpy(res, "");
    int cow = tab[strlen(a)][strlen(b)];
    while ((posx>0)&&(posy>0))
    {
        switch (dir[posx][posy])
        {
            case 2:
            {
                res[cow] = a[posx-1];
                cow--;
                --posx;
                --posy;
            }
            break;
            case 1:
            {
                --posy;
            }
            break;
            case 0:
            {
                --posx;
            }
            break;
        }
    }
    for (;++cow<=tab[strlen(a)][strlen(b)];)
    {
        printf("%c", res[cow]);
    }
    return 0;
}
