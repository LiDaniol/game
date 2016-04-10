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

private:
	std::ifstream configfile;
	std::vector<std::pair<std::string, std::string>> dictionary;
};

#endif
