#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <algorithm>

using namespace std;

const int max_n = 10000;
int size_res = 0;


bool cmp(const char *str1, const char *str2, int length) {
	for(int i = 0; i < length; ++i)
		if (str1[i] != str2[i])
			return false;
	return true;
}

char** split(const char *str, const char *delim) {
	int n = strlen(str), m = strlen(delim);
	char **result = new char*[n];
	int cur = 0, cur2 = 0;
	while (cur < n) {
		cur2 = cur;
		while ((cur2 < n - m) && !(cmp(str + cur2, delim, m)))
			++cur2;
		result[size_res] = new char [max_n];
		for (int i = 0; cur + i != cur2; ++i)
			result[size_res][i] = str[cur + i];
		result[size_res][cur2 - cur] = '\0';
		++size_res;
		cur = cur2 + m;
	}
	return result;
}

void delete_string_array(char **str) {
	for(int i = 0; i < size_res; ++i)
		delete [] str[i];
	delete [] str;
}

int main() {
    char *str = new char [max_n];
    char *delim = new char [max_n];
	cin >> str;
	cin >> delim;
	char **res = new char * [max_n];
	for (int i = 0; i < max_n; i++)
		res[i] = new char [max_n];
	res = split(str, delim);
	for (int i = 0; i < size_res; ++i) {
		for(int j = 0; j < strlen(res[i]); ++j)
			cout << res[i][j];
		cout << "\n";
	}
	delete(res);

	return 0;
}