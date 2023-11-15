#pragma once
#include <map>

namespace log {
    // Function definitions
    void info(std::string message);
    void warn(std::string message);
    void error(std::string message);

    static const char* prefix = "GENESIS";
    static std::map<const char*, const char*> colorSettings = {
        {
            "info",
            "\x1b[38;5;39m"
        },
        {
            "warning",
            "\x1b[38;5;35m"
        },
        {
            "error",
            "\x1b[38;5;196m"
        }
    };
}