#include "logger.h"
#include <iostream>
#include <string>

void log::info(std::string message) {
    const char* infoPrefix = log::colorSettings["info"];
    std::cout << '[' << infoPrefix << "INFO - " << log::prefix << "\x1b[0m] " << message << '\n';
}

void log::warn(std::string message) {
    const char* warningPrefix = log::colorSettings["warning"];
    std::cout << '[' << warningPrefix << "WARNING - " << log::prefix << "\x1b[0m] " << message << '\n';
}

void log::error(std::string message) {
    const char* errorPrefix = log::colorSettings["error"];
    std::cout << '[' << errorPrefix << "ERROR - " << log::prefix << "\x1b[0m] " << message << '\n';
}