#include "http.h"

v8::Local<v8::Value> Http::Init(v8::Isolate *isolate) {
    v8pp::module module(isolate);

    module.set("get", get());

    return module.new_instance();
}

JavascriptCallbackGetter Http::get() {
    return [this](JavascriptCallback &args) {
        if (args.Length() != 1) {
            return;
        }

        v8::String::Utf8Value url(args.GetIsolate(), args[0]);
        cpr::Response res = cpr::Get(cpr::Url{*url}, cpr::VerifySsl(false));

        try {
            // If JSON was not valid, this will error
            json::parse(res.text);

            // Perform conversion
            v8::Local<v8::String> json_string;
            if (v8::String::NewFromUtf8(args.GetIsolate(), res.text.c_str()).ToLocal(&json_string)) {
                v8::Local<v8::Value> json;
                if (v8::JSON::Parse(args.GetIsolate()->GetCurrentContext(), json_string).ToLocal(&json)) {
                    args.GetReturnValue().Set(json);
                }
            }
        } catch (const std::exception&) {
            args.GetReturnValue().Set(v8pp::to_v8(args.GetIsolate(), res.text.c_str()));
        }
    };
}