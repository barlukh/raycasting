/* ************************************************************************************ */
/*                                                                                      */
/*  File:       utils.c                                                                 */
/*  Purpose:    Various utility and helper functions                                    */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

char *copyString(const char *s)
{
    if (s == NULL)
        return NULL;

    size_t len = strlen(s) + 1;
    char *copy = calloc(len, sizeof(char));
    if (!copy)
        return NULL;

    for (size_t i = 0; i < len; i++)
        copy[i] = s[i];

    return copy;
}

void updateTimers(Game *game)
{
    float frameTime = GetFrameTime();
    for (size_t i = 0; i < game->level.spriteCount; i++)
    {
        Sprite *sprite = &game->graphics.sprites[i];
        sprite->timer += frameTime;
        if (sprite->timer >= sprite->frameThreshold)
        {
            sprite->currentFrame = (sprite->currentFrame + 1) % sprite->totalFrames;
            sprite->timer -= sprite->frameThreshold;
        }
    }
}
