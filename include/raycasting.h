/* ************************************************************************************ */
/*                                                                                      */
/*  File:       raycasting.h                                                            */
/*  Purpose:    Main header file of the program                                         */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/28                                                              */
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

#define TITLE "raycasting"

#define DEFAULT_SCREEN_WIDTH    800
#define DEFAULT_SCREEN_HEIGHT   600

#define SUCCESS 0
#define FAILURE 1

#define TARGET_FPS          60
#define MAX_MAP_SIDE_LEN    64

#define PLANE_FOV           0.66
#define MOVEMENT_SPEED      4
#define SPRITE_SPEED        1.7
#define MOUSE_SENSITIVITY   0.002f
#define ROTATION_SMOOTHING  0.8f

#define BYTES_PER_PIXEL     4
#define SHADOW_STRENGTH     0.03f

#define EMPTY           ' '
#define FLOOR           '0'
#define WALL            '1'
#define PLAYER          'P'
#define PLAYER_N        'N'
#define PLAYER_S        'S'
#define PLAYER_E        'E'
#define PLAYER_W        'W'
#define SPRITE_MAGE     'M'
#define SPRITE_MYSTIC   'Y'
#define SPRITE_SMITH    'B'
#define SPRITE_SKELWALK 'K'
#define VISITED         'V'

#define LEVEL_MAP       "level/map.rcm"
#define TEXTURE_CEILING "graphics/tiles/texture42.png"
#define TEXTURE_FLOOR   "graphics/tiles/texture85.png"
#define TEXTURE_WALL    "graphics/tiles/texture80.png"

#define SPRITE_MAGE_THRESHOLD       0.1f
#define SPRITE_MAGE_FRAMES          11
#define SPRITE_MAGE_WIDTH           82
#define SPRITE_MAGE_HEIGHT          115

#define SPRITE_MYSTIC_THRESHOLD     0.4f
#define SPRITE_MYSTIC_FRAMES        11
#define SPRITE_MYSTIC_WIDTH         70
#define SPRITE_MYSTIC_HEIGHT        94

#define SPRITE_SMITH_THRESHOLD      0.12f
#define SPRITE_SMITH_FRAMES         5
#define SPRITE_SMITH_WIDTH          126
#define SPRITE_SMITH_HEIGHT         130

#define SPRITE_SKELWALK_THRESHOLD   0.12f
#define SPRITE_SKELWALK_FRAMES      8
#define SPRITE_SKELWALK_WIDTH       130
#define SPRITE_SKELWALK_HEIGHT      140

#define SPRITE_MAGE_0       "graphics/sprites/mage0.png"
#define SPRITE_MAGE_1       "graphics/sprites/mage1.png"
#define SPRITE_MAGE_2       "graphics/sprites/mage2.png"
#define SPRITE_MAGE_3       "graphics/sprites/mage3.png"
#define SPRITE_MAGE_4       "graphics/sprites/mage4.png"
#define SPRITE_MAGE_5       "graphics/sprites/mage5.png"
#define SPRITE_MAGE_6       "graphics/sprites/mage6.png"
#define SPRITE_MAGE_7       "graphics/sprites/mage7.png"
#define SPRITE_MAGE_8       "graphics/sprites/mage8.png"
#define SPRITE_MAGE_9       "graphics/sprites/mage9.png"
#define SPRITE_MAGE_10      "graphics/sprites/mage10.png"

#define SPRITE_MYSTIC_0     "graphics/sprites/mystic0.png"
#define SPRITE_MYSTIC_1     "graphics/sprites/mystic1.png"
#define SPRITE_MYSTIC_2     "graphics/sprites/mystic2.png"
#define SPRITE_MYSTIC_3     "graphics/sprites/mystic3.png"
#define SPRITE_MYSTIC_4     "graphics/sprites/mystic4.png"
#define SPRITE_MYSTIC_5     "graphics/sprites/mystic5.png"
#define SPRITE_MYSTIC_6     "graphics/sprites/mystic6.png"
#define SPRITE_MYSTIC_7     "graphics/sprites/mystic7.png"
#define SPRITE_MYSTIC_8     "graphics/sprites/mystic8.png"
#define SPRITE_MYSTIC_9     "graphics/sprites/mystic9.png"
#define SPRITE_MYSTIC_10    "graphics/sprites/mystic10.png"

#define SPRITE_SMITH_0      "graphics/sprites/smith0.png"
#define SPRITE_SMITH_1      "graphics/sprites/smith1.png"
#define SPRITE_SMITH_2      "graphics/sprites/smith2.png"
#define SPRITE_SMITH_3      "graphics/sprites/smith3.png"
#define SPRITE_SMITH_4      "graphics/sprites/smith4.png"

#define SPRITE_SKELWALK_0   "graphics/sprites/skelWalk0.png"
#define SPRITE_SKELWALK_1   "graphics/sprites/skelWalk1.png"
#define SPRITE_SKELWALK_2   "graphics/sprites/skelWalk2.png"
#define SPRITE_SKELWALK_3   "graphics/sprites/skelWalk3.png"
#define SPRITE_SKELWALK_4   "graphics/sprites/skelWalk4.png"
#define SPRITE_SKELWALK_5   "graphics/sprites/skelWalk5.png"
#define SPRITE_SKELWALK_6   "graphics/sprites/skelWalk6.png"
#define SPRITE_SKELWALK_7   "graphics/sprites/skelWalk7.png"

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

typedef struct Animations
{
    Image       mageFrames[SPRITE_MAGE_FRAMES];
    Image       mysticFrames[SPRITE_MYSTIC_FRAMES];
    Image       smithFrames[SPRITE_SMITH_FRAMES];
    Image       skelWalkFrames[SPRITE_SKELWALK_FRAMES];
}   Animations;

typedef struct Sprite
{
    char        type;
    bool        isStationary;
    float       x;
    float       y;
    int         width;
    int         height;
    int         totalFrames;
    float       timer;
    float       frameThreshold;
    size_t      currentFrame;
    Image       *animation;
}   Sprite;

typedef struct Graphics
{
    int         *spriteOrder;
    float       *spriteDistance;
    float       *ZBuffer;
    Image       ceiling;
    Image       floor;
    Image       wall;
    Animations  animations;
}   Graphics;

typedef struct Level
{
    char        **map;
    size_t      spriteCount;
}   Level;

typedef struct Player
{
    float       posX;
    float       posY;
    float       dirX;
    float       dirY;
    float       planeX;
    float       planeY;
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
    Sprite      *sprite;
}   Game;


//----------------------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------------------

void    castRayforColumn(int x, Game *game);
void    castRayforStripe(int y, Game *game);
void    cleanProgram(const char *errMsg, Game *game);
char    *copyString(const char *s);
void    detectUserInput(Game *game);
void    drawSprites(Game *game);
void    freeMap(char **map);
Color   getColor(Image *img, int x, int y, float distance);
int     initializeGame(Game *game);
bool    isPlayerTile(char tile);
bool    isSpriteTile(char tile);
bool    isValidTile(char tile);
bool    isWalkablePlayerTile(char tile);
bool    isWalkableSpriteTile(char tile);
int     loadImages(Game *game);
int     loadMap(Game *game);
void    renderFrame(Game *game);
void    setColor(Image *img, int x, int y, Color color);
int     setSprites(Game *game);
void    updateSpritePositions(Game *game);
void    updateTimers(Game *game);
int     validateMap(Game *game);


#endif
