#include "runnable.h"

#include <v8.h>
#include <libplatform/libplatform.h>
#include <string>

Runnable::Runnable() {
    v8::Isolate::CreateParams create_params;
    this->allocator = create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    this->isolate = v8::Isolate::New(create_params);
}
std::string Runnable::Run(const std::string& code) {
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope(context);

    v8::MaybeLocal<v8::String> code_local = v8::String::NewFromUtf8(isolate, code.c_str());
    v8::MaybeLocal<v8::Script> code_compiled = v8::Script::Compile(context, code_local.ToLocalChecked());
    v8::MaybeLocal<v8::Value> code_result = code_compiled.ToLocalChecked()->Run(context);
    v8::String::Utf8Value return_string(isolate, code_result.ToLocalChecked());
    std::string final(*return_string);
    return final;
}
Runnable::~Runnable() {
    isolate->Dispose();
    delete this->allocator;
}