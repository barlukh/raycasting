/* ************************************************************************************ */
/*                                                                                      */
/*  File:       raycast.c                                                               */
/*  Purpose:    Raycasting logic                                                        */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/23                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

void castRayforStripe(int y, Game *game)
{
    float rayDirX0 = game->player.dirX - game->player.planeX;
    float rayDirY0 = game->player.dirY - game->player.planeY;
    float rayDirX1 = game->player.dirX + game->player.planeX;
    float rayDirY1 = game->player.dirY + game->player.planeY;

    int p = y - (game->screen.height / 2);

    float posZ = 0.5 * game->screen.height;
    float rowDistance = posZ / p;

    float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->screen.width;
    float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->screen.width;

    float floorX = game->player.posX + rowDistance * rayDirX0;
    float floorY = game->player.posY + rowDistance * rayDirY0;

    Image tileTex = game->graphics.floor;

    for (int x = 0; x < game->screen.width; x++)
    {
        int fixedFloorX = (int)(floorX * 256);
        int fixedFloorY = (int)(floorY * 256);

        int offsetX = fixedFloorX & 0xFF;
        int offsetY = fixedFloorY & 0xFF;

        int rawTexX = (offsetX * tileTex.width) / 256;
        int rawTexY = (offsetY * tileTex.height) / 256;

        rawTexX = (rawTexX + tileTex.width) % tileTex.width;
        rawTexY = (rawTexY + tileTex.height) % tileTex.height;

        int texX = rawTexX;
        int texY = rawTexY;

        floorX += floorStepX;
        floorY += floorStepY;

        Color cColor = getColor(&game->graphics.ceiling, texX, texY, rowDistance);
        Color fColor = getColor(&game->graphics.floor, texX, texY, rowDistance);
        
        setColor(&game->screenImg, x, game->screen.height - y - 1, cColor);
        setColor(&game->screenImg, x, y, fColor);
    }
}

void castRayforColumn(int x, Game *game)
{
    float cameraX = 2 * x / (float)game->screen.width - 1;
    float rayDirX = game->player.dirX + game->player.planeX * cameraX;
    float rayDirY = game->player.dirY + game->player.planeY * cameraX;

    int mapX = (int)(game->player.posX);
    int mapY = (int)(game->player.posY);

    float deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    int stepX;
    int stepY;
    float sideDistX;
    float sideDistY;
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

    float perpWallDist;
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

    float wallX;
    if (side == 0)
        wallX = game->player.posY + perpWallDist * rayDirY;
    else
        wallX = game->player.posX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    Image tileTex = game->graphics.wall;

    int texX = (int)(wallX * (float)(tileTex.width));
    if (side == 0 && rayDirX > 0)
        texX = tileTex.width - texX - 1;
    if (side == 1 && rayDirY < 0)
        texX = tileTex.width - texX - 1;

    float step = 1.0 * tileTex.height / lineHeight;
    float texPos = (drawStart - game->screen.height / 2 + lineHeight / 2) * step;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = ((int)texPos) % tileTex.height;
        texPos += step;

        Color wColor = getColor(&game->graphics.wall, texX, texY, perpWallDist);

        setColor(&game->screenImg, x, y, wColor);
    }
    game->graphics.ZBuffer[x] = perpWallDist;
}
