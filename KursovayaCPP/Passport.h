#pragma once
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class Passport
{
public:
	Passport() 
	{
		_series = 0;
		_number = 0;
		_name = "";
		_surname = "";
		_patronymic = "";
	}

	Passport(int series, int number, std::string name, std::string surname, std::string patronymic) : Passport()
	{
		_series = series;
		_number = number;
		_name = name;
		_surname = surname;
		_patronymic = patronymic;
	}

	int GetSeries() { return _series; }
	int GetNumber() { return _number; }
	std::string GetName() { return _name; }
	std::string GetSurname() { return _surname; }
	std::string GetPatronymic() { return _patronymic; }
	std::string GetShortFIO() 
	{
		std::string res = "";
		if (_surname.length() > 0 && _name.length() > 0 && _patronymic.length() > 0) {
			res = _surname + " " + _name[0] + ". " + _patronymic[0] + ".";
		}
		return res;
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _series;
		ar& _number;
		ar& _name;
		ar& _surname;
		ar& _patronymic;
	}

	int _series;
	int _number;
	std::string _name;
	std::string _surname;
	std::string _patronymic;
};