//
// Created by cinth on 01/12/2021.
//

#ifndef PARCHIS_GRAPHICS_H
#define PARCHIS_GRAPHICS_H

#include "turnos.h"
#include "parchis.h"

//Enumeracion con variedad de colores de la libreria de Windows.h
enum Colors { BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5,
            BROWN = 6, LGREY = 7, DGREY = 8, LBLUE = 9, LGREEN = 10, LCYAN = 11,
            LRED = 12, LMAGENTA = 13, YELLOW = 14, WHITE = 15};

//Permite inicializar los colores en la consola
void Color(int Background, int Text);

//Le da un color caracteristico al resto de la consola que no sea el tablero
void consoleColor();

/*
 * Despliega el tablero a partir de funciones que se dedican a imprimir aspectos especificos
 * de este.
 */
void displayColorBoard(Board *juego);

//Segun el jugador en turno, cambia el color de la ficha que se mueve en el tablero.
void validarColor(char Player);

//Muestra el título de la pantalla principal.
void titleScreen();


#endif //PARCHIS_GRAPHICS_H
