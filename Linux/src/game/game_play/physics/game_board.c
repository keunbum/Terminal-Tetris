#include "debug/debug.h"
#include "game_board.h"

game_board_t g_game_board = {};

void init_game_board(void)
{
    debug();
    
    for (int i = 0; i < GAME_PLAY_BOARD_HEIGHT; ++i) {
        for (int j = 0; j < GAME_PLAY_BOARD_WIDTH; ++j) {
            g_game_board.grid[i][j] = GAME_PLAY_BOARD_GRID_ELEMENT_DEFAULT;
        }
    }
}