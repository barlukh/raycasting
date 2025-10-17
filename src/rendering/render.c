/* ************************************************************************** */
/*                                                                            */
/*  File:       render.c                                                      */
/*  Purpose:    Rendering functions for raycasting and drawing                */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/17                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void clearImage(Game *game);
static void castRayforColumn(int x, Game *game);

void renderFrame(Game *game)
{
    clearImage(game);

    for (int x = 0; x < game->screen.width; x++)
    {
        castRayforColumn(x, game);
    }
}

static void clearImage(Game *game)
{
    memset(game->screenImg.data, 0xF5F5F5FF, game->screen.width * game->screen.height * sizeof(int));
}

static void castRayforColumn(int x, Game *game)
{
    double cameraX = 2 * x / (double)game->screen.width - 1;
    double rayDirX = game->player.dirX + game->player.planeX * cameraX;
    double rayDirY = game->player.dirY + game->player.planeY * cameraX;

    int mapX = (int)(game->player.posX);
    int mapY = (int)(game->player.posY);

    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    int stepX;
    int stepY;
    double sideDistX;
    double sideDistY;
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (game->player.posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (game->player.posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
    }

    int hit = 0;
    int side;
    while (hit == 0)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (game->level.map[mapY][mapX] == WALL)
            hit = 1;
    }

    double perpWallDist;
    if (side == 0)
        perpWallDist = (sideDistX - deltaDistX);
    else
        perpWallDist = (sideDistY - deltaDistY);

    int lineHeight = (int)(game->screen.height / perpWallDist);

    int drawStart = -lineHeight / 2 + game->screen.height / 2;
    if (drawStart < 0)
        drawStart = 0;

    int drawEnd = lineHeight / 2 + game->screen.height / 2;
    if (drawEnd >= game->screen.height)
        drawEnd = game->screen.height - 1;

    double wallX;
    if (side == 0)
        wallX = game->player.posY + perpWallDist * rayDirY;
    else
        wallX = game->player.posX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    int texX = (int)(wallX * (double)(game->graphics.wall.width));
    if (side == 0 && rayDirX > 0)
        texX = game->graphics.wall.width - texX - 1;
    if (side == 1 && rayDirY < 0)
        texX = game->graphics.wall.width - texX - 1;

    double step = 1.0 * game->graphics.wall.height / lineHeight;
    double texPos = (drawStart - game->screen.height / 2 + lineHeight / 2) * step;

    unsigned char *srcPixels = (unsigned char *)game->graphics.wall.data;
    unsigned char *dstPixels = (unsigned char *)game->screenImg.data;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos & (game->graphics.wall.height - 1);
        texPos += step;

        int srcOffset = (texY * game->graphics.wall.width + texX) * BYTES_PER_PIXEL;
        int dstOffset = (y * game->screenImg.width + x) * BYTES_PER_PIXEL;

        dstPixels[dstOffset + 0] = srcPixels[srcOffset + 0];
        dstPixels[dstOffset + 1] = srcPixels[srcOffset + 1];
        dstPixels[dstOffset + 2] = srcPixels[srcOffset + 2];
        dstPixels[dstOffset + 3] = srcPixels[srcOffset + 3];
    }

}
