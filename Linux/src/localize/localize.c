#include <locale.h>

#include "debug/debug.h"
#include "localize/localize.h"

void localize(void)
{
    debug();

    setlocale(LC_CTYPE, "");
}