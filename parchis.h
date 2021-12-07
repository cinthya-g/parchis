//
// Created by cinth on 14/11/2021.
//

#ifndef PARCHIS_PARCHIS_H
#define PARCHIS_PARCHIS_H

struct ficha{
    char Player;//Determina el color del jugador (b, y, r, g)
    char Path;//Path es un acumulador de el progreso de la ficha
    int Id;
    int PaGanar;
};
typedef struct ficha Ficha;

struct casilla{
    int NumCasilla;//Indica el numero de la casilla | nuemros siempre entre 1-68
    char BanSafe;//Indica si es una casilla donde se pueda comer
    char BanSalida;//Indica si la casilla es una salida para alguno de los jugadores (R, B, Y, G)
    struct ficha *ficha1;//Almacena una ficha
    struct ficha *ficha2;//Almacena una ficha
    struct casilla *next;//Hace referencia a la siguiente casilla
};
typedef struct casilla Casilla;

struct casVicLap{
    char Player;
    int NumCasilla;//Inicia en 101 y termina en 107
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct casVicLap *next;
    struct casEnd *end;
};
typedef struct casVicLap CasVicLap;

struct casEnd{
    char Player;
    int NumCasilla;//Numero siempre es 108
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct ficha *ficha3;
    struct ficha *ficha4;
};
typedef struct casEnd Final;

struct casInicio{
    char Player;
    char NumCasilla;//Numero siempre es 0
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct ficha *ficha3;
    struct ficha *ficha4;
};
typedef struct casInicio Base;

struct board{
    int currentPlayers;

    struct casilla *inicio;

    struct casVicLap *winR;
    struct casVicLap *winY;
    struct casVicLap *winB;
    struct casVicLap *winG;

    struct casInicio *baseR;
    struct casInicio *baseY;
    struct casInicio *baseB;
    struct casInicio *baseG;
};
typedef struct board Board;

void Savefile(Board *Tablero,char *Nombre);
Board *loadGame(Board *Tablero,int jugadores);
Board *iniciarEditor(int jugadores);

#endif //PARCHIS_PARCHIS_H
