#include <iostream>
using namespace std;

void PrintMem(const void *ptr, int size)
{
        int s=size*8;
		long long *p = (long long *) ptr;
        long long m = 1LL << (s-1);
        while (s) 
		{
                if ((*p)&m) cout << 1;
                else cout << 0;
                *p = *p << 1;
                s--;
        }
        cout << endl;
};

int main()
{
        double d;
        cin >> d;
        PrintMem (&d, sizeof(double));
        return 0;
}