#include "OstreamLogger.hpp"

OstreamLogger::OstreamLogger() : 
	os(NULL)
{
	// init os with NULL as it doesn't have default ctor
}

OstreamLogger::OstreamLogger(std::streambuf* sb) :
	buf(),
	os(sb)
{
}

OstreamLogger::OstreamLogger(std::streambuf* sb, LogLevel&& ll) : 
	AbstractLogger::AbstractLogger(std::forward<LogLevel>(ll)),
	buf(),
	os(sb)
{
}

inline void OstreamLogger::insertionOperatorImpl(std::stringstream&& ss) {
	buf += ss.str();
}

void OstreamLogger::insertHeaderImpl(std::string& str) {
	buf.insert(0, str);
}

void OstreamLogger::logImpl() {
	auto dbg = stream().rdbuf();
	os << buf << std::endl;
	buf.clear();
}
