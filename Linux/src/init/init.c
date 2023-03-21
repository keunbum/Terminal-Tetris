#include <locale.h>

#include "debug/debug.h"
#include "init.h"

static void localize(void)
{
    debug();

    setlocale(LC_CTYPE, "");
}

void init(void)
{
    debug();

    localize();
}