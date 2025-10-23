/* ************************************************************************************ */
/*                                                                                      */
/*  File:       render.c                                                                */
/*  Purpose:    Main rendering loop                                                     */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/23                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

void renderFrame(Game *game)
{
    updateTimers(game);

    #pragma omp parallel for schedule(static, 4)
    for (int y = game->screen.height / 2; y < game->screen.height; y++)
        castRayforStripe(y, game);

    #pragma omp parallel for schedule(dynamic, 4)
    for (int x = 0; x < game->screen.width; x++)
        castRayforColumn(x, game);

    if (game->level.spriteCount > 0)
        drawSprites(game);
}
