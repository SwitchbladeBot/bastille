#pragma once

#include <served/plugins.hpp>
#include <served/served.hpp>
#include <spdlog/spdlog.h>

#include "../runtime/runnable.h"
#include "../modules/console.h"
#include "../runtime/v8scope.h"
#include "../modules/fetch/module.h"
#include "config.h"

using RouteGetter = std::function<void(served::response &, const served::request &)>;

class app {
    static RouteGetter run();

public:
    app();
};
