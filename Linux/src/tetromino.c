#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "cursor.h"
#include "util.h"
#include "tetromino.h"



void print_tetromino(const tetromino_t* t)
{
    const polyomino_t* p = s_tetrominos + t->polyomino_id;
    for (int i = 0; p->block2d[i]; ++i)
    {
        const block_t *s = p->block2d[i];
        assert(s != NULL);
        for (int j = 0; s[j]; ++j)
        {
            if (s[j] == '1')
            {
                print_full_block();
            } else
            {
                print_empty_block();
            }
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
}

void print_a_block(wchar_t ch)
{
    putwc(ch, stdout);
}

void print_empty_block(void)
{
    print_a_block(BLOCK_EMPTY);
}

void print_full_block(void)
{
    print_a_block(BLOCK_FULL);
}