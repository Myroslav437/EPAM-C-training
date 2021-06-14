#pragma once

#include "AbstractLogger.hpp"
#include <ostream>

class OstreamLogger : public AbstractLogger {
	typedef AbstractLogger base_class;
	using base_class::defaultLogLevel;

public:
	OstreamLogger();
	OstreamLogger(std::streambuf*);
	OstreamLogger(std::streambuf*, LogLevel&&);

	std::ostream& stream() { return os;  }

	void rdBuf(std::streambuf* sb) { os.rdbuf(sb); }
	std::streambuf* rdBuf() { return os.rdbuf(); }

protected:
	void insertionOperatorImpl(std::stringstream&&) override;
	void insertHeaderImpl(std::string&) override;
	void logImpl() override;

private:
	std::ostream os;
	std::string buf;
};

