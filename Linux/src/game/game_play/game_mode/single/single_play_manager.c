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
#include "game/game_play/game_play.h"
#include "game/game_play/physics/simulate.h"
#include "game/game_play/random/random.h"
#include "game/game_play/signal/signal_macro.h"
#include "game/game_play/tetromino/tetromino.h"
#include "game/game_play/timer/game_play_timer.h"
#include "game/game_play/timer/realtime_timer_drawer.h"
#include "game/game_play/ui/game_play_screen.h"
#include "game/game_play/ui/game_play_ui.h"
#include "single_play_manager.h"

static void load_ui(void)
{
    debug();

    int res = load_game_play_ui(GAME_PLAY_MODE_SINGLE, GAME_PLAY_SINGLE_SCREEN_START_POS_X_IN_WPRINT, GAME_PLAY_SINGLE_SCREEN_START_POS_Y_IN_WPRINT, GAME_PLAY_SINGLE_SCREEN_HEIGHT_IN_WPRINT);
    if (res == -1) {
        handle_error("load_game_play_ui() error");
    }
}

static int ready_getset_go(int init_sec)
{
    /* not yet */
    debug();

    for (int sec = init_sec; sec >= 0; --sec) {
        pos_t pos_x = GAME_PLAY_SINGLE_SCREEN_START_POS_X_IN_WPRINT + 2;
        pos_t pos_y = GAME_PLAY_GRID_MATRIX_START_POS_Y_IN_WPRINT + GAME_PLAY_GRID_MATRIX_WIDTH - 2;
        if (sec == 0) {
            wdraw_digital_digit_at_r(G_DIGITAL_DIGIT_EMPTY, (int)pos_x, (int)pos_y);
            break;
        }
        wdraw_digital_digit_at_r(G_DIGITAL_DIGITS[sec], (int)pos_x, (int)pos_y);
        sleep(1);
    }
    return 0;
}

static void init_game_main_module(int* const out_block_code_ration)
{
    debug();

    init_rng((unsigned int)time(NULL));
    init_game_board();
    init_tetromino_generator();
    *out_block_code_ration = rng();
}

static void* main_func_game_main_module(void*)
{
    debug();
    /* Not a good logic yet. There is a possibility of change,
       but first of all, I will write the code sequentially. */
    int block_code_rotation;
    init_game_main_module(&block_code_rotation);
    bool game_over = false;
    while (!game_over) {
        const block_code_set_t* code_set = &G_BLOCK_CODE_SET_DEFAULT;
        tetromino_t tetromino_obj;
        symbol_id_t sid = rng() % TOTAL_TETROMINO_NUM;
        init_tetromino(
            &tetromino_obj,
            sid,
            GAME_PLAY_INIT_TETROMINO_POS_X,
            GAME_PLAY_INIT_TETROMINO_POS_Y,
            GAME_PLAY_INIT_TETROMINO_VELOCITY,
            DIR_BOT,
            code_set->codes[get_block_code_fixed(code_set, sid, block_code_rotation)]);
        // hmm...
        draw_tetromino_at_r(&tetromino_obj, tetromino_obj.pos_x, tetromino_obj.pos_y);
        /* Uh.. I think.. The concept of speed should be defined like this,
           "Every few frames it goes down by one block." */
        while (true) {
            // draw_over_all();
            // handle_user_input();
            disappear_tetromino(&tetromino_obj);
            int status = move_tetromino(&tetromino_obj);
            draw_tetromino(&tetromino_obj);
            if (status == TETROMINO_STATUS_ON_OTHERBLOCK) {
                petrity_tetromino(&tetromino_obj);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                if (is_at_skyline(&tetromino_obj)) {
                    game_over = true;
                    break;
                }
                break;
            }
            usleep(16666);
            //usleep(60000);
        }
    }

    g_realtime_timer_running = ATOMIC_VAR_INIT(false);
    wclear();

    return (void*)GAME_PLAY_STATUS_GAME_OVER;
}

