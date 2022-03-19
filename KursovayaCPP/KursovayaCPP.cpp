#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <clocale>
#include <fstream>
#include <Windows.h>
#include <ctime>

using namespace std;

struct Sportsman
{
    string LastName;
    string Sex;
    string SportType;
    int BirthYear;
    double Height;

    struct Sportsman* next;
};

typedef struct Sportsman SportsmanList;
SportsmanList* headList = nullptr;
SportsmanList* endList = nullptr;

void CopyArrays(SportsmanList* fromList, SportsmanList* inList)
{
    inList->LastName = fromList->LastName;
    inList->Sex = fromList->Sex;
    inList->SportType = fromList->SportType;
    inList->BirthYear = fromList->BirthYear;
    inList->Height = fromList->Height;
}

bool TryParse(string str, double& out)
{
    bool res = false;
    try
    {
        double resNum = std::atof(str.c_str());
        out = resNum;
        res = true;
    }
    catch (const exception&)
    {
        res = false;
    }

    return res;
}

bool TryParse(string str, int& out)
{
    bool res = false;
    try
    {
        int resNum = std::stoi(str);
        out = resNum;
        res = true;
    }
    catch (const exception&)
    {
        res = false;
    }

    return res;
}

void Add()
{
    SportsmanList* currentList = new SportsmanList;
    string tempStr; 
    int countTransaction;

    cout << "Введите фамилию: ";
    getline(cin, tempStr);
    currentList->LastName = tempStr;
    cout << endl;

    cout << "Введите пол: ";
    getline(cin, tempStr);
    currentList->Sex = tempStr;
    cout << endl;

    cout << "Введите вид спорта: ";
    getline(cin, tempStr);
    currentList->SportType = tempStr;
    cout << endl;

    cout << "Введите год рождения: ";
    cin >> currentList->BirthYear;
    cout << endl;
    cin.ignore(32767, '\n');

    cout << "Введите рост: ";
    cin >> currentList->Height;
    cout << endl;

    cin.ignore(32767, '\n');

    currentList->next = nullptr;
    if (!headList)
    {
        headList = currentList;
    }
    else endList->next = currentList;
    endList = currentList;

    cout << endl;
}

void CreateList()
{
    int n;
    cout << "Введите количество новых записей: ";
    cin >> n;
    cin.ignore(32767, '\n');
    for (int i = 1; i <= n; i++)
    {
        cout << "Заполните " << i << " запись" << ":\n";
        Add();
    }
}

void Search()
{
    if (!headList)
    {
        cout << "Список пустой" << endl;
        return;
    }
    SportsmanList* currentList = headList;
    string tempStr;
    int searchBy, tempInt;
    cout << "1. Поиск по возрасту (моложе)" << endl;
    cout << "2. Поиск по виду спорта" << endl;
    cin >> searchBy;
    cin.ignore(32767, '\n');
    if (searchBy == 1)
    {
        cout << "Введите год (включительно): ";
        cin >> tempInt;
        while (currentList)
        {
            if (currentList->BirthYear <= tempInt)
            {
                cout << "Фамилия: "; cout << currentList->LastName << endl;
                cout << "Пол: "; cout << currentList->Sex << endl;
                cout << "Вид спорта: "; cout << currentList->SportType << endl;
                cout << "Год рождения: "; cout << currentList->BirthYear << endl;
                cout << "Рост: "; cout << currentList->Height << endl;
                cout << "----------------------------" << endl;
            }
            currentList = currentList->next;
        }
    }
    else if (searchBy == 2)
    {
        cout << "Введите вид спорта: ";
        getline(cin, tempStr);
        while (currentList)
        {
            if (currentList->SportType == tempStr)
            {
                cout << "Фамилия: "; cout << currentList->LastName << endl;
                cout << "Пол: "; cout << currentList->Sex << endl;
                cout << "Вид спорта: "; cout << currentList->SportType << endl;
                cout << "Год рождения: "; cout << currentList->BirthYear << endl;
                cout << "Рост: "; cout << currentList->Height << endl;
                cout << "----------------------------" << endl;
            }
            currentList = currentList->next;
        }
    }
    else
    {
        cout << "Неверная команда" << endl;
        return;
    }
}

void WriteList()
{
    if (!headList)
    {
        cout << "Список пуст" << endl;

        return;
    }
    SportsmanList* currentList = headList;
    cout << "Список спортсменов:\n";
    while (currentList)
    {
        cout << "Фамилия: "; cout << currentList->LastName << endl;
        cout << "Пол: "; cout << currentList->Sex << endl;
        cout << "Вид спорта: "; cout << currentList->SportType << endl;
        cout << "Год рождения: "; cout << currentList->BirthYear << endl;
        cout << "Рост: "; cout << currentList->Height << endl;
        cout << "----------------------------" << endl;
        currentList = currentList->next;
    }
}

