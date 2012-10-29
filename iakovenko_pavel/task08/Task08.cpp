#include <iostream>
using namespace std;

int nString, length; 
const int maxn=10000;

char** split(const char *str, const char *delim);
void delete_string_array(char **str);

int main(){ 
	extern int length;
	char *str = (char*) malloc(maxn * sizeof(char));
    char *delim = (char*) malloc(maxn * sizeof(char));
	cin >>str;
	cin >>delim;
	length=(int)strlen(str);
	char **result = new char* [length];
    for(int i=0; i<length; i++)
    result[i] = new char [length+1];
	result=split(str, delim);
	for(int i=0; i<=nString; i++)
		cout << result[i]<< endl;
	delete_string_array(result);
	system("pause");
	return 0;
}

char** split(const char *str, const char *delim){
	extern int length,nString;
	int n=strlen(str);
	int n2=strlen(delim);
	char **ptr = new char* [length];
    for(int i=0; i<length; i++){
    ptr[i] = new char [length+1];
	int k,l; k=l=0;
	for(int i=0; i<length; i++){
		if(str[i]==delim[0]){
			for(int j=1;j<n2; j++)
				if(str[i+j]!=delim[j])
					 goto next;
			i+=n2-1; ptr[k][l+1]='\0';
			k++;l=0; goto next1;
		}
next:
	ptr[k][l]=str[i];
	l++;
next1:
;	}
	nString=k;
	ptr[k][l+1]='\0';
	return ptr;
}

void delete_string_array(char **str){
	for (int i=0; i<nString; i++)
		free(str[i]);
	free(str);
	}