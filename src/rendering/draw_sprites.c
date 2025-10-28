/* ************************************************************************************ */
/*                                                                                      */
/*  File:       draw_sprites.c                                                          */
/*  Purpose:    Drawing of sprites on the screen in the correct order                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/28                                                              */
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

        float dx = game->player.posX - game->sprite[i].x;
        float dy = game->player.posY - game->sprite[i].y;
        game->graphics.spriteDistance[i] = dx * dx + dy * dy;
    }

    sortSprites(game);

    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        int spriteIndex = game->graphics.spriteOrder[i];
        Sprite *sprite = &game->sprite[spriteIndex];
        float spriteWorldX = sprite->x;
        float spriteWorldY = sprite->y;

        float spriteX = spriteWorldX - game->player.posX;
        float spriteY = spriteWorldY - game->player.posY;

        float term1 = game->player.planeX * game->player.dirY;
        float term2 = game->player.dirX * game->player.planeY;
        float determinant = term1 - term2;
        float invDet = 1.0 / determinant;

        float termX1 = game->player.dirY * spriteX;
        float termX2 = game->player.dirX * spriteY;
        float transformX = invDet * (termX1 - termX2);

        float termY1 = -game->player.planeY * spriteX;
        float termY2 = game->player.planeX * spriteY;
        float transformY = invDet * (termY1 + termY2);

        int screenCenterX = game->screen.width / 2;
        float perspectiveRatio = transformX / transformY;
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

        #pragma omp parallel for schedule(static, 4)
        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int spriteLeft = spriteScreenX - (spriteWidth >> 1);
            int relativeStripe = stripe - spriteLeft;

            int scaledTexX = (relativeStripe << 8) * sprite->width / spriteWidth;
            int texX = scaledTexX >> 8;

            if (transformY > 0 && stripe > 0 && stripe < game->screen.width
                && transformY < game->graphics.ZBuffer[stripe])
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y << 8) - (game->screen.height << 7) + (spriteHeight << 7);
                    int texY = ((d * sprite->height) / spriteHeight) >> 8;

                    Image *currentFrame = &sprite->animation[sprite->currentFrame];
                    Color sColor = getColor(currentFrame, texX, texY, transformY);
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
                float tempDist = game->graphics.spriteDistance[i];
                game->graphics.spriteDistance[i] = game->graphics.spriteDistance[j];
                game->graphics.spriteDistance[j] = tempDist;

                int tempOrder = game->graphics.spriteOrder[i];
                game->graphics.spriteOrder[i] = game->graphics.spriteOrder[j];
                game->graphics.spriteOrder[j] = tempOrder;
            }
        }
    }
}
