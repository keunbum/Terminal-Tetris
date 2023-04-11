#include <unistd.h>

#include "debug.h"
#include "game_main_loop.h"
#include "game_system/input_reader.h"
#include "tetris/scene/renderer.h"
#include "tetris/scene/tetris_play_scene.h"
#include "tetris/tetris_play_manager.h"
#include "tetris/tetris_play_submodule.h"
#include "tetris/tetromino/block_code_set.h"
#include "tetris_play_board_frame.h"
#include "tetris_play_fps.h"
#include "tetris_play_update.h"
#include "tetromino_generator.h"

static void init_game_main_loop(tetris_play_manager_t* const out_play_manager)
{
    debug();

    init_game_board(&out_play_manager->board);
    init_tetromino_generator();
    out_play_manager->status = TETRIS_PLAY_STATUS_RUNNING;
}

void* mainfunc_game_main_loop(void* arg)
{
    debug();

    /* Not a delta time(concept of FPS) version */
    tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
    init_game_main_loop(play_manager);
    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        spawn_tetromino(&play_manager->board, &play_manager->tetromino);
        while (true) {
            tetromino_t prev_tetromino = play_manager->tetromino;
            tetromino_status_t res = try_move_tetromino_r(&play_manager->board, &play_manager->tetromino, DIR_BOT);
            if (!is_equal_pos(&play_manager->tetromino.pos, &prev_tetromino.pos)
                || play_manager->tetromino.rotate_dir != prev_tetromino.rotate_dir) {
                /* Due to flickering, I have no choice but to do it this way for now... */
                tetromino_t tmp_tetromino = play_manager->tetromino;
                play_manager->tetromino = prev_tetromino;
                erase_a_tetromino_r(&play_manager->tetromino);
                play_manager->tetromino = tmp_tetromino;
                draw_a_tetromino_r(&play_manager->tetromino);
            }
            /* Maybe race condition?? */
            if (res == TETROMINO_STATUS_ONTHEGROUND) {
                petrity_tetromino_r(&play_manager->board, &play_manager->tetromino);
                // clear_filled_lines(); --> maybe internally.
                // reflect_them_visually();
                if (is_at_skyline_r(&play_manager->tetromino)) {
                    play_manager->status = TETRIS_PLAY_STATUS_GAMEOVER;
                }
                render_out();
                break;
            }
            render_out();
            usleep(TARGET_FRAME_TIME * 1e6);
            // usleep(TARGET_FRAME_TIME * 4e7);
        }
    }
    int res = pthread_cancel(play_manager->sub_modules[2].pthread_id);
    if (res != 0) {
        handle_error_en("pthread_cancel() error", res);
    }
    set_realtime_timer(&play_manager->timer_drawer.timer, false);
    wclear();
    return (void*)play_manager->status;
}

void* new_mainfunc_game_main_loop(void* arg)
{
    debug();

    /* Not a delta time(concept of FPS) version */
    tetris_play_manager_t* play_manager = (tetris_play_manager_t*)arg;
    init_game_main_loop(play_manager);
    while (play_manager->status == TETRIS_PLAY_STATUS_RUNNING) {
        spawn_tetromino(&play_manager->board, &play_manager->tetromino);
        // ...
    }
    int res = pthread_cancel(play_manager->sub_modules[2].pthread_id);
    if (res != 0) {
        handle_error_en("pthread_cancel() error", res);
    }
    set_realtime_timer(&play_manager->timer_drawer.timer, false);
    wclear();
    return (void*)play_manager->status;
}