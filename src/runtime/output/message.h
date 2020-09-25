#pragma once
#include "logtype.h"

struct Message {
    Message(std::string&, LogType, int);

    std::string message;
    LogType type;
    int line; // Empty if not error
};