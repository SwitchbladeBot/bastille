#include "response.h"

Response::Response(const cpr::Response& res) {
    this->response = res;
}

v8::Local<v8::Value> Response::Init(v8::Isolate* isolate) {
    v8pp::module module(isolate);

    module.set("json", this->json());
    module.set("text", this->text());
    module.set("status", v8::Number::New(isolate, this->response.status_code));

    return module.new_instance();
}

JavascriptCallbackGetter Response::json() {
    return [this, _ = shared_from_this()](JavascriptCallback &args) {
        auto resolver = v8::Promise::Resolver::New(args.GetIsolate()->GetCurrentContext());
        args.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());

        v8::TryCatch try_catch(args.GetIsolate());

        v8::Local<v8::String> json_string;
        if (v8::String::NewFromUtf8(args.GetIsolate(), this->response.text.c_str()).ToLocal(&json_string)) {
            v8::Local<v8::Value> json;
            if (v8::JSON::Parse(args.GetIsolate()->GetCurrentContext(), json_string).ToLocal(&json)) {
                resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), json);
            }
        }

        if (try_catch.HasCaught()) {
            resolver.ToLocalChecked()->Reject(args.GetIsolate()->GetCurrentContext(),
                                              try_catch.Exception()->ToString(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
        }
    };
}

JavascriptCallbackGetter Response::text() {
    return [this, _ = shared_from_this()](JavascriptCallback &args) {
        auto resolver = v8::Promise::Resolver::New(args.GetIsolate()->GetCurrentContext());
        args.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());
        v8::Local<v8::String> text;

        v8::TryCatch try_catch(args.GetIsolate());

        if (v8::String::NewFromUtf8(args.GetIsolate(), this->response.text.c_str()).ToLocal(&text)) {
            resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), text);
        }

        if (try_catch.HasCaught()) {
            resolver.ToLocalChecked()->Reject(args.GetIsolate()->GetCurrentContext(),
                                              try_catch.Exception()->ToString(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
        }
    };
}