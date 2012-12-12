#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
const int MAXLEN = 1000;
int main()
{
    char str1[MAXLEN];
    char str2[MAXLEN];
    char strres[MAXLEN];
    cin >> str1;
    cin >> str2;
    int** matr = new int* [strlen(str2)+1];
    for (unsigned int i = 0; i <= strlen(str2); ++i)
     matr[i] = new int [strlen(str1)+1];
    for (unsigned int i = 0; i <= strlen(str2); ++i)
     for (unsigned int j = 0; j <= strlen(str1); ++j)
      matr[i][j] = 0;

    for (unsigned int i = 1; i <= strlen(str2); ++i)
     for (unsigned  int j = 1; j <= strlen(str1); ++j)
      if (str2[i-1] == str1 [j-1])
      matr[i][j] = matr[i-1][j-1]+1;
      else
      matr[i][j] = max( matr[i-1][j], matr[i][j-1]);

    if (matr[strlen(str2)][strlen(str1)] == 0)
    { cout << "Empty"; return 0;}
    else cout << matr[strlen(str2)][strlen(str1)] << endl;
    int i = strlen(str2);
    int j = strlen(str1);
    while (matr[i][j] != 0)
    {

      if (str2[i-1] == str1[j-1])
      {
          strres[matr[i][j]-1] = str2[i-1];
          --i;--j;
      }
      else
      {
          if (matr[i-1][j] > matr[i][j-1]) --i;
          else --j;
      }
    }
   strres[matr[strlen(str2)][strlen(str1)]] = 0;
   cout << strres;
   for (unsigned int i = 0; i<=strlen(str2); ++i)
    delete [] matr [i];
   delete [] matr;
   return 0;
}
