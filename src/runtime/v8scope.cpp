#include "v8scope.h"

auto v8scope::initialize_platform(const char* path) {
    v8::V8::InitializeICUDefaultLocation(path);
    v8::V8::InitializeExternalStartupData(path);
    return std::unique_ptr<v8::Platform> { v8::platform::NewDefaultPlatform() };
}

v8scope::v8scope(const char* path) : platform(initialize_platform(path)) {
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
}

v8scope::~v8scope() {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}