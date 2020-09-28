#include "module.h"


v8::Local<v8::Value> Fetch::Init(v8::Isolate *isolate) {
    return v8pp::wrap_function(isolate, "fetch", fetch);
}

void Fetch::fetch(JavascriptCallback &args) {
    if (args.Length() != 1) {
        return;
    }

    v8::String::Utf8Value url(args.GetIsolate(), args[0]);
    cpr::Response res = cpr::Get(cpr::Url{*url}, cpr::VerifySsl(false));

    auto resolver = v8::Promise::Resolver::New(args.GetIsolate()->GetCurrentContext());

    args.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());

    resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), Response(res).Init(args.GetIsolate()));
}

//
//JavascriptCallbackGetter Fetch::fetch() {
//    return [](JavascriptCallback &args) {
//        if (args.Length() != 1) {
//            return;
//        }
//
//        v8::String::Utf8Value url(args.GetIsolate(), args[0]);
//        cpr::Response res = cpr::Get(cpr::Url{*url}, cpr::VerifySsl(false));
//
//        auto resolver = v8::Promise::Resolver::New(args.GetIsolate()->GetCurrentContext());
//        args.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());
//
//        try {
//            // If JSON was not valid, this will error
//            json::parse(res.text);
//
//            // Perform conversion
//            v8::Local<v8::String> json_string;
//            if (v8::String::NewFromUtf8(args.GetIsolate(), res.text.c_str()).ToLocal(&json_string)) {
//                v8::Local<v8::Value> json;
//                if (v8::JSON::Parse(args.GetIsolate()->GetCurrentContext(), json_string).ToLocal(&json)) {
//                    resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), json);
//                }
//            }
//        } catch (const std::exception&) {
//            resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), v8pp::to_v8(args.GetIsolate(), res.text));
//        }
//    };
//}