#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

const int MAX_NAME_SIZE = 30;
const int MAX_LASTNAME_SIZE = 50;
const int MAX_BIO_SIZE = 1024;

class DataBase // ���� ������
{
private:

    struct TStudent // ��������� �������
    {
        char Name[MAX_NAME_SIZE]; // ���
        char LastName[MAX_LASTNAME_SIZE]; // �������
        int ID; // ����� ������������� ������
        float AverageMark; // ������� ����
        char Biography[MAX_BIO_SIZE]; // ���������

        TStudent() // �����������
        {
            Name[0] = '\0';
            LastName[0] = '\0';
            ID = -1;
            AverageMark = -1;
            Biography[0] = '\0';
        }

        ~TStudent() // ����������
        {
            Name[0] = '\0';
            LastName[0] = '\0';
            ID = -1;
            AverageMark = -1;
            Biography[0] = '\0';
        }

        void FromString(char* buffer) // ���������� ������ �� ������
        {
            char strID[100];
            char strAverageMark[100];

            int number = 1;
            int j = 0;
            int buffer_size = strlen(buffer);

            for (int i = 0; i < buffer_size; i++)
            {
                if (buffer[i] == ';') // ��������� ����
                {
                    if (number == 1)
                        Name[j] = '\0';
                    if (number == 2)
                        LastName[j] = '\0';
                    if (number == 3)
                        strID[j] = '\0';
                    if (number == 4)
                        strAverageMark[j] = '\0';
                    if (number == 5)
                        Biography[j] = '\0';

                    j = 0;
                    number++;

                    continue;
                }
                if (buffer[i] == '\\') // �������� �������������� ������
                {
                    if (buffer[i+1] == ';') // �������������� ������ ';'
                    {
                        if (number == 1)
                            Name[j] = buffer[i+1];
                        if (number == 2)
                            LastName[j] = buffer[i+1];
                        if (number == 3)
                            strID[j] = buffer[i+1];
                        if (number == 4)
                            strAverageMark[j] = buffer[i+1];
                        if (number == 5)
                            Biography[j] = buffer[i+1];

                        i++;
                        j++;
                        continue;
                    }
                    else // ��� ������ ������� ������ '\'
                    {
                        if (number == 1)
                            Name[j] = buffer[i];
                        if (number == 2)
                            LastName[j] = buffer[i];
                        if (number == 3)
                            strID[j] = buffer[i];
                        if (number == 4)
                            strAverageMark[j] = buffer[i];
                        if (number == 5)
                            Biography[j] = buffer[i];

                        j++;
                    }
                }
                else // ������� ������
                {
                    if (number == 1)
                        Name[j] = buffer[i];
                    if (number == 2)
                        LastName[j] = buffer[i];
                    if (number == 3)
                        strID[j] = buffer[i];
                    if (number == 4)
                        strAverageMark[j] = buffer[i];
                    if (number == 5)
                        Biography[j] = buffer[i];
                    j++;
                }
            }

            sscanf(strID, "%d", &ID);
            sscanf(strAverageMark, "%f", &AverageMark);
        }

        char* ToString(char* buffer) // ����� ������ � ������
        {
            char NewName[2*MAX_NAME_SIZE];
            char NewLastName[2*MAX_LASTNAME_SIZE];
            char NewBiography[2*MAX_BIO_SIZE];

            int j = 0;
            int length = strlen(Name);
            for (int i = 0; i < length; i++) // ������������� ������� ';' � �����
            {
                if(Name[i] == ';')
                {
                    NewName[j] = '\\';
                    j++;
                }
                NewName[j] = Name[i];
                j++;
            }
            NewName[j] = '\0';

            j = 0;
            length = strlen(LastName);
            for (int i = 0; i < length; i++) // ������������� ������� ';' � �������
            {
                if(LastName[i] == ';')
                {
                    NewLastName[j] = '\\';
                    j++;
                }
                NewLastName[j] = LastName[i];
                j++;
            }
            NewLastName[j] = '\0';

            j = 0;
            length = strlen(Biography);
            for (int i = 0; i < length; i++) // ������������� ������� ';' � ���������
            {
                if(Biography[i] == ';')
                {
                    NewBiography[j] = '\\';
                    j++;
                }
                NewBiography[j] = Biography[i];
                j++;
            }
            NewBiography[j] = '\0';

            sprintf(buffer, "%s;%s;%d;%f;%s;\n", NewName, NewLastName, ID, AverageMark, NewBiography);
            return buffer;
        };

