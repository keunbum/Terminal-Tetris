#include <locale.h>

#include "debug/debug.h"
#include "localize.h"

void localize(void)
{
    debug();

    setlocale(LC_CTYPE, "");
}