/* ************************************************************************************ */
/*                                                                                      */
/*  File:       load_map.c                                                              */
/*  Purpose:    Loading of map.rcm file into a 2D array                                 */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/27                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

static FILE *openMap(const char *path, Game *game);
static int allocMap(char *buffer, size_t *lineCount, FILE *fp, Game *game);
static int copyMap(char *buffer, size_t lineCount, FILE *fp, Game *game);

int loadMap(Game *game)
{
    FILE *fp = openMap(LEVEL_MAP, game);
    if (!fp)
        return FAILURE;

    char buffer[MAX_MAP_SIDE_LEN];
    size_t lineCount = 0;
    if (allocMap(buffer, &lineCount, fp, game) != SUCCESS)
        return FAILURE;

    rewind(fp);

    if (copyMap(buffer, lineCount, fp, game) != SUCCESS)
        return FAILURE;

    fclose(fp);
    
    return SUCCESS;
}

static FILE *openMap(const char *path, Game *game)
{
    FILE *fp = fopen(path, "r");
    if (!fp)
    {
        cleanProgram(ERR_FILE_OPEN, game);
        return NULL;
    }
    
    return fp;
}

static int allocMap(char *buffer, size_t *lineCount, FILE *fp, Game *game)
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
