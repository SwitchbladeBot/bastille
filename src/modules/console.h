#pragma once

#include <v8pp/module.hpp>
#include <v8.h>
#include <string>
#include <functional>
#include "callback.h"
#include "../runtime/module.h"


class Console : public Module {
    JavascriptCallbackGetter log();
    std::string* log_output;
public:
    Console(std::string* console_output);

    v8::Local<v8::Value> Init(v8::Isolate *isolate) override;
};
