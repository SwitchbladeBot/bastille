#include <iostream>
#include "src/runtime/runnable.h"
#include "src/runtime/v8scope.h"

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = std::make_unique<Runnable>();
    std::cout << runnable->Run("console.log('Hello World');");

    return 0;
}
