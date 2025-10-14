/* ************************************************************************** */
/*                                                                            */
/*  File:       clean.c                                                       */
/*  Purpose:    Functions for cleaning up the program resources               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void freeMap(Game *game);

void cleanProgram(const char *errMsg, Game *game)
{
    freeMap(game);
    fputs(errMsg, stderr);
}

void freeMap(Game *game)
{
    size_t i = 0;

    if (!game->level.map)
        return;

    while (game->level.map[i])
    {
        free(game->level.map[i]);
        game->level.map[i] = NULL;
        i++;
    }

    free(game->level.map);
    game->level.map = NULL;
}
