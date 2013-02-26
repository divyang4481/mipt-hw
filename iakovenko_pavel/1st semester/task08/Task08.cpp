#include <iostream>
using namespace std;

int nString, length; 
const int maxn=10000;

char** split(const char *str, const char *delim);
void delete_string_array(char **str);
bool chet(const char *str, const char *delim, int i);

int main(){ 
	char *str = new char [maxn];
    char *delim = new char [maxn];
	cin >>str;
	cin >>delim;
	length=strlen(str);
	char **result = new char* [length];
    for(int i=0; i<length; i++)
		result[i] = new char [length+1];
	result=split(str, delim);
	for(int i=0; i<=nString; i++)
		cout << result[i]<< endl;
	delete_string_array(result);
	delete [] str;
	delete [] delim;
	system("pause");
	return 0;
}

char** split(const char *str, const char *delim){
	int n2=strlen(delim);
	char **ptr = new char* [length];
    for(int i=0; i<length; i++)
		ptr[i] = new char [length+1];
	int k=0,l=k;
	for(int i=0; i<length; i++){
		int flag=chet(str, delim,i);
		if(flag){
			ptr[k][l]=str[i];
			l++;		
		}
		else {
			i+=n2-1; 
			ptr[k][l]='\0';
			k++;
			l=0; 
		}
	}
	nString=k;
	ptr[k][l]='\0';
	return ptr;
}

bool chet(const char *str, const char *delim, int i){
	int n2=strlen(delim);
	if(str[i]==delim[0]){
		for(int j=1;j<n2; j++)
			if(str[i+j]!=delim[j])
				return true;
		return false;
	}
	return true;
}

void delete_string_array(char **str){
	for (int i=0; i<nString; i++)
		delete [] str[i];
	delete [] str;
}