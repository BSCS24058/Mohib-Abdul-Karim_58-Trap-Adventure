#include "Logger.h"
#include <iostream>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {}

Logger::~Logger() {
    cleanup();
}

void Logger::initialize(const MyStr& filename) {
    if (!logFile.is_open()) {
        logFile.open(filename.fetchstr(), std::ios::app);
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

void Logger::writeError(const MyStr& error_message) {
    if (logFile.is_open()) {
        logFile << "ERROR: " << error_message << std::endl;
    }
    else {
        std::cerr << "Log file is not open. Cannot write error." << std::endl;
    }
}
