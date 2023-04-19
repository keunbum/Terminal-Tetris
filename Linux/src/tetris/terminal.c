#include <unistd.h>

#include "debug.h"
#include "error_handling.h"
#include "terminal.h"

static void turn_on_terminal_raw(terminal_t* const out_term)
{
    debug();

    out_term->new_termios = out_term->old_termios;
    cfmakeraw(&out_term->new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &out_term->new_termios);
}

static void turn_off_terminal_raw(terminal_t* const out_term)
{
    debug();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &out_term->old_termios);
}

void init_terminal(terminal_t* const out_term)
{
    debug();

    tcgetattr(STDIN_FILENO, &out_term->old_termios);
    turn_on_terminal_raw(out_term);
}

void cleanup_terminal(terminal_t* const out_term)
{
    debug();

    turn_off_terminal_raw(out_term);
}