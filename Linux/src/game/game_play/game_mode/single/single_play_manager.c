#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "debug/debug.h"
#include "draw_tool/cursor.h"
#include "draw_tool/digital_digit.h"
#include "error/error_handling.h"
#include "game/game_play/game_mode/game_play_manager.h"
#include "game/game_play/game_play.h"
#include "game/game_play/physics/simulate.h"
#include "game/game_play/signal/signal_macro.h"
#include "game/game_play/tetromino/block_code_set.h"
#include "game/game_play/tetromino/tetromino.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/timer_drawer.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_ui.h"
#include "single_play_manager.h"
#include "util/random/random.h"

static void load_ui(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    int res = load_game_play_ui(play_manager->mode, play_manager->screen_start_pos_x_wprint, play_manager->screen_start_pos_y_wprint, play_manager->screen_height_wprint);
    if (res == -1) {
        handle_error("load_game_play_ui() error");
    }
}

static int ready_getset_go(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    for (int cur_sec = play_manager->ready_getset_go_sec; cur_sec >= 0; --cur_sec) {
        pos_t pos_x_in_wprint = play_manager->screen_start_pos_x_wprint + 2;
        pos_t pos_y_in_wprint = GAME_PLAY_BOARD_FRAME_START_POS_Y_WPRINT + GAME_PLAY_BOARD_FRAME_WIDTH - 2;
        if (cur_sec == 0) {
            wdraw_digital_digit_at_r(G_DIGITAL_DIGIT_EMPTY, (int)pos_x_in_wprint, (int)pos_y_in_wprint);
            break;
        }
        wdraw_digital_digit_at_r(G_DIGITAL_DIGITS[cur_sec], (int)pos_x_in_wprint, (int)pos_y_in_wprint);
        /* Of course, it's not exactly 1 second. */
        sleep(1);
    }
    return 0;
}

static void init_game_main_module(void)
{
    debug();

    init_rng((unsigned int)time(NULL));
    init_game_board();
    init_tetromino_generator();
}

static void* main_func_game_main_module(void* arg)
{
    debug();
    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    init_game_main_module();
    bool is_game_over = false;
    while (!is_game_over) {
        const block_code_set_t* code_set = G_BLOCK_CODE_SET_DEFAULT;
        tetromino_t tetromino_obj;
        symbol_id_t symbol_id = rng() % TOTAL_TETROMINO_NUM_OF_KINDS;
        init_a_tetromino(
            &tetromino_obj,
            symbol_id,
            GAME_PLAY_TETROMINO_INIT_POS_X,
            GAME_PLAY_TETROMINO_INIT_POS_Y,
            GAME_PLAY_TETROMINO_INIT_VELOCITY,
            DIR_BOT,
            code_set->codes[get_block_code_fixed(code_set, symbol_id)]);
        // hmm...
        draw_a_tetromino_r(&tetromino_obj);
        /* Uh.. I think.. The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // draw_over_all();
            // handle_user_input();
            erase_a_tetromino_r(&tetromino_obj);
            int status = move_a_tetromino(&tetromino_obj);
            draw_a_tetromino_r(&tetromino_obj);
            if (status == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino(&tetromino_obj);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                if (is_at_skyline(&tetromino_obj)) {
                    is_game_over = true;
                    break;
                }
                break;
            }
            /* Not a good way. Either define a constant or use a separate variable.*/
            usleep(16666);
            // usleep(60000);
        }
    }
    timer_drawer_t* timer_drawer = (timer_drawer_t*)arg;
    set_realtime_timer(&timer_drawer->timer, false);
    wclear();

    return (void*)GAME_PLAY_STATUS_GAME_OVER;
}

static void run_game_play_module_in_parallel(game_play_module_t* const out_game_play_module)
{
    debug();

    pthread_create(&out_game_play_module->pthread_id, NULL, out_game_play_module->main_func, out_game_play_module->main_func_arg);
    if (out_game_play_module->is_detached) {
        pthread_detach(out_game_play_module->pthread_id);
    }
}

