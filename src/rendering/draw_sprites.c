/* ************************************************************************************ */
/*                                                                                      */
/*  File:       draw_sprites.c                                                          */
/*  Purpose:    Draws sprites on screen in the correct order                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/22                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static void	sortSprites(Game *game);

void drawSprites(Game *game)
{
    #pragma omp parallel for schedule(dynamic, 1)
    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        game->graphics.spriteOrder[i] = i;

        double dx = game->player.posX - game->graphics.sprites[i].x;
        double dy = game->player.posY - game->graphics.sprites[i].y;
        game->graphics.spriteDistance[i] = dx * dx + dy * dy;
    }

    sortSprites(game);

    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        int spriteIndex = game->graphics.spriteOrder[i];
        Sprite *sprite = &game->graphics.sprites[spriteIndex];
        double spriteWorldX = sprite->x;
        double spriteWorldY = sprite->y;

        double spriteX = spriteWorldX - game->player.posX;
        double spriteY = spriteWorldY - game->player.posY;

        double term1 = game->player.planeX * game->player.dirY;
        double term2 = game->player.dirX * game->player.planeY;
        double determinant = term1 - term2;
        double invDet = 1.0 / determinant;

        double termX1 = game->player.dirY * spriteX;
        double termX2 = game->player.dirX * spriteY;
        double transformX = invDet * (termX1 - termX2);

        double termY1 = -game->player.planeY * spriteX;
        double termY2 = game->player.planeX * spriteY;
        double transformY = invDet * (termY1 + termY2);

        int screenCenterX = game->screen.width / 2;
        double perspectiveRatio = transformX / transformY;
        int spriteScreenX = (int)(screenCenterX * (1 + perspectiveRatio));

        int spriteHeight = abs((int)(game->screen.height / transformY));
        int drawStartY = -spriteHeight / 2 + game->screen.height / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + game->screen.height / 2;
        if (drawEndY >= game->screen.height)
            drawEndY = game->screen.height - 1;

        int spriteWidth  = abs((int)(game->screen.height  / transformY));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= game->screen.width)
            drawEndX = game->screen.width - 1;

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int spriteLeft = spriteScreenX - spriteWidth / 2;
            int relativeStripe = stripe - spriteLeft;

            int scaledTexX = 256 * relativeStripe * sprite->width / spriteWidth;
            int texX = scaledTexX / 256;

            if (transformY > 0 && stripe > 0 && stripe < game->screen.width
                && transformY < game->graphics.ZBuffer[stripe])
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y) * 256 - game->screen.height * 128 + spriteHeight * 128;
                    int texY = ((d * sprite->height) / spriteHeight) / 256;

                    Color sColor = getColor(&sprite->anim[sprite->frame], texX, texY, transformY);
                    if (sColor.a > 0)
                        setColor(&game->screenImg, stripe, y, sColor);
                }
            }
        }
    }
}

static void	sortSprites(Game *game)
{
    for (size_t i = 0; i < game->level.spriteCount - 1; i++)
    {
        for (size_t j = i + 1; j < game->level.spriteCount; j++)
        {        
            if (game->graphics.spriteDistance[i] < game->graphics.spriteDistance[j])
            {
                double tempDist = game->graphics.spriteDistance[i];
                game->graphics.spriteDistance[i] = game->graphics.spriteDistance[j];
                game->graphics.spriteDistance[j] = tempDist;

                int tempOrder = game->graphics.spriteOrder[i];
                game->graphics.spriteOrder[i] = game->graphics.spriteOrder[j];
                game->graphics.spriteOrder[j] = tempOrder;
            }
        }
    }
}
