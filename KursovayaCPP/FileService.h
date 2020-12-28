#pragma once
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

class FileService
{
public:
	static bool FileExists(std::string path)
	{
		return boost::filesystem::exists(path);
	}

	static bool IsCorrectPath(std::string path)
	{
		return true;
	}

	template<typename T>
	static T FileLoad(std::string path)
	{
		T model;
		std::ifstream ifs(path, std::ios::binary);
		{
			boost::archive::binary_iarchive ia(ifs);
			ia >> model;
		}

		//std::ofstream file;
		//file.open(path, std::ios::app|std::ios::binary);
		//if (!file.is_open()) {
		//	throw std::exception ("Error: Could not open file");
		//}

		//T model;
		//try
		//{
		//	file.write(model, sizeof(T));
		//}
		//catch (const std::exception&)
		//{
		//	file.close();
		//	throw std::exception ("Error: Could not read file");
		//}

		//file.close();
		return model;
	}

	template<typename T>
	static void FileSave(std::string path, T model)
	{
		std::ofstream ofs(path, std::ios::binary);
		{
			boost::archive::binary_oarchive oa(ofs);
			oa << model;
		}

		//std::fstream file;
		//	file.open(path);
		//if (!file.is_open()) {
		//	throw std::exception ("Error: Could not create file");
		//}

		//T model;
		//try
		//{
		//	file << model;
		//}
		//catch (const std::exception&)
		//{
		//	file.close();
		//	throw std::exception ("Error: Could not write file");
		//}
		//file.close();
	}
};

