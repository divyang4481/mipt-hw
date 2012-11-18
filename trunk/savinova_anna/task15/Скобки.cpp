#include "cstdio"

int main()
{
    char C = 0;
    bool Cor = true;
    int sum = 0;
    scanf("%c", &C);
    while (C != 10)
    {
        if (sum > 0) 
            Cor = false;
        if (C == '(')
            --sum;
        else ++sum;
        scanf("%c", &C);
    }
    if (Cor && sum == 0)
        printf("YES");
    else printf("NO");
    return 0;
}