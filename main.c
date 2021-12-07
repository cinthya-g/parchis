#include <stdio.h>
#include "parchis.h"
#include "turnos.h"
#include "graphics.h"

/*
 *  - SUPER PARCHIS - IKER Y CINTHYA
 */


int main(void)
{
    titleScreen();
    consoleColor();

    int VICTORIA = 0;
    int contadorTurnos = 0;
    char saveToUse=0;
    Board*juego=NULL;
    Dados Dice;
    int banderaEditor;

    Board *juegonormal=NULL;
    int jugadores = cuantosJugadores();

    //Ciclo para validar la eleccion del usuario para usar el editor de tablero.
    printf("Selecciona 1 para un juego normal, 2 para editar un juego\n");
    do{
        printf(">> ");
        scanf("%d",&banderaEditor);
    }while(banderaEditor<0||banderaEditor>2);
    if(banderaEditor==2)
    {
        juego=iniciarEditor(jugadores);
    }

    else {
        juego = loadGame(juego,jugadores);
        displayColorBoard(juego);
    }

    char playerInicial=quienInicia(juego);
    char player = playerInicial;
    do{
        Dice= tiroDados();
        Turno(player, juego,Dice);
        saveToUse++;
        Savefile(juego,&saveToUse);
        hacerTiempo();
        contadorTurnos++;
        player=cambiarJugador(player,juego);
        VICTORIA=revisarVictoria(juego);
        if(VICTORIA==1) {
            printf("- - - ROJO GANO LA PARTIDA - - -");
        }
        else if(VICTORIA==2) {
            printf("- - - VERDE GANO LA PARTIDA - - -");
        }
        else if(VICTORIA==3) {
            printf("- - - AZUL GANO LA PARTIDA - - -");

        }
        else if(VICTORIA==4) {
                printf("- - - AMARILLO GANO LA PARTIDA - - -");
        }
    }while(VICTORIA==0);

    return 0;
}