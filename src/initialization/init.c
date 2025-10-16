/* ************************************************************************** */
/*                                                                            */
/*  File:       init.c                                                        */
/*  Purpose:    Functions for initializing starting values                    */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/16                                                    */
/*                                                                            */
/* ************************************************************************** */

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
    SetTargetFPS(60);

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
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

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
    game->img = GenImageColor(game->screen.width, game->screen.height, WHITE);
    if (!game->img.data)
    {
        cleanProgram(ERR_IMAGE_GEN, game);
        CloseWindow();
        return FAILURE;
    }

    game->texture = LoadTextureFromImage(game->img);
    if (game->texture.id == 0)
    {
        cleanProgram(ERR_TEX_LOAD, game);
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
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
}
