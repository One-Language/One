#include "one.h"
#include "cli.h"

int main(int argc, char** argv)
{
    CLI *cli = cli_init(argc, argv);
    int res = cli_run(cli);
    cli_free(cli);

    return res;
}
