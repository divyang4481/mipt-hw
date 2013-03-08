#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    int n;
	cin >> n;
	int answer = 1;
	for(int i = 0; i < n; i++) {
		answer *= (2 * n - i);
		answer /= (i + 1);
	}
	answer /= (n + 1);
	cout << answer;
}