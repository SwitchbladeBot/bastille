#pragma once

#include "../runtime/module.h"
#include "callback.h"
#include <v8pp/module.hpp>
#include <cpr/cpr.h>

class Http : public Module {
    JavascriptCallbackGetter get();
public:
    v8::Local<v8::Value> Init(v8::Isolate *isolate) override;
};
