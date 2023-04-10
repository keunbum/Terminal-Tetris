#include "input_reader.h"

void init_input_reader(input_reader_t* const out_reader)
{
    tcgetattr(STDIN_FILENO, &out_reader->old_termios);
    for (int i = 0; i < INPUT_READER_CHAR_NUM; ++i) {
        out_reader->events[i].func = NULL;
        out_reader->events[i].arg = NULL;
    }
}

void turn_on_input_reader_raw(input_reader_t* const out_reader)
{
    out_reader->new_termios = out_reader->old_termios;
    cfmakeraw(&out_reader->new_termios);
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->new_termios);
}

void turn_off_input_reader_raw(input_reader_t* const out_reader)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &out_reader->old_termios);
}