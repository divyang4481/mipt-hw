#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef char my_str[255];
char* my_strstr (const char * str1,const char * str2)
{
        const char* cp = str1;
        const char* s1;
		const char* s2;
        while (*cp)
        {
                s1 = cp;
                s2 = str2;
                while (*s1 && *s2 && (*s1 == *s2) )
				{
                    s1++;
					s2++;
				}
                if (!*s2)
                        return (char*)cp;
                cp++;
        }
        return NULL;
}
char** split(const char *str, const char *delim)
{
	int k;
	int i = 0;
	char** b;
	char* a;
	char* str2=(char*)malloc(sizeof(my_str));
	if (str2==NULL)
		return NULL;
	strcpy(str2,str);
	b = (char**) malloc(sizeof(char*));
	if (b==NULL)
	{
		free(str2);
		return NULL;
	}
	a=*b;
	a = my_strstr(str2,delim);
	if (a==NULL)
	{
		free(b);
		free(str2);
		return NULL;
	}
	else
	{
		while(a = my_strstr(str2,delim))
		{
			b = (char**) realloc(b,(i+2)*sizeof(char*)); 
			if (b==NULL)
			{
				free(str2);
				free(b);
				return NULL;
			}
			b[i]=(char*)malloc(sizeof(my_str));
			if (b[i]==NULL)
			{
				free(str2);
				for (int j=0;j<i;j++)
				{
					free(b[j]);
				}
				free(b);
				return NULL;
			}
			k = a-str2;
			strncpy(b[i++], str2,k);  
			b[i-1][k]='\0';                         
			a+=strlen(delim);
			str2+=(k+strlen(delim));   
		}
		b = (char**) realloc(b,(i+2)*sizeof(char*));
		if (b==NULL)
			{
				free(str2);
				free(b);
				return NULL;
			}
		b[i]=(char*)malloc(sizeof(my_str));
			if (b[i]==NULL)
			{
				free(str2);
				free(b);
				return NULL;
			}
		strncpy(b[i], str2,strlen(str2));
		b[i][strlen(str2)]='\0';
		b[i+1] = NULL;
	}
	return b;	
}
void delete_string_array(char **b)
{
	int i;
	for (i=0; b[i]!=NULL; i++)
	{
		free(b[i]);
	}
	free(b);
}
int main()
{
	my_str s,d;
	char** p;
	int i;	
	scanf("%s",s);
	scanf("%s",d);
	p = split(s, d);
	if (p != NULL)
	{
		for (i = 0; p[i]!=NULL;i++)
			printf("%s \n", p[i]);
		delete_string_array(p);
	}
	else printf("Delim is not found");
	return 0;
}
