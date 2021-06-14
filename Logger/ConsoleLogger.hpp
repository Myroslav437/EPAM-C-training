#pragma once

#include "OstreamLogger.hpp"


class ConsoleLogger : public OstreamLogger
{
public:
	ConsoleLogger();
	ConsoleLogger(LogLevel&&);

	~ConsoleLogger();
private:
};
