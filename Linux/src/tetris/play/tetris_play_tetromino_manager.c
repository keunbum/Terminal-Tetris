#include "tetris_play_tetromino_manager.h"
#include "debug.h"
#include "pthread_macro.h"
#include "tetris/scene/tetris_play_renderer.h"
#include "tetris_play_update_tetromino_in_play_status.h"

static void set_next_queue_default(tetromino_t* const out_tetro, int i, pos_int_t start_pos_wprint)
{
    static const int S_POS_X_INTERVAL = 4;

    pos_int_t pos_wprint;
    pos_wprint.x = start_pos_wprint.x + (i + 1) * S_POS_X_INTERVAL - 2;
    pos_wprint.y = start_pos_wprint.y + 5;
    out_tetro->pos_wprint = get_pos(pos_wprint);
}

static void wdraw_next_queue_each(void* const out_void, int i, void* arg)
{
    tetromino_t* tetro = (tetromino_t*)out_void;
    set_next_queue_default(tetro, i, *(pos_int_t*)arg);
    wdraw_a_tetromino(tetro);
}

static void wdraw_tetromino_manager_queue(const tetromino_manager_t* man)
{
    wdraw_frame(&man->next_queue_frame, 6);
    traverse_queue(&man->next_queue, wdraw_next_queue_each, (void*)&man->next_queue_pos_wprint);
}

static void wdraw_tetromino_manager_hold_frame(const tetromino_manager_t* man)
{
    wdraw_frame(&man->hold_frame, 4);
}

static void callback_set_next_queue_default(void* const out_void, int i, void* arg)
{
    set_next_queue_default((tetromino_t*)out_void, i, *(pos_int_t*)arg);
}

static void spawn_tetromino(tetromino_manager_t* const out_man, tetromino_t** const target_tetro, velocity_t init_velocity)
{
    *target_tetro = pop_queue(&out_man->next_queue);
    (*target_tetro)->pos = create_pos(
        TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_X,
        TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_Y);
    (*target_tetro)->velocity = init_velocity;
    (*target_tetro)->clean_wprint = MATRIX_INNTER_BLOCK_WPRINT;
    push_queue(&out_man->next_queue, create_tetromino_random_malloc(&out_man->tetro_gen, create_pos_default(), 0, BLOCK_WPRINT_EMPTY));
    traverse_queue(&out_man->next_queue, callback_set_next_queue_default, (void*)&out_man->next_queue_pos_wprint);
}

static void swap_tetromino_in_play_hold(tetromino_manager_t* const out_man)
{
    tetromino_t* tmp_ptr = out_man->tetromino_hold;
    out_man->tetromino_hold = out_man->tetromino_in_play;
    out_man->tetromino_in_play = tmp_ptr;
}

static int try_spawn_tetromino(tetromino_manager_t* const out_man, tetromino_t** out_tetro)
{
    if (is_valid_tetromino(*out_tetro)) {
        return 0;
    }
    spawn_tetromino(out_man, out_tetro, out_man->tetromino_in_play_velocity);
    inc_tetromino_cnt(&out_man->stat, (*out_tetro)->shape_id);
    return is_ok_tetromino_in_play_next_status(&out_man->matrix, *out_tetro, get_posint((*out_tetro)->pos), (*out_tetro)->dir) 
        ? 1 : -1;
}

