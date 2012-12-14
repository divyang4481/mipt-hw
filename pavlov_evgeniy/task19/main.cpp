#include<iostream>
#include<cstring>
using namespace std;
const int MAX_NAME_SIZE = 30;
const int MAX_LASTNAME_SIZE = 50;
const int MAX_BIO_SIZE = 1024;
int kontrol=0;

struct TStudent 
{
   char Name[MAX_NAME_SIZE]; // Имя 
   char LastName[MAX_LASTNAME_SIZE]; // Фамилия
   int ID; // Номер студ билета
   float AverageMark; // Средний балл
   char Bio[MAX_BIO_SIZE]; // Биография
};

struct TStu
{
	TStudent value;
	TStu *left,*right;
};

struct TS
{
	TStu *value;
	TS *left,*right;
};

void print(TS *first)
{
	if(first->left)print(first->left);
	cout<<"-------------------------------------\nName: "<<first->value->value.Name;
	cout<<"\nLastName: "<<first->value->value.LastName<<"\nID: "<<first->value->value.ID;
	cout<<"\nAverageMark: "<<first->value->value.AverageMark<<"\nBio: "<<first->value->value.Bio<<'\n';
	if(first->right)print(first->right);
}

void fpr(FILE *f,TS *first)
{
	if(first)
	{
	int j=0,k=0;
	char name[MAX_NAME_SIZE],lname[MAX_LASTNAME_SIZE],bio[MAX_BIO_SIZE];
	while(first->value->value.Name[k])
	{
		if(first->value->value.Name[k]==';')
		{
			name[j]='\\';
			++j;
		}
		name[j]=first->value->value.Name[k];
		++j;++k;
	}
	name[j]='\0';
	j=0;k=0;
	while(first->value->value.LastName[k])
	{
		if(first->value->value.LastName[k]==';')
		{
			lname[j]='\\';
			++j;
		}
		lname[j]=first->value->value.LastName[k];
		++j;++k;
	}
	lname[j]='\0';
	j=0;k=0;
	while(first->value->value.Bio[k])
	{
		if(first->value->value.Bio[k]==';')
		{
			bio[j]='\\';
			++j;
		}
		bio[j]=first->value->value.Bio[k];
		++j;++k;
	}
	bio[j]='\0';
	if(first->left)fpr(f,first->left);
	fprintf(f,"%s;%s;%d;%f;%s\n",name,lname,first->value->value.ID,first->value->value.AverageMark,bio);
	if(first->right)fpr(f,first->right);
	}
}

void del(TS *u,TStu *a)
{
	if((u->left)&&(u->left->value==a))
	{
		kontrol=1;
		TS *uu=u->left->right,*uu1;
		uu1=uu;
		if(uu)
		{
		while(uu->left)uu=uu->left;
		uu->left=u->left->left;
		}
		else uu=u->left->left;
		u->left=uu1;
		exit;
	}
	if((u->right)&&(u->right->value==a))
	{
		kontrol=1;
		TS *uu=u->right->right,*uu1;
		uu1=uu;
		if(uu)
		{
		while(uu->left)uu=uu->left;
		uu->left=u->right->left;
		}
		else uu=u->right->left;
		u->right=uu1;
		exit;
	}
	if(u->left)del(u->left,a);
	if(kontrol==1)exit;
	if(u->right)del(u->right,a);	
}

