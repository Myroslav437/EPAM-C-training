#pragma once
#include "../Logger/AbstractLogger.hpp"

class LoggerFactory {
public:
	AbstractLogger* get(std::streambuf* sb) { return getImpl(sb); };

protected:
	virtual AbstractLogger* getImpl(std::streambuf* sb) = 0;
};

