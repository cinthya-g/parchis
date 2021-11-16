#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <string.h>
#include "parchis.h"


int main()
{
    /*
     * //Pruebas con raylib, IGNORAR
    const int screenWidth = 1000;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tablero");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawText("Parchis", 450, 20, 25, DARKBLUE);
            DrawRectangle(40, 60, 920, 700, SKYBLUE);


            EndDrawing();
    }
    CloseWindow();
     */
    Board *juego = newBoard();
    creacionMaestraALV(juego);
    displayBoard(juego);
    Turno();


    return 0;
}