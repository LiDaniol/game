#include "configfile.h"

Config::Config() {}

void Config::open(const std::string &file)
{
	std::cout << "Importing config from " << file << "..." <<  std::endl;

	configfile.open("main.conf");
	std::string line;

	while (std::getline(configfile, line))
	{
		size_t eqpos = line.find('=');
		size_t commentpos = line.find('#');

		if (commentpos != std::string::npos)
		{
			line = line.substr(0, commentpos);
		}

		if (eqpos != std::string::npos)
		{
			std::string key = trim(line.substr(0, eqpos)),
					    result = trim(line.substr(eqpos + 1, line.size() - eqpos - 1));

			if ((result.size() != 0) && (result[0] == '{'))
			{
				std::vector<std::string> array;

				size_t x = 1; // skip '{'
				while (true)
				{
					size_t commapos = result.find(',', x); // @TODO dis lookz badeh
					while (commapos != std::string::npos)
					{
						std::string elem = result.substr(x, commapos - x);
						array.push_back(trim(elem));

						x = commapos + 1;
						commapos = result.find(',', x);
					}

					size_t endpos = result.find('}');
					if (endpos != std::string::npos)
					{
						std::string elem = result.substr(x, endpos - x);
						array.push_back(trim(elem));
						break;
					}

					if (!std::getline(configfile, line))
					{
						break;
					}

					result = trim(line);
					x = 0;
				}
				arrayDictionary.push_back({key, array});
			}
			else
			{
				stringDictionary.push_back({key, result});
			}
		}
	}

	std::cout << "Available keys [" << stringDictionary.size() + arrayDictionary.size() << "] :" << std::endl;
	for (auto& i : stringDictionary)
	{
		std::cout << " - " << i.first << " = \"" << i.second << "\"" << std::endl;
	}

	for (auto& i : arrayDictionary)
	{
		std::cout << " - " << i.first << " = { ";
		for (unsigned int j = 0; j < i.second.size() - 1; ++j)
		{
			std::cout << "\"" << i.second[j] << "\", ";
		}

		std::cout << "\"" << i.second[i.second.size() - 1] << "\" }" << std::endl; // @TODO that better
	}
}

std::string Config::getStringValue(const std::string& key, int number, const std::string& ifnone)
{
	for (auto& i : stringDictionary)
		if (!number-- && key == i.first) return i.second;

	return ifnone;
}

std::vector<std::string> Config::getArrayValue(const std::string& key, int number, const std::vector<std::string>& ifnone)
{
	for (auto& i : arrayDictionary)
		if (!number-- && key == i.first) return i.second;

	return ifnone;
}