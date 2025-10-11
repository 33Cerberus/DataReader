#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Person
{
public:
    string name;
    string surname;
    int age;

public:
    Person(string _name, string _surname, int _age)
    {
        name = _name;
        surname = _surname;
        age = _age;
    }
};

vector<Person> persons;
ifstream file;

void ClearConsole()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void TryOpenFile()
{
    cout << "Enter file name: ";
    string fileName;
    cin >> fileName;

    try
    {
        file.open(fileName);
    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cerr << "Error: cannot open file \"" << fileName << "\"\n";
        TryOpenFile();
    }
}

void TryReadDataFromFile()
{
    string line;
    int lineNumber = 1;
    cout << endl;
    try
    {
        while (getline(file, line))
        {
            std::istringstream iss(line);
            string name, surname;
            int age;
            if (!(iss >> name >> surname >> age))
            {
                cout << "Invalid data on the line " << lineNumber << endl;
            }
            else
            {
                persons.push_back(Person(name, surname, age));
            }
            lineNumber++;
        }
    }
    catch (const ios_base::failure& e)
    {
        cout << endl;
    }
}

int main()
{
    file.exceptions(fstream::badbit | fstream::failbit);

    TryOpenFile();
    TryReadDataFromFile(); 

    int n = 1;
    cout << "--------------" << endl;
    for (Person person : persons)
    {
        cout << n << " " << person.name << " " << person.surname << " " << person.age << endl;
        n++;
    }
    cout << "--------------" << endl;

    _getch();
}