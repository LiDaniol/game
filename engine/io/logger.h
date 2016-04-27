#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <iostream>
#include <vector>
#include <chrono>

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

/*class Task
{
public:
	template<typename T>
	Task& operator<<(const T& x)
	{
		std::cout << x;
		return *this;
	}

	enum TaskEndTypes
	{
		SUCCESS,
		FAILURE
	};

	void start();
	void end(TaskEndTypes endtype = SUCCESS);
private:
	std::chrono::time_point<std::chrono::system_clock> startpoint;
};*/

extern BaseLogger info;
extern BaseLogger warn;
extern BaseLogger err;
extern BaseLogger task;

extern char endl; // Don't use std::endl with the logger

#endif
