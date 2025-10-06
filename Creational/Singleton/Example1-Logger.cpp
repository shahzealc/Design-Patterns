#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

enum class LogType { Info, Warning, Error };

class Log {
   public:
    static Log& Get() {
        static Log instance;
        return instance;
    }

    void logIt(const std::string& message, LogType type = LogType::Info) {
        std::lock_guard<std::mutex> lock(mutex_);

        std::ostringstream oss;
        oss << "[" << getTimestamp() << "] "
            << "[" << logTypeToString(type) << "] " << message << "\n";

        std::cout << oss.str();
    }

   private:
    std::mutex mutex_;

    Log() = default;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    ~Log() = default;

    std::string logTypeToString(LogType type) const {
        switch (type) {
            case LogType::Info:
                return "INFO";
            case LogType::Warning:
                return "WARNING";
            case LogType::Error:
                return "ERROR";
            default:
                return "UNKNOWN";
        }
    }

    std::string getTimestamp() const {
        using namespace std::chrono;
        auto now{system_clock::now()};
        auto now_time{system_clock::to_time_t(now)};
        auto ms{duration_cast<milliseconds>(now.time_since_epoch()) % 1000};

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_time), "%d-%m-%Y %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }
};

int main() {
    Log::Get().logIt("Application started", LogType::Info);
    Log::Get().logIt("User interacted");
    Log::Get().logIt("Low memory warning", LogType::Warning);
    Log::Get().logIt("Fatal error: Out of memory!", LogType::Error);
    Log::Get().logIt("Application shutting down", LogType::Info);
    return 0;
}
