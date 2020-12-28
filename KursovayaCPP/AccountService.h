#pragma once
#include "Account.h"
#include "List.h"
#include <ctime>

class AccountService
{
public:
	void Add(Account account)
	{
		accountRepository.Add(account);
	}

	void Remove(int index)
	{
		if (index >= accountRepository.GetLength())
		{
			return;
		}
		accountRepository.Remove(index);
	}

	void Clear()
	{
		accountRepository.Clear();
	}

	void SetRepository(List<Account> rep)
	{
		accountRepository = rep;
	}

	bool Exists(int number)
	{
		Account temp;
		return Search(number, temp);
	}

	bool Exists(int series, int number)
	{
		Account temp;
		return Search(series, number, temp);
	}

	bool Search(int number, Account &account)
	{
		for (int i = 0; i < accountRepository.GetLength(); i++)
		{
			if (accountRepository[i].GetNumber() == number)
			{
				account = accountRepository[i];
				return true;
			}
		}
		return false;
	}

	bool Search(std::string shortFIO, List<Account> &accounts)
	{
		bool isFlag = false;
		accounts.Clear();
		for (int i = 0; i < accountRepository.GetLength(); i++)
		{
			if (shortFIO == accountRepository[i].GetPassport().GetShortFIO())
			{
				Account account = accountRepository[i];
				accounts.Add(account);
				isFlag = true;
			}
		}
		return isFlag;
	}

	bool Search(int series, int number, Account &account)
	{
		for (int i = 0; i < accountRepository.GetLength(); i++)
		{
			if (series == accountRepository[i].GetPassport().GetSeries()
				&& number == accountRepository[i].GetPassport().GetNumber())
			{
				account = accountRepository[i];
				return true;
			}
		}
		return false;
	}

	List<Account> GetAccounts()
	{
		return accountRepository;
	}


	// TODO: сделать соритировку
	
	/// <summary>
	/// Selects accounts for which there were no transactions in the last year
	/// </summary>
	/// <returns></returns>
	List<Account> GetAccountsSpecial()
	{
		List<Account> res;
		int timestampNow = std::time(0);
		for (int i = 0; i < accountRepository.GetLength(); i++)
		{
			bool flag = false;
			Account account = accountRepository[i];
			Transaction transaction = GetLastTransaction(account);
			if (timestampNow - transaction.GetDate() <= AmountSecondPerYear)
			{
				flag = true;
			}
			
			if (flag)
			{
				bool flagAdd = false;
				for (int j = 0; j < res.GetLength(); j++)
				{
					Account temp = res[j];
					if (transaction.GetDate() <= GetLastTransaction(temp).GetDate())
					{
						flagAdd = true;
						res.InsertOf(account, j);
					}
				}
				if (!flagAdd)
				{
					res.Add(account);
				}
			}
		}

		return res;
	}

	Transaction GetLastTransaction(Account& account)
	{
		Transaction empty;
		List<Transaction> transactions = account.GetTransactions();
		int maxDate = MININT32;
		int index = -1;
		for (int i = 0; i < transactions.GetLength(); i++)
		{
			if (transactions[i].GetDate() > maxDate)
			{
				maxDate = transactions[i].GetDate();
				index = i;
			}
		}
		if (index != -1)
		{
			return transactions[index];
		}
		else {
			return empty;
		}
	}

private:
	static constexpr int AmountSecondPerYear = 31536000;

	List<Account> accountRepository;
};

