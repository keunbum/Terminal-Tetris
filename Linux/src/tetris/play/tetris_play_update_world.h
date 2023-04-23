#ifndef __TETRIS_PLAY_WORLD_UPDATE__H
#define __TETRIS_PLAY_WORLD_UPDATE__H

#include "tetris/tetris_play_manager.h"

void process_tetromino_try_status(tetromino_status_t status, tetris_play_manager_t* const out_play_manager);
void update_gameworld(tetris_play_manager_t* const out_play_manager);

#endif /* __TETRIS_PLAY_WORLD_UPDATE__H */