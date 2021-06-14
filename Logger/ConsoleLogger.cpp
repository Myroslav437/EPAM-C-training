#include "ConsoleLogger.hpp"
#include <iostream>

ConsoleLogger::ConsoleLogger() :
	OstreamLogger::OstreamLogger(std::cout.rdbuf())
{
}

ConsoleLogger::ConsoleLogger(LogLevel&& l) :
	OstreamLogger::OstreamLogger(std::cout.rdbuf(), std::forward<LogLevel>(l))
{
}

ConsoleLogger::~ConsoleLogger()
{
}
