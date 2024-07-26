//
// Created by anthony on 21/07/2024.
//

#ifndef SINGLETON_ASYNC_H
#define SINGLETON_ASYNC_H


#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/async.h>
#include <memory>

class Logger {
public:
    static std::shared_ptr<spdlog::logger>& getInstance() {
        static std::shared_ptr<spdlog::logger> instance = spdlog::basic_logger_mt<spdlog::async_factory>("file_logger", "logs/logfile.log");
        return instance;
    }

    static void setupLogger(spdlog::level::level_enum level = spdlog::level::info) {
        spdlog::init_thread_pool(8192, 1); // Queue size 8192, 1 backing thread
        auto& logger = getInstance();
        logger->set_level(level); // Set global log level
        logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v"); // Set log pattern
        spdlog::set_default_logger(logger); // Set as default logger
        spdlog::set_error_handler([](const std::string &msg) {
            std::cerr << "spdlog error: " << msg << std::endl;
        });
        logger->flush_on(spdlog::level::info); // Flush on every info level message
        spdlog::info("Logger initialized");
    }

private:
    Logger() = default; // Private constructor to prevent instantiation
    Logger(const Logger&) = delete; // Delete copy constructor
    Logger& operator=(const Logger&) = delete; // Delete copy assignment operator
};




#endif //SINGLETON_ASYNC_H
