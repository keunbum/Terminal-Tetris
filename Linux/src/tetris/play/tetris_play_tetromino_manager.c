#include "tetris_play_tetromino_manager.h"
#include "debug.h"
#include "pthread_macro.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_update_tetromino_status.h"

static void set_tetro_queue_default(tetromino_t* const out_tetro, int i, pos_int_t start_pos_wprint)
{
    static const int S_POS_X_INTERVAL = 4;

    pos_int_t pos_wprint;
    pos_wprint.x = start_pos_wprint.x + (i + 1) * S_POS_X_INTERVAL - 2;
    pos_wprint.y = start_pos_wprint.y + 5;
    out_tetro->pos_wprint = get_pos(pos_wprint);
}

static void callback_wdraw_tetromino_manager_queue(void* const out_void, int i, void* arg)
{
    tetromino_t* tetro = (tetromino_t*)out_void;
    set_tetro_queue_default(tetro, i, *(pos_int_t*)arg);
    wdraw_a_tetromino(tetro);
}

static void wdraw_tetromino_manager_queue(const tetromino_manager_t* man)
{
    wdraw_frame(&man->next_frame, 6);
    traverse_queue(&man->que, callback_wdraw_tetromino_manager_queue, (void*)&man->next_pos_wprint);
}

static void wdraw_tetromino_manager_hold_frame(const tetromino_manager_t* man)
{
    wdraw_frame(&man->hold_frame, 4);
}

static void callback_spawn_tetromino_manager_tetro_main(void* const out_void, int i, void* arg)
{
    set_tetro_queue_default((tetromino_t*)out_void, i, *(pos_int_t*)arg);
}

static void spawn_tetromino(tetromino_manager_t* const out_man, tetromino_t** const target_tetro, velocity_t init_velocity)
{
    *target_tetro = pop_queue(&out_man->que);
    (*target_tetro)->pos = create_pos(
        TETRIS_PLAY_TETROMINO_INIT_POS_X,
        TETRIS_PLAY_TETROMINO_INIT_POS_Y);
    (*target_tetro)->velocity = init_velocity;
    (*target_tetro)->clean_wprint = BOARD_INNTER_BLOCK_WPRINT;
    push_queue(&out_man->que, create_tetromino_random_malloc(&out_man->tetro_gen, create_pos_default(), 0, BLOCK_WPRINT_EMPTY));
    traverse_queue(&out_man->que, callback_spawn_tetromino_manager_tetro_main, (void*)&out_man->next_pos_wprint);
}

static void swap_main_hold(tetromino_manager_t* const out_man)
{
    tetromino_t* tmp_ptr = out_man->tetro_hold;
    out_man->tetro_hold = out_man->tetro_main;
    out_man->tetro_main = tmp_ptr;
}

static int try_spawn_tetromino(tetromino_manager_t* const out_man, tetromino_t** out_tetro)
{
    if (is_valid_tetromino(*out_tetro)) {
        return 0;
    }
    spawn_tetromino(out_man, out_tetro, out_man->tetromino_init_velocity);
    inc_tetromino_cnt(&out_man->stat, (*out_tetro)->symbol_id);
    return is_ok_tetromino_next_status(&out_man->board, *out_tetro, get_posint((*out_tetro)->pos), (*out_tetro)->dir) 
        ? 1 : -1;
}

void init_tetromino_manager(tetromino_manager_t* const out_man, int que_max_size)
{
    out_man->next_pos_wprint.x = TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT;
    out_man->next_pos_wprint.y = TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT;
    out_man->hold_pos.x = TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_X + 1;
    out_man->hold_pos.y = TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_Y + 2;

    out_man->is_swaped_once = false;
    out_man->unit_velocity = (game_time_t)TETRIS_PLAY_UNIT_VELOCITY;
    out_man->tetromino_init_velocity = TETRIS_PLAY_TETROMINO_INIT_VELOCITY;

    out_man->tetro_main = NULL;
    out_man->tetro_hold = NULL;

    init_board(&out_man->board);
    init_tetromino_generator(&out_man->tetro_gen);
    init_tetris_play_statistics_malloc(&out_man->stat, &out_man->tetro_gen);
    init_queue_malloc(&out_man->que, que_max_size);
    while (out_man->que.cnt < TETROMINO_MANAGER_QUEUE_FULL_SIZE) {
        push_queue(&out_man->que, (void*)create_tetromino_random_malloc(&out_man->tetro_gen, create_pos(0, 0), 0, BLOCK_WPRINT_EMPTY));
    }
    init_frame(&out_man->next_frame,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT,
        out_man->next_pos_wprint,
        L"NEXT",
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);
    init_frame(&out_man->hold_frame,
        TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_HEIGHT_WPRINT,
        TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_WIDTH_WPRINT,
        create_posint(TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_X, TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_Y),
        L"HOLD",
        UNIT_MATRIX_HOR_LINE,
        UNIT_MATRIX_VER_LINE,
        UNIT_MATRIX_CORNER_TOP_LEFT,
        UNIT_MATRIX_CORNER_TOP_RIGHT,
        UNIT_MATRIX_CORNER_BOT_LEFT,
        UNIT_MATRIX_CORNER_BOT_RIGHT);
}

