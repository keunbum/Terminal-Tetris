#ifndef __GAME_OBJECT__H
#define __GAME_OBJECT__H

typedef void* (*game_module_t)(void*);

typedef struct {
    const char* name;
    //    char* name;
    game_module_t module;
} game_object_t;

#endif /* __GAME_OBJECT__H */