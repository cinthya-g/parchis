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
void Turno(char Player,Board *Tablero);

void displayOpcionesDeFichaInicio(char Player,Board *Tablero); //Imprime las fichas en el tablero, esta funcion es un referencia para el usuario en la terminal
Ficha *fichaElecta(int fichaInput,char playerFichaUsuario,char Player,Board *Tablero,int hayFichasEnInicio,int Tiro);
void movimientoFicha(int Dado,Ficha *ficha,Board *Tablero,char Player);
int valorDado1(Dados dados);
int valorDado2(Dados dados);
void movimientoFichaDelInicio(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player);
void comer(Casilla *casillaComida,int cualCasilla,Board *Tablero,char Player,Ficha * fichaquecomio);
int Revisarbarreras(Board* Tablero,Ficha *fichaAMover,int tiro);
int revisarVictoria(Board *Tablero);
void hacerTiempo();
int estaraLlenaLaCasillaDeSalida(Board*Tablero,char Player);
void regresarFichaInvalidaAInicio(Board*Tablero,Ficha*ficha,char Player);
void pruebaDeBarreras(Board* Tablero);
Ficha* validacionDeFichaElecta(Board*tablero,int tiro,char Player);
void pruebaDeComer(Board*Tablero);
Ficha *revisarVicLap(Board*tablero,int tiro,char Player,int FichaAMover);
int hayFichasEnVicLap(Board*tablero,char Player);//Funcion que revisa cuantas fichas existen en VicLap.
void pruebaDeVicLap(Board*Tablero);//Funcion que crea un escenario para revisar el movimiento en VicLap.
void pruebaDeVictoria(Board*Tablero);//Funcion que revisa que el juego termina cuando todas las fichas del usuario llegan al final.



int existeFichaR1EnInicio(Board*Tablero,char Player);
int existeFichaR2EnInicio(Board*Tablero,char Player);
int existeFichaR3EnInicio(Board*Tablero,char Player);
int existeFichaR4EnInicio(Board*Tablero,char Player);
int existeFichaG1EnInicio(Board*Tablero,char Player);
int existeFichaG2EnInicio(Board*Tablero,char Player);
int existeFichaG3EnInicio(Board*Tablero,char Player);
int existeFichaG4EnInicio(Board*Tablero,char Player);
int existeFichaB1EnInicio(Board*Tablero,char Player);
int existeFichaB2EnInicio(Board*Tablero,char Player);
int existeFichaB3EnInicio(Board*Tablero,char Player);
int existeFichaB4EnInicio(Board*Tablero,char Player);
int existeFichaY1EnInicio(Board*Tablero,char Player);
int existeFichaY2EnInicio(Board*Tablero,char Player);
int existeFichaY3EnInicio(Board*Tablero,char Player);
int existeFichaY4EnInicio(Board*Tablero,char Player);

int existeFichaR1EnEnd(Board*Tablero);
int existeFichaR2EnEnd(Board*Tablero);
int existeFichaR3EnEnd(Board*Tablero);
int existeFichaR4EnEnd(Board*Tablero);
int existeFichaG1EnEnd(Board*Tablero);
int existeFichaG2EnEnd(Board*Tablero);
int existeFichaG3EnEnd(Board*Tablero);
int existeFichaG4EnEnd(Board*Tablero);
int existeFichaB1EnEnd(Board*Tablero);
int existeFichaB2EnEnd(Board*Tablero);
int existeFichaB3EnEnd(Board*Tablero);
int existeFichaB4EnEnd(Board*Tablero);
int existeFichaY1EnEnd(Board*Tablero);
int existeFichaY2EnEnd(Board*Tablero);
int existeFichaY3EnEnd(Board*Tablero);
int existeFichaY4EnEnd(Board*Tablero);

int hayFichasEnInicio(Board* Tablero, char Player);



#endif //PARCHIS_TURNOS_H
