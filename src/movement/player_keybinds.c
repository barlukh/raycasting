/* ************************************************************************************ */
/*                                                                                      */
/*  File:       player_keybinds.c                                                       */
/*  Purpose:    Keybinds and user input checking                                        */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/28                                                              */
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
    float moveX = 0, moveY = 0;
    float speed = GetFrameTime() * MOVEMENT_SPEED;

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

    float oldX = game->player.posX;
    float oldY = game->player.posY;
    float nextX = oldX + moveX;
    float nextY = oldY + moveY;
    int oldTileX = (int)oldX;
    int oldTileY = (int)oldY;
    int nextTileX = (int)nextX;
    int nextTileY = (int)nextY;

    if (isWalkablePlayerTile(game->level.map[oldTileY][nextTileX]))
        game->player.posX = nextX;
    if (isWalkablePlayerTile(game->level.map[nextTileY][oldTileX]))
        game->player.posY = nextY;
    
    int newTileX = (int)game->player.posX;
    int newTileY = (int)game->player.posY;

    if (oldTileX != newTileX || oldTileY != newTileY)
    {
        game->level.map[oldTileY][oldTileX] = FLOOR;
        game->level.map[newTileY][newTileX] = PLAYER;
    }
}

static void cameraRotation(Game *game)
{
    static float smoothedDeltaX = 0.0f;
    Vector2 mouseDelta = GetMouseDelta();
    
    smoothedDeltaX += (mouseDelta.x - smoothedDeltaX) * ROTATION_SMOOTHING;
    float rotAmount = smoothedDeltaX * MOUSE_SENSITIVITY;

    float cosA = cosf(rotAmount);
    float sinA = sinf(rotAmount);

    float oldDirX = game->player.dirX;
    game->player.dirX = oldDirX * cosA - game->player.dirY * sinA;
    game->player.dirY = oldDirX * sinA + game->player.dirY * cosA;

    float oldPlaneX = game->player.planeX;
    game->player.planeX = oldPlaneX * cosA - game->player.planeY * sinA;
    game->player.planeY = oldPlaneX * sinA + game->player.planeY * cosA;
}
