#include "FileLoggerFactory.hpp"
#include "../Logger/FileLogger.hpp"

AbstractLogger* FileLoggerFactory::getImpl(std::streambuf* sb) {
	return new FileLogger(sb);
}
