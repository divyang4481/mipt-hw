#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

void SumRow(int n) {
        float sumF = 0;
        double sumD = 0;
        long double sumLD = 0;
        
        for (int i = 1; i <= n; ++i) {
                sumF += 1/((float)i*i);
        }
        cout << setprecision (8) << sumF << "\n";
        sumF = 0;
        for (int i = n; i > 0; --i) {
                sumF += 1/((float)i*i);
        }
        cout << setprecision (8) <<  sumF << "\n";

        for (int i = 1; i <= n; ++i) {
                sumD += 1.0/((double)i*i);
        }
        cout << setprecision (16) << sumD << "\n";
        sumD = 0;
        for (int i = n; i > 0; --i) {
                sumD += 1.0/((double)i*i);
        }
        cout << setprecision (16) << sumD << "\n";


        for (int i = 1; i <= n; ++i) {
                sumLD += 1.0/((long double)i*i);
        }
        cout << setprecision (32) << sumLD << "\n";
        sumLD = 0;
        for (int i = n; i > 0; --i) {
                sumLD += 1.0/((long double)i*(long double)i);
        }
        cout << setprecision (32) << sumLD << "\n";


}

int main()
{
    int n;
    cin >> n;

    SumRow(n);

    return 0;
}