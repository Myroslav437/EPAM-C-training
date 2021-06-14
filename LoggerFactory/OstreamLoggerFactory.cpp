#include "OstreamLoggerFactory.hpp"
#include "../Logger/OstreamLogger.hpp"

AbstractLogger* OstreamLoggerFactory::getImpl(std::streambuf* sb) {
	return new OstreamLogger(sb);
}
