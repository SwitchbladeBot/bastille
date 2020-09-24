#include "runtime/runnable.h"
#include "runtime/v8scope.h"

#include "modules/console.h"
#include "modules/http.h"

#include <cpr/cpr.h>

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = Runnable();

    auto console = Console(&runnable.log_output);
    auto http = Http();
    runnable.Register("http", &http);
    runnable.Register("console", &console);

    std::cout << runnable.Run(R"(
        let x = http.get("https://waifu.pics/api/nsfw/waifu")
        console.log(x.url)
    )") << std::endl;

    return 0;
}
