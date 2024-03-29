#include <iostream>
using namespace std;

int Count;

bool isSplit(const char *str, const char *delim, int st){
	for (unsigned int i=0; i<strlen(delim); i++){
		if (str[st+i]!=delim[i]) return false;
	}
	return true;
}

char** split(const char* str, const char*delim){
	int sl=strlen(str);
	int dl=strlen(delim);
	int i;
	char** s=new char*[sl];
	for (int i=0; i<sl; i++)
		s[i]=new char[sl];
	int sn=0;
	for (i=0; i<sl; i++){
		if (isSplit(str, delim, i)){
			if ((i==0)||((i>=dl)&&(isSplit(str, delim, i-dl)))) {
				i+=dl-1;
			}
			else {
				if ((i+dl<sl)){
					i+=dl-1;
					s[Count][sn]='\0';
					Count++;
					sn=0;
				}
				else {
					s[Count][sn]='\0';
					return s;
				}
			}
		}
		else{
			s[Count][sn]=str[i];
			sn++;
		}
	}
	s[Count][sn]='\0';
	return s;
}

void delete_string_array(char **str){
	for (unsigned int i=0; i<=Count; i++)
		delete [] str[i];
	delete [] str;
}

int main(){
	char* str=new char[10000];
	char* spl=new char[10000];
	cin >> str;
	cin >> spl;
	int length=strlen(str);
	char** r=new char* [length];
	for (int i=0; i<length; i++)
		r[i]=new char [length];
	r=split(str, spl);
	for (int i=0; i<=Count; i++)
		cout << r[i] << endl;
	delete_string_array(r);
	delete[] str;
	delete[] spl;
	system("pause");
	return 0;
}
