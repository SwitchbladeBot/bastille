#pragma once

#include <v8.h>
#include <cpr/cpr.h>
#include <v8pp/module.hpp>

#include "../callback.h"
#include "../../runtime/module.h"

class Response : public std::enable_shared_from_this<Response> {
    cpr::Response response;

    JavascriptCallbackGetter json();
    JavascriptCallbackGetter text();
public:
    explicit Response(const cpr::Response& res);
    v8::Local<v8::Value> Init(v8::Isolate*);
};
