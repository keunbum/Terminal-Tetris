#ifndef __POS__H
#define __POS__H

typedef float pos_each_t;
typedef pos_each_t pos_each_t;

#define DECLARE_POS(T) \
    typedef struct {   \
        T x;           \
        T y;           \
    } pos_##T##_t

DECLARE_POS(float);
typedef pos_float_t pos_t;

DECLARE_POS(int);

static inline pos_t create_pos(pos_each_t x, pos_each_t y)
{
    return (pos_t) { x, y };
}

static inline pos_t create_pos_default(void)
{
    return create_pos(0.0f, 0.0f);
}

static inline pos_int_t create_posint(int x, int y)
{
    return (pos_int_t) { x, y };
}

static inline pos_int_t create_posint_default(void)
{
    return create_posint(0, 0);
}

static inline pos_int_t convert_intpos_intwprint(pos_int_t pos)
{
    return create_posint(pos.x, 2 * pos.y);
}

static inline pos_int_t cast_pos_posint(pos_t pos)
{
    return create_posint((int)pos.x, (int)pos.y);
}

static inline pos_t cast_posint_pos(pos_int_t pos)
{
    return create_pos((pos_each_t)pos.x, (pos_each_t)pos.y);
}

#endif /* __POS__H */