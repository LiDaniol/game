#include "configfile.h"

Config::Config() {}

void Config::open(const std::string &file)
{
	std::cout << "Importing config from " << file << "..." <<  std::endl;

	configfile.open("main.conf");
	std::string line;

	int c = 0;
	while (std::getline(configfile, line))
	{
		++c;

		size_t eqpos = line.find('=');
		size_t commentpos = line.find('#');

		if (commentpos != std::string::npos)
		{
			line = line.substr(0, commentpos);
		}

		if (eqpos != std::string::npos)
		{
			std::string key = trim(line.substr(0, eqpos));
			std::string result = trim(line.substr(eqpos + 1, line.size() - eqpos - 1));
			std::cout << "key '" << key << "' - result '" << result << "'" << std::endl;
			dictionary.push_back({key, result});
		}
	}

	std::cout << "Imported " << c << " keys from configuration file." << std::endl;
}