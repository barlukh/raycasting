/* ************************************************************************************ */
/*                                                                                      */
/*  File:       set_sprites.c                                                           */
/*  Purpose:    Allocation of arrays for sprites and setting their initial variables    */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static void mapSprites(Game *game);
static void initMage(size_t pos, Game *game);
static void initMystic(size_t pos, Game *game);
static void initSmith(size_t pos, Game *game);
static void initSkelWalk(size_t pos, Game *game);

int setSprites(Game *game)
{
    if (game->level.spriteCount == 0)
        return SUCCESS;

    game->graphics.spriteOrder = calloc(game->level.spriteCount, sizeof(int));
    game->graphics.spriteDistance = calloc(game->level.spriteCount, sizeof(float));
    game->graphics.ZBuffer = calloc(game->screen.width, sizeof(float));
    game->sprite = calloc(game->level.spriteCount, sizeof(Sprite));

    if (!game->sprite || !game->graphics.spriteOrder
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
                game->sprite[pos].x = x + 0.5;
                game->sprite[pos].y = y + 0.5;
                if (game->level.map[y][x] == SPRITE_MAGE)
                    initMage(pos, game);
                else if (game->level.map[y][x] == SPRITE_MYSTIC)
                    initMystic(pos, game);
                else if (game->level.map[y][x] == SPRITE_SMITH)
                    initSmith(pos, game);
                else if (game->level.map[y][x] == SPRITE_SKELWALK)
                    initSkelWalk(pos, game);
                pos++;
            }
        }
    }
}

static void initMage(size_t pos, Game *game)
{
    game->sprite[pos].type = SPRITE_MAGE;
    game->sprite[pos].isStationary = true;
    game->sprite[pos].width = SPRITE_MAGE_WIDTH;
    game->sprite[pos].height = SPRITE_MAGE_HEIGHT;
    game->sprite[pos].totalFrames = SPRITE_MAGE_FRAMES;
    game->sprite[pos].frameThreshold = SPRITE_MAGE_THRESHOLD;
    game->sprite[pos].currentFrame = rand() % SPRITE_MAGE_FRAMES;
    game->sprite[pos].animation = game->graphics.animations.mageFrames;
}

static void initMystic(size_t pos, Game *game)
{
    game->sprite[pos].type = SPRITE_MYSTIC;
    game->sprite[pos].isStationary = true;
    game->sprite[pos].width = SPRITE_MYSTIC_WIDTH;
    game->sprite[pos].height = SPRITE_MYSTIC_HEIGHT;
    game->sprite[pos].totalFrames = SPRITE_MYSTIC_FRAMES;
    game->sprite[pos].frameThreshold = SPRITE_MYSTIC_THRESHOLD;
    game->sprite[pos].currentFrame = rand() % SPRITE_MYSTIC_FRAMES;
    game->sprite[pos].animation = game->graphics.animations.mysticFrames;
}

static void initSmith(size_t pos, Game *game)
{
    game->sprite[pos].type = SPRITE_SMITH;
    game->sprite[pos].isStationary = true;
    game->sprite[pos].width = SPRITE_SMITH_WIDTH;
    game->sprite[pos].height = SPRITE_SMITH_HEIGHT;
    game->sprite[pos].totalFrames = SPRITE_SMITH_FRAMES;
    game->sprite[pos].frameThreshold = SPRITE_SMITH_THRESHOLD;
    game->sprite[pos].currentFrame = rand() % SPRITE_SMITH_FRAMES;
    game->sprite[pos].animation = game->graphics.animations.smithFrames;
}

static void initSkelWalk(size_t pos, Game *game)
{
    game->sprite[pos].type = SPRITE_SKELWALK;
    game->sprite[pos].isStationary = false;
    game->sprite[pos].width = SPRITE_SKELWALK_WIDTH;
    game->sprite[pos].height = SPRITE_SKELWALK_HEIGHT;
    game->sprite[pos].totalFrames = SPRITE_SKELWALK_FRAMES;
    game->sprite[pos].frameThreshold = SPRITE_SKELWALK_THRESHOLD;
    game->sprite[pos].currentFrame = rand() % SPRITE_SKELWALK_FRAMES;
    game->sprite[pos].animation = game->graphics.animations.skelWalkFrames;
}
