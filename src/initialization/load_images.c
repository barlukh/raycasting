/* ************************************************************************************ */
/*                                                                                      */
/*  File:       load_images.c                                                           */
/*  Purpose:    Loads .png image files of tiles and sprites                             */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/23                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static int loadTiles(Game *game);
static int loadSpriteMage(Game *game);
static int loadSpriteMystic(Game *game);
static int loadSpriteSmith(Game *game);

int loadImages(Game *game)
{
    if (loadTiles(game) != SUCCESS)
        return FAILURE;

    if (loadSpriteMage(game) != SUCCESS)
        return FAILURE;
    
    if (loadSpriteMystic(game) != SUCCESS)
        return FAILURE;

    if (loadSpriteSmith(game) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

static int loadTiles(Game *game)
{
    game->graphics.ceiling = LoadImage(TEXTURE_CEILING);
    if (!game->graphics.ceiling.data)
        return FAILURE;
    ImageFormat(&game->graphics.ceiling, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.ceiling.data)
        return FAILURE;

    game->graphics.floor = LoadImage(TEXTURE_FLOOR);
    if (!game->graphics.floor.data)
        return FAILURE;
    ImageFormat(&game->graphics.floor, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.ceiling.data)
        return FAILURE;

    game->graphics.wall = LoadImage(TEXTURE_WALL);
    if (!game->graphics.wall.data)
        return FAILURE;
    ImageFormat(&game->graphics.wall, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.ceiling.data)
        return FAILURE;

    return SUCCESS;
}

static int loadSpriteMage(Game *game)
{
    char *sprites[SPRITE_MAGE_FRAMES] = 
    {
        SPRITE_MAGE_0,
        SPRITE_MAGE_1,
        SPRITE_MAGE_2,
        SPRITE_MAGE_3,
        SPRITE_MAGE_4,
        SPRITE_MAGE_5,
        SPRITE_MAGE_6,
        SPRITE_MAGE_7,
        SPRITE_MAGE_8,
        SPRITE_MAGE_9,
        SPRITE_MAGE_10
    };

    for (size_t i = 0; i < SPRITE_MAGE_FRAMES; i++)
    {
        game->graphics.animations.mageFrames[i] = LoadImage(sprites[i]);
        if (!game->graphics.animations.mageFrames[i].data)
            return FAILURE;
        ImageFormat(&game->graphics.animations.mageFrames[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }

    return SUCCESS;
}

static int loadSpriteMystic(Game *game)
{
    char *sprites[SPRITE_MYSTIC_FRAMES] = 
    {
        SPRITE_MYSTIC_0,
        SPRITE_MYSTIC_1,
        SPRITE_MYSTIC_2,
        SPRITE_MYSTIC_3,
        SPRITE_MYSTIC_4,
        SPRITE_MYSTIC_5,
        SPRITE_MYSTIC_6,
        SPRITE_MYSTIC_7,
        SPRITE_MYSTIC_8,
        SPRITE_MYSTIC_9,
        SPRITE_MYSTIC_10
    };

    for (size_t i = 0; i < SPRITE_MYSTIC_FRAMES; i++)
    {
        game->graphics.animations.mysticFrames[i] = LoadImage(sprites[i]);
        if (!game->graphics.animations.mysticFrames[i].data)
            return FAILURE;
        ImageFormat(&game->graphics.animations.mysticFrames[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }

    return SUCCESS;
}

static int loadSpriteSmith(Game *game)
{
    char *sprites[SPRITE_SMITH_FRAMES] = 
    {
        SPRITE_SMITH_0,
        SPRITE_SMITH_1,
        SPRITE_SMITH_2,
        SPRITE_SMITH_3,
        SPRITE_SMITH_4
    };

    for (size_t i = 0; i < SPRITE_SMITH_FRAMES; i++)
    {
        game->graphics.animations.smithFrames[i] = LoadImage(sprites[i]);
        if (!game->graphics.animations.smithFrames[i].data)
            return FAILURE;
        ImageFormat(&game->graphics.animations.smithFrames[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }

    return SUCCESS;
}
