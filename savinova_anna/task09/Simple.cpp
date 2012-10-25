#include <math.h>
#include <iostream>
using namespace std;


int main()
{
	unsigned N = 0;
    cin >> N;
    if (N % 6 == 1 || N % 6 == 5)
    {
        int count = 0;
        for (int i = 2; i < sqrt((float)N); ++i)
            if (N % 2 == 0) ++count;
        if (count || N == 1) cout << "NO";
        else cout << "YES";
    }
    else 
    {
        if (N == 2 || N == 3)
        cout << "YES";
        else cout << "NO";
    }
    return 0;
}

