#ifndef __MENU__H
#define __MENU__H

#define TITLE_MENU_CMD_EXIT_GAME (0)
#define TITLE_MENU_CMD_START_GAME (1)
#define TITLE_MENU_CMD_ERROR (-1)

void draw_title_menu_screen(void);
int read_title_menu_option(void);

#endif /* __MENU__H */