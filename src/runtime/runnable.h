#pragma once

#include <v8.h>

#include <libplatform/libplatform.h>
#include "module.h"
#include "output/output.h"
#include "output/logtype.h"


class Runnable {
public:
    Output Run(const std::string& code);
    ~Runnable();
    Runnable();
    void Register(const std::string& name, Module* module);
    Output log_output;
private:
    static v8::Isolate::CreateParams GetDefaultParams();

    v8::Local<v8::Object> global_imports;

    v8::Local<v8::Context> context;
    v8::Isolate::CreateParams create_params = GetDefaultParams();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
};