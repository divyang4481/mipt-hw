#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void PrintMem(void *ptr, int size)
{
    for (unsigned int i = 0;i < (unsigned)size;i++)
    {
        char *r = (char*)ptr;
        char *ptrc = r + i;
        char c = *ptrc;
        for (int j = 7; j >= 0; j--)
        {
            int n = c&(1 << j);
            if (n == 0)
                printf("0");
            else
                printf("1");
        }
        printf("\n");
     }
     cout << endl;
}

int main()
{

    double d = 1.0;
    cout << "1:" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = -1345;
    cout << "-1345:" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 0.0;
    cout << "0:" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 1.5;
    cout << "1.5:" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 0.008;
    cout << "0.008:" << endl;
    PrintMem((void*)&d, sizeof(double));

    d = 111111111;
    cout << "111111111:" << endl;
    PrintMem((void*)&d, sizeof(double));

    return 0;
}
