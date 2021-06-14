#include <sstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>

#include "LoggerFactory/ConsoleLoggerFactory.hpp"

int main() {
	ConsoleLoggerFactory clf;
	auto* log = clf.get(nullptr);

	log->setLevel(WarningLevel());
	(*log) << "Hello" << 123;
	log->log();
}