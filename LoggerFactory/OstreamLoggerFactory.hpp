#pragma once
#include "LoggerFactory.hpp"

class OstreamLoggerFactory :
    public LoggerFactory
{
    AbstractLogger* getImpl(std::streambuf* sb) override;
};

