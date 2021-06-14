#pragma once
#include "LoggerFactory.hpp"

class ConsoleLoggerFactory :
    public LoggerFactory
{
    AbstractLogger* getImpl(std::streambuf* sb = nullptr) override;
};

