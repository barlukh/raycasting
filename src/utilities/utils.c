/* ************************************************************************************ */
/*                                                                                      */
/*  File:       utils.c                                                                 */
/*  Purpose:    Various utility and helper functions                                    */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

char *copyString(const char *s)
{
    if (s == NULL)
        return NULL;

    size_t len = strlen(s) + 1;
    char *copy = calloc(len, sizeof(char));
    if (!copy)
        return NULL;

    for (size_t i = 0; i < len; i++)
        copy[i] = s[i];

    return copy;
}

bool isPlayerTile(char tile)
{
    if (tile == PLAYER_N || tile == PLAYER_S || tile == PLAYER_W || tile == PLAYER_E)
        return true;
    
    return false;
}

bool isValidTile(char tile)
{
    if (tile == EMPTY || tile == FLOOR || tile == WALL || isPlayerTile(tile))
        return true;

    return false;
}

bool isWalkableTile(char tile)
{
    if (tile == FLOOR || isPlayerTile(tile))
        return true;

    return false;
}
