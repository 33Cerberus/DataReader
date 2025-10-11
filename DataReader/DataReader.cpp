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
ifstream inputFile;
ofstream outputFile;

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
        inputFile.open(fileName);
    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cout << "Error: cannot open file \"" << fileName << "\"\n";
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
        while (getline(inputFile, line))
        {
            try
            {
                istringstream iss(line);
                string name, surname;
                int age;

                if (!(iss >> name >> surname >> age))
                    throw ios_base::failure("Invalid format");

                string extra;
                if (iss >> extra)
                    throw ios_base::failure("Too many values on line");

                persons.push_back(Person(name, surname, age));
            }
            catch (const ios_base::failure& e)
            {
                cout << "Invalid data on line " << lineNumber << ": " << line << endl;
            }

            lineNumber++;
        }
    }
    catch (const ios_base::failure& e)
    {
        cout << endl;
    }
}

void PrintPersons()
{
    int n = 1;
    cout << "-------------------------" << endl;
    for (const Person& person : persons)
    {
        cout << n << " " << person.name << " " << person.surname << " " << person.age << endl;
        n++;
    }
    cout << "-------------------------" << endl;
}

void PrintInputOptions()
{
    cout << "Press: " << '\n' << " 1 to ADD a new person to the list" << '\n'
        << " 2 to REMOVE a person from the list" << '\n'
        << " 3 to CHANGE data about person " << "\n"
        << " 4 to SAVE data into a new file" "\n";
}

void TryAddPerson()
{
    cin.clear();
    PrintPersons();

    string name, surname;
    int age;

    try
    {
        cout << "Enter person's data: ";
        if (!(cin >> name >> surname >> age))
            throw ios_base::failure("Invalid data");

        persons.push_back(Person(name, surname, age));
    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cout << "Error: invalid data" << '\n';
        cin.clear();    
        cin.ignore(10000, '\n');
        TryAddPerson();
    }
}

void TryRemovePerson()
{
    cin.clear();
    PrintPersons();

    int number;

    try
    {
        if (persons.size() == 0)
            return;
        cout << "Enter person's number: ";
        if (!(cin >> number) || number <= 0 || number > persons.size())
            throw std::ios_base::failure("Invalid data");

        persons.erase(persons.begin() + number - 1);
    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cout << "Error: invalid number" << '\n';
        cin.clear();
        cin.ignore(10000, '\n');
        TryRemovePerson();
    }
}

void TryChangePerson()
{
    cin.clear();
    PrintPersons();

    int number;

    string name, surname;
    int age;

    try
    {
        if (persons.size() == 0)
            return;
        cout << "Enter person's number: ";
        if (!(cin >> number) || number <= 0 || number > persons.size())
            throw std::ios_base::failure("Invalid number");

        cout << "Enter new person's data: ";

        if (!(cin >> name >> surname >> age))
            throw ios_base::failure("Invalid data");

        persons[number - 1] = (Person(name, surname, age));
    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cout << "Error: invalid data" << '\n';
        cin.clear();
        cin.ignore(10000, '\n');
        TryChangePerson();
    }
}

void TrySaveData()
{
    cout << "Enter file name: ";
    string fileName;
    cin >> fileName;

    try
    {
        outputFile.open(fileName);
        for (const Person& person : persons)
        {
            outputFile << person.name << " " << person.surname << " " << person.age << endl;
        }

    }
    catch (const ios_base::failure& e)
    {
        ClearConsole();
        cout << "Error: cannot create file \"" << fileName << "\"\n";
        TryOpenFile();
    }
}

int main()
{
    inputFile.exceptions(fstream::badbit | fstream::failbit);
    outputFile.exceptions(fstream::badbit | fstream::failbit);

    TryOpenFile();
    TryReadDataFromFile(); 

    int f = 0;

    while (true)
    {
        if (f != 0) ClearConsole();
        PrintPersons();
        PrintInputOptions();
        char input = _getch();

        if (input == '1')
        {
            ClearConsole();
            TryAddPerson();
        }
        else if (input == '2')
        {
            ClearConsole();
            TryRemovePerson();
        }
        else if (input == '3')
        {
            ClearConsole();
            TryChangePerson();
        }
        else if (input == '4')
        {
            ClearConsole();
            TrySaveData();
            break;
        }
        f = 1;
    }
    inputFile.close();
    outputFile.close();
    cout << "Data saved successfully! Press any key to exit...";
}