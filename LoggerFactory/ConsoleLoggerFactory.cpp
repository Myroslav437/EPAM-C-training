#include "ConsoleLoggerFactory.hpp"
#include "../Logger/ConsoleLogger.hpp"

AbstractLogger* ConsoleLoggerFactory::getImpl(std::streambuf*) {
	return new ConsoleLogger();
}
