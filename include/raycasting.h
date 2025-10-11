/* ************************************************************************** */
/*                                                                            */
/*  File:       raycasting.h                                                  */
/*  Purpose:    Main header file of the program                               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/11                                                    */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

#include <stdio.h>
#include "raylib.h"

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

#define TITLE "ray-casting"
#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600

#define SUCCESS 0
#define FAILURE 1

#define ERR_INIT_SCREEN "Error: Screen initialization\n"

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

typedef struct Screen
{
    int width;
    int height;
} Screen;

typedef struct Game
{
    Screen screen;
} Game;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int initializeGame(Game *game);

#endif
