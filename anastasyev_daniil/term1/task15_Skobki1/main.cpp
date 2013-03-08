#include <iostream>
using namespace std;

int main()
{
	int k = 0;
	char s[10001];
	cin >> s;
	for (int i=0; ((s[i]) && (k>=0)); ++i) 
		if (s[i] == '(') ++k;
		else --k;
	if (!k) cout << "YES";
	else cout << "NO";
	return 0;
}