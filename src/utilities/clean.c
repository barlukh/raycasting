/* ************************************************************************** */
/*                                                                            */
/*  File:       clean.c                                                       */
/*  Purpose:    Functions for cleaning up the program resources               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/15                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void cleanProgram(const char *errMsg, Game *game)
{
    freeMap(game->level.map);
    fputs(errMsg, stderr);
}

void freeMap(char **map)
{
    size_t i = 0;

    if (!map)
        return;

    while (map[i])
    {
        free(map[i]);
        map[i] = NULL;
        i++;
    }

    free(map);
    map = NULL;
}
