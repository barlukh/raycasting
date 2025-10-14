/* ************************************************************************** */
/*                                                                            */
/*  File:       level_load.c                                                  */
/*  Purpose:    Handles opening of levelX.rcm files and loads maps            */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static char *selectLevel(Game *game);
static FILE *openLevel(char *path, Game *game);
static int  countLines(char *buffer, size_t *lineCount, FILE *fp, Game *game);
static int  copyMap(char *buffer, size_t lineCount, FILE *fp, Game *game);

int levelLoad(Game *game)
{
    char *path = selectLevel(game);
    if (!path)
        return FAILURE;

    FILE *fp = openLevel(path, game);
    if (!fp)
        return FAILURE;

    char    buffer[MAX_MAP_SIDE_LEN];
    size_t  lineCount = 0;
    if (countLines(buffer, &lineCount, fp, game) != SUCCESS)
        return FAILURE;

    rewind(fp);

    if (copyMap(buffer, lineCount, fp, game) != SUCCESS)
        return FAILURE;

    fclose(fp);
    
    return SUCCESS;
}

static char *selectLevel(Game *game)
{
    switch (game->level.index)
    {
        case 0:
            return LEVEL0;
        case 1:
            return LEVEL1;
        case 2:
            return LEVEL2;
        case 3:
            return LEVEL3;
        case 4:
            return LEVEL4;
        case 5:
            return LEVEL5;
        default:
            cleanProgram(ERR_LEVEL_PATH, game);
            return NULL;
    }
}

FILE *openLevel(char *path, Game *game)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        cleanProgram(ERR_FILE_OPEN, game);
        return NULL;
    }
    
    return fp;
}

static int countLines(char *buffer, size_t *lineCount, FILE *fp, Game *game)
{
    while (fgets(buffer, MAX_MAP_SIDE_LEN, fp))
        (*lineCount)++;

    if ((*lineCount > MAX_MAP_SIDE_LEN))
    {
        cleanProgram(ERR_MAP_FORMAT, game);
        fclose(fp);
        return FAILURE;
    }

    game->level.map = calloc(*lineCount + 1, sizeof(char *));
    if (!game->level.map)
    {
        cleanProgram(ERR_MEM_ALLOC, game);
        fclose(fp);
        return FAILURE;
    }

    return SUCCESS;
}

static int copyMap(char *buffer, size_t lineCount, FILE *fp, Game *game)
{    
    for (size_t i = 0; i < lineCount; i++)
    {
        if (!fgets(buffer, MAX_MAP_SIDE_LEN, fp))
        {
            cleanProgram(ERR_FILE_READ, game);
            fclose(fp);
            return FAILURE;
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[--len] = '\0';
        else
        {
            cleanProgram(ERR_MAP_FORMAT, game);
            fclose(fp);
            return FAILURE;
        }
    
        game->level.map[i] = copyString(buffer);
        if (!game->level.map[i])
        {
            cleanProgram(ERR_MEM_ALLOC, game);
            fclose(fp);
            return FAILURE;
        }
    }

    game->level.map[lineCount] = NULL;
    
    return SUCCESS;
}
