#pragma once
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <regex>
#include <string>
#include "AccountService.h"
#include "FileService.h"

enum class CommandType
{
	Show		= 1,
	ShowSpecial = 2,
	Add			= 3,
	Remove		= 4,
	Clear		= 5,
	Load		= 6,
	Save		= 7,
	Exit		= 8,
	Undefine
};

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class IOService
{
public:
	IOService()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout << std::setiosflags(std::ios::left); // | std::ios::fixed
	}
	void Listener()
	{
		ClearConsole();

		SetColorConsole(Black, Green);
		std::cout << "Commands:" << std::endl;
		SetColorConsole(Black, Yellow);
		std::cout << "Show: 1" << std::endl;
		std::cout << "Show Special: 2" << std::endl;
		std::cout << "Add account: 3" << std::endl;
		std::cout << "Remove: 4" << std::endl;
		std::cout << "Clear: 5" << std::endl;
		std::cout << "Load: 6" << std::endl;
		std::cout << "Save: 7" << std::endl;
		std::cout << "Exit: 8" << std::endl;
		SetColorConsole(Black, White);
		std::string cmd;
		getline(std::cin, cmd);

		switch (DefineCommand(cmd))
		{
			case CommandType::Add:
				Add();
				break;
			case CommandType::Remove:
				Remove();
				break;
			case CommandType::Clear:
				Clear();
				break;
			case CommandType::Show:
				Show();
				break;
			case CommandType::ShowSpecial:
				ShowSpecial();
				break;
			case CommandType::Load:
				Load();
				break;
			case CommandType::Save:
				Save();
				break;
			case CommandType::Exit:
				Exit();
				break;
			case CommandType::Undefine:
				Undefine();
				break;
		}
	}

