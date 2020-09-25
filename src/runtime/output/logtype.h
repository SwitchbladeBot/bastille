#pragma once

enum LogType {
    LOG,
    INFO,
    ERROR,
    WARN,
    DEBUG
};

const char* GetStringLogType(LogType log_type);