/* ************************************************************************** */
/*                                                                            */
/*  File:       raycasting.h                                                  */
/*  Purpose:    Main header file of the program                               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

#define TITLE "ray-casting"

#define DEFAULT_SCREEN_WIDTH    800
#define DEFAULT_SCREEN_HEIGHT   600

#define SUCCESS 0
#define FAILURE 1

#define MAX_MAP_SIDE_LEN    64

#define LEVEL0  "levels/level0.rcm"
#define LEVEL1  "levels/level1.rcm"
#define LEVEL2  "levels/level2.rcm"
#define LEVEL3  "levels/level3.rcm"
#define LEVEL4  "levels/level4.rcm"
#define LEVEL5  "levels/level5.rcm"

#define CLEAN_EXIT      "Program terminated successfully\n"
#define ERR_FILE_OPEN   "Error: Failed to open file\n"
#define ERR_FILE_READ   "Error: Failed to read file\n"
#define ERR_MAP_FORMAT  "Error: Invalid map format\n"
#define ERR_MAP_PLAYER  "Error: Invalid player position\n"
#define ERR_MEM_ALLOC   "Error: Memory allocation\n"
#define ERR_LEVEL_PATH  "Error: Invalid level file path\n"
#define ERR_SCREEN_DEF  "Error: Invalid default window values\n"
#define ERR_SCREEN_INIT "Error: Window initialization\n"
#define ERR_SCREEN_SIZE "Error: Screen size values\n"

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

typedef struct Level
{
    char        **map;
    size_t      index;
}   Level;

typedef struct Player
{
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
}   Player;

typedef struct Screen
{
    int         width;
    int         height;
}   Screen;

typedef struct Game
{
    Level       level;
    Player      player;
    Screen      screen;
}   Game;

typedef enum Tiles
{
    FLOOR,
    CEILING,
    DOOR,
    WALL_0,
    WALL_1,
    WALL_2,
    WALL_3,
    SPRITE_0,
    SPRITE_1,
    SPRITE_2,
    PLAYER_N,
    PLAYER_S,
    PLAYER_W,
    PLAYER_E
}   Tiles;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void    cleanProgram(const char *errMsg, Game *game);
char    *copyString(const char *s);
int     initializeGame(Game *game);
int     levelLoad(Game *game);
int     levelValidate(Game *game);

#endif
