#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_NAME_SIZE = 30;
const int MAX_LASTNAME_SIZE = 50;
const int MAX_BIO_SIZE = 1024;

struct TStudent {
	char Name[MAX_NAME_SIZE]; 
	char LastName[MAX_LASTNAME_SIZE]; 
	int ID; 
	float AverageMark; 
	char Bio[MAX_BIO_SIZE]; 
	TStudent()
    {
        Name[0] = 0;
        LastName[0] = 0;
        ID = 0;
        AverageMark = 0.0;
        Bio[0] = 0;
	}
	~TStudent()
    {
        Name[0] = 0;
        LastName[0] = 0;
        ID = 0;
        AverageMark = 0;
        Bio[0] = 0;
	}

    void ReadStr(char* buf) 
    {
		int i, count=0;
		for (i=0; count<4; i++)
        {
			if (buf[i]==';')
            {
                buf[i]=' ';
				count++;
            }
		}
		sscanf(buf,"%s %s %d %f",&Name, &LastName, &ID, &AverageMark);
		int k;
        for (k=0; buf[i]!=';'; i++, k++)
        {
			Bio[k]=buf[i];
		}
		Bio[k]=0;
    }

	char* WriteStr (char* buf)
    {
		sprintf(buf, "%s;%s;%d;%f;%s;\n", Name, LastName, ID, AverageMark, Bio);
		return buf;
	}
	void print()
    {
		cout <<"------------------------------------------------"<<endl;
		cout <<"Name: "<<Name<<endl;
		cout <<"Last Name: "<<LastName<<endl;
		cout <<"ID: "<<ID<<endl;
		cout <<"Average Mark: "<<AverageMark<<endl;
		cout <<"Biography: "<<Bio<<endl<<endl;
	}
};

class DataBase
{
public:
	vector <TStudent> Students;
	vector <int> ID;
	vector <int> LN;
	vector <int> LFN;
	char FilePos[128];
      
    DataBase()
    {
        Students.clear();
        ID.clear();
        LN.clear();
        LFN.clear();
        FilePos[0] = 0;
	}
	~DataBase()
    {
        Students.clear();
        ID.clear();
        LN.clear();
        LFN.clear();
        FilePos[0] = 0;
	}

    bool LoadBase(char* pos)
    {
		int i=0;
		for(; pos[i]!=0; i++) FilePos[i] = pos[i];
		FilePos[i]=0;
        FILE* f = fopen(pos, "r");
        if (f == 0) 
        {
            cout << "Failed starting students.exe!" << endl<< "Error description: could not open file: "<<endl<< "Usage:"<< endl<<"   students.exe <db_path.exe>";
            f = fopen(pos,"w"); 
            fclose(f);
            return false;
        }
		char c;
		char newst [1024];
		while(true)
        {
			int i = 0;
            do
            {
                c = fgetc(f);
                if (c == EOF) break;
                newst[i] = c;
                i++;
            } while (c != '\n');
			if ((i==0) && (c==EOF)) break;
			TStudent NewST;
			NewST.ReadStr(newst);
			Students.push_back(NewST);
		}
		fclose(f);
		int size=Students.size();
		for (int i=0; i<size; i++)
        {
			ID.push_back(i);
			LN.push_back(i);
			LFN.push_back(i);
		}
		Sort(size);
		cout << "Database is successfully loaded!"<<endl;
		return true;
	}   	

	void Sort(int size)
    {
        for (int i = 0; i < size; i++) 
        {
            for (int j = size - 1; j >= 1; j--)
                if (Students[ID[j]].ID < Students[ID[j-1]].ID) swap(ID[j-1], ID[j]);
        }

        for (int i = 0; i < size; i++) 
        {
            for (int j = size - 1; j >= 1; j--)
                if (strcmp(Students[LN[j]].LastName, Students[LN[j-1]].LastName) < 0) swap(LN[j-1], LN[j]);
        }

        for (int i = 0; i < size; i++)
            LFN[i] = LN[i];

        for (int i = 0; i < size; i++) 
        {
            for (int j = size - 1; j >= 1; j--)
                if (strcmp(Students[LFN[j]].LastName, Students[LFN[j-1]].LastName) == 0) 
                    if (strcmp(Students[LFN[j]].Name, Students[LFN[j-1]].Name) < 0) swap(LFN[j-1], LFN[j]);
        }
	}

