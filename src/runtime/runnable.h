#include <v8.h>

#include <libplatform/libplatform.h>
#include "../modules/console.h"
#include "module.h"


class Runnable {
public:
    std::string Run(const std::string& code);
    ~Runnable();
    Runnable();
    void Register(std::string name, Module* module);
    std::string log_output;
private:
    static v8::Isolate::CreateParams GetDefaultParams();

    v8::Local<v8::Object> global_imports;

    v8::Local<v8::Context> context;
    v8::Isolate::CreateParams create_params = GetDefaultParams();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
};