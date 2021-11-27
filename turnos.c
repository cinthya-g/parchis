#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "parchis.h"
#include "turnos.h"

struct ficha{
    char Player;//Determina el color del jugador (b, y, r, g)
    char Path;//Path es un acumulador de el progreso de la ficha
    int Id;
    int PaGanar;
};
struct casilla{
    int NumCasilla;//Indica el numero de la casilla | nuemros siempre entre 1-68
    char BanSafe;//Indica si es una casilla donde se pueda comer
    char BanSalida;//Indica si la casilla es una salida para alguno de los jugadores (R, B, Y, G)
    struct ficha *ficha1;//Almacena una ficha
    struct ficha *ficha2;//Almacena una ficha
    struct casilla *next;//Hace referencia a la siguiente casilla
};
struct casVicLap{
    char Player;
    int NumCasilla;//Inicia en 101 y termina en 107
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct casVicLap *next;
    struct casEnd *end;
};
struct casEnd{
    char Player;
    int NumCasilla;//Numero siempre es 108
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct ficha *ficha3;
    struct ficha *ficha4;
};
struct casInicio{
    char Player;
    char NumCasilla;//Numero siempre es 0
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct ficha *ficha3;
    struct ficha *ficha4;
};
struct board{
    char currentPlayer;

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
void guardarPosicionesIniciales(PixelPos *pos){
    pos->xR1init = 48; pos->yR1init = 575;
    pos->xR2init = 88; pos->yR2init = 575;
    pos->xR3init = 48; pos->yR3init = 615;
    pos->xR4init = 88; pos->yR4init = 615;

    pos->xG1init = 448; pos->yG1init = 575;
    pos->xG2init = 488; pos->yG2init = 575;
    pos->xG3init = 448; pos->yG3init = 615;
    pos->xG4init = 488; pos->yG4init = 615;

    pos->xY1init = 848; pos->yY1init = 575;
    pos->xY2init = 888; pos->yY2init = 575;
    pos->xY3init = 848; pos->yY3init = 615;
    pos->xY4init = 888; pos->yY4init = 615;

    pos->xB1init = 1240; pos->yB1init = 575;
    pos->xB2init = 1280; pos->yB2init = 575;
    pos->xB3init = 1240; pos->yB3init = 615;
    pos->xB4init = 1280; pos->yB4init = 615;

    pos->xR1up=0; pos->xR2up=0; pos->xR2up=0; pos->xR2up=0;
    pos->yR1up=0; pos->yR2up=0; pos->yR2up=0; pos->yR2up=0;

    pos->xG1up=0; pos->xG2up=0; pos->xG2up=0; pos->xG2up=0;
    pos->yG1up=0; pos->yG2up=0; pos->yG2up=0; pos->yG2up=0;

    pos->xY1up=0; pos->xY2up=0; pos->xY2up=0; pos->xY2up=0;
    pos->yY1up=0; pos->yY2up=0; pos->yY2up=0; pos->yY2up=0;

    pos->xB1up=0; pos->xB2up=0; pos->xB2up=0; pos->xB2up=0;
    pos->yB1up=0; pos->yB2up=0; pos->yB2up=0; pos->yB2up=0;
}
//Coordenadas de R1
int obtenerXR1(PixelPos *pos){
    int xR1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xR1 = pos->xR1init;
    return xR1;
}
int obtenerYR1(PixelPos *pos){
    int yR1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yR1 = pos->yR1init;
    return yR1;
}
//Coordenadas de R2
int obtenerXR2(PixelPos *pos){
    int xR2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xR2 = pos->xR2init;
    return xR2;
}
int obtenerYR2(PixelPos *pos){
    int yR2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yR2 = pos->yR2init;
    return yR2;
}
//Coordenadas de R3
int obtenerXR3(PixelPos *pos){
    int xR3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xR3 = pos->xR3init;
    return xR3;
}
int obtenerYR3(PixelPos *pos){
    int yR3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yR3 = pos->yR3init;
    return yR3;
}
//Coordenadas de R4
int obtenerXR4(PixelPos *pos){
    int xR4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xR4 = pos->xR4init;
    return xR4;
}
int obtenerYR4(PixelPos *pos){
    int yR4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yR4 = pos->yR4init;
    return yR4;
}
//Coordenadas de B1
int obtenerXB1(PixelPos *pos){
    int xB1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xB1 = pos->xB1init;
    return xB1;
}
int obtenerYB1(PixelPos *pos){
    int yB1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yB1 = pos->yB1init;
    return yB1;
}
//Coordenadas de B2
int obtenerXB2(PixelPos *pos){
    int xB2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xB2 = pos->xB2init;
    return xB2;
}
int obtenerYB2(PixelPos *pos){
    int yB2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yB2 = pos->yB2init;
    return yB2;
}
//Coordenadas de B3
int obtenerXB3(PixelPos *pos){
    int xB3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xB3 = pos->xB3init;
    return xB3;
}
int obtenerYB3(PixelPos *pos){
    int yB3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yB3 = pos->yB3init;
    return yB3;
}
//Coordenadas de B4
int obtenerXB4(PixelPos *pos){
    int xB4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xB4 = pos->xB4init;
    return xB4;
}
int obtenerYB4(PixelPos *pos){
    int yB4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yB4 = pos->yB4init;
    return yB4;
}
//Coordenadas de G1
int obtenerXG1(PixelPos *pos){
    int xG1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xG1 = pos->xG1init;
    return xG1;
}
int obtenerYG1(PixelPos *pos){
    int yG1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yG1 = pos->yG1init;
    return yG1;
}
//Coordenadas de G2
int obtenerXG2(PixelPos *pos){
    int xG2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xG2 = pos->xG2init;
    return xG2;
}
int obtenerYG2(PixelPos *pos){
    int yG2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yG2 = pos->yG2init;
    return yG2;
}
//Coordenadas de G3
int obtenerXG3(PixelPos *pos){
    int xG3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xG3 = pos->xG3init;
    return xG3;
}
int obtenerYG3(PixelPos *pos){
    int yG3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yG3 = pos->yG3init;
    return yG3;
}
//Coordenadas de G4
int obtenerXG4(PixelPos *pos){
    int xG4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xG4 = pos->xG4init;
    return xG4;
}
int obtenerYG4(PixelPos *pos){
    int yG4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yG4 = pos->yG4init;
    return yG4;
}
//Coordenadas de Y1
int obtenerXY1(PixelPos *pos){
    int xY1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xY1 = pos->xY1init;
    return xY1;
}
int obtenerYY1(PixelPos *pos){
    int yY1=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yY1 = pos->yY1init;
    return yY1;
}
//Coordenadas de Y2
int obtenerXY2(PixelPos *pos){
    int xY2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xY2 = pos->xY2init;
    return xY2;
}
int obtenerYY2(PixelPos *pos){
    int yY2=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yY2 = pos->yY2init;
    return yY2;
}
//Coordenadas de Y3
int obtenerXY3(PixelPos *pos){
    int xY3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xY3 = pos->xY3init;
    return xY3;
}
int obtenerYY3(PixelPos *pos){
    int yY3=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yY3 = pos->yY3init;
    return yY3;
}
//Coordenadas de Y4
int obtenerXY4(PixelPos *pos){
    int xY4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    xY4 = pos->xY4init;
    return xY4;
}
int obtenerYY4(PixelPos *pos){
    int yY4=0;
    //Poner condicion por si se encuentra en salida, mantener en xR1init
    //si no, cambiar a la que se modificó por los dados
    yY4 = pos->yY4init;
    return yY4;
}
//------------------------------------------------------------------------
Dados tiroDados()
{
    Dados Dice={0,0};
    srand(time(NULL));

    Dice.die1 = ( (rand() % 6)+1);
    Dice.die2 = ( (rand() % 6)+1);

    //rintf("%d,%d",Dice.die1,Dice.die2);

    return Dice;
}

char quienInicia()
{
    //Se tiran los dados para cada jugador
    Dados tiroR = tiroDados();
    Dados tiroB = tiroDados();
    Dados tiroG = tiroDados();
    Dados tiroY = tiroDados();

    //Se suman los dados para poder calcular el mas grande
    int SDR= tiroR.die1+tiroR.die2;
    int SDB= tiroB.die1+tiroB.die2;
    int SDG= tiroG.die1+tiroG.die2;
    int SDY= tiroY.die1+tiroY.die2;

    //Valida cual es el dado con el numero mas grande y si son iguales hace reroll
    while(SDR==SDB||SDR==SDG||SDR==SDY||SDB==SDG||SDB==SDY||SDG==SDY)
    {
        if(SDR==SDB||SDR==SDG||SDR==SDY){
            tiroR=tiroDados();
            SDR= tiroR.die1+tiroR.die2;
        }
        if(SDB==SDG||SDB==SDY){
            tiroB=tiroDados();
            SDB=tiroB.die1+tiroB.die2;
        }
        if(SDG==SDY){
            tiroG=tiroDados();
            SDG=tiroG.die1+tiroG.die2;
        }
    }
    //Regresa el Jugador que tuvo la tirada mas grande
    if(SDR>SDB && SDR>SDG && SDR>SDY)
        return 'R';
    if(SDB>SDR && SDB>SDG && SDB>SDY)
        return 'B';
    if(SDG>SDB && SDG>SDR && SDG>SDY)
        return 'G';
    if(SDY>SDB && SDY>SDG && SDY>SDR)
        return 'Y';
}

char cambiarJugador(char Player){
    char jugadorEnTurno[4]={'R','G','Y','B'};
    if(Player == jugadorEnTurno[0])
        Player = jugadorEnTurno[1];
    else if (Player == jugadorEnTurno[1])
        Player = jugadorEnTurno[2];
    else if(Player == jugadorEnTurno[2])
        Player = jugadorEnTurno[3];
    else
        Player = jugadorEnTurno[0];

    return Player;
}
int existeFichaR1EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseR->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR2EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseR->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR3EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseR->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR4EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseR->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG1EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseG->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG2EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseG->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG3EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseG->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG4EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseG->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB1EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseB->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB2EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseB->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB3EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseB->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB4EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseB->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY1EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseY->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY2EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseY->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY3EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseY->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY4EnInicio(Board*Tablero,char Player)
{
    if(Tablero->baseY->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int hayFichasEnInicio(Board* Tablero, char Player)
{
    int cont=0;
    if(Player == 'R')
    {
        if(Tablero->baseR->ficha1 != NULL)
            cont++;
        if(Tablero->baseR->ficha2 != NULL)
            cont++;
        if(Tablero->baseR->ficha3 != NULL)
            cont++;
        if(Tablero->baseR->ficha4 != NULL)
            cont++;

        return cont;
    }

    if(Player == 'G')
    {
        if(Tablero->baseG->ficha1 != NULL)
            cont++;
        if(Tablero->baseG->ficha2 != NULL)
            cont++;
        if(Tablero->baseG->ficha3 != NULL)
            cont++;
        if(Tablero->baseG->ficha4 != NULL)
            cont++;
        return cont;
    }
    if(Player == 'B')
    {
        if(Tablero->baseB->ficha1 != NULL)
            cont++;
        if(Tablero->baseB->ficha2 != NULL)
            cont++;
        if(Tablero->baseB->ficha3 != NULL)
            cont++;
        if(Tablero->baseB->ficha4 != NULL)
            cont++;
        return cont;
    }

    if(Player == 'Y')
    {
        if(Tablero->baseY->ficha1 != NULL)
            cont++;
        if(Tablero->baseY->ficha2 != NULL)
            cont++;
        if(Tablero->baseY->ficha3 != NULL)
            cont++;
        if(Tablero->baseY->ficha4 != NULL)
            cont++;

        return cont;
    }

    return 0;
}
void Turno(char Player,Board *Tablero)
{
    printf("Es el turno del jugador: %c\n",Player );
    Dados tiro = tiroDados();
    int Dado1=valorDado1(tiro);
    int Dado2=valorDado2(tiro);
    Dado1=5;
    Dado2=4;
    int numeroDeMovimientosPorTurno=0;
    int dadoUsado=0;
    int dadoAUsar;
    int sumaDados=Dado1+Dado2;//CUANDO USEMOS ESTA MADRE, TENEMOS QUE SUMARLE DOS AL numeroDeMovimientosPorTurno para que se acaben los movimientos
    while(numeroDeMovimientosPorTurno<2)
    {
        int numeroDeFichasEnInicio=hayFichasEnInicio(Tablero,Player);
        //----------------PARA SACAR DE LA CASILLA INICIAL SI EXISTE UN 5-------------
        if(Dado1==5 && numeroDeFichasEnInicio>0)
        {
            printf("\nDado 1  = 5, sacando ficha de inicio automaticamente.\n");
            printf("Se ha usado el dado 1 para este movimiento.\n");
            dadoUsado=1;
            if(Player=='R')
            {
                int fichaR1EnInicioTrue=existeFichaR1EnInicio(Tablero,Player);
                int fichaR2EnInicioTrue=existeFichaR2EnInicio(Tablero,Player);
                int fichaR3EnInicioTrue=existeFichaR3EnInicio(Tablero,Player);
                int fichaR4EnInicioTrue=existeFichaR4EnInicio(Tablero,Player);


                if(fichaR1EnInicioTrue==1)
                {
                    int fichaDeInicioR1=1;
                    Ficha *fichaR1SaleDeInicio=fichaElecta(fichaDeInicioR1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaR1SaleDeInicio, Tablero, Player);
                }
                else if(fichaR2EnInicioTrue==1)
                {

                    int fichaDeInicioR2=2;
                    Ficha *fichaR2SaleDeInicio=fichaElecta(fichaDeInicioR2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaR2SaleDeInicio, Tablero, Player);
                }
                else if(fichaR3EnInicioTrue==1)
                {
                    int fichaDeInicioR3=3;
                    Ficha *fichaR3SaleDeInicio=fichaElecta(fichaDeInicioR3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaR3SaleDeInicio, Tablero, Player);
                }
                else if(fichaR4EnInicioTrue==1)
                {

                    int fichaDeInicioR4=4;
                    Ficha *fichaR4SaleDeInicio=fichaElecta(fichaDeInicioR4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaR4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='G')
            {
                int fichaG1EnInicioTrue=existeFichaG1EnInicio(Tablero,Player);
                int fichaG2EnInicioTrue=existeFichaG2EnInicio(Tablero,Player);
                int fichaG3EnInicioTrue=existeFichaG3EnInicio(Tablero,Player);
                int fichaG4EnInicioTrue=existeFichaG4EnInicio(Tablero,Player);


                if(fichaG1EnInicioTrue==1)
                {

                    int fichaDeInicioG1=1;
                    Ficha *fichaG1SaleDeInicio=fichaElecta(fichaDeInicioG1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaG1SaleDeInicio, Tablero, Player);
                }
                else if(fichaG2EnInicioTrue==1)
                {
                    int fichaDeInicioG2=2;
                    Ficha *fichaG2SaleDeInicio=fichaElecta(fichaDeInicioG2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaG2SaleDeInicio, Tablero, Player);
                }
                else if(fichaG3EnInicioTrue==1)
                {
                    int fichaDeInicioG3=3;
                    Ficha *fichaG3SaleDeInicio=fichaElecta(fichaDeInicioG3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaG3SaleDeInicio, Tablero, Player);
                }
                else if(fichaG4EnInicioTrue==1)
                {
                    int fichaDeInicioG4=4;
                    Ficha *fichaG4SaleDeInicio=fichaElecta(fichaDeInicioG4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaG4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='B')
            {
                int fichaB1EnInicioTrue=existeFichaB1EnInicio(Tablero,Player);
                int fichaB2EnInicioTrue=existeFichaB2EnInicio(Tablero,Player);
                int fichaB3EnInicioTrue=existeFichaB3EnInicio(Tablero,Player);
                int fichaB4EnInicioTrue=existeFichaB4EnInicio(Tablero,Player);


                if(fichaB1EnInicioTrue==1)
                {
                    int fichaDeInicioB1=1;
                    Ficha *fichaB1SaleDeInicio=fichaElecta(fichaDeInicioB1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaB1SaleDeInicio, Tablero, Player);
                }
                else if(fichaB2EnInicioTrue==1)
                {
                    int fichaDeInicioB2=2;
                    Ficha *fichaB2SaleDeInicio=fichaElecta(fichaDeInicioB2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaB2SaleDeInicio, Tablero, Player);
                }
                else if(fichaB3EnInicioTrue==1)
                {
                    int fichaDeInicioB3=3;
                    Ficha *fichaB3SaleDeInicio=fichaElecta(fichaDeInicioB3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaB3SaleDeInicio, Tablero, Player);
                }
                else if(fichaB4EnInicioTrue==1)
                {
                    int fichaDeInicioB4=4;
                    Ficha *fichaB4SaleDeInicio=fichaElecta(fichaDeInicioB4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaB4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='Y')
            {
                int fichaY1EnInicioTrue=existeFichaY1EnInicio(Tablero,Player);
                int fichaY2EnInicioTrue=existeFichaY2EnInicio(Tablero,Player);
                int fichaY3EnInicioTrue=existeFichaY3EnInicio(Tablero,Player);
                int fichaY4EnInicioTrue=existeFichaY4EnInicio(Tablero,Player);


                if(fichaY1EnInicioTrue==1)
                {
                    int fichaDeInicioY1=1;
                    Ficha *fichaY1SaleDeInicio=fichaElecta(fichaDeInicioY1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaY1SaleDeInicio, Tablero, Player);
                }
                else if(fichaY2EnInicioTrue==1)
                {
                    int fichaDeInicioY2=2;
                    Ficha *fichaY2SaleDeInicio=fichaElecta(fichaDeInicioY2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaY2SaleDeInicio, Tablero, Player);
                }
                else if(fichaY3EnInicioTrue==1)
                {
                    int fichaDeInicioY3=3;
                    Ficha *fichaY3SaleDeInicio=fichaElecta(fichaDeInicioY3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaY3SaleDeInicio, Tablero, Player);
                }
                else if(fichaY4EnInicioTrue==1)
                {
                    int fichaDeInicioY4=4;
                    Ficha *fichaY4SaleDeInicio=fichaElecta(fichaDeInicioY4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado1);
                    movimientoFichaDelInicio(Dado1, fichaY4SaleDeInicio, Tablero, Player);
                }
            }
            Dado1=0;
            numeroDeMovimientosPorTurno++;
        }
        //____________________________________Puede existir un bug aqui por como estan puestos los ifs__________________________________________________
        if(Dado2==5 && numeroDeFichasEnInicio>0)
        {
            printf("\nDado 2  = 5, sacando ficha de inicio automaticamente.");
            printf("Se ha usado el dado 2 para este movimiento.\n");
            dadoUsado=2;
            if(Player=='R')
            {
                int fichaR1EnInicioTrue=existeFichaR1EnInicio(Tablero,Player);
                int fichaR2EnInicioTrue=existeFichaR2EnInicio(Tablero,Player);
                int fichaR3EnInicioTrue=existeFichaR3EnInicio(Tablero,Player);
                int fichaR4EnInicioTrue=existeFichaR4EnInicio(Tablero,Player);


                if(fichaR1EnInicioTrue==1)
                {
                    printf("Se cumplen las condiciones para que saques una ficha del inicio");
                    int fichaDeInicioR1=1;
                    Ficha *fichaR1SaleDeInicio=fichaElecta(fichaDeInicioR1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaR1SaleDeInicio, Tablero, Player);
                }
                else if(fichaR2EnInicioTrue==1)
                {
                    printf("Se cumplen las condiciones para que saques una ficha del inicio");
                    int fichaDeInicioR2=2;
                    Ficha *fichaR2SaleDeInicio=fichaElecta(fichaDeInicioR2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaR2SaleDeInicio, Tablero, Player);
                }
                else if(fichaR3EnInicioTrue==1)
                {
                    printf("Se cumplen las condiciones para que saques una ficha del inicio");
                    int fichaDeInicioR3=3;
                    Ficha *fichaR3SaleDeInicio=fichaElecta(fichaDeInicioR3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaR3SaleDeInicio, Tablero, Player);
                }
                else if(fichaR4EnInicioTrue==1)
                {
                    printf("Se cumplen las condiciones para que saques una ficha del inicio");
                    int fichaDeInicioR4=4;
                    Ficha *fichaR4SaleDeInicio=fichaElecta(fichaDeInicioR4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaR4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='G')
            {
                int fichaG1EnInicioTrue=existeFichaG1EnInicio(Tablero,Player);
                int fichaG2EnInicioTrue=existeFichaG2EnInicio(Tablero,Player);
                int fichaG3EnInicioTrue=existeFichaG3EnInicio(Tablero,Player);
                int fichaG4EnInicioTrue=existeFichaG4EnInicio(Tablero,Player);


                if(fichaG1EnInicioTrue==1)
                {
                    int fichaDeInicioG1=1;
                    Ficha *fichaG1SaleDeInicio=fichaElecta(fichaDeInicioG1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaG1SaleDeInicio, Tablero, Player);
                }
                else if(fichaG2EnInicioTrue==1)
                {
                    int fichaDeInicioG2=2;
                    Ficha *fichaG2SaleDeInicio=fichaElecta(fichaDeInicioG2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaG2SaleDeInicio, Tablero, Player);
                }
                else if(fichaG3EnInicioTrue==1)
                {
                    int fichaDeInicioG3=3;
                    Ficha *fichaG3SaleDeInicio=fichaElecta(fichaDeInicioG3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaG3SaleDeInicio, Tablero, Player);
                }
                else if(fichaG4EnInicioTrue==1)
                {
                    int fichaDeInicioG4=4;
                    Ficha *fichaG4SaleDeInicio=fichaElecta(fichaDeInicioG4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaG4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='B')
            {
                int fichaB1EnInicioTrue=existeFichaB1EnInicio(Tablero,Player);
                int fichaB2EnInicioTrue=existeFichaB2EnInicio(Tablero,Player);
                int fichaB3EnInicioTrue=existeFichaB3EnInicio(Tablero,Player);
                int fichaB4EnInicioTrue=existeFichaB4EnInicio(Tablero,Player);


                if(fichaB1EnInicioTrue==1)
                {
                    int fichaDeInicioB1=1;
                    Ficha *fichaB1SaleDeInicio=fichaElecta(fichaDeInicioB1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaB1SaleDeInicio, Tablero, Player);
                }
                else if(fichaB2EnInicioTrue==1)
                {
                    int fichaDeInicioB2=2;
                    Ficha *fichaB2SaleDeInicio=fichaElecta(fichaDeInicioB2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaB2SaleDeInicio, Tablero, Player);
                }
                else if(fichaB3EnInicioTrue==1)
                {
                    int fichaDeInicioB3=3;
                    Ficha *fichaB3SaleDeInicio=fichaElecta(fichaDeInicioB3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaB3SaleDeInicio, Tablero, Player);
                }
                else if(fichaB4EnInicioTrue==1)
                {
                    int fichaDeInicioB4=4;
                    Ficha *fichaB4SaleDeInicio=fichaElecta(fichaDeInicioB4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaB4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='Y')
            {
                int fichaY1EnInicioTrue=existeFichaY1EnInicio(Tablero,Player);
                int fichaY2EnInicioTrue=existeFichaY2EnInicio(Tablero,Player);
                int fichaY3EnInicioTrue=existeFichaY3EnInicio(Tablero,Player);
                int fichaY4EnInicioTrue=existeFichaY4EnInicio(Tablero,Player);


                if(fichaY1EnInicioTrue==1)
                {
                    int fichaDeInicioY1=1;
                    Ficha *fichaY1SaleDeInicio=fichaElecta(fichaDeInicioY1, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaY1SaleDeInicio, Tablero, Player);
                }
                else if(fichaY2EnInicioTrue==1)
                {
                    int fichaDeInicioY2=2;
                    Ficha *fichaY2SaleDeInicio=fichaElecta(fichaDeInicioY2, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaY2SaleDeInicio, Tablero, Player);
                }
                else if(fichaY3EnInicioTrue==1)
                {
                    int fichaDeInicioY3=3;
                    Ficha *fichaY3SaleDeInicio=fichaElecta(fichaDeInicioY3, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaY3SaleDeInicio, Tablero, Player);
                }
                else if(fichaY4EnInicioTrue==1)
                {
                    int fichaDeInicioY4=4;
                    Ficha *fichaY4SaleDeInicio=fichaElecta(fichaDeInicioY4, Player, Player,Tablero,numeroDeFichasEnInicio,Dado2);
                    movimientoFichaDelInicio(Dado1, fichaY4SaleDeInicio, Tablero, Player);
                }
            }
            Dado2=0;
            numeroDeMovimientosPorTurno++;
        }
        if(sumaDados==5 && numeroDeFichasEnInicio>0)
        {
            printf("\nSuma de dados = 5, sacando ficha de inicio automaticamente.\n");
            printf("Se han usado ambos dados para este movimiento.\n");
            dadoUsado=3;
            if(Player=='R')
            {
                int fichaR1EnInicioTrue=existeFichaR1EnInicio(Tablero,Player);
                int fichaR2EnInicioTrue=existeFichaR2EnInicio(Tablero,Player);
                int fichaR3EnInicioTrue=existeFichaR3EnInicio(Tablero,Player);
                int fichaR4EnInicioTrue=existeFichaR4EnInicio(Tablero,Player);


                if(fichaR1EnInicioTrue==1)
                {
                    int fichaDeInicioR1=1;
                    Ficha *fichaR1SaleDeInicio=fichaElecta(fichaDeInicioR1, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaR1SaleDeInicio, Tablero, Player);
                }
                else if(fichaR2EnInicioTrue==1)
                {
                    int fichaDeInicioR2=2;
                    Ficha *fichaR2SaleDeInicio=fichaElecta(fichaDeInicioR2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaR2SaleDeInicio, Tablero, Player);
                }
                else if(fichaR3EnInicioTrue==1)
                {
                    int fichaDeInicioR3=3;
                    Ficha *fichaR3SaleDeInicio=fichaElecta(fichaDeInicioR3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaR3SaleDeInicio, Tablero, Player);
                }
                else if(fichaR4EnInicioTrue==1)
                {
                    int fichaDeInicioR4=4;
                    Ficha *fichaR4SaleDeInicio=fichaElecta(fichaDeInicioR4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaR4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='G')
            {
                int fichaG1EnInicioTrue=existeFichaG1EnInicio(Tablero,Player);
                int fichaG2EnInicioTrue=existeFichaG2EnInicio(Tablero,Player);
                int fichaG3EnInicioTrue=existeFichaG3EnInicio(Tablero,Player);
                int fichaG4EnInicioTrue=existeFichaG4EnInicio(Tablero,Player);


                if(fichaG1EnInicioTrue==1)
                {
                    int fichaDeInicioG1=1;
                    Ficha *fichaG1SaleDeInicio=fichaElecta(fichaDeInicioG1, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaG1SaleDeInicio, Tablero, Player);
                }
                else if(fichaG2EnInicioTrue==1)
                {
                    int fichaDeInicioG2=2;
                    Ficha *fichaG2SaleDeInicio=fichaElecta(fichaDeInicioG2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaG2SaleDeInicio, Tablero, Player);
                }
                else if(fichaG3EnInicioTrue==1)
                {
                    int fichaDeInicioG3=3;
                    Ficha *fichaG3SaleDeInicio=fichaElecta(fichaDeInicioG3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaG3SaleDeInicio, Tablero, Player);
                }
                else if(fichaG4EnInicioTrue==1)
                {
                    int fichaDeInicioG4=4;
                    Ficha *fichaG4SaleDeInicio=fichaElecta(fichaDeInicioG4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaG4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='B')
            {
                int fichaB1EnInicioTrue=existeFichaB1EnInicio(Tablero,Player);
                int fichaB2EnInicioTrue=existeFichaB2EnInicio(Tablero,Player);
                int fichaB3EnInicioTrue=existeFichaB3EnInicio(Tablero,Player);
                int fichaB4EnInicioTrue=existeFichaB4EnInicio(Tablero,Player);


                if(fichaB1EnInicioTrue==1)
                {
                    int fichaDeInicioB1=1;
                    Ficha *fichaB1SaleDeInicio=fichaElecta(fichaDeInicioB1, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaB1SaleDeInicio, Tablero, Player);
                }
                else if(fichaB2EnInicioTrue==1)
                {
                    int fichaDeInicioB2=2;
                    Ficha *fichaB2SaleDeInicio=fichaElecta(fichaDeInicioB2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaB2SaleDeInicio, Tablero, Player);
                }
                else if(fichaB3EnInicioTrue==1)
                {
                    int fichaDeInicioB3=3;
                    Ficha *fichaB3SaleDeInicio=fichaElecta(fichaDeInicioB3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaB3SaleDeInicio, Tablero, Player);
                }
                else if(fichaB4EnInicioTrue==1)
                {
                    int fichaDeInicioB4=4;
                    Ficha *fichaB4SaleDeInicio=fichaElecta(fichaDeInicioB4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaB4SaleDeInicio, Tablero, Player);
                }
            }
            if(Player=='Y')
            {
                int fichaY1EnInicioTrue=existeFichaY1EnInicio(Tablero,Player);
                int fichaY2EnInicioTrue=existeFichaY2EnInicio(Tablero,Player);
                int fichaY3EnInicioTrue=existeFichaY3EnInicio(Tablero,Player);
                int fichaY4EnInicioTrue=existeFichaY4EnInicio(Tablero,Player);


                if(fichaY1EnInicioTrue==1)
                {
                    int fichaDeInicioY1=1;
                    Ficha *fichaY1SaleDeInicio=fichaElecta(fichaDeInicioY1, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaY1SaleDeInicio, Tablero, Player);
                }
                else if(fichaY2EnInicioTrue==1)
                {
                    int fichaDeInicioY2=2;
                    Ficha *fichaY2SaleDeInicio=fichaElecta(fichaDeInicioY2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaY2SaleDeInicio, Tablero, Player);
                }
                else if(fichaY3EnInicioTrue==1)
                {
                    int fichaDeInicioY3=3;
                    Ficha *fichaY3SaleDeInicio=fichaElecta(fichaDeInicioY3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaY3SaleDeInicio, Tablero, Player);
                }
                else if(fichaY4EnInicioTrue==1)
                {
                    int fichaDeInicioY4=4;
                    Ficha *fichaY4SaleDeInicio=fichaElecta(fichaDeInicioY4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                    movimientoFichaDelInicio(Dado1, fichaY4SaleDeInicio, Tablero, Player);
                }
            }
            numeroDeMovimientosPorTurno=2;
        }
        if(numeroDeMovimientosPorTurno>=2)
            return;
        //-------------------LOGICA PARA ELEGIR DADOS--------------
        numeroDeFichasEnInicio=hayFichasEnInicio(Tablero,Player);
        if(numeroDeFichasEnInicio!=4)
        {


            if(dadoUsado==0)
            {
                do{
                    printf("\nCual dado quieres usar para mover la ficha : \nDado 1: %d\nDado 2: %d\n",Dado1,Dado2);
                    printf("Input:");
                    scanf("%d",&dadoAUsar);
                    if(dadoAUsar < 1 || dadoAUsar > 2)
                        printf("Selecciona un dado valida, entre 1 y 2\n");
                }while(dadoAUsar < 1 || dadoAUsar > 2);

                dadoUsado=dadoAUsar;
            }
            else if(dadoUsado!=0)
            {
                if(dadoUsado==1)
                    dadoAUsar=2;
                else if(dadoUsado==2)
                    dadoAUsar=1;
                else if(dadoUsado==3)
                {
                    return;
                }
            }


            displayOpcionesDeFichaInicio(Player,Tablero);//Desplieg al usuario las fichas que puede mover

            int FichaAMover=0;
            do{
                printf("\nSelecciona una ficha que quieras mover\n");
                printf("Input:");
                scanf("%d",&FichaAMover);
                if(FichaAMover < 0 || FichaAMover > 4)
                    printf("Selecciona una ficha valida, entre 1 y 4\n");
            }while(FichaAMover < 0 || FichaAMover > 4);

            Ficha *fichaAManipular=fichaElecta(FichaAMover,Player, Player,Tablero,numeroDeFichasEnInicio,dadoAUsar);//Se le asiga a la variable, la ficha que vamos a usar mediante la funcion que regresa la ficha que eligio el usuario en entrada de texto

            printf("Esta deberia de ser la impresion de la ficha que vas a mover: %c%d\n",fichaAManipular->Player,fichaAManipular->Id);
            if(dadoAUsar==1)
                movimientoFicha(Dado1, fichaAManipular, Tablero, Player);
            else if(dadoAUsar==2)
                movimientoFicha(Dado2, fichaAManipular, Tablero, Player);
        }
        else
        {
            printf("Lo siento, no sacaste un 5 para sacar una ficha de el tablero, de modo que no puedes hacer movimientos, intenta en la siguiente ronda :)");
            numeroDeMovimientosPorTurno=2;
        }
        numeroDeMovimientosPorTurno++;
    }

}
int valorDado1(Dados dados)
{
    return dados.die1;
}
int valorDado2(Dados dados)
{
    return dados.die2;
}
void displayOpcionesDeFichaInicio(char Player,Board *Tablero)//Imprime las fichas en la casilla de inicio
{
    printf("\nFichas en INICIO:");
    if(Player == 'R'){
        if(Tablero->baseR->ficha1 != NULL)
            printf(" [%c%d]", Tablero->baseR->ficha1->Player, Tablero->baseR->ficha1->Id);
        if(Tablero->baseR->ficha2 != NULL)
            printf(" [%c%d]", Tablero->baseR->ficha2->Player, Tablero->baseR->ficha2->Id);
        if(Tablero->baseR->ficha3 != NULL)
            printf(" [%c%d]", Tablero->baseR->ficha3->Player, Tablero->baseR->ficha3->Id);
        if(Tablero->baseR->ficha4 != NULL)
            printf(" [%c%d]", Tablero->baseR->ficha4->Player, Tablero->baseR->ficha4->Id);
    }

    if(Player == 'G'){
        if(Tablero->baseG->ficha1 != NULL)
            printf(" [%c%d]", Tablero->baseG->ficha1->Player, Tablero->baseG->ficha1->Id);
        if(Tablero->baseG->ficha2 != NULL)
            printf(" [%c%d]", Tablero->baseG->ficha2->Player, Tablero->baseG->ficha2->Id);
        if(Tablero->baseG->ficha3 != NULL)
            printf(" [%c%d]", Tablero->baseG->ficha3->Player, Tablero->baseG->ficha3->Id);
        if(Tablero->baseG->ficha4 != NULL)
            printf(" [%c%d]", Tablero->baseG->ficha4->Player, Tablero->baseG->ficha4->Id);
    }

    if(Player == 'B'){
        if(Tablero->baseB->ficha1 != NULL)
            printf(" [%c%d]", Tablero->baseB->ficha1->Player, Tablero->baseB->ficha1->Id);
        if(Tablero->baseB->ficha2 != NULL)
            printf(" [%c%d]", Tablero->baseB->ficha2->Player, Tablero->baseB->ficha2->Id);
        if(Tablero->baseB->ficha3 != NULL)
            printf(" [%c%d]", Tablero->baseB->ficha3->Player, Tablero->baseB->ficha3->Id);
        if(Tablero->baseB->ficha4 != NULL)
            printf(" [%c%d]", Tablero->baseB->ficha4->Player, Tablero->baseB->ficha4->Id);
    }

    if(Player == 'Y'){
        if(Tablero->baseY->ficha1 != NULL)
            printf(" [%c%d]", Tablero->baseY->ficha1->Player, Tablero->baseY->ficha1->Id);
        if(Tablero->baseY->ficha2 != NULL)
            printf(" [%c%d]", Tablero->baseY->ficha2->Player, Tablero->baseY->ficha2->Id);
        if(Tablero->baseY->ficha3 != NULL)
            printf(" [%c%d]", Tablero->baseY->ficha3->Player, Tablero->baseY->ficha3->Id);
        if(Tablero->baseY->ficha4 != NULL)
            printf(" [%c%d]", Tablero->baseY->ficha4->Player, Tablero->baseY->ficha4->Id);
    }
    printf("\n");

    Casilla *focusnode = Tablero->inicio;
    printf("Fichas en TABLERO:");
    while(focusnode != NULL)
    {
        if(Player == 'R')
        {
            if(focusnode->ficha1 != NULL && focusnode->ficha1->Player == 'R')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha1->Player, focusnode->ficha1->Id, focusnode->NumCasilla);
            if(focusnode->ficha2 != NULL && focusnode->ficha2->Player == 'R')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha2->Player, focusnode->ficha2->Id, focusnode->NumCasilla);
        }

        if(Player == 'G')
        {
            if(focusnode->ficha1 != NULL && focusnode->ficha1->Player == 'G')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha1->Player, focusnode->ficha1->Id, focusnode->NumCasilla);
            if(focusnode->ficha2 != NULL && focusnode->ficha2->Player == 'G')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha2->Player, focusnode->ficha2->Id, focusnode->NumCasilla);
        }

        if(Player == 'B')
        {
            if(focusnode->ficha1 != NULL && focusnode->ficha1->Player == 'B')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha1->Player, focusnode->ficha1->Id, focusnode->NumCasilla);
            if(focusnode->ficha2 != NULL && focusnode->ficha2->Player == 'B')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha2->Player, focusnode->ficha2->Id, focusnode->NumCasilla);
        }

        if(Player == 'Y')
        {
            if(focusnode->ficha1 != NULL && focusnode->ficha1->Player == 'Y')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha1->Player, focusnode->ficha1->Id, focusnode->NumCasilla);
            if(focusnode->ficha2 != NULL && focusnode->ficha2->Player == 'Y')
                printf("\n[%c%d] en Casilla #%d", focusnode->ficha2->Player, focusnode->ficha2->Id, focusnode->NumCasilla);
        }
        focusnode = focusnode->next;
    }
    printf("\n");

    CasVicLap *nodovictoriaR = Tablero->winR;
    CasVicLap *nodovictoriaG = Tablero->winG;
    CasVicLap *nodovictoriaB = Tablero->winB;
    CasVicLap *nodovictoriaY = Tablero->winY;

    printf("Fichas en VICLAP:");

    if(Player == 'R')
    {
        while (nodovictoriaR->next != NULL)
        {
            if (nodovictoriaR->ficha1 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaR->ficha1->Player, nodovictoriaR->ficha1->Id,
                       nodovictoriaR->NumCasilla);
            if (nodovictoriaR->ficha2 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaR->ficha2->Player, nodovictoriaR->ficha2->Id,
                       nodovictoriaR->NumCasilla);
            nodovictoriaR = nodovictoriaR->next;
        }
        if (Tablero->winR->end->ficha1 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winR->end->ficha1->Player, Tablero->winR->end->ficha1->Id);
        if (Tablero->winR->end->ficha2 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winR->end->ficha2->Player, Tablero->winR->end->ficha2->Id);
        if (Tablero->winR->end->ficha3 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winR->end->ficha3->Player, Tablero->winR->end->ficha3->Id);
        if (Tablero->winR->end->ficha4 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winR->end->ficha4->Player, Tablero->winR->end->ficha4->Id);
    }

    if(Player == 'G')
    {
        while(nodovictoriaG->next != NULL)
        {
            if(nodovictoriaG->ficha1 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaG->ficha1->Player, nodovictoriaG->ficha1->Id, nodovictoriaG->NumCasilla);
            if(nodovictoriaG->ficha2 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaG->ficha2->Player, nodovictoriaG->ficha2->Id, nodovictoriaG->NumCasilla);
            nodovictoriaG = nodovictoriaG->next;
        }
        if(Tablero->winG->end->ficha1 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winG->end->ficha1->Player, Tablero->winG->end->ficha1->Id);
        if(Tablero->winG->end->ficha2 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winG->end->ficha2->Player, Tablero->winG->end->ficha2->Id);
        if(Tablero->winG->end->ficha3 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winG->end->ficha3->Player, Tablero->winG->end->ficha3->Id);
        if(Tablero->winG->end->ficha4 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winG->end->ficha4->Player, Tablero->winG->end->ficha4->Id);
    }

    if(Player == 'B')
    {
        while(nodovictoriaB->next != NULL)
        {
            if(nodovictoriaB->ficha1 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaB->ficha1->Player, nodovictoriaB->ficha1->Id, nodovictoriaB->NumCasilla);
            if(nodovictoriaB->ficha2 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaB->ficha2->Player, nodovictoriaB->ficha2->Id, nodovictoriaB->NumCasilla);
            nodovictoriaB = nodovictoriaB->next;
        }
        if(Tablero->winB->end->ficha1 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winB->end->ficha1->Player, Tablero->winB->end->ficha1->Id);
        if(Tablero->winB->end->ficha2 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winB->end->ficha2->Player, Tablero->winB->end->ficha2->Id);
        if(Tablero->winB->end->ficha3 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winB->end->ficha3->Player, Tablero->winB->end->ficha3->Id);
        if(Tablero->winB->end->ficha4 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winB->end->ficha4->Player, Tablero->winB->end->ficha4->Id);
    }

    if(Player == 'Y')
    {
        while(nodovictoriaY->next != NULL)
        {
            if(nodovictoriaY->ficha1 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaY->ficha1->Player, nodovictoriaY->ficha1->Id, nodovictoriaY->NumCasilla);
            if(nodovictoriaY->ficha2 != NULL)
                printf("\n[%c%d] en Casilla #%d", nodovictoriaY->ficha2->Player, nodovictoriaY->ficha2->Id, nodovictoriaY->NumCasilla);
            nodovictoriaY = nodovictoriaY->next;
        }
        if(Tablero->winY->end->ficha1 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winY->end->ficha1->Player, Tablero->winY->end->ficha1->Id);
        if(Tablero->winY->end->ficha2 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winY->end->ficha2->Player, Tablero->winY->end->ficha2->Id);
        if(Tablero->winY->end->ficha3 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winY->end->ficha3->Player, Tablero->winY->end->ficha3->Id);
        if(Tablero->winY->end->ficha4 != NULL)
            printf("\n [%c%d] ganadora", Tablero->winY->end->ficha4->Player, Tablero->winY->end->ficha4->Id);
    }
    printf("\n");

}
Ficha *fichaElecta(int IDfichaInputUsuario,char playerFichaUsuario,char Player,Board *Tablero,int hayFichasEnInicio,int Tiro)//Recibe el input de la ficha que quiere mover el usuario y te regresa la estructura de la ficha para que la podamos manipular
{

    Ficha *fichaderetorno;
    if(hayFichasEnInicio!=0 && Tiro==5)
    {
        if(Player=='R')
        {
            if(Tablero->baseR->ficha1!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha1->Id && playerFichaUsuario==Tablero->baseR->ficha1->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha1;
                    Tablero->baseR->ficha1=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseR->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha2->Id && playerFichaUsuario==Tablero->baseR->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha2;
                    Tablero->baseR->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseR->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha3->Id && playerFichaUsuario==Tablero->baseR->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha3;
                    Tablero->baseR->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseR->ficha4!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha4->Id && playerFichaUsuario==Tablero->baseR->ficha4->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha4;
                    Tablero->baseR->ficha4=NULL;
                    return fichaderetorno;
                }
            }
        }
        else if(Player=='G')
        {
            if(Tablero->baseG->ficha1!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha1->Id && playerFichaUsuario==Tablero->baseG->ficha1->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha1;
                    Tablero->baseG->ficha1=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseG->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha2->Id && playerFichaUsuario==Tablero->baseG->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha2;
                    Tablero->baseG->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseG->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha3->Id && playerFichaUsuario==Tablero->baseG->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha3;
                    Tablero->baseG->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseG->ficha4!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha4->Id && playerFichaUsuario==Tablero->baseG->ficha4->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha4;
                    Tablero->baseG->ficha4=NULL;
                    return fichaderetorno;
                }
            }
        }
        else if(Player=='B')
        {
            if(Tablero->baseB->ficha1!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha1->Id && playerFichaUsuario==Tablero->baseB->ficha1->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha1;
                    Tablero->baseB->ficha1=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseB->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha2->Id && playerFichaUsuario==Tablero->baseB->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha2;
                    Tablero->baseB->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseB->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha3->Id && playerFichaUsuario==Tablero->baseB->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha3;
                    Tablero->baseB->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseB->ficha4!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha4->Id && playerFichaUsuario==Tablero->baseB->ficha4->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha4;
                    Tablero->baseB->ficha4=NULL;
                    return fichaderetorno;
                }
            }
        }
        else if(Player=='Y')
        {
            if(Tablero->baseY->ficha1!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha1->Id && playerFichaUsuario==Tablero->baseY->ficha1->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha1;
                    Tablero->baseY->ficha1=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseY->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha2->Id && playerFichaUsuario==Tablero->baseY->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha2;
                    Tablero->baseY->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseY->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha3->Id && playerFichaUsuario==Tablero->baseY->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha3;
                    Tablero->baseY->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            else if(Tablero->baseY->ficha4!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha4->Id && playerFichaUsuario==Tablero->baseY->ficha4->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha4;
                    Tablero->baseY->ficha4=NULL;
                    return fichaderetorno;
                }
            }
        }
    }
    Casilla * focusnode=Tablero->inicio;
    if(Player=='R')
    {
        while(focusnode!=NULL)
        {
            if(focusnode->ficha1!=NULL)
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
                else if(focusnode->ficha2!=NULL)
                    if(IDfichaInputUsuario==focusnode->ficha2->Id && playerFichaUsuario==focusnode->ficha2->Player)
                    {
                        fichaderetorno=focusnode->ficha2;
                        focusnode->ficha2=NULL;
                        return fichaderetorno;
                    }
            focusnode=focusnode->next;
        }
    }

    else if(Player=='G')
    {
        Casilla * focusnode=Tablero->inicio;
        while(focusnode!=NULL)
        {
            if(focusnode->ficha1!=NULL)
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
                else if(focusnode->ficha2!=NULL)
                    if(IDfichaInputUsuario==focusnode->ficha2->Id && playerFichaUsuario==focusnode->ficha2->Player)
                    {
                        fichaderetorno=focusnode->ficha2;
                        focusnode->ficha2=NULL;
                        return fichaderetorno;
                    }

            focusnode=focusnode->next;
        }
    }
    else if(Player=='B')
    {
        Casilla * focusnode=Tablero->inicio;
        while(focusnode!=NULL)
        {
            if(focusnode->ficha1!=NULL)
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
                else if(focusnode->ficha2!=NULL)
                    if(IDfichaInputUsuario==focusnode->ficha2->Id && playerFichaUsuario==focusnode->ficha2->Player)
                    {
                        fichaderetorno=focusnode->ficha2;
                        focusnode->ficha2=NULL;
                        return fichaderetorno;
                    }

            focusnode=focusnode->next;
        }
    }
    else if(Player=='Y')
    {
        Casilla * focusnode=Tablero->inicio;
        while(focusnode!=NULL)
        {
            if(focusnode->ficha1!=NULL)
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
                else if(focusnode->ficha2!=NULL)
                    if(IDfichaInputUsuario==focusnode->ficha2->Id && playerFichaUsuario==focusnode->ficha2->Player)
                    {
                        fichaderetorno=focusnode->ficha2;
                        focusnode->ficha2=NULL;
                        return fichaderetorno;
                    }

            focusnode=focusnode->next;
        }
    }
}

void movimientoFicha(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player)
{
    Casilla *focusnode=Tablero->inicio;


    //-----------------------------JUGADOR ROJO------------------------------------

    if(Player== 'R')
    {
        int posibilidadDeComer=0;
        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL && focusnode->ficha2==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha1->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=1;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=2;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    break;
                }

            }
            focusnode=focusnode->next;
        }
    }
    //-----------------------------JUGADOR VERDE------------------------------------
    if(Player== 'G')
    {
        int posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=17;

        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;

        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }

        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL && focusnode->ficha2==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha1->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=1;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=2;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    break;
                }

            }
            focusnode=focusnode->next;
        }

    }

    //-----------------------------JUGADOR AMARILLO------------------------------------
    if(Player== 'Y')
    {
        int posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=34;

        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;
        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL && focusnode->ficha2==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha1->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=1;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=2;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    break;
                }

            }
            focusnode=focusnode->next;
        }
    }
    //-----------------------------JUGADOR AZUL------------------------------------
    if(Player== 'B')
    {
        int posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=51;

        fichaQueEstamosMoviendo->Path += dado;
        fichaQueEstamosMoviendo->PaGanar += dado;
        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL && focusnode->ficha2==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha1->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=1;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                }
                else if(focusnode->ficha2->Player!=Player && focusnode->BanSafe==0)
                {
                    posibilidadDeComer=2;
                    comer(focusnode,posibilidadDeComer,Tablero,Player);
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    break;
                }

            }
            focusnode=focusnode->next;
        }
    }
}

