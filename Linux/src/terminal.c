#include <stdio.h>
#include <unistd.h>

#include "debug.h"
#include "error_handling.h"
#include "terminal.h"

static void turn_on_terminal_raw(terminal_t* const out_term)
{
    out_term->new_termios = out_term->old_termios;
    cfmakeraw(&out_term->new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &out_term->new_termios);
}

static void turn_off_terminal_raw(terminal_t* const out_term)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &out_term->old_termios);
}

void init_terminal(terminal_t* const out_term)
{
    tcgetattr(STDIN_FILENO, &out_term->old_termios);
    turn_on_terminal_raw(out_term);
    if (freopen("/dev/null", "r", stdin) == NULL) {
        handle_error("\"/dev/null\", \"r\", stdin) failed.");
    }
}

void cleanup_terminal(terminal_t* const out_term)
{
    turn_off_terminal_raw(out_term);
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        handle_error("\"/dev/tty\", \"r\", stdin) failed.");
    }
}
