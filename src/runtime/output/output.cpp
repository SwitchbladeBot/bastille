#include "output.h"

void Output::Log(std::string message, LogType log_type, int line) {
    Message m = Message(message, log_type, line);

    this->messages.push_back(m);
}

json Output::ToJson() {
    json list = json::array();

    for (Message message : messages) {
        json single = {
            {"message", message.message},
            {"type", GetStringLogType(message.type)}
        };

        if (message.type == LogType::ERROR) {
            single["line"] = message.line;
        }

        list.push_back(single);
    }

    return list;
}
