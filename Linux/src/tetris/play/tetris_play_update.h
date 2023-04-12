#ifndef __SIMULATE__H
#define __SIMULATE__H

#include <pthread.h>
#include <stdbool.h>

#include "tetris/tetris_play_manager.h"
#include "util.h"

void update_gameworld(tetris_play_manager_t* const out_play_manager);

#endif /* __SIMULATE__H */