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
Ficha *fichaElecta(int fichaInput,char playerFichaUsuario,char Player,Board *Tablero,int hayFichasEnInicio,int Tiro);
void movimientoFicha(int Dado,Ficha *ficha,Board *Tablero,char Player);
int valorDado1(Dados dados);
int valorDado2(Dados dados);
void movimientoFichaDelInicio(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player);
void comer(Casilla *casillaComida,int cualCasilla,Board *Tablero,char Player);
int Revisarbarreras(Board* Tablero,Ficha *fichaAMover,int tiro);
int revisarVictoria(Board *Tablero);
void hacerTiempo();
int estaraLlenaLaCasillaDeSalida(Board*Tablero,char Player);
void regresarFichaInvalidaAInicio(Board*Tablero,Ficha*ficha,char Player);
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

#endif //PARCHIS_TURNOS_H
