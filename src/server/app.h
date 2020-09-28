#include <served/plugins.hpp>
#include <served/served.hpp>
//#include "../runtime/output/output.h"

using RouteGetter = std::function<void(served::response &, const served::request &)>;

class app {
    static RouteGetter run();

public:
    app();
};
