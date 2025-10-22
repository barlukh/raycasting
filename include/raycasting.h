/* ************************************************************************************ */
/*                                                                                      */
/*  File:       raycasting.h                                                            */
/*  Purpose:    Main header file of the program                                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/22                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#ifndef RAYCASTING_H
#define RAYCASTING_H

//----------------------------------------------------------------------------------------
// Library Headers
//----------------------------------------------------------------------------------------

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

//----------------------------------------------------------------------------------------
// Macro Definitions
//----------------------------------------------------------------------------------------

#define TITLE "ray-casting"

#define DEFAULT_SCREEN_WIDTH    800
#define DEFAULT_SCREEN_HEIGHT   600

#define SUCCESS 0
#define FAILURE 1

#define TARGET_FPS          60
#define MAX_MAP_SIDE_LEN    64

#define PLANE_FOV           0.66
#define MOVEMENT_SPEED      4
#define MOUSE_SENSITIVITY   0.002f
#define ROTATION_SMOOTHING  0.8f

#define BYTES_PER_PIXEL     4
#define SHADOW_STRENGTH     0.07f

#define EMPTY       ' '
#define FLOOR       '0'
#define WALL        '1'
#define PLAYER_N    'N'
#define PLAYER_S    'S'
#define PLAYER_E    'E'
#define PLAYER_W    'W'
#define SPRITE_MAGE 'M'
#define VISITED     'v'

#define LEVEL_MAP   "level/map.rcm"
#define TEX_CEILING "graphics/tiles/texture42.png"
#define TEX_FLOOR   "graphics/tiles/texture85.png"
#define TEX_WALL    "graphics/tiles/texture80.png"

#define SPRITE_MAGE_THRESHOLD   0.1f
#define SPRITE_MAGE_FRAMES      11
#define SPRITE_MAGE_WIDTH       82
#define SPRITE_MAGE_HEIGHT      115

#define SPRITE_MAGE_0   "graphics/sprites/mage0.png"
#define SPRITE_MAGE_1   "graphics/sprites/mage1.png"
#define SPRITE_MAGE_2   "graphics/sprites/mage2.png"
#define SPRITE_MAGE_3   "graphics/sprites/mage3.png"
#define SPRITE_MAGE_4   "graphics/sprites/mage4.png"
#define SPRITE_MAGE_5   "graphics/sprites/mage5.png"
#define SPRITE_MAGE_6   "graphics/sprites/mage6.png"
#define SPRITE_MAGE_7   "graphics/sprites/mage7.png"
#define SPRITE_MAGE_8   "graphics/sprites/mage8.png"
#define SPRITE_MAGE_9   "graphics/sprites/mage9.png"
#define SPRITE_MAGE_10  "graphics/sprites/mage10.png"

#define CLEAN_EXIT      "Program terminated successfully\n"
#define ERR_FILE_OPEN   "Error: Failed to open file\n"
#define ERR_FILE_READ   "Error: Failed to read file\n"
#define ERR_IMAGE_GEN   "Error: Failed to generate image\n"
#define ERR_IMAGE_LOAD  "Error: Failed to load image\n"
#define ERR_MAP_OPEN    "Error: Map not enclosed\n"
#define ERR_MAP_FORMAT  "Error: Invalid map format\n"
#define ERR_MAP_PLAYER  "Error: Invalid player position\n"
#define ERR_MAP_TILE    "Error: Invalid tile character\n"
#define ERR_MEM_ALLOC   "Error: Memory allocation\n"
#define ERR_SCREEN_DEF  "Error: Invalid default window values\n"
#define ERR_SCREEN_INIT "Error: Window initialization\n"
#define ERR_SCREEN_SIZE "Error: Screen size values\n"
#define ERR_TEX_LOAD    "Error: Failed to load texture\n"

//----------------------------------------------------------------------------------------
// Type Definitions
//----------------------------------------------------------------------------------------

typedef struct SpriteMage
{
    Image       anim[SPRITE_MAGE_FRAMES];
}   SpriteMage;

typedef struct Sprite
{
    double      x;
    double      y;
    int         width;
    int         height;
    int         totalFrames;
    float       timer;
    float       threshold;
    size_t      frame;
    Image       *anim;
}   Sprite;

typedef struct Graphics
{
    int         *spriteOrder;
    double      *spriteDistance;
    double      *ZBuffer;
    Sprite      *sprites;
    Image       ceiling;
    Image       floor;
    Image       wall;
    SpriteMage  mage;
}   Graphics;

typedef struct Level
{
    char        **map;
    size_t      spriteCount;
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
    Image       screenImg;
    Texture2D   screenTexture;
    Graphics    graphics;
    Level       level;
    Player      player;
    Screen      screen;
}   Game;

//----------------------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------------------

int     allocSprites(Game *game);
void    castRayforColumn(int x, Game *game);
void    castRayforStripe(int y, Game *game);
void    cleanProgram(const char *errMsg, Game *game);
char    *copyString(const char *s);
void    detectUserInput(Game *game);
void    drawSprites(Game *game);
void    freeMap(char **map);
Color   getColor(Image *img, int x, int y, double distance);
int     initializeGame(Game *game);
bool    isPlayerTile(char tile);
bool    isSpriteTile(char tile);
bool    isValidTile(char tile);
bool    isWalkableTile(char tile);
int     loadImages(Game *game);
int     loadMap(Game *game);
void    renderFrame(Game *game);
void    setColor(Image *img, int x, int y, Color color);
void    updateTimers(Game *game);
int     validateMap(Game *game);

#endif
