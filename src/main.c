/* ************************************************************************** */
/*                                                                            */
/*  File:       main.c                                                        */
/*  Purpose:    Main source file and the starting point of the program        */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/11                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int main(void)
{
    Game game;

    if (initializeGame(&game) != SUCCESS)
        return FAILURE;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);
 
        EndDrawing();
    }

    return SUCCESS;
}
