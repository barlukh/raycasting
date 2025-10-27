/* ************************************************************************************ */
/*                                                                                      */
/*  File:       sprite_position.c                                                       */
/*  Purpose:    Updating the position non-stationary of sprite                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

void updateSpritePositions(Game *game)
{
    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        if (game->sprite[i].isStationary)
            continue;

        float speed = GetFrameTime() * SPRITE_SPEED;

        float dx = game->player.posX - game->sprite[i].x;
        float dy = game->player.posY - game->sprite[i].y;
    
        float length = sqrtf(dx * dx + dy * dy);
        if (length != 0)
        {
            dx /= length;
            dy /= length;
        }
    
        float nextX = game->sprite[i].x + dx * speed;
        float nextY = game->sprite[i].y + dy * speed;

        if (isWalkableSpriteTile(game->level.map[(int)game->sprite[i].y][(int)nextX]))
            game->sprite[i].x = nextX;
        if (isWalkableSpriteTile(game->level.map[(int)nextY][(int)game->sprite[i].x]))
            game->sprite[i].y = nextY;
    }
}
