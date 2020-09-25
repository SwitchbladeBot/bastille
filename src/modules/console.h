#pragma once

#include <v8pp/module.hpp>
#include <v8.h>
#include <string>
#include <functional>
#include "callback.h"
#include "../runtime/module.h"
#include "../runtime/output/output.h"
#include "../runtime/output/logtype.h"


class Console : public Module {
    JavascriptCallbackGetter log();
    Output* log_output;
public:
    explicit Console(Output* console_output);

    v8::Local<v8::Value> Init(v8::Isolate *isolate) override;
};
