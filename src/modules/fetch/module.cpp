#include "module.h"


v8::Local<v8::Value> Fetch::Init(v8::Isolate *isolate) {
    return v8pp::wrap_function(isolate, nullptr, fetch);
}

void Fetch::fetch(JavascriptCallback &args) {
    if (args.Length() < 1) {
        return;
    }

    v8::String::Utf8Value url(args.GetIsolate(), args[0]);

    cpr::Session session;
    cpr::Header Headers;
    session.SetUrl(*url);
    session.SetVerifySsl(false);

    // Options object
    if (args.Length() >= 2 || !args[1].IsEmpty()) {
        v8::Local<v8::Object> options;

        if (args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocal(&options)) {
            v8::Local<v8::Value> header_value;

            if (options->Get(args.GetIsolate()->GetCurrentContext(), v8::String::NewFromUtf8(args.GetIsolate(), "headers").ToLocalChecked()).ToLocal(&header_value)) {
                v8::Local<v8::Object> headers;
                if (header_value->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocal(&headers)) {
                    auto keys = headers->GetPropertyNames(args.GetIsolate()->GetCurrentContext()).ToLocalChecked();

                    for (int i = 0; i < keys->Length(); i++) {
                        auto key = keys->Get(args.GetIsolate()->GetCurrentContext(), i).ToLocalChecked();
                        auto value = headers->Get(args.GetIsolate()->GetCurrentContext(), key).ToLocalChecked();

                        Headers[*v8::String::Utf8Value(args.GetIsolate(), key)] = *v8::String::Utf8Value(args.GetIsolate(), value);
                    }
                }
            }
        }
    }

    session.SetHeader(Headers);
    cpr::Response res = session.Get();

    auto resolver = v8::Promise::Resolver::New(args.GetIsolate()->GetCurrentContext());
    args.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());

    if (!res.error) {
        resolver.ToLocalChecked()->Resolve(args.GetIsolate()->GetCurrentContext(), std::make_shared<Response>(res)->Init(args.GetIsolate()));
    } else {
        resolver.ToLocalChecked()->Reject(args.GetIsolate()->GetCurrentContext(),
                                          v8::String::NewFromUtf8(args.GetIsolate(), res.error.message.c_str()).ToLocalChecked());
    }
}
