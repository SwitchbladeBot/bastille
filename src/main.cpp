#include "runtime/v8scope.h"

#include "app/app.h"


int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);
    app();

    return 0;
}
