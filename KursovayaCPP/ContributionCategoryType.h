#pragma once
#include <string>

enum class ContributionCategoryType
{
	Demand,
	Savings,
	Cumulative,
	Estimated
};

class ContributionCategoryTypeHelper
{
public:
	static std::string EnumToString(ContributionCategoryType type)
	{
		switch (type)
		{
			case ContributionCategoryType::Demand:
				return "Denamd";
				break;
			case ContributionCategoryType::Savings:
				return "Savings";
				break;
			case ContributionCategoryType::Cumulative:
				return "Cumulative";
				break;
			case ContributionCategoryType::Estimated:
				return "Estimated";
				break;
		}
		return "";
	}
};