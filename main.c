#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <raylib.h>
#include "parchis.h"
#include "turnos.h"
#include "graphics.h"



int main(void)
{
    titleScreen();
    consoleColor();

    int VICTORIA = 0;
    int contadorTurnos = 0;
    int jugadores = 4;
    char saveToUse=0;
    Board*juego=NULL;
    Dados Dice;
    int banderaEditor;


    Board *juegonormal=NULL;
    jugadores = cuantosJugadores();

//Ciclo para validar la eleccion del usuario para usar el editor de tablero.
    printf("Selecciona 1 para un juego normal, 2 para editar un juego\n");
    do{
        printf("INPUT:");
        scanf("%d",&banderaEditor);
    }while(banderaEditor<0||banderaEditor>2);
    if(banderaEditor==2)
    {
        juego=iniciarEditor(jugadores);
    }

    else {
        juego = loadGame(juego,jugadores);
        displayColorBoard(juego);
        //juegonormal = newBoard();
        //creacionMaestra(juegonormal, jugadores);
        //juego=juegonormal;
    }
    char playerInicial=quienInicia(juego);
    char player = playerInicial;
    do{
        Dice= tiroDados();
        //Dice.die1=1;
        //Dice.die2=1;
        Turno(player, juego,Dice);
        saveToUse++;
        Savefile(juego,&saveToUse);
        hacerTiempo();
        contadorTurnos++;
        //displayColorBoard(juego);
        player=cambiarJugador(player,juego);
        VICTORIA=revisarVictoria(juego);
        if(VICTORIA==1) {
            printf("FELICIDADES GANO EL JUGADOR ROJO");
            //exit(0);
        }
        else if(VICTORIA==2) {
            printf("FELICIDADES GANO EL JUGADOR VERDE");
            //exit(0);
        }
        else if(VICTORIA==3) {
            printf("FELICIDADES GANO EL JUGADOR AZUL");
            //exit(0);
        }
        else if(VICTORIA==4) {
            printf("FELICIDADES GANO EL JUGADOR AMARILLo");
            //exit(0);
        }
    }while(VICTORIA==0);

    return 0;
}