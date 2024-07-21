//
// Created by anthony on 21/07/2024.
//

#ifndef DI_ASYNC_H
#define DI_ASYNC_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>
#include <memory>

class Logger {
public:
    Logger() {
        spdlog::init_thread_pool(8192, 1); // Queue size 8192, 1 backing thread
        logger_ = spdlog::basic_logger_mt<spdlog::async_factory>("file_logger", "logs/logfile.log");
        logger_->set_level(spdlog::level::info);
        logger_->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
        spdlog::set_default_logger(logger_);
        spdlog::set_error_handler([](const std::string &msg) {
            std::cerr << "spdlog error: " << msg << std::endl;
        });
        logger_->flush_on(spdlog::level::info); // Flush on every info level message
        spdlog::info("Logger initialized");
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

#include "logger.h"
#include "application.h"

int main() {
    auto logger = std::make_shared<Logger>();
    auto app = Application(logger->getLogger());
    app.run();
    return 0;
}


#endif //DI_ASYNC_H
