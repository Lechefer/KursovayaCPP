#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <clocale>
#include <fstream>
#include <Windows.h>
#include <ctime>

using namespace std;

static constexpr int AmountSecondPerYear = 31536000; // 365 days
static constexpr int AmountSecondPerMonth = 2592000; // 30 day
static constexpr int AmountSecondPerDay = 86400; // 24 hours
static constexpr int AmountSecondPerHour = 3600; // 60 minuts
static constexpr int AmountSecondPerMinute = 60; // 60 seconds

enum struct TransactionType
{
    Enrollment,
    Withdraw
};

struct TransactionTypeHelper
{
public:
    static std::string EnumToString(TransactionType type)
    {
        switch (type)
        {
        case TransactionType::Enrollment:
            return "Enrollment";
            break;
        case TransactionType::Withdraw:
            return "Withdraw";
            break;
        }
        return "";
    }
};

string GetDateString(int dateTimestamp)
{
    std::string dateStr = "";
    std::string years, months, days, hours, minutes, seconds;

    years = to_string(1970 + dateTimestamp / AmountSecondPerYear);
    months = to_string(1 + (dateTimestamp % AmountSecondPerYear) / AmountSecondPerMonth);
    months = months.length() == 1 ? "0" + months : months;
    days = to_string(1 + ((dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) / AmountSecondPerDay);
    days = days.length() == 1 ? "0" + days : days;
    hours = to_string((((dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) / AmountSecondPerHour);
    hours = hours.length() == 0 ? "00" + hours : hours;
    hours = hours.length() == 1 ? "0" + hours : hours;
    minutes = to_string(((((dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) % AmountSecondPerHour) / AmountSecondPerMinute);
    minutes = minutes.length() == 0 ? "00" + minutes : minutes;
    minutes = minutes.length() == 1 ? "0" + minutes : minutes;
    seconds = to_string(((((dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) % AmountSecondPerHour) % AmountSecondPerMinute);
    seconds = seconds.length() == 0 ? "00" + seconds : seconds;
    seconds = seconds.length() == 1 ? "0" + seconds : seconds;

    std::string res = years + "/" + months + "/" + days + "-" + hours + ":" + minutes + ":" + seconds;

    return res;
}

struct Account
{
    int number;
    string fio;
    string numberAndSeries;
    string contributionType;
    int dateTimestampLastTransaction;
    int amount;

    struct Account* next;
};

struct SubAccount
{
    struct Account* value;
    struct SubAccount* next;
};

typedef struct Account AccountList;
AccountList* headList = nullptr;
AccountList* endList = nullptr;

typedef struct SubAccount SubAccountList;

bool TryParse(string str, int& out)
{
    bool res = false;
    try
    {
        int resNum = std::stoi(str);
        out = resNum;
        res = true;
    }
    catch (const std::exception&)
    {
        res = false;
    }

    return res;
}

void TryParseDate(string str, int& out)
{
    int years, months, days, hours, minutes, seconds;
    std::string date = str.substr(0, str.find_first_of('-'));
    std::string time = str.substr(str.find_first_of('-') + 1, str.length() - str.find_first_of('-') - 1);

    TryParse(date.substr(0, date.find_first_of('/')), days);
    TryParse(date.substr(date.find_first_of('/') + 1, date.find_last_of('/') - date.find_first_of('/') - 1), months);
    TryParse(date.substr(date.find_last_of('/') + 1, date.length() - date.find_last_of('/') - 1), years);

    TryParse(time.substr(0, time.find_first_of(':')), hours);
    TryParse(time.substr(time.find_first_of(':') + 1, time.find_last_of(':') - time.find_first_of(':') - 1), minutes);
    TryParse(time.substr(time.find_last_of(':') + 1, time.length() - time.find_last_of(':') - 1), seconds);

    out = (((((years - 1970) * 365) + ((months - 1) * 31) + (days - 1)) * 24 + hours) * 60 + minutes) * 60 + seconds;
}

void Add()
{
    AccountList* currentList = new AccountList;
    string tempStr; 
    int countTransaction;

    cout << "Введите номер счёта: ";
    cin >> currentList->number;
    cout << endl;

    cin.ignore(32767, '\n');

    cout << "Введите номер и серию пасспорта (1234 123456): ";
    getline(cin, tempStr);
    currentList->numberAndSeries = tempStr;
    cout << endl;

    cout << "Введите ФИО пасспорта (Иванов И.И.): ";
    getline(cin, tempStr);
    currentList->fio = tempStr;
    cout << endl;

    cout << "Введите нужный тип вклада (По требованию; Сберегательный; Накопительный): ";
    getline(cin, tempStr);
    currentList->contributionType = tempStr;
    cout << endl;

    cout << "Введите сумму вклада: ";
    cin >> currentList->amount;
    cout << endl;

    cin.ignore(32767, '\n');

    cout << "Введите дату последней операции (15/01/2021-17:13:43): ";
    getline(cin, tempStr);
    TryParseDate(tempStr, currentList->dateTimestampLastTransaction);


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
    AccountList* currentList = headList;
    string tempStr;
    int searchBy, tempInt;
    cout << "1. Поиск по номеру вклада" << endl;
    cout << "2. Поиск по паспортным данным" << endl;
    cin >> searchBy;
    cin.ignore(32767, '\n');
    if (searchBy == 1)
    {
        cout << "Введите номер вклада: ";
        cin >> tempInt;
        while (currentList)
        {
            if (currentList->number == tempInt)
            {
                cout << "Номер аккаунта: "; cout << currentList->number << endl;
                cout << "ФИО: "; cout << currentList->fio << endl;
                cout << "Номер и серия паспорта: "; cout << currentList->numberAndSeries << endl;
                cout << "Тип вклада: "; cout << currentList->contributionType << endl;
                cout << "Дата последней операции: "; cout << GetDateString(currentList->dateTimestampLastTransaction) << endl;
                cout << "Текущая сумма вклада: "; cout << currentList->amount << endl;
                cout << "----------------------------" << endl;
            }
            currentList = currentList->next;
        }
    }
    else
        if (searchBy == 2)
        {
            cout << "Введите ФИО (Иванов И.И.): ";
            getline(cin, tempStr);
            while (currentList)
            {
                if (currentList->fio == tempStr)
                {
                    cout << "Номер аккаунта: "; cout << currentList->number << endl;
                    cout << "ФИО: "; cout << currentList->fio << endl;
                    cout << "Номер и серия паспорта: "; cout << currentList->numberAndSeries << endl;
                    cout << "Тип вклада: "; cout << currentList->contributionType << endl;
                    cout << "Дата последней операции: "; cout << GetDateString(currentList->dateTimestampLastTransaction) << endl;
                    cout << "Текущая сумма вклада: "; cout << currentList->amount << endl;
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
    AccountList* currentList = headList;
    cout << "Список аккаунтов:\n";
    while (currentList)
    {
        cout << "Номер аккаунта: "; cout << currentList->number << endl;
        cout << "ФИО: "; cout << currentList->fio << endl;
        cout << "Номер и серия паспорта: "; cout << currentList->numberAndSeries << endl;
        cout << "Тип вклада: "; cout << currentList->contributionType << endl;
        cout << "Дата последней операции: "; cout << GetDateString(currentList->dateTimestampLastTransaction) << endl;
        cout << "Текущая сумма вклада: "; cout << currentList->amount << endl;
        cout << "----------------------------" << endl;
        currentList = currentList->next;
    }
}

SubAccountList* SubListCreate()
{
    AccountList* currentList = headList;
    SubAccountList* sub = new SubAccountList;
    SubAccountList* subHead = new SubAccountList;
    bool first = true;
    int currentTimestamp = std::time(0);

    while (currentList)
    {
        if ((currentList->dateTimestampLastTransaction + AmountSecondPerYear >= currentTimestamp) && (currentList->dateTimestampLastTransaction <= currentTimestamp))
        {
            if (first)
            {
                first = false;
                subHead->value = currentList;
                sub = subHead;
                sub->next = nullptr;
            }
            else
            {
                sub->next = new SubAccountList;
                sub = sub->next;
                sub->value = currentList;
                sub->next = nullptr;
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
        return subHead;
    }
}

void WriteListOfLastYear()
{
    if (!headList)
    {
        cout << "Список пустой" << endl;
        return;
    }

    SubAccountList* sub = SubListCreate();
    SubAccountList* subHead = sub;

    if (!sub)
    {
        cout << "За последний год не было операций ни на одном аккаунте" << endl;
        return;
    }

    AccountList* elem;

    while (sub)
    {
        elem = sub->value;
        cout << "Номер аккаунта: "; cout << elem->number << endl;
        cout << "ФИО: "; cout << elem->fio << endl;
        cout << "Номер и серия паспорта: "; cout << elem->numberAndSeries << endl;
        cout << "Тип вклада: "; cout << elem->contributionType << endl;
        cout << "Дата последней операции: "; cout << GetDateString(elem->dateTimestampLastTransaction) << endl;
        cout << "Текущая сумма вклада: "; cout << elem->amount << endl;
        cout << "----------------------------" << endl;

        sub = sub->next;
    }

    while (subHead)
    {
        SubAccountList* currentList = subHead;
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
        AccountList* currentList = headList;
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
    AccountList* currentList = headList;
    while (currentList)
    {
        fileOut << currentList->number << ";";
        fileOut << currentList->fio << ";";
        fileOut << currentList->numberAndSeries << ";";
        fileOut << currentList->contributionType << ";";
        fileOut << currentList->dateTimestampLastTransaction << ";";
        fileOut << currentList->amount << ";" << endl;

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
        AccountList* currentList = new AccountList;

        string fio, numberAndSeries, contributionType;
        int number, dateTimestampLastTransaction, amount;

        TryParse(str.substr(0, str.find_first_of(';')), number);
        str.erase(0, str.find_first_of(';') + 1);

        fio = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        numberAndSeries = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        contributionType = str.substr(0, str.find_first_of(';'));
        str.erase(0, str.find_first_of(';') + 1);

        TryParse(str.substr(0, str.find_first_of(';')), dateTimestampLastTransaction);
        str.erase(0, str.find_first_of(';') + 1);

        TryParse(str.substr(0, str.find_first_of(';')), amount);
        str.erase(0, str.find_first_of(';') + 1);

        currentList->number = number;
        currentList->fio = fio;
        currentList->numberAndSeries = numberAndSeries;
        currentList->contributionType = contributionType;
        currentList->dateTimestampLastTransaction = dateTimestampLastTransaction;
        currentList->amount = amount;

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
        cout << "7. Вывести записи за последний год" << endl;
        cout << "0. Выход" << endl;
        cout << "\nВведите номер команды: ";
        cin >> command;
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
            cout << "7. Вывести записи за последний год\n" << endl;
            WriteListOfLastYear();
            system("pause");
            break;

        case 0:
            system("cls");
            DeleteList();
            system("pause");
            break;

        default:
            cout << endl << "Ошибка ввода..." << endl;
            system("pause");
            break;
        }

    } while (command != 0);
    cin.get();
}