        void print() // ����� ������ �� �����
        {
            cout << "------------------------------------------------" << endl;
            cout << "Name: " << Name << endl;
            cout << "Last Name: " << LastName << endl;
            cout << "ID: " << ID << endl;
            cout << "Average Mark: " << AverageMark << endl;
            cout << "Biography: " << Biography << endl;
            cout << endl;
        }
    };

    vector < TStudent > Students; // ������ ���������
    vector < int > ID; // ������� �� ������ ������������� ������
    vector < int > LN; // ������� �� �������
    vector < int > LFN; // ������� �� ����� � �������
    char DataPath[128]; // ����� ���� ������
    size_t DataBaseSize;

    void Sort(bool first) // ���������� ���� ������
    {
        for (size_t i = 0; i < DataBaseSize; i++) // ���������� �� ID
        {
            for (size_t j = DataBaseSize - 1; j >= 1; j--)
                if (Students[ID[j]].ID < Students[ID[j-1]].ID)
                    swap(ID[j-1], ID[j]);
            if (!first)
                break;
        }

        for (size_t i = 0; i < DataBaseSize; i++) // ���������� �� �������
        {
            for (size_t j = DataBaseSize - 1; j >= 1; j--)
                if (strcmp(Students[LN[j]].LastName, Students[LN[j-1]].LastName) < 0)
                    swap(LN[j-1], LN[j]);
            if (!first)
                break;
        }

        for (size_t i = 0; i < DataBaseSize; i++)
            LFN[i] = LN[i];

        for (size_t i = 0; i < DataBaseSize; i++) // ���������� �� �������, ��� ��������� - �� �����
        {
            for (size_t j = DataBaseSize - 1; j >= 1; j--)
                if (strcmp(Students[LFN[j]].LastName, Students[LFN[j-1]].LastName) == 0) // ������� ���������
                    if (strcmp(Students[LFN[j]].Name, Students[LFN[j-1]].Name) < 0) // ��������� ����
                        swap(LFN[j-1], LFN[j]);
            if (!first)
                break;
        }

        return;
    }

    bool LoadDataBase(char* Path) // �������� ���� ������
    {
        int i;
        for (i = 0; Path[i] != '\0'; i++) //����������� ������ ���� ������
            DataPath[i] = Path[i];
        DataPath[i] = '\0';

        FILE* f = fopen(Path, "r");
        if (f == 0) // ���� �� ����������
        {
            cout << "Failed starting students.exe!" << endl;
            cout << "Error description: could not open file: ";
            puts(Path);
            cout << "Usage:" << endl;
            cout << "   students.exe <db_path.exe>";

            f = fopen(Path,"w"); // ������� ����
            fclose(f);

            return false;
        }
        else
        {
            char c;
            char temp[2048];

            while (true) // ������� ����
            {
                int i = 0;
                do
                {
                    c = fgetc(f);
                    if (c == EOF)
                        break;
                    temp[i] = c;
                    i++;
                }
                while (c != '\n');

                if (i == 0 && c == EOF)
                    break;

                TStudent TempStudent;
                TempStudent.FromString(temp);
                Students.push_back(TempStudent);
            }

            fclose(f);

            DataBaseSize = Students.size();
            ID.resize(DataBaseSize);
            LN.resize(DataBaseSize);
            LFN.resize(DataBaseSize);
            for (size_t i = 0; i < DataBaseSize; i++)
                ID[i] = LN[i] = LFN[i] = i;

            Sort(1); // �������������
            cout << "Database is successfully loaded!" << endl;

            return true;
        }
    }

    int SearchByLastName(char* LastName) // ����� �� �������
    {
        // ����� �������� ��������
        int first = 0;
        int last = DataBaseSize - 1;
        while (first < last)
        {
            int mid = (first + last) / 2;
            if (strcmp(LastName, Students[LN[mid]].LastName) <= 0)
                last = mid;
            else
                first = mid + 1;
        }

        if (strcmp(LastName, Students[LN[first]].LastName) != 0) // ��� �� ������ ���� ���� �������
        {
            cout << "Error! There is no student with such LastName in database!" << endl;
            return 0;
        }

        int start = first; // ����� ���������� �����, ��������������� �������� ������
        int ammount = 0;
        while (true)
        {
            if ((strcmp(LastName, Students[LN[start]].LastName)) == 0)
                ammount++;
            else
                break;
            start++;
            if (start >= DataBaseSize)
                break;
        }

        cout << "Students found with LastName=\"" << LastName << "\": " << ammount << endl;
        for (int i = 0; i < ammount; i++)
            Students[LN[first + i]].print();

        return ammount;
    }

