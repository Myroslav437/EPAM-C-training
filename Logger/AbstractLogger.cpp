#include "AbstractLogger.hpp"

#include <chrono>
#include <iomanip>
#include <ctime>


AbstractLogger::AbstractLogger(LogLevel && l ) :
	level(l),
	Mutex()
{
}

AbstractLogger::~AbstractLogger() 
{
}

void AbstractLogger::log() {
	std::string header;
	header += level.get().getString() + "\t";

	// Make timestamp:
	auto now = std::chrono::system_clock::now();
	std::time_t tt = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::gmtime(&tt); //GMT (UTC)
	std::stringstream ss;
	ss << std::put_time(&tm, "UTC: %Y-%m-%d %H:%M:%S");


	header += ss.str();
	header += "[ ";
	*this << " ]";

	std::scoped_lock lock(Mutex);
	insertHeaderImpl(header);
	logImpl();

	return;
}
