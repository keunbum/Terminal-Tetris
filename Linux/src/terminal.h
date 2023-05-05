#ifndef __TERMINAL__H
#define __TERMINAL__H

#include <wchar.h>
#include <termios.h>

typedef struct {
    struct termios old_termios;
    struct termios new_termios;
} terminal_t;

void init_terminal(terminal_t* const out_term);
void cleanup_terminal(terminal_t* const out_term);

#endif /* __TERMINAL__H */