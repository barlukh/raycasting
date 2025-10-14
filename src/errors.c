/* ************************************************************************** */
/*                                                                            */
/*  File:       errors.c                                                      */
/*  Purpose:    Utilities for cleaning up the program resources               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void cleanProgram(char *errMsg, Game *game)
{
    free(game->level.map);
    CloseWindow();

    fputs(errMsg, stderr);
}
