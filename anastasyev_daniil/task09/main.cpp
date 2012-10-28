#include <stdio.h>

bool Prime(long n)
{
    if (n<1) return false;
    if ((n==1) || (n==2)) return true;
    for (int i=2; i*i<n; ++i) if (n % i==0) return false;
    return true;
}

int main()
{
    long n;
    scanf("%d",&n);
    if (Prime(n)) printf("YES");
    else printf("NO");
    return 0;
}