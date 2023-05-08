#ifndef __TETRIS_PLAY_UPDATE_GAMEPLAY__H
#define __TETRIS_PLAY_UPDATE_GAMEPLAY__H

#include "tetris_play_manager.h"

void process_tetromino_status(tetromino_in_play_status_t status, tetris_play_manager_t* const out_play_manager);
void update_gameplay(tetris_play_manager_t* const out_play_manager);

#endif /* __TETRIS_PLAY_UPDATE_GAMEPLAY__H */