#include "console.h"

Console::Console(Output* log_output) {
    this->log_output = log_output;
}

v8::Local<v8::Value> Console::Init(v8::Isolate *isolate) {
    v8pp::module module(isolate);

    module.set("log", log());

    return module.new_instance();
}

JavascriptCallbackGetter Console::log() {
    return [this](JavascriptCallback &args) {
        if (args.Length() < 1) {
            this->log_output->Log(std::string(), LogType::LOG);
            return;
        }
        for (int i = 0; i < args.Length(); i++) {
            v8::Local<v8::Value> arg_input = args[i];

            // Promise returns "[object Promise]"
            // Stringify on "[object Promise]" is "{}"
            if (arg_input->IsPromise()) {
                arg_input->ToString(args.GetIsolate()->GetCurrentContext()).ToLocal(&arg_input);
            } else {
                v8::JSON::Stringify(args.GetIsolate()->GetCurrentContext(), arg_input).ToLocal(&arg_input);
            }
            v8::String::Utf8Value output(args.GetIsolate(), arg_input);
            std::string arg_output(*output);
            this->log_output->Log(arg_output, LogType::LOG);
        }
    };
}