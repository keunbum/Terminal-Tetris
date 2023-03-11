#ifndef __HUD__H
#define __HUD__H

#include "draw/draw_manager.h"

#define UNIT_SEC (1)

#define MAX_PLAY_TIME (3) // in seconds

void draw_time_at(int, int, int);
void run_draw_time_at();

#endif /* __HUD__H */