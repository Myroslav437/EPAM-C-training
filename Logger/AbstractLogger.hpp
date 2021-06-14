#pragma once

#include <functional>
#include <sstream>
#include <mutex>

#include "LogLevel.hpp"

class AbstractLogger {
protected:
	typedef AbstractLogger this_type;
	typedef InfoLevel defaultLevel;

public:
	AbstractLogger( LogLevel&& = std::forward<defaultLevel>(defaultLogLevel));

	virtual ~AbstractLogger();

	void log();

	void setLevel( LogLevel&& l) { level = l; }
	const LogLevel& getLevel() const { return level.get(); }

	template <class T>
	friend this_type& operator<<(this_type&, const T&);

protected:
	
	virtual void insertionOperatorImpl(std::stringstream&&) = 0;
	virtual void insertHeaderImpl(std::string&) = 0;
	virtual void logImpl() = 0;

	std::reference_wrapper<LogLevel> level;
	mutable std::mutex Mutex;
	inline static defaultLevel&& defaultLogLevel = defaultLevel();
};

template <class T>
AbstractLogger::this_type& operator<<(AbstractLogger::this_type& os, const T& dt) {
	std::stringstream ss; ss << dt;
	std::scoped_lock lock(os.Mutex);
	os.insertionOperatorImpl(std::move(ss));
	return os;
}