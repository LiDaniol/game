#ifndef GAME_CONFIGFILE_H
#define GAME_CONFIGFILE_H

#include <string>
#include <fstream>
#include <vector>
#include <utility>

class Config
{
public:
	Config(const std::string& file);

private:
	std::ifstream configfile;
	std::vector<std::pair<std::string, std::string>> dictionary;
};

#endif
