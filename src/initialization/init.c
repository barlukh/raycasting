/* ************************************************************************** */
/*                                                                            */
/*  File:       init.c                                                        */
/*  Purpose:    Functions for initializing starting values                    */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int  initializeScreen(Game *game);

int initializeGame(Game *game)
{
    if (levelLoad(game) != SUCCESS)
        return FAILURE;

    if (levelValidate(game) != SUCCESS)
        return FAILURE;

    if (initializeScreen(game) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

static int initializeScreen(Game *game)
{
    SetTraceLogLevel(LOG_NONE);

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
    HideCursor();

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
