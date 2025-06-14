#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include"MyStr.h"

using namespace std;

class Logger {
public:
    static Logger& getInstance();

    void initialize(const MyStr& filename);
    void cleanup();
    void writeError(const MyStr& error_message);

private:
    std::ofstream logFile;

    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H