private:
	void Add()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Adding new account" << std::endl;
		SetColorConsole(Black, White);

		bool flag = false;
		int number, passportSeries, passportNumber, countTransaction, transactionType, amount, contributionCategoryNum;
		std::string passportName, passportSurname, passportPatronymic, tempStr;

		Passport passport;
		ContributionCategoryType contributionCategoryType;
		List<Transaction> transactions;
		// Number Account
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Number account (Example: '123456'): ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*(\\d){6}\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, number);
			if (!flag && accountService.Exists(number))
			{
				SetColorConsole(Black, Red);
				std::cout << "Account with this number exists!" << std::endl;
				SetColorConsole(Black, White);
				flag = true;
			}
		} while (flag);

		// Passport Series and Number
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Passport series and number (Example: '1234 567890'): ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*(\\d){4} (\\d){6}\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) 
				|| !TryParse(tempStr.substr(0, tempStr.find_first_of(' ')), passportSeries)
				|| !TryParse(tempStr.substr(tempStr.find_first_of(' ') + 1, tempStr.length() - tempStr.find_first_of(' ') - 1), passportNumber);
			if (!flag && accountService.Exists(passportNumber, passportSeries))
			{
				SetColorConsole(Black, Red);
				std::cout << "Account with this passport data exists!" << std::endl;
				SetColorConsole(Black, White);
				flag = true;
			}
		} while (flag);

		// Name
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect name! Enter name from 2 to 45 letters!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Name (Example: 'Ivan'): ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*([a-zA-Z]){2,45}s*$");
			flag = !std::regex_match(tempStr, numberRegex);
			if (!flag)
			{
				passportName = tempStr;
			}
		} while (flag);

		// Surname
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect name! Enter surname from 2 to 45 letters!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Name (Example: 'Ivanov'): ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*([a-zA-Z]){2,45}s*$");
			flag = !std::regex_match(tempStr, numberRegex);
			if (!flag)
			{
				passportSurname = tempStr;
			}
		} while (flag);

		// Patronymic
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect name! Enter patronymic from 2 to 45 letters!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Name (Example: 'Ivanovich'): ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*([a-zA-Z]){2,45}s*$");
			flag = !std::regex_match(tempStr, numberRegex);
			if (!flag)
			{
				passportPatronymic = tempStr;
			}
		} while (flag);
		
		// Contribution category
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Contribution category ( 1 - Demand, 2 -Savings, 3 - Cumulative, 4 - Estimated): ";
			getline(std::cin, tempStr);
			std::regex regexStr("^\\s*([1-4]){1}\\s*$");
			flag = !std::regex_match(tempStr, regexStr) || !TryParse(tempStr, contributionCategoryNum);
			if (!flag)
			{
				switch (contributionCategoryNum)
				{
				case 1:
					contributionCategoryType = ContributionCategoryType::Demand;
					break;
				case 2:
					contributionCategoryType = ContributionCategoryType::Savings;
					break;
				case 3:
					contributionCategoryType = ContributionCategoryType::Cumulative;
					break;
				case 4:
					contributionCategoryType = ContributionCategoryType::Estimated;
					break;
				default:
					contributionCategoryType = ContributionCategoryType::Savings;
					break;
				}
			}
		} while (flag);

		// Count transaction
		flag = false;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command! Enter number form 1 to 10!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Count transaction: ";
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[1-10]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, countTransaction);
		} while (flag);

		// Transactions
		for (int i = 0; i < countTransaction; i++)
		{
			int transactionTypeNum, dateSeconds = 0;
			std::string date;
			TransactionType transactionType;
			std::cout << "Transaction" << "[" << i + 1 << "]:" << std::endl;

			// Transaction Type
			flag = false;
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command!" << std::endl;
					SetColorConsole(Black, White);
				}
				std::cout << "	Type ( 1 - Enrollment, 2 - Withdraw): ";
				getline(std::cin, tempStr);
				std::regex numberRegex("^\\s*[1-2]\\s*$");
				flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, transactionTypeNum);
				if (!flag)
				{
					switch (transactionTypeNum)
					{
					case 1:
						transactionType = TransactionType::Enrollment;
						break;
					case 2:
						transactionType = TransactionType::Withdraw;
						break;
					default:
						transactionType = TransactionType::Enrollment;
						break;
					}
				}
			} while (flag);

			// Transaction date
			flag = false;
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command! Enter date from 01/01/1970-00:00:00 to with 31/12/2034-23:59:59" << std::endl;
					SetColorConsole(Black, White);
				}
				std::cout << "	Date (Example: '25/06/2016-16:25:47'): ";
				getline(std::cin, tempStr);
				flag = !TryParseDate(tempStr, dateSeconds);
			} while (flag);

			// TODO: test dateSeconds

			// Transaction amount
			flag = false;
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command! Enter amount from 1 to 9999999" << std::endl;
					SetColorConsole(Black, White);
				}
				std::cout << "	Amount: ";
				getline(std::cin, tempStr);
				std::regex numberRegex("^\\s*(\\d){1,7}\\s*$");
				flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, amount);
			} while (flag);

			Transaction transaction = Transaction(transactionType, amount, dateSeconds);
			transactions.Add(transaction);
		}

		Account account = Account(number, Passport(passportSeries, passportNumber, passportName, passportSurname, passportPatronymic), contributionCategoryType, transactions);
		accountService.Add(account);

		SetColorConsole(Black, Yellow);
		std::cout << "Account added, Success!" << std::endl;
		std::cout << "Add more: 1" << std::endl;
		std::cout << "Go to the menu: 2" << std::endl;
		SetColorConsole(Black, White);
		flag = false;
		int cmd;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[12]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
			case 1:
				Add();
				break;
			case 2:
				return;
				break;
		}
	}
	void Remove()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Remove" << std::endl;
		SetColorConsole(Black, White);

		SetColorConsole(Black, Yellow);
		std::cout << "Remove: 1" << std::endl;
		std::cout << "Go to the menu: 2" << std::endl;
		SetColorConsole(Black, White);
		bool flag = false;
		std::string tempStr;
		int cmd, cmd2;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[12]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
		case 1:
			int index;
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command!" << std::endl;
					SetColorConsole(Black, White);
				}
				std::cout << "Enter index: " << std::endl;
				getline(std::cin, tempStr);
				std::regex numberRegex("^\\s*(\\d){1,7}\\s*$");
				flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, index);
			} while (flag);
			accountService.Remove(index);
			SetColorConsole(Black, Yellow);
			std::cout << "Removing Succeed!" << std::endl;
			std::cout << "Go to the menu: 1" << std::endl;
			SetColorConsole(Black, White);
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command!" << std::endl;
					SetColorConsole(Black, White);
				}
				getline(std::cin, tempStr);
				std::regex numberRegex("^\\s*[1]\\s*$");
				flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd2);
			} while (flag);
			if (cmd2 == 1)
			{
				return;
			}
			break;
		case 2:
			return;
			break;
		}
	}
	void Clear()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Clear" << std::endl;
		SetColorConsole(Black, White);

		SetColorConsole(Black, Yellow);
		std::cout << "Clear: 1" << std::endl;
		std::cout << "Go to the menu: 2" << std::endl;
		SetColorConsole(Black, White);
		bool flag = false;
		std::string tempStr;
		int cmd, cmd2;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[12]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
		case 1:
			accountService.Clear();
			SetColorConsole(Black, Yellow);
			std::cout << "Clearing Succeed!" << std::endl;
			std::cout << "Go to the menu: 1" << std::endl;
			SetColorConsole(Black, White);
			do {
				if (flag) {
					SetColorConsole(Black, Red);
					std::cout << "Incorrect command!" << std::endl;
					SetColorConsole(Black, White);
				}
				getline(std::cin, tempStr);
				std::regex numberRegex("^\\s*[1]\\s*$");
				flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd2);
			} while (flag);
			if (cmd2 == 1)
			{
				return;
			}
			break;
		case 2:
			return;
			break;
		}
	}
	void ShowSpecial()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Show Special" << std::endl;
		SetColorConsole(Black, White);

		List<Account> accountList = accountService.GetAccountsSpecial();
		Show(accountList);
	}
	void Show()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Show" << std::endl;
		SetColorConsole(Black, White);

		List<Account> accountList = accountService.GetAccounts();
		Show(accountList);
	}
	void Show(List<Account> accountList)
	{
		if (accountService.GetAccounts().GetLength() == 0)
		{
			std::cout << "No accounts added yet ..." << std::endl;
		}
		else
		{
			// Headers
			SetColorConsole(Black, Yellow);
			std::cout
				<< std::setw(5)  << "#" << "|"
				<< std::setw(10) << "Number" << "|"
				<< std::setw(52) << "FIO" << "|"
				<< std::setw(25) << "Contribution Category" << "|"
				<< std::setw(15) << "Amount" << "|"
				<< std::setw(30) << "Date last transaction" << std::endl << std:: endl;
			SetColorConsole(Black, White);

			for (int i = 0; i < accountList.GetLength(); i++)
			{
				Account account = accountList[i];
				std::cout
					<< std::setw(5)  << (i + 1) << "|"
					<< std::setw(10) << account.GetNumber() << "|"
					<< std::setw(52) << account.GetPassport().GetShortFIO() << "|"
					<< std::setw(25) << ContributionCategoryTypeHelper::EnumToString(account.GetContributionCategoryType()) << "|"
					<< std::setw(15) << account.GetAmount() << "|" 
					<< std::setw(30) << accountService.GetLastTransaction(account).GetDateString() << std::endl;
			}
		}

		SetColorConsole(Black, Yellow);
		std::cout << "Go to the menu: 1" << std::endl;
		SetColorConsole(Black, White);
		bool flag = false;
		std::string tempStr;
		int cmd;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*1\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
		case 1:
			return;
			break;
		}
	}
	void Exit()
	{
		exit(0);
	}
	void Undefine()
	{
		SetColorConsole(Black, Red);
		std::cout << "Incorrect command!" << std::endl;
		SetColorConsole(Black, White);
	}
	void Load()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Load" << std::endl;
		SetColorConsole(Black, White);
		std::string path;

		bool flag = false;
		std::string tempStr;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect path or not succes create file" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Enter path to load: " << std::endl;
			getline(std::cin, tempStr);
			flag = !FileService::FileExists(tempStr);
			if (!flag)
			{
				path = tempStr;
			}
		} while (flag);

		List<Account> rep;

		try
		{
			rep = FileService::FileLoad<List<Account>>(path);
			accountService.SetRepository(rep);
		}
		catch (const std::exception& ex)
		{
			SetColorConsole(Black, Red);
			std::cout << ex.what();
			SetColorConsole(Black, White);
		}

		SetColorConsole(Black, Yellow);
		std::cout << "Load again: 1" << std::endl;
		std::cout << "Go to the menu: 2" << std::endl;
		SetColorConsole(Black, White);
		flag = false;
		tempStr;
		int cmd;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[12]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
		case 1:
			Load();
			break;
		case 2:
			return;
			break;
		}
	}
	void Save()
	{
		ClearConsole();
		SetColorConsole(Black, Green);
		std::cout << "Save" << std::endl;
		SetColorConsole(Black, White);
		std::string path;
		
		bool flag = false;
		std::string tempStr;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect path or file not exists!" << std::endl;
				SetColorConsole(Black, White);
			}
			std::cout << "Enter path to save ( Example: 'C://tmp.dat'): " << std::endl;
			getline(std::cin, tempStr);
			flag = !FileService::IsCorrectPath(tempStr);
			if (!flag)
			{
				path = tempStr;
			}
		} while (flag);
		
		List<Account> rep;

		try
		{
			FileService::FileSave<List<Account>>(path, accountService.GetAccounts());
		}
		catch (const std::exception& ex)
		{
			SetColorConsole(Black, Red);
			std::cout << ex.what();
			SetColorConsole(Black, White);
		}

		SetColorConsole(Black, Yellow);
		std::cout << "Save again: 1" << std::endl;
		std::cout << "Go to the menu: 2" << std::endl;
		SetColorConsole(Black, White);
		flag = false;
		int cmd;
		do {
			if (flag) {
				SetColorConsole(Black, Red);
				std::cout << "Incorrect command!" << std::endl;
				SetColorConsole(Black, White);
			}
			getline(std::cin, tempStr);
			std::regex numberRegex("^\\s*[12]\\s*$");
			flag = !std::regex_match(tempStr, numberRegex) || !TryParse(tempStr, cmd);
		} while (flag);
		switch (cmd)
		{
		case 1:
			Save();
			break;
		case 2:
			return;
			break;
		}
	}

	void ClearConsole()
	{
		system("cls");
	}
	CommandType DefineCommand(std::string cmdStr)
	{
		int cmdNum = 0;
		if (!TryParse(cmdStr, cmdNum)) {
			return CommandType::Undefine;
		}

		CommandType cmdType;
		switch (cmdNum)
		{
		case 1:
			cmdType = CommandType::Show;
			break;
		case 2:
			cmdType = CommandType::ShowSpecial;
			break;
		case 3:
			cmdType = CommandType::Add;
			break;
		case 4:
			cmdType = CommandType::Remove;
			break;
		case 5:
			cmdType = CommandType::Clear;
			break;
		case 6:
			cmdType = CommandType::Load;
			break;
		case 7:
			cmdType = CommandType::Save;
			break;
		case 8:
			cmdType = CommandType::Exit;
			break;
		default:
			cmdType = CommandType::Undefine;
			break;
		}
		return cmdType;
	}
	bool TryParse(std::string str, int& out)
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
	bool TryParseDate(std::string str, int& out)
	{
		std::regex dateRegex("^\\s*(3[01]|[12][0-9]|0?[1-9])\/(1[012]|0?[1-9])\/((?:19|20)[7-9|0-3]\\d)\-(0?[1-9]|1[0-9]|2[0-3])\:(0?[1-9]|[1-5][0-9])\:(0?[1-9]|[1-5][0-9])\\s*$");
		bool flagRes = std::regex_match(str, dateRegex);

		if (flagRes)
		{
			// 2016/01/01-00:00:01

			int years, months, days, hours, minutes, seconds;
			std::string date = str.substr(0, str.find_first_of('-'));
			std::string time = str.substr(str.find_first_of('-') + 1, str.length() - str.find_first_of('-') - 1);

			TryParse(date.substr(0, date.find_first_of('/')), years);
			TryParse(date.substr(date.find_first_of('/') + 1, date.find_last_of('/') - date.find_first_of('/') - 1), months);
			TryParse(date.substr(date.find_last_of('/') + 1, date.length() - date.find_last_of('/') - 1), days);

			TryParse(time.substr(0, time.find_first_of(':')), hours);
			TryParse(time.substr(time.find_first_of(':') + 1, time.find_last_of(':') - time.find_first_of(':') - 1), minutes);
			TryParse(time.substr(time.find_last_of(':') + 1, time.length() - time.find_last_of(':') - 1), seconds);

			out = (((((years - 1) * 365) + ((months - 1) * 31) + (days - 1))
				* 24 + hours == 0 ? hours : hours - 1)
				* 60 + minutes == 0 ? minutes : minutes - 1)
				* 60 + seconds;
		}

		return flagRes;
	}
	void SetColorConsole(ConsoleColor BG, ConsoleColor TX)
	{
		if (hConsole == NULL) return;
		SetConsoleTextAttribute(hConsole, (WORD)((BG << 4) | TX));
	}

	AccountService accountService;

	HANDLE hConsole;
};

