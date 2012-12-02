#include <iostream>
#include <bitset>
using namespace std;

union t1{
	double d;
    unsigned char c[sizeof(double)];
	t1(double n);
};

t1::t1(double n)
{
    d=n;
}


void PrintMem(const void *ptr, int size){
	const double* c=(const double *)ptr;
	t1 a(*c);
	int i,j;
    for(j=sizeof(double)-1;j>=0;j--)
        for(i=128;i;i>>=1)
            if(i & a.c[j])
                cout<<"1";
			else
				cout<<"0";
	cout << endl;
}

int main(){
	double n;
	cin >> n;
	const void* ptr=&n;
	int size=sizeof(n);
	PrintMem(ptr, size);
	system("pause");
	return 0;
}