static void run_game_play_module_in_parallel(game_play_module_t* const out_module)
{
    debug();

    pthread_create(&out_module->tid, NULL, out_module->func, out_module->arg);
    if (out_module->is_detached) {
        pthread_detach(out_module->tid);
    }
}

static int run_game_play_modules_in_parallel(void)
{
    debug();

    static realtime_timer_data_t s_timer_data = {
        .time_limit = GAME_PLAY_TIME_LIMIT,
        .draw_module = {
            .pos_x = GAME_PLAY_TIMER_POS_X,
            .pos_y = GAME_PLAY_TIMER_POS_Y,
            .its.it_value.tv_sec = GAME_PLAY_TIMER_INIT_EXPIRE_SEC,
            .its.it_value.tv_nsec = GAME_PLAY_TIMER_INIT_EXPIRE_NSEC,
            .its.it_interval.tv_sec = GAME_PLAY_TIMER_INTERVAL_SEC,
            .its.it_interval.tv_nsec = GAME_PLAY_TIMER_INTERVAL_NSEC,
            .draw_func = draw_game_play_timer_at_with_r,
        },
    };
    static game_play_module_t s_game_play_modules[] = {
        {
            -1,
            main_func_game_main_module,
            NULL,
            false,
            NULL,
        },
        {
            -1,
            main_func_game_play_timer,
            (void*)&s_timer_data,
            false,
            NULL,
        },
    };
    static size_t s_game_play_module_num = (size_t)(sizeof(s_game_play_modules) / sizeof(s_game_play_modules[0]));
    static int main_module_id = 0;

    for (size_t i = 0; i < s_game_play_module_num; ++i) {
        run_game_play_module_in_parallel(s_game_play_modules + i);
    }
    for (size_t i = 0; i < s_game_play_module_num; ++i) {
        game_play_module_t* const m = s_game_play_modules + i;
        if (m->is_detached) {
            continue;
        }
        if (pthread_join(m->tid, &m->retval) != 0) {
            handle_error("pthread_join() error");
        }
    }
    return (int)(long long)s_game_play_modules[main_module_id].retval;
}

/*
static int selection_after_game_over(void)
{
    debug();

    // not yet implemented.

    return GAME_PLAY_CMD_EXIT_GAME;
} */

static int run_simulation(void)
{
    debug();

    int res;
    const int init_sec = GAME_PLAY_TIMEINTERVAL_BEFORESTART_SEC;
    if ((res = ready_getset_go(init_sec)) == -1) {
        handle_error("ready_getset_go() error");
    }

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, REALTIME_TIMER_SIG);
    if ((res = pthread_sigmask(SIG_BLOCK, &sigset, NULL)) == -1) {
        handle_error_en(res, "pthread_sigmask() error");
    }

    if ((res = run_game_play_modules_in_parallel()) == -1) {
        handle_error("run_game_play_modules_in_parallel() error");
    }
    return GAME_PLAY_CMD_REGAME;
    // return selection_after_game_over();
}

static int start_game(void)
{
    debug();

    load_ui();

    int res;
    if ((res = run_simulation()) == -1) {
        handle_error("run_simulation() error");
    }
    return res;
}

static int new_play_game(void)
{
    debug();

    int res = GAME_PLAY_CMD_ERROR;
    if ((res = start_game()) == -1) {
        handle_error("start_simulation() error");
    }
    return res;
}

/* --------------------------------------------------------------------------------------------------------- */

void* run_single_mode(void* arg)
{
    debug();

    while (true) {
        int status = new_play_game();
        // int status = new_play_game();
        if (status == GAME_PLAY_CMD_EXIT_GAME) {
            break;
        }
        if (status == GAME_PLAY_CMD_ERROR) {
            handle_error("run_single_play() error");
        }
        if (status == GAME_PLAY_CMD_REGAME) {
            continue;
        }
        my_assert(false);
    }
    return NULL;
}
