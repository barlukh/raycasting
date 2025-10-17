/* ************************************************************************************ */
/*                                                                                      */
/*  File:       keybinds.c                                                              */
/*  Purpose:    Keybinds and user input checking                                        */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

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
    static float smoothedDeltaX = 0.0f;
    Vector2 mouseDelta = GetMouseDelta();
    
    smoothedDeltaX += (mouseDelta.x - smoothedDeltaX) * ROTATION_SMOOTHING;
    float rotAmount = GetFrameTime() * smoothedDeltaX * MOUSE_SENSITIVITY;

    float cosA = cosf(rotAmount);
    float sinA = sinf(rotAmount);

    float oldDirX = game->player.dirX;
    game->player.dirX = oldDirX * cosA - game->player.dirY * sinA;
    game->player.dirY = oldDirX * sinA + game->player.dirY * cosA;

    float oldPlaneX = game->player.planeX;
    game->player.planeX = oldPlaneX * cosA - game->player.planeY * sinA;
    game->player.planeY = oldPlaneX * sinA + game->player.planeY * cosA;
}
