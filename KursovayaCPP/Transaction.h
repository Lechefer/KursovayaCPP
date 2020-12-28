#pragma once
#include "TransactionType.h"
#include <chrono>
#include <string>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class Transaction
{
public:
	Transaction()
	{
		_transactionType = TransactionType::Enrollment;
		_amount = 0;
		_dateTimestamp = 0;
	}

	Transaction(TransactionType transactionType, double amount, int dateTimestamp) : Transaction()
	{
		_transactionType = transactionType;
		_amount = amount;
		_dateTimestamp = dateTimestamp;
	}

	TransactionType GetTransactionType() { return _transactionType; }
	double GetAmount() { return _amount; }
	int GetDate() { return _dateTimestamp; }
	std::string GetDateString() 
	{ 
		std::string dateStr = "";
		std::string years, months, days, hours, minutes, seconds;

		years = std::to_string(1970 + _dateTimestamp / AmountSecondPerYear);
		months = std::to_string(1 + (_dateTimestamp % AmountSecondPerYear) / AmountSecondPerMonth);
		months = months.length() == 1 ? "0" + months : months;
		days = std::to_string(1 + ((_dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) / AmountSecondPerDay);
		days = days.length() == 1 ? "0" + days : days;
		hours = std::to_string((((_dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) / AmountSecondPerHour);
		hours = hours.length() == 0 ? "00" + hours : hours;
		hours = hours.length() == 1 ? "0" + hours : hours;
		minutes = std::to_string(((((_dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) % AmountSecondPerHour) / AmountSecondPerMinute);
		minutes = minutes.length() == 0 ? "00" + minutes : minutes;
		minutes = minutes.length() == 1 ? "0" + minutes : minutes;
		seconds = std::to_string(((((_dateTimestamp % AmountSecondPerYear) % AmountSecondPerMonth) % AmountSecondPerDay) % AmountSecondPerHour) % AmountSecondPerMinute);
		seconds = seconds.length() == 0 ? "00" + seconds : seconds;
		seconds = seconds.length() == 1 ? "0" + seconds : seconds;

		std::string res = years + "/" + months + "/" + days + "-" + hours + ":" + minutes + ":" + seconds;

		return res;
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _transactionType;
		ar& _amount;
		ar& _dateTimestamp;
	}

	TransactionType _transactionType;
	double _amount;
	int _dateTimestamp;

	static constexpr int AmountSecondPerYear = 31536000; // 365 days
	static constexpr int AmountSecondPerMonth = 2592000; // 30 day
	static constexpr int AmountSecondPerDay = 86400; // 24 hours
	static constexpr int AmountSecondPerHour = 3600; // 60 minuts
	static constexpr int AmountSecondPerMinute = 60; // 60 seconds
};

