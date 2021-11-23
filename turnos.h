//
// Created by cinth on 17/11/2021.
//

#ifndef PARCHIS_TURNOS_H
#define PARCHIS_TURNOS_H


struct dados{
    int die1;
    int die2;
};

struct pixelesPosicion{
    int xR1init; int yR1init;
    int xR2init; int yR2init;
    int xR3init; int yR3init;
    int xR4init; int yR4init;

    int xG1init; int yG1init;
    int xG2init; int yG2init;
    int xG3init; int yG3init;
    int xG4init; int yG4init;

    int xB1init; int yB1init;
    int xB2init; int yB2init;
    int xB3init; int yB3init;
    int xB4init; int yB4init;

    int xY1init; int yY1init;
    int xY2init; int yY2init;
    int xY3init; int yY3init;
    int xY4init; int yY4init;

    int xR1up; int yR1up;
    int xR2up; int yR2up;
    int xR3up; int yR3up;
    int xR4up; int yR4up;

    int xG1up; int yG1up;
    int xG2up; int yG2up;
    int xG3up; int yG3up;
    int xG4up; int yG4up;

    int xB1up; int yB1up;
    int xB2up; int yB2up;
    int xB3up; int yB3up;
    int xB4up; int yB4up;

    int xY1up; int yY1up;
    int xY2up; int yY2up;
    int xY3up; int yY3up;
    int xY4up; int yY4up;
};

typedef struct dados Dados;
typedef struct pixelesPosicion PixelPos;

Dados tiroDados();
char quienInicia();
char cambiarJugador(char Player);
void Turno(char Player,Board *Tablero);
void displayOpcionesDeFichaInicio(char Player,Board *Tablero);
Ficha *fichaElecta(int fichaInput,char Player,Board *Tablero);
void movimientoFicha(Dados *tiro,Ficha *ficha,Board *Tablero,char Player);

//Posiciones en pixeles
void guardarPosicionesIniciales(PixelPos *posiciones);
//-----------------ROJO-------------------
int obtenerXR1(PixelPos *pos);
int obtenerYR1(PixelPos *pos);
int obtenerXR2(PixelPos *pos);
int obtenerYR2(PixelPos *pos);
int obtenerXR3(PixelPos *pos);
int obtenerYR3(PixelPos *pos);
int obtenerXR4(PixelPos *pos);
int obtenerYR4(PixelPos *pos);
//---------------AZUL-----------------------
int obtenerXB1(PixelPos *pos);
int obtenerYB1(PixelPos *pos);
int obtenerXB2(PixelPos *pos);
int obtenerYB2(PixelPos *pos);
int obtenerXB3(PixelPos *pos);
int obtenerYB3(PixelPos *pos);
int obtenerXB4(PixelPos *pos);
int obtenerYB4(PixelPos *pos);
//---------------VERDE------------------------
int obtenerXG1(PixelPos *pos);
int obtenerYG1(PixelPos *pos);
int obtenerXG2(PixelPos *pos);
int obtenerYG2(PixelPos *pos);
int obtenerXG3(PixelPos *pos);
int obtenerYG3(PixelPos *pos);
int obtenerXG4(PixelPos *pos);
int obtenerYG4(PixelPos *pos);
//------------AMARILLO-------------------------
int obtenerXY1(PixelPos *pos);
int obtenerYY1(PixelPos *pos);
int obtenerXY2(PixelPos *pos);
int obtenerYY2(PixelPos *pos);
int obtenerXY3(PixelPos *pos);
int obtenerYY3(PixelPos *pos);
int obtenerXY4(PixelPos *pos);
int obtenerYY4(PixelPos *pos);
//--------------------------------------------------

int updateDado1(Dados *dice);
int updateDado2(Dados *dice);





#endif //PARCHIS_TURNOS_H
