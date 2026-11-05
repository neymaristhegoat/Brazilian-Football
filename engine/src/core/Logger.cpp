#include "core/Logger.h"
#include <iostream>
#include <ctime>

namespace bf {
namespace core {

void Logger::Init() {
    std::cout << "[BF Engine] Logger initialized" << std::endl;
}

void Logger::Shutdown() {
    std::cout << "[BF Engine] Logger shutdown" << std::endl;
}

void Logger::Log(int level, const std::string& message) {
    const char* levelStr[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"
    };

    // Get timestamp
    time_t now = time(nullptr);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", localtime(&now));

    // Color codes
    const char* colors[] = {
        "\033[37m",  // TRACE - White
        "\033[36m",  // DEBUG - Cyan
        "\033[32m",  // INFO - Green
        "\033[33m",  // WARN - Yellow
        "\033[31m",  // ERROR - Red
        "\033[35m"   // CRITICAL - Magenta
    };
    const char* reset = "\033[0m";

    std::cout << colors[level] << "[" << timestamp << "] [" 
              << levelStr[level] << "] " << message << reset << std::endl;
}

} // namespace core
} // namespace bf
