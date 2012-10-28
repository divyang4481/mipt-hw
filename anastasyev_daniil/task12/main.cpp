#include <stdio.h>
#include <time.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ct = clock();    
    float c=0., sum=0.;
    float *f = new float[n];
    for (int i=0; i<n; ++i)
    {
        scanf("%f",(f+i));
        float y = f[i] - c;
        float t = sum + y;
        c = (t - sum) - y;   
        sum = t; 
    }
    int t1 = clock() - ct;
    printf("%f %f",sum,((float)t1)/CLOCKS_PER_SEC);
    return 0;
}