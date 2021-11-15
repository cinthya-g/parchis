//
// Created by cinth on 14/11/2021.
//

#ifndef PARCHIS_PARCHIS_H
#define PARCHIS_PARCHIS_H

typedef struct board Board;
typedef struct dados Dados;
typedef struct casilla Casilla;
typedef struct ficha Ficha;
typedef struct casInicio Base;
typedef struct casEnd Final;


Dados tiroDados();
Board* newboard();
void displayBoard(Board *juego);

#endif //PARCHIS_PARCHIS_H
