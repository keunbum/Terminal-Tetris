#ifndef __GAME_MANAGER__H
#define __GAME_MANAGER__H

#include "draw_manager.h"
#include "hud.h"

#define EXIT_GAME_OVER (2)

void menu(void);
void load_game(void);
int start_game(void);

typedef void (*module_t)(void);

#endif /* __GAME_MANAGER__H */