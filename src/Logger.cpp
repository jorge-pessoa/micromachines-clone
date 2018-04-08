//
//  Logger.cpp
//  CGProj
//

#include "Logger.h"

void Logger::printf(std::string text)
{
	std::cout << text << "\n";
}

void Logger::print(GLdouble d)
{
	std::cout << d;
}

void Logger::printError(std::string text)
{
	std::cout << "[ERROR] " << text << "\n";
}

void Logger::print(std::string text)
{
	std::cout << text;
}
