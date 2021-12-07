//
// Created by cinth on 17/11/2021.
//

#ifndef PARCHIS_TURNOS_H
#define PARCHIS_TURNOS_H
#include "parchis.h"

struct dados{
    int die1;
    int die2;
};
typedef struct dados Dados;

int cuantosJugadores();

Dados tiroDados(); //Asigna aleatoriamente un valor a cada uno de los dados|Regresa la estructura de los dos dados.
char quienInicia(); //Determina mediante comparaciones entre tiros aleatorios de los usuarios, cual saco el tiro mas grande, y regresa el jugador que iniciara la partida.
char cambiarJugador(char Player, Board *juego); //Dependiendo del numero de jugadores, hace los cambios de jugador en turno.

/*
 * Turno: Funcion con la logica del turno, recibe el jugador en turno, el tablero y el tiro de dados. En funcion de los dados,
 * saca una ficha del inicio si el tiro es 5, en caso de que no lo sea, permite al usuario elegir el dado que quiere
 * mover y realiza el movimiento pertinente en la ficha que selecciono el usuario.
 */
void Turno(char Player,Board *Tablero,Dados tiro);

//Recibe enter del usuario.
void hacerTiempo();

//Revisa ganador en su Final.
int revisarVictoria(Board *Tablero);

//Llama al editor del juego custom.
void editorDeJuego(Board *tablero);

#endif //PARCHIS_TURNOS_H
