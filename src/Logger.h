//
//  Logger.h
//  CGProj
//

#include "Common.h"

class Logger {
public:
	static void printf(std::string text);
	static void printError(std::string text);
	static void print(std::string text);
	static void print(GLdouble d);
};