	void SearchByLastName()
    {
		if (LN.empty())
        {
			cout<<"Error! The database is empty!";
			return;
		}
        char LastName[MAX_LASTNAME_SIZE];
		cout << "Enter Last Name:"<<endl;
        cin >> LastName;
        int l = 0;
        int r = LN.size() - 1;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (strcmp(LastName, Students[LN[m]].LastName) <= 0)
                r = m;
            else
                l = m + 1;
        }

		if (strcmp(LastName,Students[LN[r]].LastName)!=0)
        {
			cout<<"Error! There is no student with such LastName in database!"<<endl;
			return;
		}
        l = r;
        int count = 0;
        do
        {
            count++; l++;
        } while ( (l<LN.size()) && (strcmp(LastName, Students[LN[l]].LastName) == 0) );

        cout << "Students found with LastName=\"" << LastName << "\": " << count << endl;
        for (int i = 0; i < count; i++)
            Students[LN[r + i]].print();
	}

	void SearchByLastFirstName()
    {
		if (LFN.empty())
        {
			cout<<"Error! The database is empty!";
			return;
		}
        char LastName[MAX_LASTNAME_SIZE];
        char Name[MAX_NAME_SIZE];
		cout << "Enter LastName + Name:"<<endl;
        cin >> LastName;
        cin >> Name;
        int l = 0;
        int r = LN.size() - 1;
        while (l < r)
        {
            int m = (l + r) / 2;
            if ((strcmp(LastName, Students[LFN[m]].LastName) <= 0) || ((strcmp(LastName, Students[LFN[m]].LastName) == 0) && (strcmp(Name, Students[LFN[m]].Name) <= 0)))
                r = m;
            else
                l = m + 1;
        }

		if ((strcmp(LastName,Students[LFN[r]].LastName)!=0)|| (strcmp(Name, Students[LFN[r]].Name) != 0))
        {
			cout<<"Error! There is no student with such LastName in database!"<<endl;
			return;
		}
        l = r;
        int count = 0;
        do
        {
            count++; l++;
        } while ( (l<LFN.size()) && ((strcmp(LastName, Students[LFN[l]].LastName) == 0) && (strcmp(Name, Students[LFN[l]].Name) == 0)) );

        cout << "Students found with LastName + Name=\"" << LastName << "\" \"" << Name <<"\":" <<  count << endl;
        for (int i = 0; i < count; i++)
            Students[LFN[r + i]].print();
	}

    int SearchByID(int id, bool add) 
    {
		if (ID.empty())
        {
			cout<<"Error! The database is empty!";
            return -1;
		}
        int l = 0;
        int r = ID.size()-1;
        while (r < l)
        {
            int m = (l + r) / 2;
            if (id <= Students[ID[m]].ID)
                l = m;
            else
                r = m + 1;
        }
        if (id == Students[ID[r]].ID)
        {
            if (add) Students[ID[r]].print();
            return ID[r];
        }
        else
        {
            if (add) cout << "Error! There is no student with such ID in database!" << endl;
            return -1;
        }
    }

	void Search()
    {
		cout<<"Enter:"<<endl<<" 1 - to search by LastName"<<endl<<" 2 - to search by LastName+Name"<<endl<<" 3 - to search by ID"<<endl;
		int n;
		cin >> n;
        if (n==1) SearchByLastName();
        else if (n==2) SearchByLastFirstName();
        else if (n==3)
        {
            int id; 
            cout << "Enter ID:"<<endl; 
            cin >> id;
            SearchByID(id,1); 
        }
        else cout << "Wrong command!"<<endl;
	}

	void Add()
    {
		TStudent St;
		cout << "Enter the ID: ";
		cin >> St.ID;
        if (SearchByID(St.ID, 0)>=0)
        {
			cout << "Error: The student with this ID has been already added in Database!"<<endl;
			return;
		}
		cout << "Enter the name: ";
		cin >> St.Name;
		cout << "Enter the last name: ";
		cin >> St.LastName;
		cout << "Enter Average Mark: ";
		cin >> St.AverageMark;
		cout <<"Enter the biography: ";
		char c;
        int i=0;
        cin >> c;
        while (c!='\n') 
        {
            St.Bio[i++] = c;
            c=getchar();
        }
        St.Bio[i]=0;
		Students.push_back(St);
		LN.push_back(Students.size()-1);
		LFN.push_back(Students.size()-1);
		ID.push_back(Students.size()-1);
		Sort(Students.size());
		cout<<endl<<"This student is seccessfully added!"<<endl;
	}
    
	void Del()
    {
		if (ID.empty())
        {
			cout << "Error! The database is empty!";
			return;
		}
		cout << "Enter ID: ";
		int id;
		cin >> id;
		if (id<0)
			cout <<"Wrong ID!"<<endl;
		int i=SearchByID(id, 0);
		if (i>=0)
        {
			for (int j=0; j<ID.size(); j++)
            {
				if (ID[j]==i)
					ID.erase(ID.begin()+j);
				if ((j<ID.size()) && (ID[j]>i))
					ID[j]--;
			}
			for (int j=0; j<LN.size(); j++)
            {
				if(LN[j]==i)
					LN.erase(LN.begin()+j);
				if ((j<LN.size()) && (LN[j]>i))
					LN[j]--;
			}
			for (int j=0; j<LFN.size(); j++)
            {
				if (LFN[j]==i)
					LFN.erase(LFN.begin()+j);
				if ((j<LFN.size()) && (LFN[j]>i))
					LFN[j]--;
			}
			Students.erase(Students.begin()+i);
			cout <<"Student was successfully deleted!"<<endl;
		}
		else 
			cout <<"Error! There is no student with such ID!"<<endl;
	}

	void Printall()
    {
		int size=LFN.size();
		for(int i=0; i<size; i++) Students[LFN[i]].print();
	}

	void Quit(char* pos)
    {
		FILE* f = fopen(pos, "w");
		int size = Students.size();
		char buf [2048];
		for(int i=0; i<size; i++) fputs(Students[i].WriteStr(buf), f);	
		fclose(f);
	}

};

