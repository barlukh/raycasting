/* ************************************************************************** */
/*                                                                            */
/*  File:       main.c                                                        */
/*  Purpose:    Main source file and the starting point of the program        */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/14                                                    */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int main(void)
{
    Game game = {0};
    
    if (initializeGame(&game) != SUCCESS)
        return FAILURE;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    cleanProgram(CLEAN_EXIT, &game);
    CloseWindow();

    return SUCCESS;
}