    int SearchByLastFirstName(char* LastName, char* Name) // ����� �� ����� � �������
    {
        // ����� �������� ��������
        int first = 0;
        int last = DataBaseSize - 1;
        while (first < last)
        {
            int mid = (first + last) / 2;
            if ((strcmp(LastName, Students[LFN[mid]].LastName) <= 0) ||
               ((strcmp(LastName, Students[LFN[mid]].LastName) == 0) &&
                 (strcmp(Name, Students[LFN[mid]].Name) <= 0)))
                last = mid;
            else
                first = mid + 1;
        }

        if ((strcmp(LastName, Students[LFN[first]].LastName) != 0) ||
            (strcmp(Name, Students[LFN[first]].Name) != 0)) // ��� �� ������ ���� ���� �������
        {
            cout << "Error! There is no student with such LastName + Name in database!" << endl;
            return 0;
        }

        int start = first; // ����� ���������� �����, ��������������� �������� ������
        int ammount = 0;
        while (true)
        {
            if ((strcmp(LastName, Students[LFN[start]].LastName) == 0) &&
                (strcmp(Name, Students[LFN[start]].Name) == 0))
                ammount++;
            else
                break;
            start++;
            if (start >= DataBaseSize)
                break;
        }

        cout << "Students found with LastName + Name=\"" << LastName << "\" \"" << Name <<"\": " << ammount << endl;
        for (int i = 0; i < ammount; i++)
            Students[LFN[first + i]].print();

        return ammount;
    }

    int SearchByID(int SearchedID, bool ToBePrinted) // ����� �� ������ ������������� ������
    {
        if (DataBaseSize == 0)
            return -1;
        int first = 0;
        int last = DataBaseSize - 1;
        while (first < last)
        {
            int mid = (first + last) / 2;
            if (SearchedID <= Students[ID[mid]].ID)
                last = mid;
            else
                first = mid + 1;
        }
        if (SearchedID == Students[ID[first]].ID)
        {
            if (ToBePrinted)
                Students[ID[first]].print();
            return ID[first];
        }
        else
        {
            if (ToBePrinted)
                cout << "Error! There is no student with such ID in database!" << endl;
            return -1;
        }
    }

    void Search() // �����
    {
        cout << "Enter" << endl;
        cout << " 1 - to search by LastName" << endl;
        cout << " 2 - to search by LastName+Name" << endl;
        cout << " 3 - to search by ID" << endl;

        int n;
        cin >> n;

        if (DataBaseSize == 0) // ���� ������ �����
        {
            cout << "Error! The database is empty!" << endl;
            return;
        }

        if (n == 1) // ����� �� �������
        {
            char LastName[MAX_LASTNAME_SIZE];
            cout << "Enter Last Name:" << endl;
            cin >> LastName;
            SearchByLastName(LastName);
        }
        if (n == 2) // ����� �� ����� � �������
        {
            char LastName[MAX_LASTNAME_SIZE];
            char Name[MAX_NAME_SIZE];
            cout << "Enter Last Name:" << endl;
            cin >> LastName;
            cout << "Enter Name:" << endl;
            cin >> Name;
            SearchByLastFirstName(LastName, Name);
        }
        if (n == 3) // ����� �� ������ ������������� ������
        {
            int ID;
            cout << "Enter ID:" << endl;
            cin >> ID;
            SearchByID(ID, 1);
        }
        if (n < 1 || n > 3) // �������� �������
            cout << "Wrong command!" << endl;

        return;
    }

    void Add() // ���������� ������
    {
        TStudent TempStudent;
        cout << "Enter the ID: ";
        cin >> TempStudent.ID;
        if (SearchByID(TempStudent.ID, 0) >= 0) // ����� ������� ��� ����������
        {
            cout << "Error: The student with this ID has been already added in Database!" << endl;
            return;
        }

        cout << "Enter the name: ";
        cin >> TempStudent.Name;
        cout << "Enter the last name: ";
        cin >> TempStudent.LastName;
        cout << "Enter average mark: ";
        cin >> TempStudent.AverageMark;
        cout << "Enter the biography: ";
        string s, ss;
        cin >> s;
        s += ss;
        for (size_t i = 0; i < s.length(); i++)
            TempStudent.Biography[i] = s[i];
        TempStudent.Biography[s.length()] = '\0';

        Students.push_back(TempStudent);
        LN.push_back(DataBaseSize);
        LFN.push_back(DataBaseSize);
        ID.push_back(DataBaseSize);
        DataBaseSize++;

        Sort(0); // ����������
        cout << "This student is seccessfully added!" << endl;

        return;
    }

