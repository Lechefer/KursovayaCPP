#pragma once
#include "Passport.h"
#include "ContributionCategoryType.h"
#include "Transaction.h"
#include "List.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class Account
{
public:
	Account()
	{
		_number = 0;
		_contributionCategoryType = ContributionCategoryType::Savings;
		_amount = 0;
	}

	Account(int number, Passport passport, ContributionCategoryType contributionCategoryType, List<Transaction> transactions) : Account()
	{
		_number = number;
		_passport = passport;
		_contributionCategoryType = contributionCategoryType;
		_transactions = transactions;

		for (int i = 0; i < _transactions.GetLength(); i++)
		{
			_amount += _transactions[i].GetAmount();
		}
	}

	int GetNumber() { return _number; }
	Passport GetPassport() { return _passport; }
	ContributionCategoryType GetContributionCategoryType() { return _contributionCategoryType; }
	List<Transaction> GetTransactions() { return _transactions; }
	double GetAmount() { return _amount; }

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _number;
		ar& _passport;
		ar& _contributionCategoryType;
		ar& _transactions;
		ar& _amount;
	}

	int _number;
	Passport _passport;
	ContributionCategoryType _contributionCategoryType;
	List<Transaction> _transactions;
	double _amount;
};

