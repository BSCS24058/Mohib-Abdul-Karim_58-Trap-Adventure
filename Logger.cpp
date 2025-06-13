#include "Logger.h"
#include <iostream>
#include <ctime>
#include <iomanip>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {}

Logger::~Logger() {
    cleanup();
}

void Logger::initialize(const std::string& filename) {
    if (!logFile.is_open()) {
        logFile.open(filename, std::ios::app);
        if (!logFile) {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }
}

void Logger::cleanup() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::writeError(const std::string& error_message) {
    if (logFile.is_open()) {
        auto now = std::time(nullptr);
        auto localTime = std::localtime(&now);
        logFile << "["
            << std::put_time(localTime, "%Y-%m-%d %H:%M:%S")
            << "] ERROR: " << error_message << std::endl;
    }
    else {
        std::cerr << "Log file is not open. Cannot write error." << std::endl;
    }
}
