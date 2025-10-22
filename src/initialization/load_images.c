/* ************************************************************************************ */
/*                                                                                      */
/*  File:       load_images.c                                                           */
/*  Purpose:    Loads .png image files of tiles and sprites                             */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/22                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static int loadTiles(Game *game);
static int loadSpriteMage(Game *game);

int loadImages(Game *game)
{
    if (loadTiles(game) != SUCCESS)
        return FAILURE;

    if (loadSpriteMage(game) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

static int loadTiles(Game *game)
{
    game->graphics.ceiling = LoadImage(TEX_CEILING);
    if (!game->graphics.ceiling.data)
        return FAILURE;
    ImageFormat(&game->graphics.ceiling, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.ceiling.data)
        return FAILURE;

    game->graphics.floor = LoadImage(TEX_FLOOR);
    if (!game->graphics.floor.data)
        return FAILURE;
    ImageFormat(&game->graphics.floor, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    if (!game->graphics.ceiling.data)
        return FAILURE;

    game->graphics.wall = LoadImage(TEX_WALL);
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
        game->graphics.mage.anim[i] = LoadImage(sprites[i]);
        if (!game->graphics.mage.anim[i].data)
            return FAILURE;
        ImageFormat(&game->graphics.mage.anim[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }

    return SUCCESS;
}
