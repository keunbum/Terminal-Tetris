#include <locale.h>

#include "debug.h"
#include "localize.h"

void localize(void)
{
    setlocale(LC_CTYPE, "");
}