/* ************************************************************************************ */
/*                                                                                      */
/*  File:       pixel_colors.c                                                          */
/*  Purpose:    Functions for getting and setting pixel colors in the image buffer      */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/23                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

Color getColor(Image *img, int x, int y, float distance)
{
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;
    unsigned char *p = (unsigned char *)img->data + offset;
    int scale = (int)(fmaxf(0.2f, 1.0f - distance * SHADOW_STRENGTH) * 256);

    Color color;
    color.r = (p[0] * scale) >> 8;
    color.g = (p[1] * scale) >> 8;
    color.b = (p[2] * scale) >> 8;
    color.a = (p[3] * scale) >> 8;

    return color;
}

void setColor(Image *img, int x, int y, Color color)
{
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;
    unsigned char *p = (unsigned char *)img->data + offset;

    p[0] = color.r;
    p[1] = color.g;
    p[2] = color.b;
    p[3] = color.a;
}
