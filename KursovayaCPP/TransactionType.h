#pragma once
#include <string>

enum class TransactionType
{
	Enrollment,
	Withdraw
};

class TransactionTypeHelper
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