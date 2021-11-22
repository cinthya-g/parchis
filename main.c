#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <string.h>
#include "parchis.h"
#include "turnos.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int width = 1600;
    const int height = 900;

    InitWindow(width, height, "PARCHIS - KER Y TIA");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //Iniciar tablero y fichas
    Image fondo = LoadImage("..\\tablero.png");
    Image imgR1 = LoadImage("..\\fichas\\R1.png");
    Texture2D textureBg = LoadTextureFromImage(fondo);
    Texture2D textureficha1 = LoadTextureFromImage(imgR1);
    UnloadImage(fondo);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(textureBg, 0, 0, WHITE);
        DrawTexture(textureficha1, 405, 410, WHITE);

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


/*
    Board *juego = newBoard();
    creacionMaestra(juego);
    displayBoard(juego);
    Turno();
    char player=quienInicia();
    printf("%c",player);
*/

    return 0;
}