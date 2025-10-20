/* ************************************************************************************ */
/*                                                                                      */
/*  File:       render.c                                                                */
/*  Purpose:    Rendering functions for raycasting and drawing                          */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/20                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static void castRayforStripe(int y, Game *game);
static void castRayforColumn(int x, Game *game);
static Color getColor(Image *img, int x, int y);
static void setColor(Image *img, int x, int y, Color color);

void renderFrame(Game *game)
{
    #pragma omp parallel for schedule(static, 4)
    for (int y = game->screen.height / 2; y < game->screen.height; y++)
        castRayforStripe(y, game);

    #pragma omp parallel for schedule(dynamic, 4)
    for (int x = 0; x < game->screen.width; x++)
        castRayforColumn(x, game);
}

static void castRayforStripe(int y, Game *game)
{
    float rayDirX0 = game->player.dirX - game->player.planeX;
    float rayDirY0 = game->player.dirY - game->player.planeY;
    float rayDirX1 = game->player.dirX + game->player.planeX;
    float rayDirY1 = game->player.dirY + game->player.planeY;

    int p = y - (game->screen.height >> 1);

    float posZ = 0.5 * game->screen.height;
    float rowDistance = posZ / p;

    float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->screen.width;
    float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->screen.width;

    float floorX = game->player.posX + rowDistance * rayDirX0;
    float floorY = game->player.posY + rowDistance * rayDirY0;

    Image tileTex = game->graphics.floor;

    for (int x = 0; x < game->screen.width; x++)
    {
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        int texX = ((int)(tileTex.width * (floorX - cellX))) % tileTex.width;
        int texY = ((int)(tileTex.height * (floorY - cellY))) % tileTex.height;

        floorX += floorStepX;
        floorY += floorStepY;

        Color ceilingColor = getColor(&game->graphics.ceiling, texX, texY);
        Color floorColor = getColor(&game->graphics.floor, texX, texY);
        
        setColor(&game->screenImg, x, game->screen.height - y - 1, ceilingColor);
        setColor(&game->screenImg, x, y, floorColor);
    }
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

    Image tileTex = game->graphics.wall;

    int texX = (int)(wallX * (double)(tileTex.width));
    if (side == 0 && rayDirX > 0)
        texX = tileTex.width - texX - 1;
    if (side == 1 && rayDirY < 0)
        texX = tileTex.width - texX - 1;

    double step = 1.0 * tileTex.height / lineHeight;
    double texPos = (drawStart - game->screen.height / 2 + lineHeight / 2) * step;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = ((int)texPos) % tileTex.height;
        texPos += step;

        Color pixelColor = getColor(&game->graphics.wall, texX, texY);

        setColor(&game->screenImg, x, y, pixelColor);
    }
}

static Color getColor(Image *img, int x, int y)
{
    unsigned char *pixels = (unsigned char *)img->data;
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;
    Color color;
    color.r = pixels[offset + 0];
    color.g = pixels[offset + 1];
    color.b = pixels[offset + 2];
    color.a = pixels[offset + 3];
    return color;
}

static void setColor(Image *img, int x, int y, Color color)
{
    unsigned char *pixels = (unsigned char *)img->data;
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;
    pixels[offset + 0] = color.r;
    pixels[offset + 1] = color.g;
    pixels[offset + 2] = color.b;
    pixels[offset + 3] = color.a;
}
