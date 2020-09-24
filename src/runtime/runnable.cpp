#include "runnable.h"

std::string Runnable::Run(const std::string& code) {
    context->Enter();
    v8::HandleScope handle_scope(isolate);
    v8::Context::Scope context_scope = v8::Context::Scope(isolate->GetCurrentContext());

    v8::MaybeLocal<v8::String> code_local = v8::String::NewFromUtf8(this->isolate, code.c_str());

    v8::TryCatch try_catch{isolate};

    v8::Local<v8::Script> code_compiled;
    if (!v8::Script::Compile(isolate->GetCurrentContext(), code_local.ToLocalChecked()).ToLocal(&code_compiled)) {
        // If compilation failed

        auto exc = try_catch.Exception();
        v8::String::Utf8Value err(isolate, exc);
        if (*err) {
            int line = try_catch.Message()->GetLineNumber(this->context).FromJust();

            std::ostringstream error;
            error << "[" << line << "] " << *err;

            std::cerr << error.str();
        }
    }

    if (!code_compiled.IsEmpty()) {
        code_compiled->Run(isolate->GetCurrentContext());
    }

    return log_output;
}

Runnable::~Runnable() {
    isolate->Dispose();
}

v8::Isolate::CreateParams Runnable::GetDefaultParams() {
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    return create_params;
}

void Runnable::Register(std::string name, Module* module) {
    context->Enter();

    v8::HandleScope handle_scope(isolate);
    isolate->GetCurrentContext()->Global()->Set(isolate->GetCurrentContext(),
            v8::MaybeLocal<v8::String>(v8::String::NewFromUtf8(isolate, name.c_str())).ToLocalChecked(),
            module->Init(isolate));
}

Runnable::Runnable() {
    v8::HandleScope handle_scope(isolate);
    v8::EscapableHandleScope escape_scope(isolate);
    v8::Local<v8::Context> context = v8::Context::New(isolate);

    this->context = escape_scope.Escape(context);
}
