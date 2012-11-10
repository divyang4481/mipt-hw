#include <iostream>
using namespace std;

int nString, length; 
const int maxn=10000;

char** split(const char *str, const char *delim);
void delete_string_array(char **str);
int chet(const char *str, const char *delim, int i); //определяет, есть ли последовательность символов в расщепляемой строке, которая равна расщепителю

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

int chet(const char *str, const char *delim, int i){
	int n2=strlen(delim);
	if(str[i]==delim[0]){
		for(int j=1;j<n2; j++)
			if(str[i+j]!=delim[j])
				return 1;
		return 0;
	}
	return 1;
}

void delete_string_array(char **str){
	for (int i=0; i<nString; i++)
		free(str[i]);
	free(str);
	}