#include "cstdio"
#include<iostream>
using namespace std;
int main()
{   int t=0;
    int p=0;
	char a;
	scanf("%c",&a);
	 while ((a==')')||(a=='('))
	 {
		 if (a=='(') t++; else t--;
		 if (t<0) p=1;
         scanf("%c",&a);
	 }
    if ((p==0)&&(t==0)) printf ("yes");
	else printf ("no");
	
	return 0;
	
	
}