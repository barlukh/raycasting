/* ************************************************************************************ */
/*                                                                                      */
/*  File:       utils.c                                                                 */
/*  Purpose:    Various utility and helper functions                                    */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/23                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static bool isMapTile(char tile);

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

bool isSpriteTile(char tile)
{
    if (tile == SPRITE_MAGE || tile == SPRITE_MYSTIC || tile == SPRITE_SMITH)
        return true;

    return false;
}

bool isValidTile(char tile)
{
    if (isMapTile(tile) || isSpriteTile(tile) || isPlayerTile(tile))
        return true;

    return false;
}

bool isWalkableTile(char tile)
{
    if (tile == FLOOR || isPlayerTile(tile))
        return true;

    return false;
}

static bool isMapTile(char tile)
{
    if (tile == EMPTY || tile == FLOOR || tile == WALL)
        return true;

    return false;
}

void updateTimers(Game *game)
{
    float frameTime = GetFrameTime();
    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        Sprite *sprite = &game->graphics.sprites[i];
        sprite->timer += frameTime;
        if (sprite->timer >= sprite->frameThreshold)
        {
            sprite->currentFrame = (sprite->currentFrame + 1) % sprite->totalFrames;
            sprite->timer -= sprite->frameThreshold;
        }
    }
}
