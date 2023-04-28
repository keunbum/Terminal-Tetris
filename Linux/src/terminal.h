#ifndef __TERMINAL__H
#define __TERMINAL__H

#include <wchar.h>
#include <termios.h>

#include "color.h"

typedef struct {
    int text_color;
    int background_color;
    struct termios old_termios;
    struct termios new_termios;
} terminal_t;

static inline void set_terminal_text_color(terminal_t* const out_term, int text_color)
{
    out_term->text_color = text_color;
    // printf("\e[0;%dm, ", out_term->text_color);
    wprintf(L"\e[0;%dm, ", out_term->text_color);
}

static inline void set_terminal_background_color(terminal_t* const out_term, int background_color)
{
    out_term->background_color = background_color;
    // printf("\e[%dm", out_term->background_color);
    wprintf(L"\e[%dm", out_term->background_color);
}

void init_terminal(terminal_t* const out_term);
void cleanup_terminal(terminal_t* const out_term);

#endif /* __TERMINAL__H */