#include <iostream>
#include <cstdio>
using namespace std;

void PrintMem(void *p, size_t size)
{
    for (unsigned int i=0;i<size;i++)
     {
         char *r=(char*)p;
         char *pc=r+i;
         char c=*pc;
         for (int j=7;j>=0;j--)
         {
          int n=c&(1<<j);
          if (n==0)
          printf("0");
          else
          printf("1")   ;
         }
         printf("\n");

     }
     cout << endl;
}
int main()
{


    double d = 1.0;
    cout << "1" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 0.0;
    cout << "0" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = -0.125;
    cout << "-0.125" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 0.125;
    cout << "0.125" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 0.125;
    cout << "0.125" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = -10000.125;
    cout << "-10000.125" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 10000.125;
    cout << "10000.125" << endl;
    PrintMem((void*)&d, sizeof(double));
    return 0;
}