void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man)
{
    cleanup_frame(&out_man->hold_frame);
    cleanup_frame(&out_man->next_frame);
    while (!is_queue_empty(&out_man->que)) {
        tetromino_t* tetro = (tetromino_t*)pop_queue(&out_man->que);
        cleanup_tetromino_free(tetro);
        tetro = NULL;
    }
    cleanup_queue_free(&out_man->que);
    cleanup_tetris_play_statistics_free(&out_man->stat);
    cleanup_tetromino_generator(&out_man->tetro_gen);
    cleanup_board(&out_man->board);

    cleanup_tetromino_free(out_man->tetro_hold);
    out_man->tetro_hold = NULL;
    cleanup_tetromino_free(out_man->tetro_main);
    out_man->tetro_main = NULL;
}

tetromino_status_t update_tetromino_manager(tetromino_manager_t* const out_man, game_time_t delta_time)
{
    int res = try_spawn_tetromino(out_man, &out_man->tetro_main);
    my_assert(out_man->tetro_main != NULL);
    if (res == -1) {
        return TETROMINO_STATUS_ONTHEGROUND;
    }
    if (res == 1) {
        init_tetromino_silhouette(&out_man->tetro_silhou);
        update_tetromino_silhouette(&out_man->tetro_silhou, out_man->tetro_main);
    }
    return try_move_down_tetromino_deltatime_r(&out_man->board, out_man->tetro_main, delta_time);
}

void wdraw_tetromino_manager(const tetromino_manager_t* man)
{
    wdraw_tetris_play_statistics(&man->stat);
    wdraw_tetromino_manager_queue(man);
    wdraw_tetromino_manager_hold_frame(man);
    wdraw_tetromino_speed(man);
}

tetromino_status_t try_swap_tetromino_hold(tetromino_manager_t* const out_man)
{
    {
        if (!is_valid_tetromino(out_man->tetro_main) || out_man->is_swaped_once) {
            return TETROMINO_STATUS_NULL;
        }
        int res = try_spawn_tetromino(out_man, &out_man->tetro_hold);
        if (res == -1) {
            return TETROMINO_STATUS_NULL;
        }
        swap_main_hold(out_man);
    }
    {
        static const int S_X_OFFSET[] = {-1, -1, 0, 0, 0, 0, 0};
        static const int S_Y_OFFSET[] = {0, 0, 1, 1, 1, 1, 1};
        out_man->tetro_hold->pos = create_pos(out_man->hold_pos.x + S_X_OFFSET[out_man->tetro_hold->symbol_id], out_man->hold_pos.y + S_Y_OFFSET[out_man->tetro_hold->symbol_id]);
        out_man->tetro_hold->pos_wprint = out_man->tetro_hold->pos;
        out_man->tetro_hold->dir = TETROMINO_INIT_DIR;
        out_man->tetro_hold->clean_wprint = BLOCK_WPRINT_EMPTY;
        wdraw_a_tetromino(out_man->tetro_hold);
    }
    {
        update_tetromino_pos(out_man->tetro_main, 
            create_pos(TETRIS_PLAY_TETROMINO_INIT_POS_X, TETRIS_PLAY_TETROMINO_INIT_POS_Y));
        out_man->tetro_main->clean_wprint = BLOCK_WPRINT_EMPTY;
        update_tetromino_silhouette(&out_man->tetro_silhou, out_man->tetro_main);
        wdraw_a_tetromino_with_silhouette(out_man->tetro_main, &out_man->tetro_silhou, &out_man->board);
        out_man->tetro_main->clean_wprint = BOARD_INNTER_BLOCK_WPRINT;
    }
    {
        out_man->is_swaped_once = true;
    }
    return TETROMINO_STATUS_MOVE;
}
