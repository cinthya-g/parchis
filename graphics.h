//
// Created by cinth on 01/12/2021.
//

#ifndef PARCHIS_GRAPHICS_H
#define PARCHIS_GRAPHICS_H

#include "turnos.h"
#include "parchis.h"

//---------DISPLAY GRAFICO--------------------------------------------
void mainScreen();
void displayPlayerInTurn(char playerInTurn, Board *juego);
void displayMainDice();
//-------------------------------------------------------------------

//---------POSICIONES CON PIXELES------------------------------------

typedef struct pixelesPosiciones PixelPos;
typedef struct arreglosPosiciones Positions;

//Obtener dados para tablero grafico
PixelPos guardarDadosIniciales(Dados *mainDice);

//Posiciones en pixeles
Positions *initialPositions();

PixelPos *guardarPosicionesIniciales(PixelPos *pos);

//-----------------ROJO-------------------
int obtenerXR1(Positions *pix, Board *juego, char Player);
int obtenerYR1(Positions *pix, Board *juego, char Player);
int obtenerXR2(Positions *pix, Board *juego, char Player);
int obtenerYR2(Positions *pix, Board *juego, char Player);
int obtenerXR3(Positions *pix, Board *juego, char Player);
int obtenerYR3(Positions *pix, Board *juego, char Player);
int obtenerXR4(Positions *pix, Board *juego, char Player);
int obtenerYR4(Positions *pix, Board *juego, char Player);
//---------------AZUL-----------------------
int obtenerXB1(Positions *pix, Board *juego, char Player);
int obtenerYB1(Positions *pix, Board *juego, char Player);
int obtenerXB2(Positions *pix, Board *juego, char Player);
int obtenerYB2(Positions *pix, Board *juego, char Player);
int obtenerXB3(Positions *pix, Board *juego, char Player);
int obtenerYB3(Positions *pix, Board *juego, char Player);
int obtenerXB4(Positions *pix, Board *juego, char Player);
int obtenerYB4(Positions *pix, Board *juego, char Player);
//---------------VERDE------------------------
int obtenerXG1(Positions *pix, Board *juego, char Player);
int obtenerYG1(Positions *pix, Board *juego, char Player);
int obtenerXG2(Positions *pix, Board *juego, char Player);
int obtenerYG2(Positions *pix, Board *juego, char Player);
int obtenerXG3(Positions *pix, Board *juego, char Player);
int obtenerYG3(Positions *pix, Board *juego, char Player);
int obtenerXG4(Positions *pix, Board *juego, char Player);
int obtenerYG4(Positions *pix, Board *juego, char Player);
//------------AMARILLO-------------------------
int obtenerXY1(Positions *pix, Board *juego, char Player);
int obtenerYY1(Positions *pix, Board *juego, char Player);
int obtenerXY2(Positions *pix, Board *juego, char Player);
int obtenerYY2(Positions *pix, Board *juego, char Player);
int obtenerXY3(Positions *pix, Board *juego, char Player);
int obtenerYY3(Positions *pix, Board *juego, char Player);
int obtenerXY4(Positions *pix, Board *juego, char Player);
int obtenerYY4(Positions *pix, Board *juego, char Player);

#endif //PARCHIS_GRAPHICS_H
