#pragma once

#include <string>

struct LogLevel {
	virtual std::string getString() const = 0;
	virtual operator std::string() const = 0;
};

struct DebugLevel : public LogLevel {
	std::string getString() const override { return message; }
	operator std::string() const override { return message;	}

private:
	inline static const std::string message = "DebugLevel";
};

struct InfoLevel : public LogLevel {
	std::string getString() const override { return message; }
	operator std::string() const override { return message; }

private:
	inline static const std::string message = "InfoLevel";
};

struct WarningLevel : public LogLevel {
	std::string getString() const override { return message; }
	operator std::string() const override { return message; }

private:
	inline static const std::string message = "WarningLevel";
};

struct ErrorLevel : public LogLevel {
	std::string getString() const override { return message; }
	operator std::string() const override { return message; }

private:
	inline static const std::string message = "ErrorLevel";
};

