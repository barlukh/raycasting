/* ************************************************************************** */
/*                                                                            */
/*  File:       raycasting.h                                                  */
/*  Purpose:    Main header file of the program                               */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/16                                                    */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

#include <math.h>
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
#define PLANE_FOV           0.66
#define MOVEMENT_SPEED      4
#define MOUSE_SENSITIVITY   0.002f

#define LEVEL0  "levels/level0.rcm"
#define LEVEL1  "levels/level1.rcm"
#define LEVEL2  "levels/level2.rcm"
#define LEVEL3  "levels/level3.rcm"
#define LEVEL4  "levels/level4.rcm"
#define LEVEL5  "levels/level5.rcm"

#define EMPTY       ' '
#define FLOOR       '0'
#define WALL        '1'
#define PLAYER_N    'N'
#define PLAYER_S    'S'
#define PLAYER_E    'E'
#define PLAYER_W    'W'
#define VISITED     'v'

#define CLEAN_EXIT      "Program terminated successfully\n"
#define ERR_FILE_OPEN   "Error: Failed to open file\n"
#define ERR_FILE_READ   "Error: Failed to read file\n"
#define ERR_IMAGE_GEN   "Error: Failed to generate image\n"
#define ERR_MAP_OPEN    "Error: Map not enclosed\n"
#define ERR_MAP_FORMAT  "Error: Invalid map format\n"
#define ERR_MAP_PLAYER  "Error: Invalid player position\n"
#define ERR_MAP_TILE    "Error: Invalid tile character\n"
#define ERR_MEM_ALLOC   "Error: Memory allocation\n"
#define ERR_LEVEL_PATH  "Error: Invalid level file path\n"
#define ERR_SCREEN_DEF  "Error: Invalid default window values\n"
#define ERR_SCREEN_INIT "Error: Window initialization\n"
#define ERR_SCREEN_SIZE "Error: Screen size values\n"
#define ERR_TEX_LOAD    "Error: Failed to load texture\n"

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
    Image       img;
    Texture2D   texture;
    Level       level;
    Player      player;
    Screen      screen;
}   Game;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

void    cleanProgram(const char *errMsg, Game *game);
char    *copyString(const char *s);
void    detectUserInput(Game *game);
void    freeMap(char **map);
int     initializeGame(Game *game);
bool    isPlayerTile(char tile);
bool    isValidTile(char tile);
bool    isWalkableTile(char tile);
int     levelLoad(Game *game);
int     levelValidate(Game *game);
void    renderFrame(Game *game);

#endif
