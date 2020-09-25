#include <served/plugins.hpp>
#include <served/served.hpp>

using RouteGetter = std::function<void(served::response &, const served::request &)>;

class App {
    static RouteGetter run();

public:
    App();
};
