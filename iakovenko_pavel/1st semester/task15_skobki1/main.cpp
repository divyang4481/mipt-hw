#include <iostream>
#include <stack>
using namespace std;

int main(){
	stack<int> mystack;
	char c;
	do{c=getchar();
		if(c=='(')
		mystack.push(c);
		else if(c==')'){
			if (mystack.empty()){
				cout << "NO";
				return 0;
			}
			else{
			char tmp=mystack.top();
			if (tmp==')'){
				cout << "NO";
				return 0;
			}
			mystack.pop();
			}
		}
		else
			break;
	}while (true);
	if (!mystack.empty())
		cout << "NO";
	else
		cout <<"YES";
	system("pause");
	return 0;
}


