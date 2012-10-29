#include <iostream>
#include <time.h>
using namespace std;


int main(){
	int n;
	scanf("%d", &n);
	float* arr=new float[n];
	for(int i=0; i<n; i++)
	cin>>arr[i];
	int t=clock();
	float sum = 0.0;
    float c = 0.0;
	float y, t;
    for(int i = 0; i<n;++i){
        y = arr[i] - c;    
        t = sum + y;        
        c = (t - sum) - y;   
        sum = t;
	}
	int t1=clock()-t;
	printf("%f %f\n", sum, ((float)t1)/CLOCKS_PER_SEC);
	system("pause");
	return 0;
	} 
