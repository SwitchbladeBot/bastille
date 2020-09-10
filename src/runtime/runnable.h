#include <v8.h>

class Runnable {
public:
    explicit Runnable();
    std::string Run(const std::string& code);
    ~Runnable();
private:
    v8::Isolate* isolate;
    v8::ArrayBuffer::Allocator *allocator;
};