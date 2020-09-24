#include "runtime/runnable.h"
#include "runtime/v8scope.h"

#include "modules/console.h"
#include "modules/http.h"


int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = Runnable();

    auto console = Console(&runnable.log_output);
    auto http = Http();
    runnable.Register("http", &http);
    runnable.Register("console", &console);

    std::cout << runnable.Run(R"(
        http.get("https://waifu.pics/api/nsfw/waifu").then(data => {
            console.log(data.url)
        })
        ff(
    )") << std::endl;

    return 0;
}
