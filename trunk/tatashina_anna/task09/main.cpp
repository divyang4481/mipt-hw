
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

using namespace std;

bool SimpleNumber(int n) {

	if (n == 1)
		return(false);
	else {
		for (int i = 2; i*i <= n; ++i) {
			if (n % i == 0)
				return(false);

		}
		return(true);
	}
}


int main()
{
    unsigned N;
    cin >> N;

	if (SimpleNumber(N))
		cout << "YES";
	else
		cout << "NO";

	return 0;
}