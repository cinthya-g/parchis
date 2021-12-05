//
// Created by cinth on 01/12/2021.
//
#include <stdio.h>
#include <raylib.h>
#include "graphics.h"
#include "turnos.h"
#include "parchis.h"
#include <stdlib.h>

//----------TITULOS Y PANTALLAS--------------------------------------------
void mainScreen()
{
    Color fondoInicio = {14, 119, 153, 1};
    ClearBackground(fondoInicio);
    DrawText("SUPER", 180, 90, 190, WHITE);
    DrawText("PERPENDICULAR", 370, 250, 90, WHITE);
    DrawText("PARCHIS", 480, 325, 190, WHITE);
    DrawText("Presione el número de jugadores", 350, 610, 50, WHITE);
}
void displayPlayerInTurn(char playerInTurn, Board *juego){
    DrawText(TextFormat("TURNO DE %c", playerInTurn), 1190, 35, 30, WHITE);

}
void displayMainDice(int d1, int d2){
    DrawText(TextFormat("D1 [%d]  D2 [%d]", d1, d2), 1230, 780, 50, WHITE);
}

//--------------------------------------------------------------------------


//--------------------POSICIONES FICHAS-----------------------------------

struct arreglosPosiciones{
    int yBOARD[3];
    int xBOARD[69];

    int fijasRED[16];
    int fijasGREEN[16];
    int fijasBLUE[16];
    int fijasYELLOW[16];

};

