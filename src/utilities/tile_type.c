/* ************************************************************************************ */
/*                                                                                      */
/*  File:       tile_type.c                                                             */
/*  Purpose:    Checking for various tile types                                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static bool isMapTile(char tile);

bool isPlayerTile(char tile)
{
    if (tile == PLAYER_N || tile == PLAYER_S || tile == PLAYER_W || tile == PLAYER_E)
        return true;
    
    return false;
}

bool isSpriteTile(char tile)
{
    if (tile == SPRITE_MAGE || tile == SPRITE_MYSTIC || tile == SPRITE_SMITH
        || tile == SPRITE_SKELWALK)
        return true;

    return false;
}

bool isValidTile(char tile)
{
    if (isMapTile(tile) || isSpriteTile(tile) || isPlayerTile(tile))
        return true;

    return false;
}

bool isWalkablePlayerTile(char tile)
{
    if (tile == FLOOR || isPlayerTile(tile))
        return true;

    return false;
}

bool isWalkableSpriteTile(char tile)
{
    if (tile == FLOOR || tile == SPRITE_SKELWALK)
        return true;

    return false;
}

static bool isMapTile(char tile)
{
    if (tile == EMPTY || tile == FLOOR || tile == WALL)
        return true;

    return false;
}