void init_tetromino_manager(tetromino_manager_t* const out_man, int que_max_size)
{
    out_man->next_queue_pos_wprint.x = TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT;
    out_man->next_queue_pos_wprint.y = TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT;
    out_man->hold_piece_pos.x = TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_X + 1;
    out_man->hold_piece_pos.y = TETRIS_PLAY_TETROMINO_MANAGER_HOLD_FRAME_POS_Y + 2;

    out_man->is_swaped_once = false;
    out_man->tetromino_in_play_velocity_rate_of_change = (game_time_t)TETRIS_PLAY_TETROMINO_IN_PLAY_UNIT_VELOCITY;
    out_man->tetromino_in_play_velocity = TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_VELOCITY;

    out_man->tetromino_in_play = NULL;
    out_man->tetromino_hold = NULL;

    init_matrix(&out_man->matrix);
    init_tetromino_generator(&out_man->tetro_gen);
    init_tetris_play_statistics_malloc(&out_man->stat);
    init_queue_malloc(&out_man->next_queue, que_max_size);
    while (out_man->next_queue.cnt < TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FULL_SIZE) {
        push_queue(&out_man->next_queue, (void*)create_tetromino_random_malloc(&out_man->tetro_gen, create_pos(0, 0), 0, BLOCK_WPRINT_EMPTY));
    }
    init_frame(&out_man->next_queue_frame,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT,
        out_man->next_queue_pos_wprint,
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
    cleanup_frame(&out_man->next_queue_frame);
    while (!is_queue_empty(&out_man->next_queue)) {
        tetromino_t* tetro = (tetromino_t*)pop_queue(&out_man->next_queue);
        cleanup_tetromino_free(tetro);
        tetro = NULL;
    }
    cleanup_queue_free(&out_man->next_queue);
    cleanup_tetris_play_statistics_free(&out_man->stat);
    cleanup_tetromino_generator(&out_man->tetro_gen);
    cleanup_matrix(&out_man->matrix);

    cleanup_tetromino_free(out_man->tetromino_hold);
    out_man->tetromino_hold = NULL;
    cleanup_tetromino_free(out_man->tetromino_in_play);
    out_man->tetromino_in_play = NULL;
}

tetromino_in_play_status_t update_tetromino_manager(tetromino_manager_t* const out_man, game_time_t delta_time)
{
    int res = try_spawn_tetromino(out_man, &out_man->tetromino_in_play);
    my_assert(out_man->tetromino_in_play != NULL);
    if (res == -1) {
        return TETROMINO_IN_PLAY_STATUS_ONTHEGROUND;
    }
    if (res == 1) {
        init_ghost_piece(&out_man->ghost_piece);
        update_ghost_piece(&out_man->ghost_piece, out_man->tetromino_in_play);
    }
    return try_move_down_tetromino_in_play_deltatime(&out_man->matrix, out_man->tetromino_in_play, delta_time);
}

void wdraw_tetromino_manager(const tetromino_manager_t* man)
{
    wdraw_tetris_play_statistics(&man->stat);
    wdraw_tetromino_manager_queue(man);
    wdraw_tetromino_manager_hold_frame(man);
    wdraw_tetromino_in_play_speed(man);
}

tetromino_in_play_status_t try_hold_tetromino_in_play(tetromino_manager_t* const out_man)
{
    {
        if (!is_valid_tetromino(out_man->tetromino_in_play) || out_man->is_swaped_once) {
            return TETROMINO_IN_PLAY_STATUS_NULL;
        }
        int res = try_spawn_tetromino(out_man, &out_man->tetromino_hold);
        if (res == -1) {
            return TETROMINO_IN_PLAY_STATUS_NULL;
        }
        swap_tetromino_in_play_hold(out_man);
    }
    {
        static const int S_X_OFFSET[] = {-1, -1, 0, 0, 0, 0, 0};
        static const int S_Y_OFFSET[] = {0, 0, 1, 1, 1, 1, 1};
        out_man->tetromino_hold->pos = create_pos(out_man->hold_piece_pos.x + S_X_OFFSET[out_man->tetromino_hold->shape_id], out_man->hold_piece_pos.y + S_Y_OFFSET[out_man->tetromino_hold->shape_id]);
        out_man->tetromino_hold->pos_wprint = out_man->tetromino_hold->pos;
        out_man->tetromino_hold->dir = TETROMINO_INIT_DIR;
        out_man->tetromino_hold->clean_wprint = BLOCK_WPRINT_EMPTY;
        wdraw_a_tetromino(out_man->tetromino_hold);
    }
    {
        update_tetromino_pos(out_man->tetromino_in_play, 
            create_pos(TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_X, TETRIS_PLAY_TETROMINO_IN_PLAY_INIT_POS_Y));
        out_man->tetromino_in_play->clean_wprint = BLOCK_WPRINT_EMPTY;
        update_ghost_piece(&out_man->ghost_piece, out_man->tetromino_in_play);
        wdraw_a_tetromino_with_ghost_piece(out_man->tetromino_in_play, &out_man->ghost_piece, &out_man->matrix);
        out_man->tetromino_in_play->clean_wprint = MATRIX_INNTER_BLOCK_WPRINT;
    }
    {
        out_man->is_swaped_once = true;
    }
    return TETROMINO_IN_PLAY_STATUS_MOVE;
}
