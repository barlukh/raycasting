/* ************************************************************************** */
/*                                                                            */
/*  File:       render.c                                                      */
/*  Purpose:    Rendering functions for raycasting and drawing                */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/16                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void castRayforColumn(int x, int *drawStart, int *drawEnd, Game *game);
static void drawVerticalLine(int x, int drawStart, int drawEnd, Game *game);

void renderFrame(Game *game)
{
    for (int x = 0; x < game->screen.width; x++)
    {
        int drawStart, drawEnd;
        castRayforColumn(x, &drawStart, &drawEnd, game);
        drawVerticalLine(x, drawStart, drawEnd, game);
    }
}

static void castRayforColumn(int x, int *drawStart, int *drawEnd, Game *game)
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
    
    *drawStart = -lineHeight / 2 + game->screen.height / 2;
    if (*drawStart < 0)
        *drawStart = 0;

    *drawEnd = lineHeight / 2 + game->screen.height / 2;
    if (*drawEnd >= game->screen.height)
        *drawEnd = game->screen.height - 1;
}

static void drawVerticalLine(int x, int drawStart, int drawEnd, Game *game)
{
    int y = drawStart;
    while (y < drawEnd)
	{
		const Color color = DARKGRAY;
        unsigned char *pixels = (unsigned char *)game->img.data;
        int offset = (y * game->img.width + x) * 4;
        pixels[offset + 0] = color.r;
        pixels[offset + 1] = color.g;
        pixels[offset + 2] = color.b;
        pixels[offset + 3] = color.a;
		y++;
	}
}
