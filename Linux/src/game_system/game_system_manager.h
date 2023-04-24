#ifndef __GAME_SYSTEM_MANAGER__H
#define __GAME_SYSTEM_MANAGER__H

typedef void* (*game_module_func_t)(void*);

typedef struct {
    const char* name;
    const game_module_func_t module;
    void* module_arg;
} game_system_module_t;

typedef enum {
    TETRIS_PLAY_MODE_SINGLE,
    TETRIS_PLAY_MODE_MULTI,
} tetris_play_mode_t;

typedef enum {
    TETRIS_PLAY_CMD_ERROR = -1,
    TETRIS_PLAY_CMD_EXIT_GAME = 0,
    TETRIS_PLAY_CMD_REGAME = 1,
} tetris_play_cmd_t;

void exit_cleanup_game_system(int status);
void run_game_system_manager(void);

#endif /* __GAME_SYSTEM_MANAGER__H */