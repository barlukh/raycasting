/* ************************************************************************************ */
/*                                                                                      */
/*  File:       sprite_position.c                                                       */
/*  Purpose:    Updating the position of non-stationary sprites                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/28                                                              */
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

        float oldX = game->sprite[i].x;
        float oldY = game->sprite[i].y;
        int oldTileX = (int)oldX;
        int oldTileY = (int)oldY;

        float nextX = oldX + dx * speed;
        float nextY = oldY + dy * speed;
        int nextTileX = (int)nextX;
        int nextTileY = (int)nextY;

        if (isWalkableSpriteTile(game->level.map[nextTileY][nextTileX])
            && !isTileOccupied(game, nextTileX, nextTileY, i))
        {
            game->sprite[i].x = nextX;
            game->sprite[i].y = nextY;

            int newTileX = (int)game->sprite[i].x;
            int newTileY = (int)game->sprite[i].y;

            if (oldTileX != newTileX || oldTileY != newTileY)
            {
                game->level.map[oldTileY][oldTileX] = FLOOR;
                game->level.map[newTileY][newTileX] = game->sprite[i].type;
            }
        }
    }
}
