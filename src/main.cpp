#include "runtime/runnable.h"
#include "runtime/v8scope.h"

#include "modules/http.h"

#include "server/app.h"

#include "modules/console.h"
#include "modules/http.h"

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

//    auto runnable = Runnable();
//
//    auto console = Console(&runnable.log_output);
//    auto http = Http();
//    runnable.Register("fetch", &http);
//    runnable.Register("console", &console);
//
//    runnable.Run("console.log(5,6)");

    app();

    return 0;
}
