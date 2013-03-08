#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	long long **d = new long long* [2*n+2];
	for (int i=0; i<=2*n+1; ++i) d[i] = new long long [n+3];
	for (int i=0; i<=2*n+1; ++i)
		for (int j=0; j<=n+2; ++j)	d[i][j] = 0;
	d[0][0] = 1;
	for (int i=1; i<=2*n+1; ++i)
		for (int j=1; j<=n+1; ++j)	if (i>=j) d[i][j] = d[i-1][j+1] + d[i-1][j-1];
	cout << d[2*n+1][1];
	for (int i=0; i<=2*n+1; ++i) delete [] d[i];
	delete [] d;
	return 0;
}