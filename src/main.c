/* ************************************************************************** */
/*                                                                            */
/*  File:       main.c                                                        */
/*  Purpose:    Main source file and the starting point of the program        */
/*  Author:     barlukh (Boris Gazur)                                         */
/*  Updated:    2025/10/16                                                    */
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
        renderFrame(&game);
        UpdateTexture(game.texture, game.img.data);
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawTexture(game.texture, 0, 0, WHITE);
        DrawFPS(100, 100);

        EndDrawing();
    }

    cleanProgram(CLEAN_EXIT, &game);
    CloseWindow();

    return SUCCESS;
}
