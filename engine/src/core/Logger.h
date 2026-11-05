#pragma once

#include <string>
#include <sstream>
#include <memory>

// Log levels
#define BF_LOG_LEVEL_TRACE 0
#define BF_LOG_LEVEL_DEBUG 1
#define BF_LOG_LEVEL_INFO 2
#define BF_LOG_LEVEL_WARN 3
#define BF_LOG_LEVEL_ERROR 4
#define BF_LOG_LEVEL_CRITICAL 5

// Logging macros
#define BF_LOG_TRACE(...)    bf::core::Logger::Trace(__VA_ARGS__)
#define BF_LOG_DEBUG(...)    bf::core::Logger::Debug(__VA_ARGS__)
#define BF_LOG_INFO(...)     bf::core::Logger::Info(__VA_ARGS__)
#define BF_LOG_WARN(...)     bf::core::Logger::Warn(__VA_ARGS__)
#define BF_LOG_ERROR(...)    bf::core::Logger::Error(__VA_ARGS__)
#define BF_LOG_CRITICAL(...) bf::core::Logger::Critical(__VA_ARGS__)

namespace bf {
namespace core {

class Logger {
public:
    static void Init();
    static void Shutdown();

    template<typename... Args>
    static void Trace(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_TRACE, Format(format, args...));
    }

    template<typename... Args>
    static void Debug(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_DEBUG, Format(format, args...));
    }

    template<typename... Args>
    static void Info(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_INFO, Format(format, args...));
    }

    template<typename... Args>
    static void Warn(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_WARN, Format(format, args...));
    }

    template<typename... Args>
    static void Error(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_ERROR, Format(format, args...));
    }

    template<typename... Args>
    static void Critical(const std::string& format, Args... args) {
        Log(BF_LOG_LEVEL_CRITICAL, Format(format, args...));
    }

private:
    static void Log(int level, const std::string& message);
    
    template<typename T>
    static std::string Format(const std::string& format, T value) {
        std::ostringstream oss;
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << value << format.substr(pos + 2);
        } else {
            oss << format;
        }
        return oss.str();
    }

    template<typename T, typename... Args>
    static std::string Format(const std::string& format, T first, Args... rest) {
        std::ostringstream oss;
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << first;
            std::string remaining = format.substr(pos + 2);
            oss << Format(remaining, rest...);
        } else {
            oss << format;
        }
        return oss.str();
    }

    static std::string Format(const std::string& format) {
        return format;
    }
};

} // namespace core
} // namespace bf