void movimientoFichaDelInicio(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player)
{
    Casilla *focusnode=Tablero->inicio;


    //-----------------------------JUGADOR ROJO------------------------------------

    if(Player== 'R')
    {
        int posibilidadDeComer=0;
        fichaQueEstamosMoviendo->Path=1;
        fichaQueEstamosMoviendo->PaGanar=1;
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else
                {
                    if(focusnode->ficha1->Player!=Player)
                    {
                        posibilidadDeComer=1;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha1=fichaQueEstamosMoviendo;
                        break;
                    }
                    else if(focusnode->ficha2->Player!=Player)
                    {
                        posibilidadDeComer=2;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha2=fichaQueEstamosMoviendo;
                        break;
                    }
                    else
                    {
                        printf("Movimiento invalido, no puedes sacar de la casilla de inicio, mueve otra ficha");
                        //VER AQUI COMO LE HACEMOS PARA QUE SE PERMITA OTRO MOVIMIENTO QUE VAYA A SER VALIDO
                    }
                }
            }
            focusnode=focusnode->next;
        }
    }
    //-----------------------------JUGADOR VERDE------------------------------------
    if(Player== 'G')
    {	int posibilidadDeComer=0;
        fichaQueEstamosMoviendo->Path=18;
        fichaQueEstamosMoviendo->PaGanar=1;

        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else
                {
                    if(focusnode->ficha1->Player!=Player)
                    {
                        posibilidadDeComer=1;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha1=fichaQueEstamosMoviendo;
                        break;
                    }
                    else if(focusnode->ficha2->Player!=Player)
                    {
                        posibilidadDeComer=2;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha2=fichaQueEstamosMoviendo;
                        break;
                    }
                    else
                    {
                        printf("Movimiento invalido, no puedes sacar de la casilla de inicio, mueve otra ficha");
                        //VER AQUI COMO LE HACEMOS PARA QUE SE PERMITA OTRO MOVIMIENTO QUE VAYA A SER VALIDO
                    }
                }
            }
            focusnode=focusnode->next;
        }

    }

    //-----------------------------JUGADOR AMARILLO------------------------------------
    if(Player== 'Y')
    {
        int posibilidadDeComer=0;
        fichaQueEstamosMoviendo->Path=35;
        fichaQueEstamosMoviendo->PaGanar=1;

        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2==NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else
                {
                    if(focusnode->ficha1->Player!=Player)
                    {
                        posibilidadDeComer=1;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha1=fichaQueEstamosMoviendo;
                        break;
                    }
                    else if(focusnode->ficha2->Player!=Player)
                    {
                        posibilidadDeComer=2;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha2=fichaQueEstamosMoviendo;
                        break;
                    }
                    else
                    {
                        printf("Movimiento invalido, no puedes sacar de la casilla de inicio, mueve otra ficha");
                        //VER AQUI COMO LE HACEMOS PARA QUE SE PERMITA OTRO MOVIMIENTO QUE VAYA A SER VALIDO
                    }
                }
            }
            focusnode=focusnode->next;
        }
    }
    //-----------------------------JUGADOR AZUL------------------------------------
    if(Player== 'B')
    {
        int posibilidadDeComer=0;
        fichaQueEstamosMoviendo->Path =52;
        fichaQueEstamosMoviendo->PaGanar =1;

        while(focusnode != NULL)
        {
            if(focusnode->NumCasilla == fichaQueEstamosMoviendo->Path)
            {
                if(focusnode->ficha1==NULL)
                {
                    focusnode->ficha1=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else if(focusnode->ficha2 == NULL)
                {
                    focusnode->ficha2=fichaQueEstamosMoviendo;
                    printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                    break;
                }
                else
                {
                    if(focusnode->ficha1->Player!=Player)
                    {
                        posibilidadDeComer=1;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha1=fichaQueEstamosMoviendo;
                        break;
                    }
                    else if(focusnode->ficha2->Player!=Player)
                    {
                        posibilidadDeComer=2;
                        comer(focusnode,posibilidadDeComer,Tablero,Player);
                        focusnode->ficha2=fichaQueEstamosMoviendo;
                        break;
                    }
                    else
                    {
                        printf("Movimiento invalido, no puedes sacar de la casilla de inicio, mueve otra ficha");
                        //VER AQUI COMO LE HACEMOS PARA QUE SE PERMITA OTRO MOVIMIENTO QUE VAYA A SER VALIDO
                    }
                }

            }
            focusnode = focusnode->next;
        }
    }
}

