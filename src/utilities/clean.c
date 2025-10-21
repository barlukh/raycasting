/* ************************************************************************************ */
/*                                                                                      */
/*  File:       clean.c                                                                 */
/*  Purpose:    Functions for cleaning up the program resources                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/21                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static void unloadResources(Game *game);

void cleanProgram(const char *errMsg, Game *game)
{
    unloadResources(game);
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

static void unloadResources(Game *game)
{
    UnloadImage(game->screenImg);
    UnloadImage(game->graphics.ceiling);
    UnloadImage(game->graphics.floor);
    UnloadImage(game->graphics.wall);
    
    for (size_t i = 0; i < SPRITE_MAGE_N; i++)
        UnloadImage(game->graphics.mage.animFrame[i]);
    
    UnloadTexture(game->screenTexture);
}
