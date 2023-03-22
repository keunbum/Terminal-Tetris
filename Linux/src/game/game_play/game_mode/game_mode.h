#ifndef __GAME_MODE__H
#define __GAME_MODE__H

typedef void* (*game_mode_module_t)(void*);

typedef struct {
    const char* name;
    game_mode_module_t module;
    void* arg;
} game_mode_t;

#endif /* __GAME_MODE__H */