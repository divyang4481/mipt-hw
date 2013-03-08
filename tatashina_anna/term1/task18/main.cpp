#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <crtdbg.h>

using namespace std;

void PrintMem(const void* ptr, int size) {
        char* p = (char*) ptr;
        for (char* q = p + size - 1; q >= p; q--) {
                for (int bit = 7; bit >= 0; bit--) {
                        printf("%d", ((*q) >> bit)&0x01);
                }
        }
        printf("\n");
        return;
}

int main() {
        double f;
		cin >> f;
        PrintMem(&f, sizeof(double));
        system("pause");
        return 0;
}