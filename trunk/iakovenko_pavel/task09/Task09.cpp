#include <iostream>
#include <math.h>
using namespace std;

int prime(int n){
	if (n%2==0)
		return 0;
	else{
		double s=sqrt((double)n);
		for(int i=3;i<=s;i+=2)
			if(n%i==0){
				return 0;
			}
		return 1;
    }
}

int main(){
	int n;
    cin >> n;
    cout <<(prime(n) ? "YES": "NO")<<endl; 
	system ("pause");
	return 0;
}


