#include <stdio.h>

#include "parchis.h"
#include "turnos.h"
#include "graphics.h"

int main(void)
{
    titleScreen();
    consoleColor();

    int VICTORIA = 0;
    int contadorTurnos = 0;
    int jugadores = 0;

    Board *juego = NULL;
    jugadores = cuantosJugadores();

    juego=newBoard();
    creacionMaestra(juego,jugadores);
    displayColorBoard(juego);

    char playerInicial=quienInicia(juego);
    char player = playerInicial;
    do{
        Turno(player, juego);
        hacerTiempo();
        contadorTurnos++;
        displayColorBoard(juego);

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

return 0;
}
