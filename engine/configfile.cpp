#include "configfile.h"

Config::Config(const std::string& file)
{
	configfile.open("main.conf");
	std::string line;
	while (std::getline(configfile, line))
	{
		size_t eqpos = line.find('=');
		if (eqpos != std::string::npos)
		{
			std::string key = line.substr(0, eqpos);
			std::string result = line.substr(eqpos + 1, line.size() - eqpos - 1);
			dictionary.push_back({key, result});
		}
	}
}