Positions *initialPositions() {
    Positions *pixels = malloc(sizeof(Positions));

    //---POSICIONES EJE Y DEL TABLERO---
    pixels->yBOARD[0] = 0;
    pixels->yBOARD[1] = 455; //altura slot1
    pixels->yBOARD[2] = 412; //altura slot2

    //---POSICIONES EJE X DEL TABLERO---
    pixels->xBOARD[0] = 0; pixels->xBOARD[1] = 10; pixels->xBOARD[2] = 33; pixels->xBOARD[3] = 56;
    pixels->xBOARD[4] = 79; pixels->xBOARD[5] = 102; pixels->xBOARD[6] = 125; pixels->xBOARD[7] = 148;
    pixels->xBOARD[8] = 171; pixels->xBOARD[9] = 196; pixels->xBOARD[10] = 219; pixels->xBOARD[11] = 242;
    pixels->xBOARD[12] = 266; pixels->xBOARD[13] = 288; pixels->xBOARD[14] = 312; pixels->xBOARD[15] = 335;
    pixels->xBOARD[16] = 359; pixels->xBOARD[17] = 382; pixels->xBOARD[18] = 405; pixels->xBOARD[19] = 428;
    pixels->xBOARD[20] = 452; pixels->xBOARD[21] = 475; pixels->xBOARD[22] = 498; pixels->xBOARD[23] = 522;
    pixels->xBOARD[24] = 546; pixels->xBOARD[25] = 569; pixels->xBOARD[26] = 592; pixels->xBOARD[27] = 615;
    pixels->xBOARD[28] = 638; pixels->xBOARD[29] = 661; pixels->xBOARD[30] = 684; pixels->xBOARD[31] = 707;
    pixels->xBOARD[32] = 730; pixels->xBOARD[33] = 755; pixels->xBOARD[34] = 778; pixels->xBOARD[35] = 801;
    pixels->xBOARD[36] = 824; pixels->xBOARD[37] = 848; pixels->xBOARD[38] = 873; pixels->xBOARD[39] = 896;
    pixels->xBOARD[40] = 919; pixels->xBOARD[41] = 942; pixels->xBOARD[42] = 965; pixels->xBOARD[43] = 988;
    pixels->xBOARD[44] = 1011; pixels->xBOARD[45] = 1034; pixels->xBOARD[46] = 1057; pixels->xBOARD[47] = 1081;
    pixels->xBOARD[48] = 1105; pixels->xBOARD[49] = 1128; pixels->xBOARD[50] = 1152; pixels->xBOARD[51] = 1175;
    pixels->xBOARD[52] = 1198; pixels->xBOARD[53] = 1222; pixels->xBOARD[54] = 1245; pixels->xBOARD[55] = 1268;
    pixels->xBOARD[56] = 1291; pixels->xBOARD[57] = 1314; pixels->xBOARD[58] = 1337; pixels->xBOARD[59] = 1362;
    pixels->xBOARD[60] = 1385; pixels->xBOARD[61] = 1409; pixels->xBOARD[62] = 1432; pixels->xBOARD[63] = 1455;
    pixels->xBOARD[64] = 1478; pixels->xBOARD[65] = 1501; pixels->xBOARD[66] = 1524; pixels->xBOARD[67] = 1547;
    pixels->xBOARD[68] = 1571;

    //---ROJO BASE---
    //------------EJE X -------------------EJE Y--------
    pixels->fijasRED[0] = 48; pixels->fijasRED[1] = 575;
    pixels->fijasRED[2] = 88; pixels->fijasRED[3] = 575;
    pixels->fijasRED[4] = 48; pixels->fijasRED[5] = 615;
    pixels->fijasRED[6] = 88; pixels->fijasRED[7] = 615;
    //---ROJO FINAL---
    pixels->fijasRED[8] = 1495; pixels->fijasRED[9] = 160;
    pixels->fijasRED[10] = 1520; pixels->fijasRED[11] = 160;
    pixels->fijasRED[12] = 1495; pixels->fijasRED[13] = 185;
    pixels->fijasRED[14] = 1520; pixels->fijasRED[15] = 185;
    //---VERDE BASE---
    pixels->fijasGREEN[0] = 448; pixels->fijasGREEN[1] = 575;
    pixels->fijasGREEN[2] = 488; pixels->fijasGREEN[3] = 575;
    pixels->fijasGREEN[4] = 448; pixels->fijasGREEN[5] = 615;
    pixels->fijasGREEN[6] = 488; pixels->fijasGREEN[7] = 615;
    //---VERDE FINAL---
    pixels->fijasGREEN[8] = 305; pixels->fijasGREEN[9] = 160;
    pixels->fijasGREEN[10] = 333; pixels->fijasGREEN[11] = 160;
    pixels->fijasGREEN[12] = 305; pixels->fijasGREEN[13] = 185;
    pixels->fijasGREEN[14] = 333; pixels->fijasGREEN[15] = 185;
    //---AZUL BASE---
    pixels->fijasBLUE[0] = 1240; pixels->fijasBLUE[1] = 575;
    pixels->fijasBLUE[2] = 1280; pixels->fijasBLUE[3] = 575;
    pixels->fijasBLUE[4] = 1240; pixels->fijasBLUE[5] = 615;
    pixels->fijasBLUE[6] = 1280; pixels->fijasBLUE[7] = 615;
    //---AZUL FINAL---
    pixels->fijasBLUE[8] = 1100; pixels->fijasBLUE[9] = 160;
    pixels->fijasBLUE[10] = 1125; pixels->fijasBLUE[11] = 160;
    pixels->fijasBLUE[12] = 1100; pixels->fijasBLUE[13] = 185;
    pixels->fijasBLUE[14] = 1125; pixels->fijasBLUE[15] = 185;
    //---AMARILLO BASE---
    pixels->fijasYELLOW[0] = 848; pixels->fijasYELLOW[1] = 575;
    pixels->fijasYELLOW[2] = 888; pixels->fijasYELLOW[3] = 575;
    pixels->fijasYELLOW[4] = 848; pixels->fijasYELLOW[5] = 615;
    pixels->fijasYELLOW[6] = 888; pixels->fijasYELLOW[7] = 615;
    //---AMARILLO FINAL---
    pixels->fijasYELLOW[8] = 702; pixels->fijasYELLOW[9] = 160;
    pixels->fijasYELLOW[10] = 727; pixels->fijasYELLOW[11] = 160;
    pixels->fijasYELLOW[12] = 702; pixels->fijasYELLOW[13] = 185;
    pixels->fijasYELLOW[14] = 727; pixels->fijasYELLOW[15] = 185;

    return pixels;
}

