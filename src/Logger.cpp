#include "Logger.h"

#include <fstream>
#include <iostream>
#include <ctime>

namespace
{
    const std::string LOG_FILE = "logs/processpilot.log";

    void writeLog(const std::string& level,
                  const std::string& message)
    {
        std::ofstream file(LOG_FILE, std::ios::app);

        if (!file)
        {
            std::cerr << "Unable to open log file.\n";
            return;
        }

        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        char timeBuffer[32];

        std::strftime(
            timeBuffer,
            sizeof(timeBuffer),
            "%Y-%m-%d %H:%M:%S",
            localTime
        );

        file << "[" << timeBuffer << "] "
             << "[" << level << "] "
             << message << '\n';

        file.close();
    }
}

void Logger::info(const std::string& message)
{
    writeLog("INFO", message);
}

void Logger::warning(const std::string& message)
{
    writeLog("WARNING", message);
}

void Logger::error(const std::string& message)
{
    writeLog("ERROR", message);
}