    void PrintAll() // ����� ����� ������
    {
//        cout << "DataBase.Size = " << DataBaseSize << endl;

        for(size_t i = 0; i < DataBaseSize; i++)
            Students[LFN[i]].print();

        return;
    }

    void Del() // ��������
    {
        cout << "Enter ID: ";
        int SearchedID;
        cin >> SearchedID;

        int Pos = SearchByID(SearchedID, 0); // ����� �������� �� ������ �������� ������
        if (Pos >= 0) // ���� ������� ������
        {
            for (size_t i = 0; i < DataBaseSize; i++) // �������� �� ������ ID
            {
                if (ID[i] == Pos)
                    ID.erase(ID.begin() + i);
                if (ID[i] > Pos)
                    ID[i]--;
            }
            for (size_t i = 0; i < DataBaseSize; i++) // �������� �� ������ �������
            {
                if (LN[i] == Pos)
                        LN.erase(LN.begin() + i);
                if (LN[i] > Pos)
                        LN[i]--;
            }
            for (size_t i = 0; i < DataBaseSize; i++) // �������� �� ������ ������� � ����
            {
                if (LFN[i] == Pos)
                        LFN.erase(LFN.begin() + i);
                if (LFN[i] > Pos)
                        LFN[i]--;
            }

            Students.erase(Students.begin() + Pos); // �������� �� ������ ���������
            cout << "Student was successfully deleted!" << endl;
            DataBaseSize--;
        }
        else
            cout << "Error! There is no student with such ID!" << endl;

        return;
    }

    void Quit(char* Path) // ����� � ����������� ����
    {
        FILE* f = fopen(Path, "w");
        char buffer [2048];
        for (size_t i = 0; i < Students.size(); i++)
            fputs(Students[LFN[i]].ToString(buffer), f);
        fclose(f);
        return;
    }

public:
    DataBase() // �����������
    {
        Students.clear();
        ID.clear();
        LN.clear();
        LFN.clear();
        DataPath[0] = '\0';
        DataBaseSize = 0;
    }

    ~DataBase() // ����������
    {
        Students.clear();
        ID.clear();
        LN.clear();
        LFN.clear();
        DataPath[0] = '\0';
        DataBaseSize = 0;
    }

    void Run(char* Path) // ������ � �����
    {
        if (LoadDataBase(Path))
        {
            char command[50];
            bool f;

            cout << "Possible commands:" << endl;
            cout << "  search" << endl;
            cout << "  add" << endl;
            cout << "  del" << endl;
            cout << "  printall" << endl;
            cout << "  quit" << endl;

            while (true)
            {
                cout << "Enter command:" << endl;
                cin >> command;
                f = false;

                if (strcmp("search", command) == 0)
                {
                    Search();
                    f = true;
                }
                if (strcmp("add", command) == 0)
                {
                    Add();
                    f = true;
                }
                if (strcmp("del", command) == 0)
                {
                    Del();
                    f = true;
                }
                if (strcmp("printall", command) == 0)
                {
                    PrintAll();
                    f = true;
                }
                if (strcmp("quit", command) == 0)
                {
                    Quit(Path);
                    return;
                }
                if (!f)
                    cout << "Error: Unknown command!" << endl;
            }
        }

        return;
    }
};

bool ArgCheck(int argc, char** argv) // �������� ������������ ����������
{
    if (argc < 2) // ���� ����������
    {
        cout << "Failed starting students.exe!" << endl;
        cout << "Error description: not enough command-line arguments!" << endl;
        cout << "Usage:" << endl;
        cout << "     students.exe <db_path.exe>" << endl;
        return false;
    }
    if (argc > 2) // ����� ����������
    {
        cout << "Failed starting students.exe!" << endl;
        cout << "Error description: too many command-line arguments!" << endl;
        cout << "Usage:" << endl;
        cout << "     students.exe <db_path.exe>" << endl;
        return false;
    }
    if (argc == 2) // ��������� ����������
    {
        if ((strcmp(argv[1], "--help") == 0)) // ����� �������
        {
            cout << "Usage:" << endl;
            cout << "  students.exe <db_path.exe>";
            return false;
        }
        else // ������ ���� ������
            return true;
    }

    return false;
}

int main(int argc, char** argv) // �������� ���������
{
    if (!ArgCheck(argc, argv))
        return 0;

    DataBase StudentDataBase; // �������� ���� ������

    StudentDataBase.Run(argv[1]); // ���� � ����� ���������� � �������� ���� ������
/*
    char path[8];
    cin >> path;
    StudentDataBase.Run(path);
//*/
    return 0;
}
 