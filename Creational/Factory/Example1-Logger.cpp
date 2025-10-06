#include <iostream>
#include <memory>
#include <string>

enum class LogType
{
    File,
    Console
};

class Logger
{
public:
    virtual void log(const std::string &message) = 0;
    virtual ~Logger() = default;
};

class FileLogger : public Logger
{
public:
    void log(const std::string &message)
    {
        std::cout << "[FILE] " << message << "\n";
    }
};

class ConsoleLogger : public Logger
{
public:
    void log(const std::string &message)
    {
        std::cout << "[CONSOLE] " << message << "\n";
    }
};

class LoggerFactory
{
public:
    static std::unique_ptr<Logger> createLogger(const LogType logType)
    {
        switch (logType)
        {
        case LogType::File:
            return std::make_unique<FileLogger>();
        case LogType::Console:
            return std::make_unique<ConsoleLogger>();
        default:
            return std::make_unique<ConsoleLogger>();
        }
    }
};

int main()
{
    auto fileLogger{LoggerFactory::createLogger(LogType::File)};
    auto consoleLogger{LoggerFactory::createLogger(LogType::Console)};

    fileLogger->log("Application started.");
    consoleLogger->log("Application started.");

    return 0;
}