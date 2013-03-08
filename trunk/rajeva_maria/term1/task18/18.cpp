#include "cstdio"
#include <iostream>
using namespace std;

void PrintMem(const void *ptr, int size)
 {
	 for (char* t = (char*)ptr + size - 1; t >= (char*)ptr; --t)
	  {
        for (int i = 7; i >= 0; i--)
		   {    
			 int c=(*t) >> i;
             printf("%d", (c)&0x01);
           }
		printf("\n");
      }
      printf("\n");
      return ;

 }


int main()
{
	 double Nc; 
	 Nc=1;
	    printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
     Nc=0;
		printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
     Nc=0.1;
		printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
     Nc=-0.1;
		printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
	 Nc=1000;
		printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
     Nc=-1000;
	    printf("%f\n",Nc);
		PrintMem(&Nc, sizeof(double));
		scanf("%f",&Nc);
        PrintMem(&Nc, sizeof(double));
	    system("pause");
        return 0;
}