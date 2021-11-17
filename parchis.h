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
typedef struct casVicLap CasVicLap;


typedef struct board Board;
typedef struct dados Dados;
typedef struct casilla Casilla;
typedef struct ficha Ficha;
typedef struct casInicio Base;
typedef struct casEnd Final;
typedef struct casVicLap CasVicLap;

Dados tiroDados();

Board* newBoard();
void finishBoard(Board* juego, int contador);
void beginning(Board* juego);
void ending(Board* juego);
CasVicLap* emptyEnding(char Player);
//CasVicLap* emptyEndingG();
//CasVicLap* emptyEndingB();
//CasVicLap* emptyEndingY();
void finishEnding(CasVicLap* recorridoFinal,int contador,char Player);
void creacionMaestraALV(Board* juego);
void Turno();

void displayBoard(Board *juego);


#endif //PARCHIS_PARCHIS_H
