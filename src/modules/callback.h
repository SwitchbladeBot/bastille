#include <v8.h>
#include <functional>


using JavascriptCallback = const v8::FunctionCallbackInfo<v8::Value>;
using JavascriptCallbackGetter = std::function<void(JavascriptCallback &)>;
