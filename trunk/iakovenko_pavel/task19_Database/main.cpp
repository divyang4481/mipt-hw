#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_NAME_SIZE = 30;
const int MAX_LASTNAME_SIZE = 50;
const int MAX_BIO_SIZE = 1024;
const int maxn=20;

struct TStudent {
	char Name[MAX_NAME_SIZE]; 
	char LastName[MAX_LASTNAME_SIZE]; 
	int ID; 
	float AverageMark; 
	char Bio[MAX_BIO_SIZE]; 
	TStudent(){
		char LastName[MAX_LASTNAME_SIZE]={' '};
		char Name[MAX_LASTNAME_SIZE]={' '};
		char Bio[MAX_BIO_SIZE]={' '};
		ID=0;
		AverageMark=0.0;
	};
	~TStudent(){
	}
	void FromString(char* buf){
		int k; int count=0;
		for (k=0;; k++){
			if (buf[k]==';')
				count++;
			if (count==4)
				break;
		}
		count=0;
		for (int i=0;count <4 ; i++){
			if (buf[i]==';'){
				buf[i]=' ';
				count++;
			}
		}
		sscanf(buf,"%s %s %d %f",&Name, &LastName, &ID, &AverageMark);
		int j=0;
		for (int i=k+1; buf[i]!=';'; i++){
			Bio[j]=buf[i];
			j++;
		}
		Bio[j]='\0';
	};
	char* ToString (char* buf){
		sprintf(buf, "%s;%s;%d;%f;%s;\n", Name,LastName,ID,AverageMark,Bio);
		return buf;
	};
	void print(){
		cout <<"------------------------------------------------\n";
		cout <<"Name: "<<Name<<endl;
		cout <<"Last Name: "<<LastName<<endl;
		cout <<"ID: "<<ID<<endl;
		cout <<"Average Mark: "<<AverageMark<<endl;
		cout <<"Biography: "<<Bio<<endl<<endl;
	}


};



class DataBase{
	vector<TStudent> Students;
	vector<int>ID ;
	vector<int>LN ;
	vector<int>LFN ;
	char path[128];

public:
	DataBase(){
	}
	~DataBase(){
	}
	void sort(int size){
		for (int k=1; k<size; k++){
			char temp [MAX_LASTNAME_SIZE];
			int key=LN[k];
			int j; 
			for (j=0; Students[key].LastName[j]!='\0'; j++)
				temp[j]=Students[key].LastName[j];
			temp[j]='\0';
			int i=k-1;
			while(i>=0 && (strcmp(Students[LN[i]].LastName,temp))>0){
				LN[i+1]=LN[i];
				i--;
			}

				LN[i+1]=key;
		}
		for(int k=0; k<size; k++)
			LFN[k]=LN[k];
		for (int k=1; k<size; k++){
			int key=LFN[k];
			char temp [MAX_LASTNAME_SIZE];
			char name [MAX_NAME_SIZE];
			int j;
			for (j=0; Students[key].Name[j]!='\0'; j++){
				name[j]=Students[key].Name[j];
			}
			name[j]='\0';
			for (j=0; Students[key].LastName[j]!='\0'; j++)
				temp[j]=Students[key].LastName[j];
			temp[j]='\0';
			int i=k-1;
			while(i>=0 && (strcmp(Students[LFN[i]].LastName,temp))==0 && (strcmp(Students[LFN[i]].Name,name))>0 ){
				LFN[i+1]=LFN[i];
				i--;
			}
			LFN[i+1]=key;
		}
		for( int k=1; k<size; k++){ 
			int key=ID[k];
			int ID1=Students[key].ID;
			int i=k-1;
			while(i>=0 && (Students[ID[i]].ID > ID1)){
				ID[i+1]=ID[i];
				i--;
			}
				ID[i+1]=key;
		}
	}
	
	bool loadbase(char* truepath){
		int i=0;
		for(; truepath[i]!='\0'; i++)
			path[i]=truepath[i];
		path[i]='\0';
		FILE* f=fopen(truepath,"r");
		if (f==0){
			f=fopen(truepath, "w");
			if (f==0){
			cout <<"Failed starting students.exe!\n" <<  
				"Error description:  could not open file!\n" <<
				"Usage:\n"<<
				"	students.exe <db_path.exe>\n";
			return false;
			}
			fclose(f);
			return true;
		}
		char c='5';
		char temp [1500];
		while(true){
			int i=0;
			do{
				c=fgetc(f);
				if(c==EOF)
					break;
				temp[i]=c;
				i++;
			}while(c!='\n');
			if(i==0 && c==EOF)
				break;
			TStudent tp;
			tp.FromString(temp);
			Students.push_back(tp);
		}
		fclose(f);
		int size=Students.size();
		for (int i=0; i<size; i++){
			ID.push_back(i);
			LN.push_back(i);
			LFN.push_back(i);
		}
		sort(size);
		cout << "Database is successfully loaded!\n";
		return true;
	}

