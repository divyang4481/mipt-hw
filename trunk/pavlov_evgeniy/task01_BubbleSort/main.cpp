#include<iostream>
using namespace std;
void BubbleSort(int *m,int s)
{for(int i=0;i<s;++i)
	for(int j=i+1;j<s;++j)
		if (m[j]<m[i]){
			int k;k=m[i];m[i]=m[j];m[j]=k;}
}
int main()
{
	int s;
	cin>>s;
	int* m=new int[s];
	for(int i=0;i<s;++i)cin>>m[i];
	BubbleSort(m,s);
	for(int i=0;i<s;++i)cout<<m[i]<<" ";
	delete m;
	return 0;
}

