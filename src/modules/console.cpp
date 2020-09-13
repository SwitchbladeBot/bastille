#include "console.h"

Console::Console(std::string* log_output) {
    this->log_output = log_output;
}

v8::Local<v8::Value> Console::Init(v8::Isolate *isolate) {
    v8pp::module module(isolate);

    module.set("log", log());

    return module.new_instance();
}

JavascriptCallbackGetter Console::log() {
    return [this](JavascriptCallback &args) {
        if (args.Length() != 1) {
            return;
        }
        v8::String::Utf8Value output(args.GetIsolate(), args[0]);
        this->log_output->append(*output);
    };
}