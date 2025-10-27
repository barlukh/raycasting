/* ************************************************************************************ */
/*                                                                                      */
/*  File:       sprite_position.c                                                       */
/*  Purpose:    Updating the position non-stationary of sprites                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

void updateSpritePositions(Game *game)
{
    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        if (!game->graphics.sprites[i].isStationary)
            printf("pos.x = %f  pos.y = %f\n", game->graphics.sprites[i].x, game->graphics.sprites[i].y);
    }
}
