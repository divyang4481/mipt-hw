#include<iostream>
using namespace std;
int size=0;
void delete_string_array(char **str)
{
	for(int i=0;i<size;++i)delete[]str[i];
	delete[] str;
}
char* copy(const char *a,int b,int l)
{
	char *c;int bb=b;
	c=new char[10000];
	for(int i=0;i<l;++i)
	{
		c[i]=a[bb];
		++bb;
	}
	c[l]='\0';
	return c;
}
char** split(const char *str, const char *delim)
{
	char **a;
	a=new char*[10000];
	char *t;
	t=new char[10000];
	int k=0,i=0,kk=0;
	while(i<=strlen(str)-strlen(delim))
	{   
		int kkk=0;
		t=copy(str,i,strlen(delim));
		for(int j=0;j<strlen(delim);++j)
			if(delim[j]!=t[j]){kkk=1;break;}
		if(kkk==0)
		{
				if(i-k!=0)
				{
					a[kk]=new char[10000];
					a[kk]=copy(str,k,i-k);
					++kk;
				}
				i+=strlen(delim);
				k=i;
		}
		else ++i;
	}
	if(i-k!=0)
				{
					a[kk]=new char[10000];
					a[kk]=copy(str,k,strlen(str)+1-k);
					++kk;
				}


			size=kk;
	return a;
}
int main()
{
	char **c;
	c=new char*[10000];
	char *a,*b;
	a=new char[10000];
	b=new char[10000];
	cin>>a;
	cin>>b;
	c=split(a,b);
	for(int i=0;i<size;++i)cout<<c[i]<<'\n';
	delete(c);
	return 0;
}