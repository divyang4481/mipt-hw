#include <iostream>

int main()
{int n,i,flag;flag=1;
    scanf_s("%d", &n);
    for(i=2;i<n;i++){
        if(n%i==0){
            flag=0;goto next;
        }
    }
    next:
    if(flag)
        printf_s("YES");
    else 
        printf_s("NO");
	return 0;
}

