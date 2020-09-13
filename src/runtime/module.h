#pragma once

class Module {
public:
    std::string name = "console";
    virtual v8::Local<v8::Value> Init(v8::Isolate *isolate) = 0;
};