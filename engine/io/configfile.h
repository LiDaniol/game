#ifndef GAME_CONFIGFILE_H
#define GAME_CONFIGFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>

#include "../extra/stringutils.h"
#include "logger.h"

struct StringValue
{
	template<typename returnType>
	returnType parse(returnType defaultValue, returnType (&f)(const std::string&, std::size_t*, int))
	{
		try
		{
			return f(value, 0, 10);
		}
		catch (const std::invalid_argument& e)
		{
			warn << "Argument exception during parsing : " << e.what() << endl;
			return defaultValue;
		}
		catch (const std::out_of_range& e)
		{
			warn << "Out of range exception during parsing : " << e.what() << endl;
			return defaultValue;
		}
	}

	bool asBool(bool defaultValue = false);

	std::string value;
};

struct StringArrayValue
{
	std::vector<StringValue> values;
};

class Config
{
public:
	Config();

	void open(const std::string& file);

	StringValue getStringValue(const std::string &key, int number, const std::string &ifnone = "");
	StringArrayValue getArrayValue(const std::string &key, int number, const StringArrayValue &ifnone = StringArrayValue());

	size_t getCountString(const std::string &key);
	size_t getCountArray(const std::string &key);

private:
	std::ifstream configfile;
	std::vector<std::pair<std::string, StringValue>> stringDictionary;
	std::vector<std::pair<std::string, StringArrayValue>> arrayDictionary;
};

#endif
