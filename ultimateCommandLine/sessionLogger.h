#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>
#include <format>
#include <chrono>
#include <filesystem>
#include "Windows.h"

class SingletonLogger {

private:

	// Private constructor
	SingletonLogger() : m_logFilePath(""), m_logLevel(static_cast<uint16_t>(SingletonLogger::LOG_LEVEL::TRACE)) {

		// Get a handle to the console
		m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string exePath = getExePath();
		std::string utcTime = getCurrentUTCTime();
		m_logFilePath = exePath + "\\log_" + utcTime + ".txt";
		SingletonLogger::openStream();
	}

	// Private Destructor
	~SingletonLogger() {
	
		// Close the stream
		SingletonLogger::m_logFile.close();
	}

	// Instance of the class as a ptr
	static SingletonLogger* m_loggerInstance;

	// String containing filepath to the log
	std::string m_logFilePath;

	// Ofstream object to the logfile
	std::ofstream m_logFile;

	// Log level
	uint16_t m_logLevel;

	// Console handle
	HANDLE m_consoleHandle;

public:

	enum class LOG_LEVEL {
		TRACE = 0,
		WARNING = 1, 
		FATAL = 2,
		UNKNOWN = 3
	};

	std::vector<std::string> m_logLevelsAsStrings = {"Trace", "WARNING", "FATAL", "UNKNOWN"};

	static SingletonLogger* getInstance();

	std::string getExePath();

	std::string getCurrentUTCTime();

	void setLoglevel(SingletonLogger::LOG_LEVEL logLevel);

	SingletonLogger::LOG_LEVEL getLoglevel();

	void openStream();

	void log(const std::string& fileName, long lineNumber, LOG_LEVEL logLevel, std::string msg);
};

#define LOG_TRACE(msg) SingletonLogger::getInstance()->log(__FILE__, __LINE__, SingletonLogger::LOG_LEVEL::TRACE, msg)
#define LOG_WARNING(msg) SingletonLogger::getInstance()->log(__FILE__, __LINE__, SingletonLogger::LOG_LEVEL::WARNING, msg)
#define LOG_FATAL(msg) SingletonLogger->getInstance()->loglog(__FILE__, __LINE__, SingletonLogger::LOG_LEVEL::FATAL, msg)