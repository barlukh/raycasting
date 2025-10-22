/* ************************************************************************************ */
/*                                                                                      */
/*  File:       alloc_sprites.c                                                         */
/*  Purpose:    Allocates arrays for sprite rendering                                   */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/22                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static void mapSprites(Game *game);
static void initMage(size_t pos, Game *game);

int allocSprites(Game *game)
{
    game->graphics.spriteOrder = calloc(game->level.spriteCount, sizeof(int));
    game->graphics.spriteDistance = calloc(game->level.spriteCount, sizeof(double));
    game->graphics.ZBuffer = calloc(game->screen.width, sizeof(double));
    game->graphics.sprites = calloc(game->level.spriteCount, sizeof(Sprite));

    if (!game->graphics.sprites || !game->graphics.spriteOrder
        || !game->graphics.spriteDistance || !game->graphics.ZBuffer)
    {
        cleanProgram(ERR_MEM_ALLOC, game);
        CloseWindow();
        return (FAILURE);
    }

    mapSprites(game);

    return (SUCCESS);
}

static void mapSprites(Game *game)
{
    size_t pos = 0;

    for (size_t y = 0; game->level.map[y]; y++)
    {
        for (size_t x = 0; game->level.map[y][x]; x++)
        {
            if (isSpriteTile(game->level.map[y][x]))
            {
                game->graphics.sprites[pos].x = x + 0.5;
                game->graphics.sprites[pos].y = y + 0.5;
                if (game->level.map[y][x] == SPRITE_MAGE)
                    initMage(pos, game);
                pos++;
            }
        }
    }
}

static void initMage(size_t pos, Game *game)
{
    game->graphics.sprites[pos].width = SPRITE_MAGE_WIDTH;
    game->graphics.sprites[pos].height = SPRITE_MAGE_HEIGHT;
    game->graphics.sprites[pos].totalFrames = SPRITE_MAGE_FRAMES;
    game->graphics.sprites[pos].threshold = SPRITE_MAGE_THRESHOLD;
    game->graphics.sprites[pos].anim = game->graphics.mage.anim;
}