static int run_game_play_modules_in_parallel(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    game_play_module_t game_play_modules[] = {
        {
            .main_func = main_func_game_main_module,
            .main_func_arg = (void*)&play_manager->timer_drawer,
            .is_detached = false,
        },
        {
            .main_func = main_func_game_play_timer,
            .main_func_arg = (void*)&play_manager->timer_drawer,
            .is_detached = false,
        },
    };
    size_t game_play_module_num = (size_t)(sizeof(game_play_modules) / sizeof(game_play_modules[0]));

    /* Block REALTIME_TIMER_SIG */
    block_signal(SIGRTMIN);

    for (size_t i = 0; i < game_play_module_num; ++i) {
        run_game_play_module_in_parallel(game_play_modules + i);
    }
    for (size_t i = 0; i < game_play_module_num; ++i) {
        game_play_module_t* const module = game_play_modules + i;
        if (module->is_detached) {
            continue;
        }
        if (pthread_join(module->pthread_id, &module->retval) != 0) {
            handle_error("pthread_join() error");
        }
    }
    game_play_module_t* const main_module = game_play_modules + 0;
    return (int)(long long)main_module->retval;
}

/*
static int selection_after_game_over(void)
{
    debug();

    // not yet implemented.

    return GAME_PLAY_CMD_EXIT_GAME;
} */

static int run_simulation(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    if (ready_getset_go(play_manager) == -1) {
        handle_error("ready_getset_go() error");
    }

    if (run_game_play_modules_in_parallel(play_manager) == -1) {
        handle_error("run_game_play_modules_in_parallel() error");
    }

    /* UX after Game Over not implemented yet. */
    return GAME_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

static int start_game(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    load_ui(play_manager);

    int res;
    if ((res = run_simulation(play_manager)) == -1) {
        handle_error("run_simulation() error");
    }
    return res;
}

static int play_a_new_game(const game_play_manager_module_arg_t* play_manager)
{
    debug();

    int res = GAME_PLAY_CMD_ERROR;
    if ((res = start_game(play_manager)) == -1) {
        handle_error("start_simulation() error");
    }
    return res;
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_single_play_mode(void* arg)
{
    debug();

    (void)arg;

    game_play_manager_module_arg_t play_manager = {
        .mode = GAME_PLAY_MODE_SINGLE,
        .screen_start_pos_x_wprint = GAME_PLAY_SINGLE_SCREEN_START_POS_X_WPRINT,
        .screen_start_pos_y_wprint = GAME_PLAY_SINGLE_SCREEN_START_POS_Y_WPRINT,
        .screen_height_wprint = GAME_PLAY_SINGLE_SCREEN_HEIGHT_WPRINT,
        .ready_getset_go_sec = GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC,
        .timer_drawer = {
            .timer = {
                .its.it_interval = {
                    .tv_sec = GAME_PLAY_TIMER_IT_INTERVAL_SEC,
                    .tv_nsec = GAME_PLAY_TIMER_IT_INTERVAL_NSEC,
                },
                .its.it_value = {
                    .tv_sec = GAME_PLAY_TIMER_IT_VALUE_SEC,
                    .tv_nsec = GAME_PLAY_TIMER_IT_VALUE_NSEC,
                },
                .timer_sig = SIGRTMIN,
                .clockid = REALTIME_TIMER_CLOCK_ID,
            },
            .draw_module = {
                .pos_x_wprint = GAME_PLAY_TIMER_POS_X_WPRINT,
                .pos_y_wprint = GAME_PLAY_TIMER_POS_Y_WPRINT,
                .draw_func = draw_game_play_timer_at_with_r,
            },
        },
    };

    while (true) {
        int res = play_a_new_game(&play_manager);
        if (res == GAME_PLAY_CMD_EXIT_GAME) {
            break;
        }
        if (res == GAME_PLAY_CMD_ERROR) {
            handle_error("run_single_play() error");
        }
        if (res == GAME_PLAY_CMD_REGAME) {
            continue;
        }
        my_assert(false);
    }
    return NULL;
}
