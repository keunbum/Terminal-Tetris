#ifndef __GAME_PLAY_UI__H
#define __GAME_PLAY_UI__H

#define GAME_PLAY_MODE_SINGLE (1)
#define GAME_PLAY_MODE_MULTI (2)

#define draw_row_cursor_newline(buf, width) wprintf(buf), wprintf(L"\e[1B\e[%dD", width)

void set_row_line(wchar_t* const, int, wchar_t, wchar_t, wchar_t);
void load_game_play_ui(int, int, int, int);

#endif /* __GAME_PLAY_UI__H */