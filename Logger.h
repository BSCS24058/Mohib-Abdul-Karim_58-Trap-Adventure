#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    static Logger& getInstance();

    void initialize(const std::string& filename);
    void cleanup();
    void writeError(const std::string& error_message);

private:
    std::ofstream logFile;

    Logger();
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H
