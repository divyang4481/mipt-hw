#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <algorithm>
#include <cstring>

using namespace std;

const int max_n = 10000;
int size_res = 0;

bool compare_from_n(const char *str, const char *substr, int pos) {
    int l = strlen(substr);
    if (l + pos - 1 > (int) strlen(str))
        return false;
    for(int i = 0; i < l; i++)
        if(str[pos + i] != substr[i])
            return false;
    return true;
}

char** split(const char *str, const char *delim) {
    int n = strlen(str);
    int m = strlen(delim);
    int temp_pos = 0;

    char **result = new char*[n + 1];
    for (int i = 0; i < n; i++)
        result[i] = new char[n + 1];


    for (int i = 0; i < n; i++) {
        if (!compare_from_n(str, delim, i))
            result[size_res][temp_pos++] = str[i];
        if (compare_from_n(str, delim, i)) {
            if (temp_pos)
                result[size_res++][temp_pos] = '\0';
            temp_pos = 0;
            i += m - 1;
        }
    }

    result[size_res][temp_pos] = '\0';
    return result;
}

void delete_string_array(char **str) {
    for(int i = 0; i < size_res; ++i)
        delete [] str[i];
    delete [] str;
}

int main() {
    char *str = new char [max_n + 1];
    char *delim = new char [max_n + 1];
    cin >> str;
    cin >> delim;
    char **res = new char* [max_n + 1];
    strcat(str, delim);
    for (int i = 0; i < max_n; i++)
        res[i] = new char [max_n + 1];
    res = split(str, delim);
    for (int i = 0; i < size_res; ++i) {
        cout << "|";
        for(int j = 0; j < (int) strlen(res[i]); ++j)
            cout << res[i][j];
        cout << "|\n";
    }
    delete(res);

    return 0;
}
 