int main()
{
	char a[50],b,name[MAX_NAME_SIZE],lname[MAX_LASTNAME_SIZE],bio[MAX_BIO_SIZE],a1[50],fail[50];
	cin.getline(a,50);
	strcpy(fail,a);
	if(a[0]=='\0')
	{
		cout<<"Failed starting students.exe!\nError description: not enough command-line arguments!";
		return 0;
	}
	int kon=0,kol=0;
	for(int i=0;a[i];++i)if(a[i]==' '){kon=1;break;}
	if(kon)
	{
		cout<<"Failed starting students.exe!\nError description: too many command-line arguments!";
		return 0;
	}
	FILE *f;
	f=fopen(a,"a+");
	if(f==NULL)
	{
		cout<<"Failed starting students.exe!\nError description: could not open file: \""<<a<<"\"";
		return 0;
	}
	int k=0,id;
	float ball;
	TStu *first1=NULL,*x;
	TS *first2=NULL,*xx,*first3=NULL,*xxx;
	while(!(feof(f)))
	{
		fscanf(f,"%c",&b);
		if(feof(f))break;
		while(b!=';')
		{
			name[k]=b;
			++k;
			fscanf(f,"%c",&b);
			if((b==';')&&(name[k-1]=='\\'))
			{
				name[k-1]=';';
				fscanf(f,"%c",&b);
			}
		}
		name[k]='\0';
		k=0;
		fscanf(f,"%c",&b);
		while(b!=';')
		{
			lname[k]=b;
			++k;
			fscanf(f,"%c",&b);
			if((b==';')&&(lname[k-1]=='\\'))
			{
				lname[k-1]=';';
				fscanf(f,"%c",&b);
			}
		}
		lname[k]='\0';
		k=0;
		fscanf(f,"%d",&id);
		fscanf(f,"%c",&b);
		fscanf(f,"%f",&ball);
		fscanf(f,"%c",&b);
		fscanf(f,"%c",&b);
		while((b!='\n')&&!(feof(f)))
		{
			bio[k]=b;
			++k;
			fscanf(f,"%c",&b);
			if((b==';')&&(bio[k-1]=='\\'))
			{
				bio[k-1]=';';
				fscanf(f,"%c",&b);
			}
		}
		bio[k]='\0';
		k=0;
		x=first1;
		xx=first2;
		xxx=first3;
		if(first1==NULL)
		{
			first1=new TStu;
			first1->left=NULL;
			first1->right=NULL;
			x=first1;
			x->value.ID=id;
			x->value.AverageMark=ball;
			strcpy(x->value.Bio,bio);
			strcpy(x->value.LastName,lname);
			strcpy(x->value.Name,name);
			first2=new TS;
			first2->left=NULL;
			first2->right=NULL;
			first2->value=first1;
			first3=new TS;
			first3->left=NULL;
			first3->right=NULL;
			first3->value=first1;
		}
		else
		{
			while(1)
			{
				if(id>x->value.ID)
				{
					if(x->right==NULL)
					{
						x->right=new TStu;
						x=x->right;
						break;
					}
					else
					{
						x=x->right;
					}
				}
				else
				{
					if(x->left==NULL)
					{
						x->left=new TStu;
						x=x->left;
						break;
					}
					else
					{
						x=x->left;
					}
				}
			}
			x->left=x->right=NULL;
			x->value.ID=id;
			x->value.AverageMark=ball;
			strcpy(x->value.Bio,bio);
			strcpy(x->value.LastName,lname);
			strcpy(x->value.Name,name);




			while(1)
			{
				if((strcmp(xx->value->value.LastName,x->value.LastName)<0)||((strcmp(xx->value->value.LastName,x->value.LastName)==0)&&(strcmp(xx->value->value.Name,x->value.Name)<0)))
				{
					if(xx->right==NULL)
					{
						xx->right=new TS;
						xx=xx->right;
						break;
					}
					else
					{
						xx=xx->right;
					}
				}
				else
				{
					if(xx->left==NULL)
					{
						xx->left=new TS;
						xx=xx->left;
						break;
					}
					else
					{
						xx=xx->left;
					}
				}
			}
			xx->left=xx->right=NULL;
			xx->value=x;



			while(1)
			{
				if(strcmp(xxx->value->value.LastName,x->value.LastName)<0)
				{
					if(xxx->right==NULL)
					{
						xxx->right=new TS;
						xxx=xxx->right;
						break;
					}
					else
					{
						xxx=xxx->right;
					}
				}
				else
				{
					if(xxx->left==NULL)
					{
						xxx->left=new TS;
						xxx=xxx->left;
						break;
					}
					else
					{
						xxx=xxx->left;
					}
				}
			}
			xxx->left=xxx->right=NULL;
			xxx->value=x;
		}
		++kol;
	}
	cout<<"Database successfully loaded!\nNumber of students "<<kol<<"\nPossible commands:\n   search\n   add\n   del\n   printall\n   quit\nEnter command:\n";
	char aa[50];
	while(1)
	{
		cin>>aa;
		if(!strcmp(aa,"search"))
		{
			cout<<"Enter:\n   1 - to search by LastName\n   2 - to search by LastName+Name\n   3 - to search by ID\n";
			k=0;
			while((k>3)||(k<1))cin>>k;
			if(k==1)
			{
				cout<<"Enter LastName:\n";
				cin>>a;
				kol=0;
				TS *u=first3,*uu;
				while((u)&&(strcmp(u->value->value.LastName,a)!=0))
					if(strcmp(u->value->value.LastName,a)<0)u=u->right;
					else u=u->left;
				uu=u;
				while((uu)&&(!strcmp(uu->value->value.LastName,a)))
				{
					++kol;
					uu=uu->left;
				}
				cout<<"Students found with LastName=\""<<a<<"\": "<<kol<<"\n";
				for(int i=0;i<kol;++i)
				{
					cout<<"-------------------------------------\nName: "<<u->value->value.Name;
					cout<<"\nLastName: "<<u->value->value.LastName<<"\nID: "<<u->value->value.ID;
					cout<<"\nAverageMark: "<<u->value->value.AverageMark<<"\nBio: "<<u->value->value.Bio<<'\n';
					u=u->left;
				}
			}
			else if(k==2)
			{
				cout<<"Enter LastName+Name:\n";
				cin>>a>>a1;
				kol=0;
				TS *u=first2,*uu;
				while((u)&&((strcmp(u->value->value.LastName,a)!=0)||(strcmp(u->value->value.Name,a1)!=0)))
					if((strcmp(u->value->value.LastName,a)<0)||((strcmp(u->value->value.LastName,a)==0)&&(strcmp(u->value->value.Name,a1)<0)))u=u->right;
					else u=u->left;
				uu=u;
				while((uu)&&(!strcmp(uu->value->value.LastName,a))&&(!strcmp(uu->value->value.Name,a1)))
				{
					++kol;
					uu=uu->left;
				}
				cout<<"Students found with LastName+Name=\""<<a<<" "<<a1<<"\": "<<kol<<"\n";
				for(int i=0;i<kol;++i)
				{
					cout<<"-------------------------------------\nName: "<<u->value->value.Name;
					cout<<"\nLastName: "<<u->value->value.LastName<<"\nID: "<<u->value->value.ID;
					cout<<"\nAverageMark: "<<u->value->value.AverageMark<<"\nBio: "<<u->value->value.Bio<<'\n';
					u=u->left;
				}
			}
			else
			{
				cout<<"Enter ID:\n";
				cin>>kon;
				kol=0;
				TStu *u=first1,*uu;
				while((u)&&(u->value.ID!=kon))
					if(u->value.ID<kon)u=u->right;
					else u=u->left;
				if(u)
				{
				cout<<"-------------------------------------\nName: "<<u->value.Name;
				cout<<"\nLastName: "<<u->value.LastName<<"\nID: "<<u->value.ID;
				cout<<"\nAverageMark: "<<u->value.AverageMark<<"\nBio: "<<u->value.Bio<<'\n';
				u=u->left;
				}
				else cout<<"student with this ID dont exist\n";
			}
		}
		else if(!strcmp(aa,"add"))
		{
			cout<<"Enter Name:\n";
			cin>>name;
			cout<<"Enter LastName:\n";
			cin>>lname;
			cout<<"Enter ID:\n";
			cin>>id;
			cout<<"Enter AverageMark:\n";
			cin>>ball;
			cout<<"Enter Bio:\n";
			cin>>bio;
			TStu *u=first1;
            while((u)&&(u->value.ID!=id))
				if(u->value.ID<id)u=u->right;
				else u=u->left;
				if(u)
				{
					cout<<"Error:student with this ID already in the database\n";
				}
				else
				{


			k=0;
		x=first1;
		xx=first2;
		xxx=first3;
		if(first1==NULL)
		{
			first1=new TStu;
			first1->left=NULL;
			first1->right=NULL;
			x=first1;
			x->value.ID=id;
			x->value.AverageMark=ball;
			strcpy(x->value.Bio,bio);
			strcpy(x->value.LastName,lname);
			strcpy(x->value.Name,name);
			first2=new TS;
			first2->left=NULL;
			first2->right=NULL;
			first2->value=first1;
			first3=new TS;
			first3->left=NULL;
			first3->right=NULL;
			first3->value=first1;
		}
		else
		{
			while(1)
			{
				if(id>x->value.ID)
				{
					if(x->right==NULL)
					{
						x->right=new TStu;
						x=x->right;
						break;
					}
					else
					{
						x=x->right;
					}
				}
				else
				{
					if(x->left==NULL)
					{
						x->left=new TStu;
						x=x->left;
						break;
					}
					else
					{
						x=x->left;
					}
				}
			}
			x->left=x->right=NULL;
			x->value.ID=id;
			x->value.AverageMark=ball;
			strcpy(x->value.Bio,bio);
			strcpy(x->value.LastName,lname);
			strcpy(x->value.Name,name);




			while(1)
			{
				if((strcmp(xx->value->value.LastName,x->value.LastName)<0)||((strcmp(xx->value->value.LastName,x->value.LastName)==0)&&(strcmp(xx->value->value.Name,x->value.Name)<0)))
				{
					if(xx->right==NULL)
					{
						xx->right=new TS;
						xx=xx->right;
						break;
					}
					else
					{
						xx=xx->right;
					}
				}
				else
				{
					if(xx->left==NULL)
					{
						xx->left=new TS;
						xx=xx->left;
						break;
					}
					else
					{
						xx=xx->left;
					}
				}
			}
			xx->left=xx->right=NULL;
			xx->value=x;



			while(1)
			{
				if(strcmp(xxx->value->value.LastName,x->value.LastName)<0)
				{
					if(xxx->right==NULL)
					{
						xxx->right=new TS;
						xxx=xxx->right;
						break;
					}
					else
					{
						xxx=xxx->right;
					}
				}
				else
				{
					if(xxx->left==NULL)
					{
						xxx->left=new TS;
						xxx=xxx->left;
						break;
					}
					else
					{
						xxx=xxx->left;
					}
				}
			}
			xxx->left=xxx->right=NULL;
			xxx->value=x;
			}
			cout<<"student successfully loaded\n";
			}
		}
		else if(!strcmp(aa,"del"))
		{
			cout<<"Enter ID:\n";
			cin>>id;
			TStu *u=first1,*u1,*u2;
			while((u)&&(u->value.ID!=id))
				if(u->value.ID<id){u1=u;u=u->right;}
				else {u1=u;u=u->left;}
				if(!u)
				{
					cout<<"Error:student with this ID dont exist\n";
				}
				else
				{
					TS *uu=new TS;
					uu->left=NULL;
					uu->right=first2;
					del(uu,u);
					kontrol=0;
					first2=uu->right;
					uu=new TS;
					uu->left=NULL;
					uu->right=first3;
					del(uu,u);
					kontrol=0;
					if(u==first1)
					{
						u2=first1;
						if(u->right)
						{
							u=u->right;
							while(u->left)u=u->left;
							u->left=first1->left;
							first1=first1->right;
						}
						else first1=first1->left;
						delete u2;
					}else
					{
					first3=uu->right;
					if(u1->left==u)
					{
						u2=u1->left->right;
						if(u2)
						{
							while(u2->left)u2=u2->left;
							u2->left=u1->left->left;
							u1->left=u1->left->right;
						}
						else u1->left=u1->left->left;
					}
					else
					{
						u2=u1->right->right;
						if(u2)
						{
							while(u2->left)u2=u2->left;
							u2->left=u1->right->left;
							u1->right=u1->right->right;
						}
						else u1->right=u1->right->left;
					}
					delete u;
					}
					cout<<"studen successfully removed\n";
				}
		}
		else if(!strcmp(aa,"printall"))
		{
			if(first2)
			print(first2);
			else cout<<"database is empty\n";
		}
		else if(!strcmp(aa,"quit"))
		{
			fclose(f);
			f=fopen(fail,"wt");
			fpr(f,first2);
			fclose(f);
			break;
		}
	}
	return 0;
}