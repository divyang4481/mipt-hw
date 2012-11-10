#include <stdio.h>

int main()
{
    unsigned long long c=1;
    int n;
    scanf("%d",&n);
    for (int i=0; i<=n; ++i)
    {
        printf("%llu\n",c);
        c=c*(n-i)/(i+1);
    }
    return 0;
}