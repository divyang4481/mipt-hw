#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    string s;
	getline(cin, s);
	int n = s.length();
	int t = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '(')
			++t;
		else
			--t;
		if (t < 0) {
			cout << "NO";
			return 0;
		}
	}
	if (t)
		cout << "NO";
	else
		cout << "YES";
    return 0;
}