/* ************************************************************************** */
/*                                                                            */
/*  File:       utils.c                                                       */
/*  Purpose:    Various utility and helper functions                          */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

char *copyString(const char *s)
{
    if (s == NULL)
        return NULL;

    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (!copy)
        return NULL;

    for (size_t i = 0; i < len; i++)
        copy[i] = s[i];

    return copy;
}
