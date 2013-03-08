#include <iostream>
using namespace std;

void Print(int **b, char *str1, int i, int j)
{
    if ((i==0) || (j==0))
        return;
    if (b[i][j]==0)
    {
        Print(b, str1, i-1, j-1);
        cout << str1[i-1];
    }
    else if (b[i][j]==1) Print(b, str1, i-1, j);
    else Print(b, str1, i, j-1);
}

int main()
{
    char str1[1000], str2[1000], strcmn[1000];
    cin >> str1;
    cin >> str2;
    int m = strlen(str1), n = strlen(str2);
    int **c = new int*[m+1];
    for (int i=0; i<m+1; i++)
        c[i] = new int [n+1];
    int **b = new int*[m+1];
    for (int i=0; i<m+1; i++)
        b[i] = new int [n+1];
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <=n; ++j)
            c[i][j] = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (str1[i-1] == str2[j-1])
            {
                c[i][j] = c[i-1][j-1]+1;
                b[i][j] = 0;
            }
            else if (c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]=1;
            }
            else
            {
                c[i][j]=c[i][j-1];
                b[i][j]=-1;
            }
    if (c[m][n] == 0) return 0;
    else cout << c[m][n] << endl;
    Print(b, str1, m, n);
    for (int i=0; i<=m; ++i) delete [] b[i];
    delete [] b;
    for (int i=0; i<=m; ++i) delete [] c[i];
    delete [] c;
    return 0;
}