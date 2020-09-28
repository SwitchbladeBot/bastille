#pragma once

#include "../callback.h"
#include "../../runtime/module.h"
#include <v8pp/function.hpp>
#include <cpr/cpr.h>
#include "response.h"


class Fetch : public Module {
    static void fetch(JavascriptCallback &args);
public:
    v8::Local<v8::Value> Init(v8::Isolate *isolate) override;
};
