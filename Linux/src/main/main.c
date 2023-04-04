#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "draw/cursor.h"
#include "error_handling.h"
#include "game_system/game_system_manager.h"
#include "localize/localize.h"
#include "test/test.h"

static void init(void)
{
    debug();
    
    localize();
}

static void main2(void)
{
    debug();

    init();
    run_game_manager();
    wgotoxy(CONSOLE_STDOUT_POS_X + 1, CONSOLE_STDOUT_POS_Y);
    ewprintf("GAME ENDED.\n");
}

int main(int argc, char* argv[])
{
    debug();

    (void) argc;
    (void) argv;

#ifdef UNIT_TEST
    test_module();
#else
    main2();
#endif
    return EXIT_SUCCESS;
}

/*
 * You actually read the stuff from the bottom.

 * basic strategy:
  * read it as if you were wrong once. --> "why is this wrong??"
  * simplify. a step-by-step approach
  * readability is important
  * think rationally. keep calm
  * WRITE STUFF DOWN
  * DON'T GET STUCK ON ONE APPROACH

 * stuff you should look for
  * special cases
  * invalid pointer operation (ex. null pointer exception)
  * invalid argument passing --> type conversion required
  * error return handling
*/