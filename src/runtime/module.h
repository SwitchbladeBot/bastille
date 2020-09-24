#pragma once

class Module {
public:
    virtual v8::Local<v8::Value> Init(v8::Isolate *isolate) = 0;
};