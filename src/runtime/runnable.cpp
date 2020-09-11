#include "runnable.h"

std::string Runnable::Run(const std::string& code) {
    v8::HandleScope handle_scope = v8::HandleScope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);
    v8::Context::Scope context_scope = v8::Context::Scope(context);

    // Register modules
    // CONSOLE
    Module::Console console = Module::Console();
    isolate->GetCurrentContext()->Global()->Set(context,
            v8::MaybeLocal<v8::String>(v8::String::NewFromUtf8(isolate, "console")).ToLocalChecked(),
            console.Init(isolate));
    // Stop registering

    v8::MaybeLocal<v8::String> code_local = v8::String::NewFromUtf8(this->isolate, code.c_str());
    v8::MaybeLocal<v8::Script> code_compiled = v8::Script::Compile(context, code_local.ToLocalChecked());
    v8::MaybeLocal<v8::Value> code_result = code_compiled.ToLocalChecked()->Run(context);
    v8::String::Utf8Value return_string(this->isolate, code_result.ToLocalChecked());
    std::string final(*return_string);
    return console.log_output;
}

Runnable::~Runnable() {
    isolate->Dispose();
}

v8::Isolate::CreateParams Runnable::GetDefaultParams() {
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    return create_params;
}
