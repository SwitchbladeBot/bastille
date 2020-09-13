#include <iostream>
#include "src/runtime/runnable.h"
#include "src/runtime/v8scope.h"
#include "src/modules/console.h"

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = std::make_unique<Runnable>();

    auto console = Console(&runnable->log_output);
    runnable->Register("console", &console);

    std::cout << runnable->Run(R"(
        for (i = 0; i < 5; i++) {
            console.log(i)
        }
    )");

    return 0;
}
