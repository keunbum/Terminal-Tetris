#include "tetris_play_tetromino_manager.h"
#include "pthread_macro.h"
#include "tetris/scene/tetris_play_renderer.h"

static void callback_wdraw_tetromino_manager_queue(void* const out_void, int i, void* arg)
{
    static const int S_POS_X_INTERVAL = 4;

    tetromino_t* const out_tetro = (tetromino_t*)out_void;
    const tetromino_matrix_n_t n = get_tetromino_matrix_n(out_tetro->symbol_id);
    pos_t start_pos_wprint = *(pos_t*)arg;
    pos_t pos;
    pos.x = start_pos_wprint.x + (i + 1) * S_POS_X_INTERVAL - 2;
    pos.y = start_pos_wprint.y + 8 - n;
    set_tetromino_pos(out_tetro, pos);
    wdraw_a_tetromino_at_wprint_r(out_tetro, pos);
}

static void wdraw_tetromino_manager_queue(const tetromino_manager_t* man)
{
    wdraw_frame(&man->frame, 6);
    traverse_tetromino_manager_queue(&man->que, callback_wdraw_tetromino_manager_queue, (void*)&man->pos_wprint);
}

void init_tetromino_manager_malloc(tetromino_manager_t* const out_man, int que_max_size)
{
    debug();

    my_assert(out_man != NULL);

    out_man->pos_wprint.x = TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT;
    out_man->pos_wprint.y = TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT;
    out_man->tetro_main = NULL;
    out_man->tetro_hold = NULL;

    init_tetromino_generator(&out_man->tetro_gen);

    init_queue(&out_man->que, que_max_size);
    for (int i = 0; i < (int)get_max_size_queue(&out_man->que); ++i) {
        pos_t empty_pos;
        push_queue(&out_man->que, (void*)spawn_tetromino_malloc(empty_pos, 0));
    }

    init_frame(&out_man->frame,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT,
        out_man->pos_wprint,
        L"NEXT",
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);

    init_tetris_play_statistics(&out_man->stat);

    init_lock(out_man->lock);
}

void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man)
{
    debug();

    my_assert(out_man != NULL);
    my_assert(out_man->pa_que != NULL);

    cleanup_lock(out_man->lock);
    cleanup_frame(&out_man->frame);
    cleanup_queue(&out_man->que);
}

void spawn_tetromino_manager_tetro_main(tetromino_manager_t* const out_man, pos_t init_pos, velocity_t init_velocity)
{
    out_man->tetro_main = pop_queue(&out_man->que);
    set_tetromino_pos(out_man->tetro_main, init_pos);
    pos_t empty_pos;
    push_queue(&out_man->que, spawn_tetromino_malloc(empty_pos, init_velocity));
}

tetromino_try_status_t update_tetromino_manager(tetromino_manager_t* const out_man, const board_t* board, game_time_t delta_time)
{
    debug();

    if (!is_valid_tetromino(out_man->tetro_main)) {
        pos_t tetro_main_init_pos = { TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y };
        spawn_tetromino_manager_tetro_main(out_man, tetro_main_init_pos, TETRIS_PLAY_TETROMINO_INIT_VELOCITY);
        inc_tetromino_cnt(&out_man->stat, out_man->tetro_main->symbol_id);
    }
    tetromino_try_status_t res = try_move_tetromino_deltatime_r(board, out_man->tetro_main, DIR_BOT, delta_time);
    return res;
}

void wdraw_tetromino_manager(const tetromino_manager_t* man)
{
    wdraw_tetromino_manager_queue(man);
    wdraw_tetris_play_statistics(&man->stat, get_block_wprint_set(&man->tetro_gen));
}