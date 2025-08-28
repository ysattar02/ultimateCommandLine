#include "sessionLogger.h"

SingletonLogger* SingletonLogger::m_loggerInstance = nullptr;

static std::mutex instanceLock;

static std::mutex logLock;

SingletonLogger* SingletonLogger::getInstance() {

    // Case the logger instance doesn't exist
    if (SingletonLogger::m_loggerInstance == nullptr) {

        // Set up the lock guard
        std::lock_guard<std::mutex> lock(instanceLock);

        // Call constructor
        SingletonLogger::m_loggerInstance = new SingletonLogger;
    }

    return SingletonLogger::m_loggerInstance;
}

std::string SingletonLogger::getExePath() {

    char buffer[MAX_PATH];
    std::string filepath = "";
    if (GetModuleFileNameA(NULL, buffer, MAX_PATH)) {
        int i = 0;
        while (buffer[i] != '\0') {
            i++;
        }
        int buffer_size = i;
        i = 0;
        for (int i = 0; i < buffer_size - 24; i++) {
            filepath += buffer[i];
        }
        return filepath;
    }
    else {
        return filepath;
    }
}

std::string SingletonLogger::getCurrentUTCTime() {

    // Get current system time in UTC
    auto now = std::chrono::utc_clock::now();

    // Format it as ISO 8601 string
    return std::format("{:%Y-%m-%d %H-%M-%S}", now);
}

void SingletonLogger::setLoglevel(SingletonLogger::LOG_LEVEL logLevel) {
    
    m_logLevel = static_cast<uint16_t>(logLevel);
}

SingletonLogger::LOG_LEVEL SingletonLogger::getLoglevel() {

    if (SingletonLogger::m_logLevel == 0) {
        return SingletonLogger::LOG_LEVEL::TRACE;
    }
    else if (SingletonLogger::m_logLevel == 1) {
        return SingletonLogger::LOG_LEVEL::WARNING;
    }
    else if (SingletonLogger::m_logLevel == 2) {
        return SingletonLogger::LOG_LEVEL::FATAL;
    }
    else {
        return SingletonLogger::LOG_LEVEL::UNKNOWN;
    }
}

void SingletonLogger::openStream() {

    SingletonLogger::m_logFile.open(SingletonLogger::m_logFilePath, std::ios::app);
    if (SingletonLogger::m_logFile.is_open() == false) {
        return;
    }
    return;
}

void SingletonLogger::log(const std::string& fileName, long lineNumber, LOG_LEVEL logLevel, std::string msg) {

    // Calculate if we should log this
    uint16_t logLevelIndex = static_cast<uint16_t>(logLevel);
    if (logLevelIndex < SingletonLogger::m_logLevel) {
        return;
    }

    // Take the log lock
    std::lock_guard<std::mutex> lock(logLock);

    // Calculate the log level
    std::string currLogLevel = SingletonLogger::m_logLevelsAsStrings[logLevelIndex];

    // If the log level is fatal, set console to red
    if (m_logLevel == static_cast<uint16_t>(LOG_LEVEL::FATAL)) {

        // Set to red text
        SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED);

        // Print to console
        std::cout << "[" << currLogLevel << "] " << msg << std::endl;

        // Revert back to normal text
        SetConsoleTextAttribute(m_consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else {

        // Print to console
        std::cout << "[" << currLogLevel << "] " << msg << std::endl;
    }

    // Log the message to logfile
    SingletonLogger::m_logFile << "[" << currLogLevel << "] " << fileName << " (" << lineNumber << "): " << msg << std::endl;

    return;
}