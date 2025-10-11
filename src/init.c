/* ************************************************************************** */
/*                                                                            */
/*  File:       init.c                                                        */
/*  Purpose:    Functions for initializing starting values                    */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/11                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int initializeScreen(Game *game);

int initializeGame(Game *game)
{
    if (initializeScreen(game) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

static int initializeScreen(Game *game)
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, TITLE);
    ToggleBorderlessWindowed();
    HideCursor();

    int currentMonitor = GetCurrentMonitor();
    game->screen.width = GetMonitorWidth(currentMonitor);
    game->screen.height = GetMonitorHeight(currentMonitor);

    if (!IsWindowReady() || game->screen.width <= 0 || game->screen.height <= 0)
    {
        fputs(ERR_INIT_SCREEN, stderr);
        return FAILURE;
    }

    return SUCCESS;
}