//Coordenadas de R1
int obtenerXR1(Positions *pix, Board *juego, char Player){

    if(existeFichaR1EnInicio(juego, Player) == 1)
        return pix->fijasRED[0];
    if(existeFichaR1EnEnd(juego) == 1)
        return pix->fijasRED[8];

    return 0;
}
int obtenerYR1(Positions *pix, Board *juego, char Player){

    if(existeFichaR1EnInicio(juego, Player) == 1)
        return pix->fijasRED[1];
    if(existeFichaR1EnEnd(juego) == 1)
        return pix->fijasRED[9];

    return 0;
}

//Coordenadas de R2
int obtenerXR2(Positions *pix, Board *juego, char Player){

    if(existeFichaR2EnInicio(juego, Player) == 1)
        return pix->fijasRED[2];
    if(existeFichaR2EnEnd(juego) == 1)
        return pix->fijasRED[10];

    return 0;
}
int obtenerYR2(Positions *pix, Board *juego, char Player){

    if(existeFichaR2EnInicio(juego, Player) == 1)
        return pix->fijasRED[3];
    if(existeFichaR2EnEnd(juego) == 1)
        return pix->fijasRED[11];

    return 0;
}
//Coordenadas de R3
int obtenerXR3(Positions *pix, Board *juego, char Player){

    if(existeFichaR3EnInicio(juego, Player) == 1)
        return pix->fijasRED[4];
    if(existeFichaR3EnEnd(juego) == 1)
        return pix->fijasRED[12];

    return 0;
}
int obtenerYR3(Positions *pix, Board *juego, char Player){

    if(existeFichaR3EnInicio(juego, Player) == 1)
        return pix->fijasRED[5];
    if(existeFichaR3EnEnd(juego) == 1)
        return pix->fijasRED[13];

    return 0;
}
//Coordenadas de R4
int obtenerXR4(Positions *pix, Board *juego, char Player){

    if(existeFichaR4EnInicio(juego, Player) == 1)
        return pix->fijasRED[6];
    if(existeFichaR4EnEnd(juego) == 1)
        return pix->fijasRED[14];

    return 0;
}
int obtenerYR4(Positions *pix, Board *juego, char Player){
    if(existeFichaR4EnInicio(juego, Player) == 1)
        return pix->fijasRED[7];
    if(existeFichaR4EnEnd(juego) == 1)
        return pix->fijasRED[15];

    return 0;
}

