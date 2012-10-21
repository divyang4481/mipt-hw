#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

char** split(const char *str, const char *delim);
void delete_string_array(char **str);

const char someUnusedChar = (char) 18;
const int maxn = 10000;

extern int size = 0;

vector<int> prefix_function(const char *s) {
    int n = (int) strlen(s);
	vector<int> pi (n);
	for (int i = 1; i < n; ++i) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])
            ++j;
		pi[i] = j;
	}
    return pi;
}

char** split(const char *str, const char *delim) {
    char **temp = (char **) malloc(maxn * sizeof(char*));

    char *s = (char*) malloc((size_t) (strlen(str) + strlen(delim)) * sizeof(char) + 2);     //  1 for '\0' and 1 for separator
    int divLen = strlen(delim);
    int sLen = strlen(str);
    for (int i = 0; i < divLen; ++i)
        s[i] = delim[i];
    s[divLen] = someUnusedChar;
    for (int i = 0; i < sLen; ++i)
        s[divLen + 1 + i] = str[i];
    s[divLen + 1 + sLen] = '\0';

	vector<int> pi = prefix_function(s);
    int n = strlen(s);
    char *pBuffer = (char*) malloc((size_t) maxn * sizeof(char));
    int currentLength = 0;
    int strings = 0;
    for (int i = divLen + 1; i < n; ++i) {
        if (pi[i] == divLen) {
            //  separator matches
            if (currentLength > 0) {
                int id = strings++;
                temp[id] = (char*) malloc((size_t) (currentLength + 1) * sizeof(char));
                for (int j = 0; j < currentLength; ++j)
                    temp[id][j] = pBuffer[j];
                temp[id][currentLength] = '\0';
            }
            currentLength = 0;
        }
        else
            pBuffer[currentLength++] = s[i];
    }
    if (currentLength > 0) {
        int id = strings++;
        temp[id] = (char*) malloc((size_t) (currentLength + 1) * sizeof(char));
        for (int j = 0; j < currentLength; ++j)
            temp[id][j] = pBuffer[j];
        temp[id][currentLength] = '\0';
    }
    free(pBuffer);
    free(s);

    char **ret = (char **) malloc((size_t) strings * sizeof(char*));
    for (int i = 0; i < strings; ++i)
        ret[i] = temp[i];
    free(temp);
    size = strings;
    return ret;
}

void delete_string_array(char **str) {
    for (int i = 0; i < size; ++i)
        free(str[i]);
    free(str);
}

int main() {
    char *s = (char*) malloc((size_t) maxn * sizeof(char));
    char *separator = (char*) malloc((size_t) maxn * sizeof(char));
    cin >> s;
    cin >> separator;
    char **res = split(s, separator);
    for (int i = 0; i < size; ++i)
        cout << res[i] << endl;
    delete_string_array(res);
    system("pause");
    return 0;
}