#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <iostream>
#include <vector>

class Logger
{
public:
	template<class T>
	Logger& operator<<(const T& x)
	{
		std::cout << x;
		return *this;
	}
};

class BaseLogger
{
public:
	BaseLogger(std::string prefix = "");

	template<class T>
	Logger& operator<<(const T& x)
	{
		std::cout << prefix << x;
		return logger;
	}
private:
	std::string prefix;
	Logger logger;
};

extern BaseLogger info;
extern BaseLogger warn;
extern BaseLogger err;
extern BaseLogger task;

extern char endl; // Don't use std::endl with the logger

#endif
