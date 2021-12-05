#include <stdio.h>
#include <raylib.h>

#include "parchis.h"
#include "turnos.h"
#include "graphics.h"

int main(void)
{
    /*
    int noTePasesDeDobles=0;
    int VICTORIA = 0;
    int contadorTurnos = 0;
    int jugadores = 2;
    int saveToUse=0;
    Board*juego=NULL;
    Dados Dice;

    juego=newBoard();
    creacionMaestra(juego,jugadores);

    char playerInicial=quienInicia(juego);
    char player = playerInicial;
    do{
        do{
            if(noTePasesDeDobles==1)
                printf("Ulala te sacaste un doble, te regalo otro tiro, pero nomas otro, mas de 2 es ilegal, te meto al bote prro\n");
            Dice= tiroDados();
            Turno(player, juego,Dice);
            noTePasesDeDobles++;
            if(noTePasesDeDobles==2)
                break;
        }while(Dice.die1==Dice.die2);//Este ciclo, permite que si el usuario saca dobles, se le conceda un segundo tiro.

        hacerTiempo();
        contadorTurnos++;
        if(contadorTurnos%4==0)
        {
            displayBoard(juego);
        }
        player=cambiarJugador(player,juego);
        VICTORIA=revisarVictoria(juego);
        if(VICTORIA==1)
            printf("FELICIDADES GANO EL JUGADOR ROJO");
        else if(VICTORIA==2)
            printf("FELICIDADES GANO EL JUGADOR VERDE");
        else if(VICTORIA==3)
            printf("FELICIDADES GANO EL JUGADOR AZUL");
        else if(VICTORIA==4)
            printf("FELICIDADES GANO EL JUGADOR AMARILLo");
    }while(VICTORIA==0);
*/


    // INICIALIZACION DE RAYLIB
    //--------------------------------------------------------------------------------------
    const int HEIGHT = 900;
    const int WIDTH = 1600;
    InitWindow(WIDTH, HEIGHT, "SUPER PERPENDICULAR PARCHIS - Iker y Cinthya");
    SetTargetFPS(30);

    //Iniciar tablero y fichas
    Image fondo = LoadImage("..\\fondos\\tablero.png");
        Texture2D textureBg = LoadTextureFromImage(fondo);

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


    UnloadImage(fondo);
    UnloadImage(imgR1); UnloadImage(imgR2); UnloadImage(imgR3); UnloadImage(imgR4);
    UnloadImage(imgB1); UnloadImage(imgB2); UnloadImage(imgB3); UnloadImage(imgB4);
    UnloadImage(imgG1); UnloadImage(imgG2); UnloadImage(imgG3); UnloadImage(imgG4);
    UnloadImage(imgY1); UnloadImage(imgY2); UnloadImage(imgY3); UnloadImage(imgY4);
    UnloadImage(dado);

    //-------- INICIAR TABLERO ------------------------------------------------------
    Board *juegoG = newBoard();

    //---------INICIALIZAR ESTRUCTURAS-------------------------------------------------
    Positions *pix = initialPositions();
    Dados DiceG = {0,0};

    //---------BANDERAS Y VARIABLES-------------------------------------------------------------
    int inicio = 0, jugadoresG = 0, victoria = 0, tiempo = 0;
    char playerInTurn = 'N';
    int d1 = 0, d2=0;

    //--------------------------MAIN GAME LOOP-------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here -> Dados, turno

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        if(inicio == 0){
            mainScreen();

            if(IsKeyPressed(KEY_TWO)){
                inicio = 1;
                jugadoresG = 2;
                creacionMaestra(juegoG, jugadoresG);
            }
            else if(IsKeyPressed(KEY_THREE)){
                inicio = 1;
                jugadoresG = 3;
                creacionMaestra(juegoG, jugadoresG);
            }
            else if(IsKeyPressed(KEY_FOUR)){
                inicio = 1;
                jugadoresG = 4;
                creacionMaestra(juegoG, jugadoresG);

            }
        }

        if(inicio == 1 && victoria == 0)
        {

            ClearBackground(RAYWHITE);

            DrawTexture(textureBg, 0, 0, WHITE);
            //ROJO
            DrawTexture(textureR1, obtenerXR1(pix, juegoG, 'R'), obtenerYR1(pix, juegoG, 'R'), WHITE);
            DrawTexture(textureR2, obtenerXR2(pix, juegoG, 'R'), obtenerYR2(pix, juegoG, 'R'), WHITE);
            DrawTexture(textureR3, obtenerXR3(pix, juegoG, 'R'), obtenerYR3(pix, juegoG, 'R'), WHITE);
            DrawTexture(textureR4, obtenerXR4(pix, juegoG, 'R'), obtenerYR4(pix, juegoG, 'R'), WHITE);

            //VERDE
            DrawTexture(textureG1, obtenerXG1(pix, juegoG, 'G'), obtenerYG1(pix, juegoG, 'G'), WHITE);
            DrawTexture(textureG2, obtenerXG2(pix, juegoG, 'G'), obtenerYG2(pix, juegoG, 'G'), WHITE);
            DrawTexture(textureG3, obtenerXG3(pix, juegoG, 'G'), obtenerYG3(pix, juegoG, 'G'), WHITE);
            DrawTexture(textureG4, obtenerXG4(pix, juegoG, 'G'), obtenerYG4(pix, juegoG, 'G'), WHITE);


            //AMARILLO
            DrawTexture(textureY1, obtenerXY1(pix, juegoG, 'Y'), obtenerYY1(pix, juegoG, 'Y'), WHITE);
            DrawTexture(textureY2, obtenerXY2(pix, juegoG, 'Y'), obtenerYY2(pix, juegoG, 'Y'), WHITE);
            DrawTexture(textureY3, obtenerXY3(pix, juegoG, 'Y'), obtenerYY3(pix, juegoG, 'Y'), WHITE);
            DrawTexture(textureY4, obtenerXY4(pix, juegoG, 'Y'), obtenerYY4(pix, juegoG, 'Y'), WHITE);

            //AZUL
            DrawTexture(textureB1, obtenerXB1(pix, juegoG, 'B'), obtenerYB1(pix, juegoG, 'B'), WHITE);
            DrawTexture(textureB2, obtenerXB2(pix, juegoG, 'B'), obtenerYB2(pix, juegoG, 'B'), WHITE);
            DrawTexture(textureB3, obtenerXB3(pix, juegoG, 'B'), obtenerYB3(pix, juegoG, 'B'), WHITE);
            DrawTexture(textureB4, obtenerXB4(pix, juegoG, 'B'), obtenerYB4(pix, juegoG, 'B'), WHITE);

            //NUMERO DE JUGADORES
            DrawText(TextFormat("Jugadores [%d]", jugadoresG), 45, 40, 25, WHITE);

            //IMAGEN DADOS
            DrawTexture(textureDado, 1100, 750, WHITE);

            //JUGADOR EN TURNO
            if(playerInTurn == 'N'){
                playerInTurn = quienInicia(juegoG);
            }
            else {
                playerInTurn = cambiarJugador(playerInTurn, juegoG);
                d1 = valorDado1(DiceG);
                d2 = valorDado2(DiceG);
            }

            displayPlayerInTurn(playerInTurn, juegoG);
            displayMainDice(d1, d2);

            tiempo = 1;
            if(tiempo == 1){
                DrawText("Presione ENTER para continuar", 500, 600, 30, WHITE);

                if(IsKeyPressed(KEY_ENTER))
                    tiempo=0;
            }

            //----------------------------------------------------------------------------------
        }
        EndDrawing();
    }

    CloseWindow();


    return 0;
}
