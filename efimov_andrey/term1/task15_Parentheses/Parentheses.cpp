#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	int c=0;
	bool f=true;
	getline(cin, s);
	for (int i=0; i<s.length(); i++){
		if (s[i]=='(') c++;
		else c--;
		if (c<0) f=false;
	}
	if (c!=0) f=false;
	if (f) cout << "YES";
	else cout << "NO";
	return 0;
}