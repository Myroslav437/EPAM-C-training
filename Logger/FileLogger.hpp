#pragma once 
#include "OstreamLogger.hpp"
#include <fstream>

// redesign this class
class FileLogger : public OstreamLogger {
public:
	FileLogger();
	FileLogger(std::streambuf* s);
	FileLogger(std::streambuf* s, LogLevel&& l);
	FileLogger(std::ofstream&);
	FileLogger(std::ofstream&, LogLevel&&);

	//~FileLogger();
};