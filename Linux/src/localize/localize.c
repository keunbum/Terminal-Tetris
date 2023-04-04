#include <locale.h>

#include "debug.h"
#include "localize.h"

void localize(void)
{
    debug();

    setlocale(LC_CTYPE, "");
}