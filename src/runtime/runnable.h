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
    static v8::Isolate::CreateParams GetDefaultParams();

    v8::Isolate::CreateParams create_params = GetDefaultParams();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
};