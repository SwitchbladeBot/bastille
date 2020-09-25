#include "message.h"

Message::Message(std::string& message, LogType type, int line) {
    this->message = message;
    this->type = type;
    this->line = line;
}
