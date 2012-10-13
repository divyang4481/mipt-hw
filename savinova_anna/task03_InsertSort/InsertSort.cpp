// InsertSort.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

int InsertSort(int* a, int l, int r)
{
    for (int j=l+1; j<r; ++j)
    {
        int key=a[j], i=j-1;
        while ((i>l-1) && (a[i]>key))
        {
            a[i+1]=a[i];
            --i;
        }
        a[i+1]=key;
    }
    return 0;
}

int main()
{
	int N=0;
    cin>>N;
    int* A=new int[N];
    for (int i=0; i<N; ++i)
        cin>>A[i];
    InsertSort(A,0,N);
    for (int i=0; i<N; ++i)
        cout<<A[i]<<" ";
    return 0;
}

