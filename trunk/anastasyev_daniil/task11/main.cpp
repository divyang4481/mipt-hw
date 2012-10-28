#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);

    float fsum_vozr=0., fsum_ubyv=0.;
    double dsum_vozr=0., dsum_ubyv=0.;
    long double dlsum_vozr=0., dlsum_ubyv=0.;
    for (int i=1; i<=n; ++i)
    {
        fsum_ubyv+=(float)1/(i*i);
    }
    for (int i=n; i>=1; --i)
    {
        fsum_vozr+=(float)1./(i*i);
    }
    for (int i=1; i<=n; ++i)
    {
        dsum_ubyv+=(double)1/(i*i);
    }
    for (int i=n; i>=1; --i)
    {
        dsum_vozr+=(double)1/(i*i);
    }
    for (int i=1; i<=n; ++i)
    {
        dlsum_ubyv+=(long double)1/(i*i);
    }
    for (int i=n; i>=1; --i)
    {
        dlsum_vozr+=(long double)1/(i*i);
    }
    printf(" %f\n %f\n %lf\n %lf\n %lf\n %lf\n",fsum_vozr, fsum_ubyv, dsum_vozr, dsum_ubyv, dlsum_vozr, dlsum_ubyv);
    return 0;
}