void comer(Casilla *casillaComida,int cualCasilla,Board *Tablero,char Player)
{
    if(cualCasilla==1)
    {
        casillaComida->ficha1->Path=0;
        casillaComida->ficha1->PaGanar=0;
        if(casillaComida->ficha1->Player=='R')
        {
            if(Tablero->baseR->ficha1==NULL)
                Tablero->baseR->ficha1=casillaComida->ficha1;
            if(Tablero->baseR->ficha2==NULL)
                Tablero->baseR->ficha2=casillaComida->ficha1;
            if(Tablero->baseR->ficha3==NULL)
                Tablero->baseR->ficha3=casillaComida->ficha1;
            if(Tablero->baseR->ficha4==NULL)
                Tablero->baseR->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='G')
        {
            if(Tablero->baseG->ficha1==NULL)
                Tablero->baseG->ficha1=casillaComida->ficha1;
            if(Tablero->baseG->ficha2==NULL)
                Tablero->baseG->ficha2=casillaComida->ficha1;
            if(Tablero->baseG->ficha3==NULL)
                Tablero->baseG->ficha3=casillaComida->ficha1;
            if(Tablero->baseG->ficha4==NULL)
                Tablero->baseG->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='B')
        {
            if(Tablero->baseB->ficha1==NULL)
                Tablero->baseB->ficha1=casillaComida->ficha1;
            if(Tablero->baseB->ficha2==NULL)
                Tablero->baseB->ficha2=casillaComida->ficha1;
            if(Tablero->baseB->ficha3==NULL)
                Tablero->baseB->ficha3=casillaComida->ficha1;
            if(Tablero->baseB->ficha4==NULL)
                Tablero->baseB->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='Y')
        {
            if(Tablero->baseY->ficha1==NULL)
                Tablero->baseY->ficha1=casillaComida->ficha1;
            if(Tablero->baseY->ficha2==NULL)
                Tablero->baseY->ficha2=casillaComida->ficha1;
            if(Tablero->baseY->ficha3==NULL)
                Tablero->baseY->ficha3=casillaComida->ficha1;
            if(Tablero->baseY->ficha4==NULL)
                Tablero->baseY->ficha4=casillaComida->ficha1;
        }
    }
    else if(cualCasilla==2)
    {
        casillaComida->ficha2->Path=0;
        casillaComida->ficha2->PaGanar=0;
        if(casillaComida->ficha2->Player=='R')
        {
            if(Tablero->baseR->ficha1==NULL)
                Tablero->baseR->ficha1=casillaComida->ficha2;
            if(Tablero->baseR->ficha2==NULL)
                Tablero->baseR->ficha2=casillaComida->ficha2;
            if(Tablero->baseR->ficha3==NULL)
                Tablero->baseR->ficha3=casillaComida->ficha2;
            if(Tablero->baseR->ficha4==NULL)
                Tablero->baseR->ficha4=casillaComida->ficha2;
        }
        if(casillaComida->ficha2->Player=='G')
        {
            if(Tablero->baseG->ficha1==NULL)
                Tablero->baseG->ficha1=casillaComida->ficha2;
            if(Tablero->baseG->ficha2==NULL)
                Tablero->baseG->ficha2=casillaComida->ficha2;
            if(Tablero->baseG->ficha3==NULL)
                Tablero->baseG->ficha3=casillaComida->ficha2;
            if(Tablero->baseG->ficha4==NULL)
                Tablero->baseG->ficha4=casillaComida->ficha2;
        }
        if(casillaComida->ficha2->Player=='B')
        {
            if(Tablero->baseB->ficha1==NULL)
                Tablero->baseB->ficha1=casillaComida->ficha2;
            if(Tablero->baseB->ficha2==NULL)
                Tablero->baseB->ficha2=casillaComida->ficha2;
            if(Tablero->baseB->ficha3==NULL)
                Tablero->baseB->ficha3=casillaComida->ficha2;
            if(Tablero->baseB->ficha4==NULL)
                Tablero->baseB->ficha4=casillaComida->ficha2;
        }
        if(casillaComida->ficha2->Player=='Y')
        {
            if(Tablero->baseY->ficha1==NULL)
                Tablero->baseY->ficha1=casillaComida->ficha2;
            if(Tablero->baseY->ficha2==NULL)
                Tablero->baseY->ficha2=casillaComida->ficha2;
            if(Tablero->baseY->ficha3==NULL)
                Tablero->baseY->ficha3=casillaComida->ficha2;
            if(Tablero->baseY->ficha4==NULL)
                Tablero->baseY->ficha4=casillaComida->ficha2;
        }
    }
    displayOpcionesDeFichaInicio(Player,Tablero);
    int FichaAMover=0;
    do{
        printf("Input:");
        scanf("%d",&FichaAMover);
        if(FichaAMover < 0 || FichaAMover > 4)
            printf("Selecciona una ficha valida, entre 1 y 4\n");
    }while(FichaAMover < 0 || FichaAMover > 4);

    Ficha *fichaAManipular=fichaElecta(FichaAMover, Player, Player,Tablero,0,20);//Se le asiga a la variable, la ficha que vamos a usar mediante la funcion que regresa la ficha que eligio el usuario en entrada de texto

    printf("Esta deberia de ser la impresion de la ficha que vas a mover: %c%d\n",fichaAManipular->Player,fichaAManipular->Id);
    movimientoFicha(20,fichaAManipular,Tablero,Player);
}