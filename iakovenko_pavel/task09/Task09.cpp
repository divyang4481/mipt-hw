#include <iostream>
using namespace std;

int main()
{int n,i,flag;flag=1;
    cin >> n;
	if (n%2==0)
		flag=0;
	else
    for(i=3;i<n;i+=2){
        if(n%i==0){
            flag=0;goto next;
        }
    }
    next:
    if(flag)
        cout << "YES" << endl;
	else
        cout << "NO" << endl;
		system ("pause");
	return 0;
}


