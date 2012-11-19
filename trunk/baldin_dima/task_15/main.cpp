#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    getline(cin,s);
    int c = 0;

    for (int i=0; (unsigned)i< s.length(); ++i)
    {
        if (s[i] == '(') ++c;
            else --c;
        if (c < 0)
        {
           cout << "NO";
           return 0;
        }
    }
    if (c!=0)
    cout << "NO";
    else cout << "YES";
    return 0;
}
