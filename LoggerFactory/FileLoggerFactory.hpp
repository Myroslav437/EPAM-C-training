#pragma once
#include "LoggerFactory.hpp"

class FileLoggerFactory :
    public LoggerFactory
{
    AbstractLogger* getImpl(std::streambuf* sb) override;
};

