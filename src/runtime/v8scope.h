#include <v8.h>
#include <libplatform/libplatform.h>

class v8scope {
private:
    std::unique_ptr<v8::Platform> platform;
    static auto initialize_platform(const char* path);
public:
    explicit v8scope(const char* path);
    ~v8scope();
};
