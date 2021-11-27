//
// Created by cinth on 14/11/2021.
//

#ifndef PARCHIS_PARCHIS_H
#define PARCHIS_PARCHIS_H

typedef struct board Board;

typedef struct casilla Casilla;
typedef struct ficha Ficha;
typedef struct casInicio Base;
typedef struct casEnd Final;
typedef struct casVicLap CasVicLap;


Board* newBoard();
void emptyEnding(Board *juego, char Player);

void finishBoard(Board* juego, int contador);
void beginning(Board* juego);
void ending(Board* juego);
void finishEnding(Board* juego, int contador,char Player);
void creacionMaestra(Board* juego);

void displayBoard(Board *juego);


#endif //PARCHIS_PARCHIS_H
