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
        fsum_ubyv+=1/(float(i)*float(i));
        dsum_ubyv+=1/(double(i)*double(i));
        dlsum_ubyv+=1/((long double)(i)*(long double)(i));
    }
    for (int i=n; i>=1; --i)
    {
        fsum_vozr+=1/(float(i)*float(i));
        dsum_vozr+=1/(double(i)*double(i));
        dlsum_vozr+=1/((long double)(i)*(long double)(i));
    }
    printf("%.8f\n%.8f\n%.16lf\n%.16lf\n%.16Lf\n%.16Lf\n",fsum_vozr, fsum_ubyv, dsum_vozr, dsum_ubyv, dlsum_vozr, dlsum_ubyv);
    return 0;
}