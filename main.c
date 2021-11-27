#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include <string.h>

#include "parchis.h"
#include "turnos.h"

int VICTORIA=0;

int main(void)
{

    Board *juego = newBoard();
    creacionMaestra(juego);
    char playerInicial=quienInicia();
    do{
        displayBoard(juego);
        char player = cambiarJugador(playerInicial);
        Turno(player, juego);
        displayBoard(juego);
        VICTORIA=revisarVictoria(juego);
        if(VICTORIA==1)
            printf("FELICIDADES GANO EL JUGADOR ROJO");
        else if(VICTORIA==2)
            printf("FELICIDADES GANO EL JUGADOR VERDE");
        else if(VICTORIA==3)
            printf("FELICIDADES GANO EL JUGADOR AZUL");
        else if(VICTORIA==4)
            printf("FELICIDADES GANO EL JUGADOR AMARILLO");
    }while(VICTORIA==0);


/*
    // INICIALIZACION DE RAYLIB
    //--------------------------------------------------------------------------------------
    const int width = 1600;
    const int height = 900;

    InitWindow(width, height, "PARCHIS - KER Y TIA");
    SetTargetFPS(30);

    //Iniciar tablero y fichas
    Image fondo = LoadImage("..\\fondos\\tablero.png");
        Texture2D textureBg = LoadTextureFromImage(fondo);
        Image fondoinicio = LoadImage("..\\fondos\\fondoinicio.png");
        Texture2D textureInitBg = LoadTextureFromImage(fondoinicio);

        //Fichas rojas y su textura
    Image imgR1 = LoadImage("..\\fichas\\R1.png");
        Texture2D textureR1 = LoadTextureFromImage(imgR1);
    Image imgR2 = LoadImage("..\\fichas\\R2.png");
        Texture2D textureR2 = LoadTextureFromImage(imgR2);
    Image imgR3 = LoadImage("..\\fichas\\R3.png");
        Texture2D textureR3 = LoadTextureFromImage(imgR3);
    Image imgR4 = LoadImage("..\\fichas\\R4.png");
        Texture2D textureR4 = LoadTextureFromImage(imgR4);
        //Fichas azules
    Image imgB1 = LoadImage("..\\fichas\\B1.png");
        Texture2D textureB1 = LoadTextureFromImage(imgB1);
    Image imgB2 = LoadImage("..\\fichas\\B2.png");
        Texture2D textureB2 = LoadTextureFromImage(imgB2);
    Image imgB3 = LoadImage("..\\fichas\\B3.png");
        Texture2D textureB3 = LoadTextureFromImage(imgB3);
    Image imgB4 = LoadImage("..\\fichas\\B4.png");
        Texture2D textureB4 = LoadTextureFromImage(imgB4);
        //Fichas verdes
    Image imgG1 = LoadImage("..\\fichas\\G1.png");
        Texture2D textureG1 = LoadTextureFromImage(imgG1);
    Image imgG2 = LoadImage("..\\fichas\\G2.png");
        Texture2D textureG2 = LoadTextureFromImage(imgG2);
    Image imgG3 = LoadImage("..\\fichas\\G3.png");
        Texture2D textureG3 = LoadTextureFromImage(imgG3);
    Image imgG4 = LoadImage("..\\fichas\\G4.png");
        Texture2D textureG4 = LoadTextureFromImage(imgG4);
        //Fichas amarillas
    Image imgY1 = LoadImage("..\\fichas\\Y1.png");
        Texture2D textureY1 = LoadTextureFromImage(imgY1);
    Image imgY2 = LoadImage("..\\fichas\\Y2.png");
        Texture2D textureY2 = LoadTextureFromImage(imgY2);
    Image imgY3 = LoadImage("..\\fichas\\Y3.png");
        Texture2D textureY3 = LoadTextureFromImage(imgY3);
    Image imgY4 = LoadImage("..\\fichas\\Y4.png");
        Texture2D textureY4 = LoadTextureFromImage(imgY4);

        //Cargar dado
    Image dado = LoadImage("..\\fichas\\dado.png");
        Texture2D textureDado = LoadTextureFromImage(dado);


    UnloadImage(fondo); UnloadImage(fondoinicio);
    UnloadImage(imgR1); UnloadImage(imgR2); UnloadImage(imgR3); UnloadImage(imgR4);
    UnloadImage(imgB1); UnloadImage(imgB2); UnloadImage(imgB3); UnloadImage(imgB4);
    UnloadImage(imgG1); UnloadImage(imgG2); UnloadImage(imgG3); UnloadImage(imgG4);
    UnloadImage(imgY1); UnloadImage(imgY2); UnloadImage(imgY3); UnloadImage(imgY4);
    UnloadImage(dado);

    //--------------------------------------------------------------------------------------
    PixelPos pix;
    guardarPosicionesIniciales(&pix);

    Dados dice;
    //guardarDadosInicio(&dice);


    //---------------------------------------------------------------------------------------
    int inicio = 0, jugadores = 0;
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

        DrawTexture(textureInitBg, 0, 0, WHITE);
        DrawText("ola", 110, 150, 200, RAYWHITE);
        DrawText("Seleccione jugadores:", 560, 380, 40, RAYWHITE);


            DrawTexture(textureBg, 0, 0, WHITE);
            //ROJO
            DrawTexture(textureR1, obtenerXR1(&pix), obtenerYR1(&pix), WHITE);
            DrawTexture(textureR2, obtenerXR2(&pix), obtenerYR2(&pix), WHITE);
            DrawTexture(textureR3, obtenerXR3(&pix), obtenerYR3(&pix), WHITE);
            DrawTexture(textureR4, obtenerXR4(&pix), obtenerYR4(&pix), WHITE);

            //VERDE
            DrawTexture(textureG1, obtenerXG1(&pix), obtenerYG1(&pix), WHITE);
            DrawTexture(textureG2, obtenerXG2(&pix), obtenerYG2(&pix), WHITE);
            DrawTexture(textureG3, obtenerXG3(&pix), obtenerYG3(&pix), WHITE);
            DrawTexture(textureG4, obtenerXG4(&pix), obtenerYG4(&pix), WHITE);

            //AMARILLO
            DrawTexture(textureY1, obtenerXY1(&pix), obtenerYY1(&pix), WHITE);
            DrawTexture(textureY2, obtenerXY2(&pix), obtenerYY2(&pix), WHITE);
            DrawTexture(textureY3, obtenerXY3(&pix), obtenerYY3(&pix), WHITE);
            DrawTexture(textureY4, obtenerXY4(&pix), obtenerYY4(&pix), WHITE);

            //AZUL
            DrawTexture(textureB1, obtenerXB1(&pix), obtenerYB1(&pix), WHITE);
            DrawTexture(textureB2, obtenerXB2(&pix), obtenerYB2(&pix), WHITE);
            DrawTexture(textureB3, obtenerXB3(&pix), obtenerYB3(&pix), WHITE);
            DrawTexture(textureB4, obtenerXB4(&pix), obtenerYB4(&pix), WHITE);

            //DADOS
            //int d1 = updateDado1(&dice); int d2 = updateDado2(&dice);
            DrawText(TextFormat("D1 [%d]  D2 [%d]", 0, 0), 1230, 780, 50, WHITE);
            DrawTexture(textureDado, 1100, 750, WHITE);

            //TÍTULO
            DrawText("PERPENDICULAR PARCHEESI", 360, 45, 60, RAYWHITE);


            EndDrawing();
            //----------------------------------------------------------------------------------
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

        */
}