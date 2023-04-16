#include "tetris_play_tetromino_manager.h"
#include "pthread_macro.h"
#include "tetris/scene/tetris_play_renderer.h"

void init_tetromino_manager_malloc(tetromino_manager_t* const out_man, int max_size)
{
    debug();

    my_assert(out_man != NULL);

    out_man->pos_wprint.x = TETRIS_PLAY_TETROMINO_MANAGER_POS_X_WPRINT;
    out_man->pos_wprint.y = TETRIS_PLAY_TETROMINO_MANAGER_POS_Y_WPRINT;

    out_man->max_size = max_size;
    out_man->beg = 0;
    out_man->end = 0;
    out_man->cnt = 0;
    out_man->que = (tetromino_t*)malloc(sizeof(tetromino_t) * out_man->max_size);

    init_tetromino_generator(&out_man->tetro_gen);
    for (int i = 0; i < out_man->max_size; ++i) {
        pos_t pos;
        tetromino_t t = new_spawn_tetromino(pos, 0);
        push_queue(out_man, t);
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

    init_lock(out_man->lock);
}

void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man)
{
    debug();

    my_assert(out_man != NULL);
    my_assert(out_man->que != NULL);

    cleanup_lock(out_man->lock);
    free(out_man->que);
    out_man->que = NULL;
}

void wdraw_tetromino_manager_queue(const tetromino_manager_t* man)
{
    wdraw_frame(&man->frame, 6);

    int ptr = man->beg;
    for (int i = 0; i < man->cnt; ++i) {
        static const int S_POS_X_INTERVAL = 4;
        tetromino_t* t = man->que + ptr;
        const tetromino_matrix_n_t n = get_tetromino_matrix_n(t->symbol_id);
        pos_t pos;
        pos.x = man->pos_wprint.x + (i + 1) * S_POS_X_INTERVAL - 2;
        pos.y = man->pos_wprint.y + 8 - n;
        set_tetromino_pos(t, pos);
        wdraw_a_tetromino_at_wprint_r(t, pos);
        if (++ptr == man->max_size) {
            ptr = 0;
        }
    }
}

void spawn_tetro_main(tetromino_manager_t* const out_man, pos_t init_pos, velocity_t init_velocity)
{
    out_man->tetro_main = pop_queue(out_man);
    set_tetromino_pos(&out_man->tetro_main, init_pos);
    pos_t empty_pos;
    push_queue(out_man, new_spawn_tetromino(empty_pos, init_velocity));
}