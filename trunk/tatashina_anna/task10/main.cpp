
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

using namespace std;


int main()
{
    int n;
    cin >> n;
	int ans = 1;
	cout << ans << " ";
	for(int i = 0; i < n; i++)
	{
		ans *= (n - i);
		ans /= (i + 1);
		cout << ans << " ";
	}

	return 0;
}