#include "runtime/runnable.h"
#include "runtime/v8scope.h"
#include "modules/console.h"

#include <cpr/cpr.h>

int main(int argc, char* argv[]) {
    v8scope v8(argv[0]);

    auto runnable = Runnable();

    auto console = Console(&runnable.log_output);
    runnable.Register("console", &console);

    std::cout << runnable.Run(R"(
        for (i = 0; i < 5; i++) {
            console.log(i)
        }
    )") << std::endl;

    cpr::Response r = cpr::Get(cpr::Url{"https://waifu.pics/api/nsfw/waifu"}, cpr::VerifySsl(false));
    std::cout << r.text << std::endl;

    return 0;
}
