/* ************************************************************************** */
/*                                                                            */
/*  File:       keybinds.c                                                    */
/*  Purpose:    Keybinds and user input checking                              */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/16                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void playerMovement(Game *game);
static void cameraRotation(Game *game);

void detectUserInput(Game *game)
{
    playerMovement(game);
    cameraRotation(game);
}

static void playerMovement(Game *game)
{
    double moveX = 0, moveY = 0;
    double speed = GetFrameTime() * MOVEMENT_SPEED;

    if (IsKeyDown(KEY_W))
    {
        moveX += game->player.dirX * speed;
        moveY += game->player.dirY * speed;
    }

    if (IsKeyDown(KEY_S))
    {
        moveX -= game->player.dirX * speed;
        moveY -= game->player.dirY * speed;
    }

    if (IsKeyDown(KEY_A))
    {
        moveX -= game->player.planeX * speed;
        moveY -= game->player.planeY * speed;
    }

    if (IsKeyDown(KEY_D))
    {
        moveX += game->player.planeX * speed;
        moveY += game->player.planeY * speed;
    }

    double nextX = game->player.posX + moveX;
    double nextY = game->player.posY + moveY;

    if (game->level.map[(int)game->player.posY][(int)nextX] != WALL)
        game->player.posX = nextX;
    if (game->level.map[(int)nextY][(int)game->player.posX] != WALL)
        game->player.posY = nextY;
}

static void cameraRotation(Game *game)
{
    Vector2 mouseDelta = GetMouseDelta();
    float rotAmount = mouseDelta.x * MOUSE_SENSITIVITY;

    float oldDirX = game->player.dirX;
    game->player.dirX =game->player.dirX * cosf(rotAmount) - game->player.dirY * sinf(rotAmount);
    game->player.dirY = oldDirX * sinf(rotAmount) + game->player.dirY * cosf(rotAmount);

    float oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cosf(rotAmount) - game->player.planeY * sinf(rotAmount);
    game->player.planeY = oldPlaneX * sinf(rotAmount) + game->player.planeY * cosf(rotAmount);
}
