#include "app.h"

app::app() {
    served::multiplexer mux;

    mux.handle("/run").post(run());

    served::net::server server("0.0.0.0", "8080", mux);
    server.run(10);
}

RouteGetter app::run() {
    return [](served::response & res, const served::request & req) {
        json body;
        try {
            body = json::parse(req.body());
            if (body["script"].is_null()) {
                throw std::exception();
            }
        } catch (std::exception& e) {
            res.set_status(400);
            res << "Invalid body";
            return;
        }

        auto runnable = Runnable();

        auto console = Console(runnable.log_output);
        auto fetch = Fetch();
        runnable.Register("fetch", fetch);
        runnable.Register("console", console);

        res.set_header("Content-Type", "application/json");

        res << runnable.Run(body["script"]).ToJson().dump();
    };
}
