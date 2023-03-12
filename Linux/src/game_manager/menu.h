#ifndef __MENU__H
#define __MENU__H

#define MENU_CMD_EXIT_GAME 0
#define MENU_CMD_START_GAME 1
#define MENU_CMD_ERROR -1

void draw_menu_screen(void);
int read_menu_option(void);

#endif /* __MENU__H */