#ifndef GAME_CONFIGFILE_H
#define GAME_CONFIGFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream> // broke hte include record

#include "stringutils.h"

class Config
{
public:
	Config();

	void open(const std::string& file);

	// For following functions, number = the number of the value to take
	std::string getStringValue(const std::string& key, int number = 0, const std::string& ifnone = "");
	std::vector<std::string> getArrayValue(const std::string& key, int number = 0, const std::vector<std::string>& ifnone = std::vector<std::string>());

private:
	std::ifstream configfile;
	std::vector<std::pair<std::string, std::string>> stringDictionary;
	std::vector<std::pair<std::string, std::vector<std::string>>> arrayDictionary;
};

#endif
