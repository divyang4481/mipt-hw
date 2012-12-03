#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;


const int MAXLEN = 10000;
int count = 0;
bool tocheck(const char* s, int len, const char *ssplit)
{

    for (int i = 0; (i < len); ++i)
     if (s[i]!=ssplit[i])
     return false;
    return true;
}

char** split(const char *s, const char *ssplit)
{
    int lens = strlen(s); int lenss = strlen(ssplit);
    char** buf = new char* [lens];


    int afterwr = 0;
    for (int i = 0; (i < (lens - lenss+1)); ++i)
     {
         if (tocheck(s+i, lenss, ssplit))
         {

             buf [count] = new char [i - afterwr];
             for (int j = 0; j < (i-afterwr); ++j)
              buf[count][j] = s[afterwr+j];
             buf[count][i-afterwr] = '\0';
             //if (buf[count][0]!=0) cout << buf[count] << '\n';
             count++;
             afterwr = i+lenss;

             i = i + lenss-1;

         }
     }
    if (s[afterwr] != '\0')
    {
        buf [count] = new char [lens - afterwr];
        for (int j = 0; s[afterwr+j]!=0; ++j)
         buf[count][j] = s[afterwr+j];
        buf[count][lens-afterwr]=0;
        count++;

       // buf[count][i-afterwr] = 0;
    }
    return buf;
}
void delete_string_array(char **str, int len)
{
    for (int i = 0; i < len; ++i)
     delete [] str [i];
    delete [] str;
}
int main()
{
   char* s = new char [MAXLEN];
   char* ssplit = new char [MAXLEN];
   cin >> s;
   cin >> ssplit;

   int len = strlen(s);
   char** buf = new char* [len];
   for (int i = 0; i < len; ++i )
     buf[i] = new char [len];
   buf = split(s,ssplit);
   for (int i = 0; i< count; ++i)
    if (buf[i][0]!=0) cout << buf[i] << '\n';
   delete_string_array(buf, len);
   return 0;
}
