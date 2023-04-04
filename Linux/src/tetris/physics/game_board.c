#include "game_board.h"
#include "debug.h"

void init_game_board(game_board_t* const board)
{
    debug();
    
    // board->height = height;
    // board->width = width;
    // board->height_wprint = height_wprint;
    // board->width_wprint = width_wprint;
    for (int i = 0; i < GAME_PLAY_BOARD_HEIGHT; ++i) {
        for (int j = 0; j < GAME_PLAY_BOARD_WIDTH; ++j) {
            board->grid[i][j] = GAME_PLAY_BOARD_GRID_ELEMENT_DEFAULT;
        }
    }
}