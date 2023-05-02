#ifndef __TITLE_MENU__H
#define __TITLE_MENU__H

typedef enum {
    TITLE_MENU_CMD_INVAL = -1,
    TITLE_MENU_CMD_EXIT_GAME,
    TITLE_MENU_CMD_RUN_GAME_SELECTION_MENU = 64
} title_menu_cmd_t;

void run_title_menu(void);

#endif /* __TITLE_MENU__H */