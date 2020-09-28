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

    if (!res.error) {
        resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), Response(res).Init(args.GetIsolate()));
    } else {
        resolver.ToLocalChecked()->Reject(args.GetIsolate()->GetCurrentContext(),
                                          v8::String::NewFromUtf8(args.GetIsolate(), res.error.message.c_str()).ToLocalChecked());
    }
}
