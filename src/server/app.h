#include <served/plugins.hpp>
#include <served/served.hpp>

using RouteGetter = std::function<void(served::response &, const served::request &)>;

class app {
    static RouteGetter run();

public:
    app();
};
