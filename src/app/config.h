#pragma once

#include <iostream>
#include <fstream>
#include <streambuf>

#include <spdlog/spdlog.h>

struct Config {
    explicit Config(const char* path);

    int port;
};
