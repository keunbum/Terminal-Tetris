#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "debug.h"
#include "draw/cursor.h"
#include "error_handling.h"
#include "game_system/game_system_manager.h"
#include "localize/localize.h"
#include "mt19937.h"
#include "test/test.h"
#include "tetris/tetromino/tetromino.h"
#include "tetris/play/tetris_play_board.h"

static void init(void)
{
    debug();

    localize();
    
    init_cursor_lock();
    init_tetris_play_tetromino_lock();
    init_tetris_play_board_lock();   

    init_rng((uint32_t)time(NULL));
}

static void cleanup(void)
{
    debug();

    cleanup_tetris_play_board_lock();
    cleanup_tetris_play_update_lock();
    cleanup_cursor_lock();
}

static void main2(void)
{
    debug();

    init();
    run_game_system_manager();
    cleanup();
}

int main(int argc, char* argv[])
{
    debug();

    (void)argc;
    (void)argv;

#ifdef UNIT_TEST
    test_module(argc, argv);
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