SportsmanList* SubListCreate(string sportType)
{
    SportsmanList* currentList = headList;
    SportsmanList* subList = new SportsmanList;
    SportsmanList* headSubList = subList;

    bool first = true;
    int currentTimestamp = time(0);

    while (currentList)
    {
        if (currentList->SportType == sportType)
        {
            if (first)
            {
                first = false;
                CopyArrays(currentList, subList);
                subList->next = nullptr;
            }
            else
            {
                subList->next = new SportsmanList();
                subList = subList->next;
                CopyArrays(currentList, subList);
                subList->next = nullptr;
            }
        }
        currentList = currentList->next;
    }

    if (first)
    {
        return 0;
    }
    else
    {
        return headSubList;
    }
}

void WriteListBySportType()
{
    if (!headList)
    {
        cout << "Список пустой" << endl;
        return;
    }

    string tempStr;
    cout << "Введите вид спорта: ";
    getline(cin, tempStr);

    SportsmanList* subList = SubListCreate(tempStr);
    SportsmanList* subHead = subList;
    
    if (!subList)
    {
        cout << "Не найдено ни одного спортсмена по этому виду спорта" << endl;
        return;
    }

    SportsmanList* elem;

    while (subList)
    {
        cout << "Фамилия: "; cout << subList->LastName << endl;
        cout << "Пол: "; cout << subList->Sex << endl;
        cout << "Вид спорта: "; cout << subList->SportType << endl;
        cout << "Год рождения: "; cout << subList->BirthYear << endl;
        cout << "Рост: "; cout << subList->Height << endl;
        cout << "----------------------------" << endl;

        subList = subList->next;
    }

    while (subHead)
    {
        SportsmanList* currentList = subHead;
        subHead = currentList->next;
        delete currentList;
    }
}

void DeleteList()
{
    if (!headList)
    {
        cout << "Список пуст" << endl;

        return;
    }
    while (headList)
    {
        SportsmanList* currentList = headList;
        headList = currentList->next;
        delete currentList;
    }
    cout << "Список очищен" << endl;
}

void SaveList()
{
    if (!headList)
    {
        cout << "Список пуст" << endl;
        return;
    }

    ofstream fileOut("list.txt");
    SportsmanList* currentList = headList;
    while (currentList)
    {
        fileOut << currentList->LastName << ";";
        fileOut << currentList->Sex << ";";
        fileOut << currentList->SportType << ";";
        fileOut << currentList->BirthYear << ";";
        fileOut << currentList->Height << ";" << endl;

        currentList = currentList->next;
    }
    fileOut.close();
    cout << "Запись завершена" << endl;
}

void ReadList()
{
    fstream fileIn("list.txt");

    if (!fileIn.is_open())
    {
        cout << "Файл не может быть открыт" << endl;
        return;
    }
    string str;
    while (getline(fileIn, str))
    {
        SportsmanList* currentList = new SportsmanList;

        string lastName, sex, sportType;
        int birthYear;
        double height;

        lastName = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        sex = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        sportType = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        TryParse(str.substr(0, str.find_first_of(';')), birthYear);
        str.erase(0, str.find_first_of(';') + 1);     

        TryParse(str.substr(0, str.find_first_of(';')), height);
        str.erase(0, str.find_first_of(';') + 1);

        currentList->LastName = lastName;
        currentList->Sex = sex;
        currentList->SportType = sportType;
        currentList->BirthYear = birthYear;
        currentList->Height = height;
        
        currentList->next = NULL;

        if (!headList)
        {
            headList = currentList;
        }
        else endList->next = currentList;
        endList = currentList;
    }
    fileIn.close();

    cout << "Чтение завершено" << endl;
}

void main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int command;
    do
    {
        system("cls");
        cout << "1. Загрузить" << endl;
        cout << "2. Сохранить" << endl;
        cout << "3. Поиск" << endl;
        cout << "4. Добавить записи" << endl;
        cout << "5. Вывести всё" << endl;
        cout << "6. Удалить всё" << endl;
        cout << "7. Вывести записи по виду спорта" << endl;
        cout << "0. Выход" << endl;
        cout << "\nВведите номер команды: ";
        cin >> command;
        cin.ignore(32767, '\n');
        switch (command)
        {
        case 1:
            system("cls");
            cout << "1. Загрузить\n" << endl;
            ReadList();
            system("pause");
            break;

        case 2:
            system("cls");
            cout << "2. Сохранить\n" << endl;
            SaveList();
            system("pause");
            break;
        
        case 3:
            system("cls");
            cout << "3. Поиск\n" << endl;
            Search();
            system("pause");
            break;

        case 4:
            system("cls");
            cout << "4. Добавить\n" << endl;
            CreateList();
            system("pause");
            break;

        case 5:
            system("cls");
            cout << "5. Вывести всё\n" << endl;
            WriteList();
            system("pause");
            break;

        case 6:
            system("cls");
            cout << "6. Удалить всё\n" << endl;
            DeleteList();
            system("pause");
            break;
        case 7:
            system("cls");
            cout << "7. Вывести записи по виду спорта\n" << endl;
            WriteListBySportType();
            system("pause");
            break;

        case 0:
            system("cls");
            DeleteList();
            break;

        default:
            cout << endl << "Ошибка ввода..." << endl;
            system("pause");
            break;
        }

    } while (command != 0);
    cin.get();
}