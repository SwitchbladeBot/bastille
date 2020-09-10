#include <iostream>
#include <memory>
#include <string>
#include "src/runtime/runnable.h"
#include "src/runtime/v8scope.h"

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = std::make_unique<Runnable>();
    std::cout << runnable->Run("5+5");

    return 0;
}