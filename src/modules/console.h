#include <v8pp/module.hpp>
#include <v8.h>
#include <string>
#include <functional>
#include "module.h"

namespace Module {
    class Console {
        Module::JavascriptCallbackGetter log();
    public:
        std::string log_output;
        v8::Local<v8::Value> Init(v8::Isolate *isolate);
    };
}