	void searchByLastName(){
		if (LN.empty()){
			cout<<"Error! The database is empty!";
			return;
		}
		cout << "Enter Last Name:\n";
		char lastname[MAX_LASTNAME_SIZE];
		cin>> lastname;
		int a=0; int b=LN.size()-1; unsigned int tp; unsigned int tp1;
		int count1=0; int count2=0; 
		while(a<b){
			tp=a+(b-a)/2;
			int value=strcmp(lastname,Students[LN[tp]].LastName);
			if(value<=0)
				b=tp;
			else
				a=tp+1;
		}
		if (strcmp(lastname,Students[LN[b]].LastName)!=0){
			cout<<"Error! There is no student with such LastName in database!\n";
					return;
		}
		tp1=b;
		while (true){
			tp1++;
			if (tp1>Students.size()-1)
				break;
			if ((strcmp(lastname,Students[LN[tp1]].LastName))==0)
				count1++;
			else 
				break;
		}
		tp1=b;
		while (true){
			tp1--;
			if(tp1<0)
				break;
			if ((strcmp(lastname,Students[LN[tp1]].LastName))==0)
				count2++;
			else 
				break;
		}
	int count=count1+count2+1;
	cout <<"Students found with Last Name "<<lastname<<":"<<count<<endl;
		for (int i=b;i<=(count1+b); i++)
			Students[LN[i]].print();
		for (int i=b-1; i>(b-count2); i++)
			Students[LN[i]].print();
	}

	void searchByLastFirstName(){
		if (LN.empty()){
			cout<<"Error! The database is empty!";
			return;
		}
		cout << "Enter Last Name:\n";
		char lastname[MAX_LASTNAME_SIZE];
		cin >>lastname;
		cout << "Enter Name:\n";
		char name[MAX_NAME_SIZE];
		cin>>name;
		int count1=0; int count2=0; unsigned int tp1;
		int a=0; int b=LN.size()-1; unsigned int tp; int count=0; int count3=0;
		while(a<b){
			tp=a+(b-a)/2;
			int value=strcmp(lastname,Students[LN[tp]].LastName);
			if(value<=0)
				b=tp;
			else
				a=tp+1;
		}
		if (strcmp(lastname,Students[LN[b]].LastName)!=0){
			cout<<"Error! There is no student with such LastName + Name in database!\n";
			return;
		}
		if (strcmp(name,Students[LN[b]].Name)==0)
			count3++;
		tp1=b;
		while (true){
			tp1++;
			if (tp1>Students.size()-1)
				break;
			if ((strcmp(lastname,Students[LN[tp1]].LastName))==0){
				count1++;
				if (strcmp(name,Students[LN[tp1]].Name)==0)
					count3++;
			}
			else 
				break;
		}
		tp1=b;
		while (true){
			tp1--;
			if(tp1<0)
				break;
			if ((strcmp(lastname,Students[LN[tp1]].LastName))==0){
				count2++;
				if (strcmp(name,Students[LN[tp1]].Name)==0)
					count3++;
			}
			else 
				break;
		}
		if (count3==0){
			cout<<"Error! There is no student with such LastName + Name in database!\n";
			return;
		}
		cout <<"Students found with Last Name + Name "<<lastname<<" "<<name<<": "<<count3<<endl;
		for (int i=b;i<=(count1+b); i++)
			if(!strcmp(name,Students[LN[i]].Name))
				Students[LN[i]].print();
		for (int i=b-1; i>(b-count2); i++)
			if(!strcmp(name,Students[LN[i]].Name))
				Students[LN[i]].print();
	}

	int searchByIDhelp(int ID1){
		if (ID.size()==0)
			return -1;
		int count1=0; int count2=0;
		int a=0; int b=ID.size()-1; int tp; int count=0;
		while(a<b){
			tp=a+(b-a)/2;
			if (ID1<=Students[ID[tp]].ID)
				b=tp;
			else
				a=tp+1;
		}
		if (ID1==Students[ID[b]].ID)
			return ID[b];
		else
			return -1;
	}

	void searchByID(){
		if (ID.empty()){
			cout<<"Error! The database is empty!";
			return;
		}
		cout << "Enter ID:\n";
		int ID1;
		cin >>ID1;
		int i=searchByIDhelp(ID1);
		if(i<0)
			cout<<"Error! There is no student with such ID in database!\n";		
		else
			Students[i].print();
		return;
	}

	void search(){
		cout << "Enter:\n" <<
			" 1 - to search by LastName\n"<<
			" 2 - to search by LastName+Name\n" <<
			" 3 - to search by ID\n";
		int n;
		cin >> n;
		switch (n){
		case 1:searchByLastName(); break;
		case 2:searchByLastFirstName(); break;
		case 3:searchByID(); break;
		default: cout << "Wrong command!\n"; break;
		}
	}