//Coordenadas de B1
int obtenerXB1(Positions *pix, Board *juego, char Player){

    if(existeFichaB1EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[0];
    if(existeFichaB1EnEnd(juego) == 1)
        return pix->fijasBLUE[8];

    return 0;
}
int obtenerYB1(Positions *pix, Board *juego, char Player){
    if(existeFichaB1EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[1];
    if(existeFichaB1EnEnd(juego) == 1)
        return pix->fijasBLUE[9];

    return 0;
}
//Coordenadas de B2
int obtenerXB2(Positions *pix, Board *juego, char Player){
    if(existeFichaB2EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[2];
    if(existeFichaB2EnEnd(juego) == 1)
        return pix->fijasBLUE[10];

    return 0;
}
int obtenerYB2(Positions *pix, Board *juego, char Player){
    if(existeFichaB2EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[3];
    if(existeFichaB2EnEnd(juego) == 1)
        return pix->fijasBLUE[11];

    return 0;
}
//Coordenadas de B3
int obtenerXB3(Positions *pix, Board *juego, char Player){
    if(existeFichaB3EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[4];
    if(existeFichaB3EnEnd(juego) == 1)
        return pix->fijasBLUE[12];

    return 0;
}
int obtenerYB3(Positions *pix, Board *juego, char Player){
    if(existeFichaB3EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[5];
    if(existeFichaB3EnEnd(juego) == 1)
        return pix->fijasBLUE[13];

    return 0;
}
//Coordenadas de B4
int obtenerXB4(Positions *pix, Board *juego, char Player){
    if(existeFichaB4EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[6];
    if(existeFichaB4EnEnd(juego) == 1)
        return pix->fijasBLUE[14];

    return 0;
}
int obtenerYB4(Positions *pix, Board *juego, char Player){
    if(existeFichaB4EnInicio(juego, Player) == 1)
        return pix->fijasBLUE[7];
    if(existeFichaB4EnEnd(juego) == 1)
        return pix->fijasBLUE[15];

    return 0;
}

//Coordenadas de G1
int obtenerXG1(Positions *pix, Board *juego, char Player){
    if(existeFichaG1EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[0];
    if(existeFichaG1EnEnd(juego) == 1)
        return pix->fijasGREEN[8];

    return 0;
}
int obtenerYG1(Positions *pix, Board *juego, char Player){
    if(existeFichaG1EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[1];
    if(existeFichaG1EnEnd(juego) == 1)
        return pix->fijasGREEN[9];

    return 0;
}
//Coordenadas de G2
int obtenerXG2(Positions *pix, Board *juego, char Player){
    if(existeFichaG2EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[2];
    if(existeFichaG2EnEnd(juego) == 1)
        return pix->fijasGREEN[10];

    return 0;
}
int obtenerYG2(Positions *pix, Board *juego, char Player){
    if(existeFichaG2EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[3];
    if(existeFichaG2EnEnd(juego) == 1)
        return pix->fijasGREEN[11];

    return 0;
}
//Coordenadas de G3
int obtenerXG3(Positions *pix, Board *juego, char Player){
    if(existeFichaG3EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[4];
    if(existeFichaG3EnEnd(juego) == 1)
        return pix->fijasGREEN[12];

    return 0;
}
int obtenerYG3(Positions *pix, Board *juego, char Player){
    if(existeFichaG3EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[5];
    if(existeFichaG3EnEnd(juego) == 1)
        return pix->fijasGREEN[13];

    return 0;
}
//Coordenadas de G4
int obtenerXG4(Positions *pix, Board *juego, char Player){
    if(existeFichaG4EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[6];
    if(existeFichaG4EnEnd(juego) == 1)
        return pix->fijasGREEN[14];

    return 0;
}
int obtenerYG4(Positions *pix, Board *juego, char Player){
    if(existeFichaG4EnInicio(juego, Player) == 1)
        return pix->fijasGREEN[7];
    if(existeFichaG4EnEnd(juego) == 1)
        return pix->fijasGREEN[15];

    return 0;
}

//Coordenadas de Y1
int obtenerXY1(Positions *pix, Board *juego, char Player){
    if(existeFichaY1EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[0];
    if(existeFichaY1EnEnd(juego) == 1)
        return pix->fijasYELLOW[8];

    return 0;
}
int obtenerYY1(Positions *pix, Board *juego, char Player){
    if(existeFichaY1EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[1];
    if(existeFichaY1EnEnd(juego) == 1)
        return pix->fijasYELLOW[9];

    return 0;
}
//Coordenadas de Y2
int obtenerXY2(Positions *pix, Board *juego, char Player){
    if(existeFichaY2EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[2];
    if(existeFichaY2EnEnd(juego) == 1)
        return pix->fijasYELLOW[10];

    return 0;
}
int obtenerYY2(Positions *pix, Board *juego, char Player){
    if(existeFichaY2EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[3];
    if(existeFichaY2EnEnd(juego) == 1)
        return pix->fijasYELLOW[11];

    return 0;
}
//Coordenadas de Y3
int obtenerXY3(Positions *pix, Board *juego, char Player){
    if(existeFichaY3EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[4];
    if(existeFichaY3EnEnd(juego) == 1)
        return pix->fijasYELLOW[12];

    return 0;
}
int obtenerYY3(Positions *pix, Board *juego, char Player){
    if(existeFichaY3EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[5];
    if(existeFichaY3EnEnd(juego) == 1)
        return pix->fijasYELLOW[13];

    return 0;
}
//Coordenadas de Y4
int obtenerXY4(Positions *pix, Board *juego, char Player){
    if(existeFichaY4EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[6];
    if(existeFichaY4EnEnd(juego) == 1)
        return pix->fijasYELLOW[14];

    return 0;
}
int obtenerYY4(Positions *pix, Board *juego, char Player){
    if(existeFichaY4EnInicio(juego, Player) == 1)
        return pix->fijasYELLOW[7];
    if(existeFichaY4EnEnd(juego) == 1)
        return pix->fijasYELLOW[15];

    return 0;
}


