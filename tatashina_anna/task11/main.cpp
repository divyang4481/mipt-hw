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
                sumF += (float)1/((float)i*(float)i);
        }
        cout << sumF << "\n";
        sumF = 0;
        for (int i = n; i > 0; --i) {
                sumF += (float)1/((float)i*(float)i);
        }
        cout << sumF << "\n";

        for (int i = 1; i <= n; ++i) {
                sumD += 1.0/((double)i*(double)i);
        }
        cout << sumD << "\n";
        sumD = 0;
        for (int i = n; i > 0; --i) {
                sumD += 1.0/((double)i*(double)i);
        }
        cout << sumD << "\n";


        for (int i = 1; i <= n; ++i) {
                sumLD += 1.0/((long double)i*(long double)i);
        }
        cout << sumLD << "\n";
        sumLD = 0;
        for (int i = n; i > 0; --i) {
                sumLD += 1.0/((long double)i*(long double)i);
        }
        cout << sumLD << "\n";


}

int main()
{
    cout << fixed << setprecision(15);
        int n;
    cin >> n;

        SumRow(n);

        return 0;
}
