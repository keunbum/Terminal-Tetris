#include "tetris_play_tetromino_manager.h"
#include "tetris/scene/tetris_play_renderer.h"

static void wdraw_tetromino_queue_frame(const tetromino_manager_t* man)
{
    wprintf_at_r((int)man->que_pos_wprint.x - 1, (int)man->que_pos_wprint.y + 6, L"NEXT");
    wdraw_boundary_at_with(UNIT_MATRIX_HOR_LINE_THIN,
        UNIT_MATRIX_VER_LINE_THIN,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_HEIGHT_WPRINT,
        TETRIS_PLAY_TETROMINO_MANAGER_QUEUE_FRAME_WIDTH_WPRINT,
        (int)man->que_pos_wprint.x, (int)man->que_pos_wprint.y,
        UNIT_MATRIX_CORNER_TOP_LEFT_THIN,
        UNIT_MATRIX_CORNER_TOP_RIGHT_THIN,
        UNIT_MATRIX_CORNER_BOT_LEFT_THIN,
        UNIT_MATRIX_CORNER_BOT_RIGHT_THIN);
}

void init_tetromino_manager_malloc(tetromino_manager_t* const out_man, int max_size)
{
    debug();

    my_assert(out_man != NULL);

    out_man->max_size = max_size;
    out_man->beg = 0;
    out_man->end = 0;
    out_man->cnt = 0;
    out_man->que = (tetromino_t*)malloc(sizeof(tetromino_t) * out_man->max_size);

    init_tetromino_generator(&out_man->tetro_gen);

    for (int i = 0; i < out_man->max_size; ++i) {
        tetromino_t t;
        /* hmmm */
        static const int S_POS_X_INTERVAL = 4;
        static const int S_POS_Y_CORRECTION[TOTAL_TETROMINO_NUM_OF_KINDS] = { -2, 0, -1, -1, -1, -1, -1 };
        pos_t pos;
        spawn_tetromino(&out_man->tetro_gen, &t, pos, 0);
        pos.x = out_man->que_pos_wprint.x + (i + 1) * S_POS_X_INTERVAL - 2;
        pos.y = out_man->que_pos_wprint.y + 6 + S_POS_Y_CORRECTION[t.symbol_id];
        set_tetromino_pos(&t, pos);
        push_tetromino(out_man, t);
    }
}

void cleanup_tetromino_manager_free(tetromino_manager_t* const out_man)
{
    debug();

    my_assert(out_man != NULL);
    my_assert(out_man->que != NULL);

    free(out_man->que);
}

void wdraw_tetromino_manager_queue(const tetromino_manager_t* man)
{
    wdraw_tetromino_queue_frame(man);
    int ptr = man->beg;
    for (int i = 0; i < man->cnt; ++i) {
        tetromino_t* t = man->que + ptr;
        wdraw_a_tetromino_at_wprint_r(t, t->pos);
        if (++ptr == man->max_size) {
            ptr = 0;
        }
    }
}
