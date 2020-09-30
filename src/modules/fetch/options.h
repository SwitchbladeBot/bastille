#pragma once

struct Options {
    explicit Options(v8::Local<v8::Object>);

    std::string method, body;
    std::map<std::string, std::string> headers;
};