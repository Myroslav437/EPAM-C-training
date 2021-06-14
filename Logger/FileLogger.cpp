#include "FileLogger.hpp"

FileLogger::FileLogger()
{
}

FileLogger::FileLogger(std::streambuf* s) : 
	OstreamLogger::OstreamLogger(s)
{
}

FileLogger::FileLogger(std::streambuf* s, LogLevel&& l) : 
	OstreamLogger::OstreamLogger(s, std::forward<LogLevel>(l))
{
}

FileLogger::FileLogger(std::ofstream& of) :
	OstreamLogger::OstreamLogger(of.rdbuf()) {
}

FileLogger::FileLogger(std::ofstream& of, LogLevel&&  l) : 
	OstreamLogger::OstreamLogger(of.rdbuf(), std::forward<LogLevel>(l)) {
}
