//
// Created by anthony on 21/07/2024.
//

#ifndef DI_SYNC_H
#define DI_SYNC_H


#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

class Logger {
public:
    Logger() {
        logger_ = spdlog::basic_logger_mt("file_logger", "logs/logfile.log");
        logger_->set_level(spdlog::level::info);
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
    }

    std::shared_ptr<spdlog::logger> getLogger() {
        return logger_;
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};

#include <memory>

class Application {
public:
    Application(std::shared_ptr<spdlog::logger> logger) : logger_(logger) {}

    void run() {
        logger_->info("Application started");
        // Your application code here
        logger_->info("Application finished");
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};

int main() {
    auto logger = std::make_shared<Logger>();
    auto app = Application(logger->getLogger());
    app.run();
    return 0;
}


#endif //DI_SYNC_H
