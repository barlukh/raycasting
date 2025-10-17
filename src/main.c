/* ************************************************************************************ */
/*                                                                                      */
/*  File:       main.c                                                                  */
/*  Purpose:    Main source file and the starting point of the program                  */
/*  Author:     barlukh (Boris Gazur)                                                   */
/*  Updated:    2025/10/17                                                              */
/*                                                                                      */
/* ************************************************************************************ */

#include "raycasting.h"

int main(void)
{
    Game game = {0};
    
    if (initializeGame(&game) != SUCCESS)
        return FAILURE;

    while (!WindowShouldClose())
    {
        detectUserInput(&game);
        renderFrame(&game);
        UpdateTexture(game.screenTexture, game.screenImg.data);

        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawTexture(game.screenTexture, 0, 0, RAYWHITE);
        DrawFPS(100, 100);

        EndDrawing();
    }

    cleanProgram(CLEAN_EXIT, &game);
    CloseWindow();

    return SUCCESS;
}
