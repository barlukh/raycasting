/* ************************************************************************** */
/*                                                                            */
/*  File:       level_validate.c                                              */
/*  Purpose:    Validates the content of a loaded level map                   */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static int  findPlayer(Game *game);
static int  setPlayer(char tile, int i, int j, Game *game);

int levelValidate(Game *game)
{
    if (findPlayer(game) != SUCCESS)
        return FAILURE;
    
    return SUCCESS;
}

static int findPlayer(Game *game)
{
    bool playerFound = false;

    for (size_t i = 0; game->level.map[i]; i++)
    {
        for (size_t j = 0; game->level.map[i][j]; j++)
        {
            char tile = game->level.map[i][j];
            if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
            {
                if (playerFound)
                {
                    cleanProgram(ERR_MAP_PLAYER, game);
                    return FAILURE;
                }
                else
                {
                    playerFound = true;
                    if (setPlayer(game->level.map[i][j], i, j, game) != SUCCESS)
                        return FAILURE;
                }
            }
        }
        
    }

    if (!playerFound)
    {
        cleanProgram(ERR_MAP_PLAYER, game);
        return FAILURE;
    }

    return SUCCESS;
}

static int  setPlayer(char tile, int i, int j, Game *game)
{
    game->player.posX = j;
    game->player.posY = i;

    switch (tile)
    {
        case 'N':
            game->player.dirX = 0;
            game->player.dirY = -1;
            game->player.planeX = 0.66;
            game->player.planeY = 0;
            break;
        case 'S':
            game->player.dirX = 0;
            game->player.dirY = 1;
            game->player.planeX = -0.66;
            game->player.planeY = 0;
            break;
        case 'W':
            game->player.dirX = -1;
            game->player.dirY = 0;
            game->player.planeX = 0;
            game->player.planeY = -0.66;
            break;
        case 'E':
            game->player.dirX = 1;
            game->player.dirY = 0;
            game->player.planeX = 0;
            game->player.planeY = 0.66;
            break;
        default:
            cleanProgram(ERR_MAP_PLAYER, game);
            return FAILURE;
    }

    return SUCCESS;
}
