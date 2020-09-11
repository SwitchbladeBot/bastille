#include <iostream>
#include <string>

#include <v8.h>
#include <v8pp/module.hpp>
#include <libplatform/libplatform.h>
#include "../modules/console.h"

class Runnable {
public:
    std::string Run(const std::string& code);
    ~Runnable();
private:
    v8::Isolate::CreateParams create_params = v8::Isolate::CreateParams();
    v8::ArrayBuffer::Allocator* allocator = create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
//    v8::Local<v8::ObjectTemplate> base_object = v8::ObjectTemplate::New(isolate);
//    v8::Global<v8::Context> global_context = v8::Global<v8::Context>();
    v8::Global<v8::ObjectTemplate> global = v8::Global<v8::ObjectTemplate>();
};