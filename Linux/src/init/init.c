#include <locale.h>

#include "debug/debug.h"
#include "init.h"

void init_localize(void)
{
    debug();

    setlocale(LC_CTYPE, "");
}

void init(void)
{
    debug();

    init_localize();
}