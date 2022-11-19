#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <string>
using namespace std::string_literals;

int main(int argc, char **argv) {
    doctest::Context context;
    const char *clicolor_force = std::getenv("CLICOLOR_FORCE");

    context.setOption("force-colors", clicolor_force != nullptr && clicolor_force == "1"s ? true : false);

    context.applyCommandLine(argc, argv);

    int res = context.run();

    if (context.shouldExit())
        return res;

    int client_stuff_return_code = 0;

    return res + client_stuff_return_code;
}