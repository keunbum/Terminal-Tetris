#include "game/game_play/game_play.h"

const struct timespec G_GAME_PLAY_TIMER_INTERVAL = {
    .tv_sec = 1,
    .tv_nsec = 0,
};
const struct timespec G_GAME_PLAY_TIMER_INIT_EXPIRE = {
    .tv_sec = 1,
    .tv_nsec = 0,
};
