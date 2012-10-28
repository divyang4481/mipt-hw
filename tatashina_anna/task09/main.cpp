
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

using namespace std;

bool SimpleNumber(int n) {

	if (n == 1)
		return(false);
	else {
		for (int i = 2; i < sqrt(double(n)); ++i) {
			if (n % i == 0)
				return(false);

		}
		return(true);
	}
}


int main()
{
    unsigned N = 0;
    cin >> N;

	if (SimpleNumber(N))
		cout << "YES";
	else
		cout << "NO";
    cin >> N;
	return 0;
}