#include "config.h"

Config::Config(const char* path) {
    std::ifstream stream("config.json");

    std::string text((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());

    try {
        json j = json::parse(text);

        this->port = j["port"];
    } catch (...) {
        spdlog::error("Invalid config file");
        exit(0);
    }

    stream.close();
}
