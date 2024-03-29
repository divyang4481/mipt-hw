#include <iostream>
#include <cmath>
using namespace std;

void merge(int* arr, int l, int r, int* temp)
{
    int m = (l+r)/2;
    int t = 0;
    int i1 = l;
    int i2 = m + 1;
    while ( i1 <= m && i2 <= r )
        if ( arr[i1] < arr[i2] )
            temp[t++] = arr[i1++];
        else
            temp[t++] = arr[i2++];
    while ( i1 <= m )
        temp[t++] = arr[i1++];
    while ( i2 <= r )
        temp[t++] = arr[i2++];
    for ( int i = l; i <= r; i++ )
        arr[i] = temp[i-l];
}

void merge_sort(int* arr, int l, int r, int* buff)
{
    if ( l < r )
    {
        int m = (l + r)/2;
        merge_sort(arr, l, m, buff);
        merge_sort(arr, m + 1, r, buff);
        merge(arr, l, r, buff);
    }
}

int main()
{
	freopen ("in.txt", "rt", stdin);
	freopen ("out.txt", "wt", stdout);
	int n;
	cin >> n; 
	int* ar=new int[n];
	int* buff=new int[n];
	for (int i=0; i<n; i++)
		cin >> ar[i];
	merge_sort(ar, 0, n-1, buff);
	for (int i=0; i<n; i++)
		cout << ar[i] << " ";
	delete[] ar;
	delete[] buff;
}