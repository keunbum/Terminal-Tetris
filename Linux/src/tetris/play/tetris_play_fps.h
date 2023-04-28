#ifndef __TETRIS_PLAY_FPS__H
#define __TETRIS_PLAY_FPS__H

#include "draw/draw_tool.h"

#define TETRIS_PLAY_FPS (120)
#define TETRIS_PLAY_FRAME_TIME (1.0 / TETRIS_PLAY_FPS)
#define TETRIS_PLAY_GAME_DELTA_TIME_FACTOR (1)

#define FRAME_DRAW_POS_X_WPRINT (2)
#define FRAME_DRAW_POS_Y_WPRINT (50)

/* Accuracy of double type is not required.
   Performance first. */
typedef float game_time_t;

static inline void wdraw_fps(int* out_frame, game_time_t* out_time)
{
   if (*out_time >= 1.0f) {
      wprintf_at_r(FRAME_DRAW_POS_X_WPRINT, FRAME_DRAW_POS_Y_WPRINT, L"  FPS: %.2f\n", *out_frame / *out_time);
      *out_time = 0.0f;
      *out_frame = 0;
   }   
}

#endif /* __TETRIS_PLAY_FPS__H */