#ifndef __TETRIS_PLAY_FPS__H
#define __TETRIS_PLAY_FPS__H

#define TETRIS_PLAY_FPS (60)
#define TETRIS_PLAY_FRAME_TIME (1.0 / TETRIS_PLAY_FPS)
#define TETRIS_PLAY_GAME_DELTA_TIME_FACTOR (1)

/* Accuracy of double type is not required.
   Performance first. */
typedef float game_time_t;

#endif /* __TETRIS_PLAY_FPS__H */