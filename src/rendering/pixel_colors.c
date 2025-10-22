/* ************************************************************************************ */
/*                                                                                      */
/*  File:       pixel_colors.c                                                          */
/*  Purpose:    Functions for getting and setting pixel colors in the image buffer      */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/22                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

Color getColor(Image *img, int x, int y, double distance)
{
    unsigned char *pixels = (unsigned char *)img->data;
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;

    float brightness = fmaxf(0.2f, 1.0f - distance * SHADOW_STRENGTH);
    int scale = (int)(brightness * 256);

    Color color;
    color.r = (pixels[offset + 0] * scale) >> 8;
    color.g = (pixels[offset + 1] * scale) >> 8;
    color.b = (pixels[offset + 2] * scale) >> 8;
    color.a = (pixels[offset + 3] * scale) >> 8;

    return color;
}

void setColor(Image *img, int x, int y, Color color)
{
    unsigned char *pixels = (unsigned char *)img->data;
    int offset = (y * img->width + x) * BYTES_PER_PIXEL;

    pixels[offset + 0] = color.r;
    pixels[offset + 1] = color.g;
    pixels[offset + 2] = color.b;
    pixels[offset + 3] = color.a;
}
