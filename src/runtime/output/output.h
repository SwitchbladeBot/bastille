#pragma once

#include <vector>
#include "message.h"
#include "logtype.h"

class Output {
    std::vector<Message> messages;

public:
    void Log (std::string, LogType, int = 0);
    json ToJson();
};