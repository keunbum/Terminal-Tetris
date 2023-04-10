#ifndef __INPUT_READER__H
#define __INPUT_READER__H

#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "game_event.h"

#define INPUT_READER_CHAR_NUM (1 << 8)


typedef int input_char_t;

typedef enum {
    READER_MODE_KEYBOARD,
    READER_MODE_GAMEPAD,
} reader_mode_t;

typedef struct {
    input_char_t ch_prev;
    input_char_t ch_curr;
    reader_mode_t mode;
    struct termios old_termios;
    struct termios new_termios;
    game_event_t events[INPUT_READER_CHAR_NUM];
    game_event_t* events_ptr;
} input_reader_t;

static inline void read_char(input_reader_t* const out_reader)
{
    out_reader->ch_prev = out_reader->ch_curr;
    out_reader->ch_curr = (input_char_t)getchar();
}

static inline input_char_t get_char(const input_reader_t* reader)
{
    return reader->ch_curr;
}

static inline void register_input_reader_event(input_reader_t* const out_reader, input_char_t ch, game_event_func func, void* arg)
{
    register_event(out_reader->events + (int)ch, func, arg);
}

// static inline void register_input_reader_events_ptr(input_reader_t* const out_reader, game_event_t* src)
// {
//     out_reader->events_ptr = src;
// }

static inline void set_input_reader_mode(input_reader_t* const out_reader, reader_mode_t mode)
{
    out_reader->mode = mode;
}

void init_input_reader(input_reader_t* const);
void turn_on_input_reader_raw(input_reader_t* const);
void turn_off_input_reader_raw(input_reader_t* const);

#endif /* __INPUT_READER__H */