void UseBase(char *FilePos)
    {
        DataBase db;
	    if (db.LoadBase(FilePos))
        {
    		char reply[64];
	    	while (true)
            {
		    	cout <<"Possible commands:\n" <<"	search\n	add\n	del\n	printall\n	quit\n"<<
				"Enter command:\n";
	    		bool flag=true;
		    	cin >> reply;
                if (strcmp("search", reply) == 0)
    				db.Search(); 
	    		else if (strcmp("add", reply) == 0)
                {
		    		db.Add();
			    	db.Sort(db.Students.size());
			    }
    			else if (strcmp("del", reply) == 0)
	    			db.Del(); 
		    	else if (strcmp("printall", reply) == 0)
			    	db.Printall();
    			else if (strcmp("quit", reply) == 0)
                {
	    			db.Quit(db.FilePos);
		    		return;
    			}
	    		else cout << "Error: Unknown command!"<<endl;
		    }
        }
	}

bool ArgCheck(int argc, char** argv)
{
	if (argc==2)
    {
		if((strcmp(argv[1],"--help")==0))
        {
			cout << "Usage:"<<endl<<"  students.exe <db_path.exe>";
			return true;
		}
		else return false;
	}
	else if (argc<2) 
    {
		cout << "Failed starting students.exe!"<<endl<<"Error description: not enough command-line arguments!"<<endl<< "Usage:\n     students.exe <db_path.exe>"<<endl;
		return true;
	}
	else if (argc>2)
    {
		cout << "Failed starting students.exe!"<<endl<<"Error description: too many command-line arguments!"<<endl<<"Usage:"<<endl<<"     students.exe <db_path.exe>"<<endl;
		return true;
	}
	return true;
}


int main(int argc, char** argv)
{
	if(ArgCheck(argc, argv))
    {
		return 0;
	}
    UseBase(argv[1]);
	return 0;
}