	void add(){
		TStudent temp;
		cout << "Enter the ID: ";
		cin>>temp.ID;
		if(searchByIDhelp(temp.ID)>=0){
			cout << "Error: The student with this ID has been already added in Database!\n";
			return;
		}
		cout <<"Enter the name: ";
		char tempName[MAX_NAME_SIZE];
		cin >>tempName;
		int i;
		for (i=0;tempName[i]!='\0'; i++)
			temp.Name[i]=tempName[i];
		temp.Name[i]='\0';
		cout <<"Enter the last name: ";
		char tempLastName[MAX_LASTNAME_SIZE];
		cin>>tempLastName;
		for (i=0;tempLastName[i]!='\0'; i++)
			temp.LastName[i]=tempLastName[i];
		temp.LastName[i]='\0';
		cout << "Enter Average Mark: ";
		cin >> temp.AverageMark;
		cout <<"Enter the biography: ";
		char tempBio [MAX_BIO_SIZE];
		char c='5';
		cin>>c;
		gets(tempBio);
		temp.Bio[0]=c;
		int j;
		for (j=1; tempBio[j-1]!='\0'; j++)
			temp.Bio[j]=tempBio[j-1];
		temp.Bio[j]='\0';
		Students.push_back(temp);
		LN.push_back(Students.size()-1);
		LFN.push_back(Students.size()-1);
		ID.push_back(Students.size()-1);
		sort(Students.size());
		cout <<endl<< "This student is seccessfully added!\n";
	}

	void printall(){
		int size=LFN.size();
		for(int i=0; i<size; i++)
			Students[LFN[i]].print();
	}

	void del(){
		if (ID.empty()){
			cout<<"Error! The database is empty!";
			return;
		}
		cout << "Enter ID: ";
		int ID1;
		cin >>ID1;
		if (ID1<0)
			cout <<"Wrong ID! It should be non negative number\n";
		int i=searchByIDhelp(ID1);
		if(i>=0){
			for (unsigned int j=0; j<ID.size(); j++){
				if(ID[j]==i)
					ID.erase(ID.begin()+j);
				if (j<ID.size() &&ID[j]>i)
					ID[j]--;
			}
			for (unsigned int j=0; j<LN.size(); j++){
				if(LN[j]==i)
					LN.erase(LN.begin()+j);
				if (j<LN.size() &&LN[j]>i)
					LN[j]--;
			}
			for (unsigned int j=0; j<LFN.size(); j++){
				if(LFN[j]==i)
					LFN.erase(LFN.begin()+j);
				if (j<LFN.size() && LFN[j]>i)
					LFN[j]--;
			}
			Students.erase(Students.begin()+i);
			cout <<"Student was successfully deleted!\n";
		}
		else 
			cout <<"Error! There is no student with such ID!\n";
	}

	void quit(char* truepath){
		FILE* f=fopen(truepath, "w");
		int size=Students.size();
		char buf [2048];
		for(int i=0; i<size;i++)
			fputs(Students[i].ToString(buf), f);	
		fclose(f);
	}

	void InterFace (){
		char command[100];
		while (true){
			cout <<"Possible commands:\n" <<"	search\n	add\n	del\n	printall\n	quit\n"<<
				"Enter command:\n";
			bool flag=true;
			cin>>command;
			if(strcmp("search",command)==0)
				search(); 
			else if (strcmp("add",command)==0){
				add();
				sort(Students.size());
			}
			else if(strcmp("del",command)==0)
				del(); 
			else if (strcmp("printall",command)==0)
				printall();
			else if (strcmp("quit",command)==0){
				quit(path);
				return;
			}
			else
				flag=false;

			if(!flag)
				cout << "Error: Unknown command!\n";
		}
	}
};



bool CheckCommandLineArgs(int argc, char** argv){
	if (argc==2){
		if((strcmp(argv[1],"--help")==0)){
			cout <<"Usage:\n  students.exe <db_path.exe>";
			return false;
		}
		else
		return true;
	}
	else if (argc<2) {
		cout << "Failed starting students.exe!\nError description: not enough command-line arguments!\n"<<
		"Usage:\n     students.exe <db_path.exe>"<<endl;
		return false;
	}
	else if (argc>2){
		cout << "Failed starting students.exe!\nError description: too many command-line arguments!\n"<<
		"Usage:\n     students.exe <db_path.exe>"<<endl;
		return false;
	}
	return false;
}

int main(int argc, char** argv){
	if(!CheckCommandLineArgs(argc, argv)){
		return 0;
	}
	DataBase db;
	if(db.loadbase(argv[1]))
		db.InterFace();
	return 0;
}