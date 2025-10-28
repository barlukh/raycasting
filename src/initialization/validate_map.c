/* ************************************************************************************ */
/*                                                                                      */
/*  File:       validate_map.c                                                          */
/*  Purpose:    Validating the content of a loaded map                                  */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/28                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static int validateTiles(Game *game);
static int setPlayer(char tile, size_t x, size_t y, Game *game);
static size_t countLines(Game *game);
static char **createTempMap(size_t lineCount, Game *game);
static int floodFill(char **map, char **tempMap, int height, int col, int row);

int validateMap(Game *game)
{
    if (validateTiles(game) != SUCCESS)
        return FAILURE;

    size_t lineCount = countLines(game);

    char **tempMap = createTempMap(lineCount, game);
    if (!tempMap)
        return FAILURE;

    int col = (int)game->player.posX;
    int row = (int)game->player.posY;
    if (floodFill(game->level.map, tempMap, lineCount, col, row) != SUCCESS)
    {
        cleanProgram(ERR_MAP_OPEN, game);
        freeMap(tempMap);
        return FAILURE;
    }

    freeMap(tempMap);

    return SUCCESS;
}

static int validateTiles(Game *game)
{
    bool playerFound = false;

    for (size_t y = 0; game->level.map[y]; y++)
    {
        for (size_t x = 0; game->level.map[y][x]; x++)
        {
            if (!isValidTile(game->level.map[y][x]))
            {
                cleanProgram(ERR_MAP_TILE, game);
                return FAILURE;
            }

            if (isPlayerTile(game->level.map[y][x]))
            {
                if (playerFound)
                {
                    cleanProgram(ERR_MAP_PLAYER, game);
                    return FAILURE;
                }
                else
                {
                    playerFound = true;
                    if (setPlayer(game->level.map[y][x], x, y, game) != SUCCESS)
                        return FAILURE;
                    
                    game->level.map[y][x] = PLAYER;
                }
            }

            if (isSpriteTile(game->level.map[y][x]))
                game->level.spriteCount++;
        } 
    }

    if (!playerFound)
    {
        cleanProgram(ERR_MAP_PLAYER, game);
        return FAILURE;
    }

    return SUCCESS;
}

static int setPlayer(char tile, size_t x, size_t y, Game *game)
{
    game->player.posX = (float)x + 0.5;
    game->player.posY = (float)y + 0.5;

    switch (tile)
    {
        case PLAYER_N:
            game->player.dirX = 0;
            game->player.dirY = -1;
            game->player.planeX = PLANE_FOV;
            game->player.planeY = 0;
            break;
        case PLAYER_S:
            game->player.dirX = 0;
            game->player.dirY = 1;
            game->player.planeX = -PLANE_FOV;
            game->player.planeY = 0;
            break;
        case PLAYER_W:
            game->player.dirX = -1;
            game->player.dirY = 0;
            game->player.planeX = 0;
            game->player.planeY = -PLANE_FOV;
            break;
        case PLAYER_E:
            game->player.dirX = 1;
            game->player.dirY = 0;
            game->player.planeX = 0;
            game->player.planeY = PLANE_FOV;
            break;
        default:
            cleanProgram(ERR_MAP_PLAYER, game);
            return FAILURE;
    }

    return SUCCESS;
}

static size_t countLines(Game *game)
{
    size_t lineCount = 0;

    while (game->level.map[lineCount])
        lineCount++;
    
    return lineCount;
}

static char **createTempMap(size_t lineCount, Game *game)
{
    char **tempMap = calloc(sizeof(char *), lineCount + 1);
    if (!tempMap)
    {
        cleanProgram(ERR_MEM_ALLOC, game);
        return NULL;
    }

    for (size_t i = 0; i < lineCount; i++)
    {
        size_t lineLength = strlen(game->level.map[i]);
        tempMap[i] = calloc(lineLength + 1, sizeof(char));
        if (!tempMap[i])
        {
            freeMap(tempMap);
            cleanProgram(ERR_MEM_ALLOC, game);
            return NULL;
        }
    }

    tempMap[lineCount] = NULL;
    
    return tempMap;
}

static int floodFill(char **map, char **tempMap, int height, int col, int row)
{
    if (row < 0 || row >= height || col < 0 || col >= (int)strlen(map[row]))
        return (FAILURE);

    if (!map[row] || col >= (int)strlen(map[row]))
        return (FAILURE);

    if (tempMap[row][col] == VISITED)
        return (SUCCESS);

    tempMap[row][col] = VISITED;

    if (map[row][col] == WALL)
        return (SUCCESS);

    if (map[row][col] == EMPTY)
        return (FAILURE);

    if (!isWalkablePlayerTile(map[row][col]) && map[row][col] != EMPTY)
        return (SUCCESS);

    if (floodFill(map, tempMap, height, col - 1, row) != SUCCESS)
        return (FAILURE);
    if (floodFill(map, tempMap, height, col + 1, row) != SUCCESS)
        return (FAILURE);
    if (floodFill(map, tempMap, height, col, row - 1) != SUCCESS)
        return (FAILURE);
    if (floodFill(map, tempMap, height, col, row + 1) != SUCCESS)
        return (FAILURE);

    return (SUCCESS);
}
