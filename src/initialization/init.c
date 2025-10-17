/* ************************************************************************************ */
/*                                                                                      */
/*  File:       init.c                                                                  */
/*  Purpose:    Functions for initializing starting values                              */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static int initializeScreen(Game *game);
static int initializeGraphics(Game *game);
static void initialDraw(void);

int initializeGame(Game *game)
{
    if (levelLoad(game) != SUCCESS)
        return FAILURE;

    if (levelValidate(game) != SUCCESS)
        return FAILURE;

    if (initializeScreen(game) != SUCCESS)
        return FAILURE;

    if (initializeGraphics(game) != SUCCESS)
        return FAILURE;

    initialDraw();

    return SUCCESS;
}

static int initializeScreen(Game *game)
{
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(TARGET_FPS);

    if (DEFAULT_SCREEN_WIDTH <= 0 || DEFAULT_SCREEN_HEIGHT <= 0)
    {
        cleanProgram(ERR_SCREEN_DEF, game);
        return FAILURE;
    }

    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, TITLE);
    if (!IsWindowReady())
    {
        cleanProgram(ERR_SCREEN_INIT, game);
        return FAILURE;
    }

    ToggleBorderlessWindowed();
    DisableCursor();

    int currentMonitor = GetCurrentMonitor();
    game->screen.width = GetMonitorWidth(currentMonitor);
    game->screen.height = GetMonitorHeight(currentMonitor);

    if (game->screen.width <= 0 || game->screen.height <= 0)
    {
        cleanProgram(ERR_SCREEN_SIZE, game);
        CloseWindow();
        return FAILURE;
    }

    return SUCCESS;
}

static int initializeGraphics(Game *game)
{
    game->screenImg = GenImageColor(game->screen.width, game->screen.height, BLACK);
    if (!game->screenImg.data)
    {
        cleanProgram(ERR_IMAGE_GEN, game);
        CloseWindow();
        return FAILURE;
    }

    game->screenTexture = LoadTextureFromImage(game->screenImg);
    if (game->screenTexture.id == 0)
    {
        cleanProgram(ERR_TEX_LOAD, game);
        CloseWindow();
        return FAILURE;
    }

    game->graphics.wall = LoadImage(TEXTURE_0);
    ImageFormat(&game->graphics.wall, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.wall.data)
    {
        cleanProgram(ERR_IMAGE_LOAD, game);
        CloseWindow();
        return FAILURE;
    }

    return SUCCESS;
}

// Workaround the glfw bug having incorrect mouse delta value on second frame
static void initialDraw(void)
{
    for (int i = 0; i < 4; i++)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
}
