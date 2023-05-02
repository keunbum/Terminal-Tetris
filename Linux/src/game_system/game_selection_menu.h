#ifndef __GAME_SELECTION_MENU__H
#define __GAME_SELECTION_MENU__H

#define GAME_SELECTION_MENU_CMD

typedef enum {
    GAME_SELECTION_MENU_CMD_INVAL = -1,
    GAME_SELECTION_MENU_CMD_EXIT_GAME = 2,
} game_selection_menu_cmd_t;

void run_game_selection_menu(void);

#endif /* __GAME_SELECTION_MENU__H */