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

//Imprime las 4 fichas en la casilla de inicio
void displayOpcionesDeFichaInicio(char Player,Board *Tablero)
{
    if(Player=='R')
        printf("Selecciona la ficha que quieres mover [%d],[%d],[%d],[%d] \n",Tablero->baseR->ficha1->Id,Tablero->baseR->ficha2->Id,Tablero->baseR->ficha3->Id,Tablero->baseR->ficha4->Id);
    else if(Player=='G')
        printf("Selecciona la ficha que quieres mover [%d],[%d],[%d],[%d] \n",Tablero->baseG->ficha1->Id,Tablero->baseG->ficha2->Id,Tablero->baseG->ficha3->Id,Tablero->baseG->ficha4->Id);
    else if(Player=='B')
        printf("Selecciona la ficha que quieres mover [%d],[%d],[%d],[%d] \n",Tablero->baseB->ficha1->Id,Tablero->baseB->ficha2->Id,Tablero->baseB->ficha3->Id,Tablero->baseB->ficha4->Id);
    else if(Player=='Y')
        printf("Selecciona la ficha que quieres mover [%d],[%d],[%d],[%d] \n",Tablero->baseY->ficha1->Id,Tablero->baseY->ficha2->Id,Tablero->baseY->ficha3->Id,Tablero->baseY->ficha4->Id);
}

//Recibe el NUMERO DE LA CASILLA (Id) DEL USUARIO, su JUGADOR y BOARD
// Te regresa la estructura de la ficha para que la podamos manipular
//Modificar para que cheque si la casilla puede seleccionarse o no*
Ficha *fichaElecta(int fichaInputUsuario,char Player,Board *Tablero)
{
    if(Player=='R')
    {
        if(fichaInputUsuario==Tablero->baseR->ficha1->Id)
            return Tablero->baseR->ficha1;
        else if(fichaInputUsuario==Tablero->baseR->ficha2->Id)
            return Tablero->baseR->ficha2;
        else if(fichaInputUsuario==Tablero->baseR->ficha3->Id)
            return Tablero->baseR->ficha3;
        else if(fichaInputUsuario==Tablero->baseR->ficha4->Id)
            return Tablero->baseR->ficha4;
    }
    else if(Player=='G')
    {
        if(fichaInputUsuario==Tablero->baseG->ficha1->Id)
            return Tablero->baseG->ficha1;
        else if(fichaInputUsuario==Tablero->baseG->ficha2->Id)
            return Tablero->baseG->ficha2;
        else if(fichaInputUsuario==Tablero->baseG->ficha3->Id)
            return Tablero->baseG->ficha3;
        else if(fichaInputUsuario==Tablero->baseG->ficha4->Id)
            return Tablero->baseG->ficha4;
    }
    else if(Player=='B')
    {
        if(fichaInputUsuario==Tablero->baseB->ficha1->Id)
            return Tablero->baseB->ficha1;
        else if(fichaInputUsuario==Tablero->baseB->ficha2->Id)
            return Tablero->baseB->ficha2;
        else if(fichaInputUsuario==Tablero->baseB->ficha3->Id)
            return Tablero->baseB->ficha3;
        else if(fichaInputUsuario==Tablero->baseB->ficha4->Id)
            return Tablero->baseB->ficha4;
    }
    else if(Player=='Y')
    {
        if(fichaInputUsuario==Tablero->baseY->ficha1->Id)
            return Tablero->baseY->ficha1;
        else if(fichaInputUsuario==Tablero->baseY->ficha2->Id)
            return Tablero->baseY->ficha2;
        else if(fichaInputUsuario==Tablero->baseY->ficha3->Id)
            return Tablero->baseY->ficha3;
        else if(fichaInputUsuario==Tablero->baseY->ficha4->Id)
            return Tablero->baseY->ficha4;
    }
}

//¿regresa ficha a manipular?
void Turno(char Player,Board *Tablero)
{
    printf("Es el turno del jugador: %c\n",Player );
    Dados tiro = tiroDados();

    //*IMPORTANTE*
    //ESTO SOLO SIRVE PARA CUANDO LAS FICHAS ESTAN EN 0
    displayOpcionesDeFichaInicio(Player,Tablero);//Desplieg al usuario las fichas que puede mover

    int FichaAMover=0;
    do{
        scanf("%d",&FichaAMover);
    }while(FichaAMover < 0 || FichaAMover > 4);

    Ficha *fichaAManipular=fichaElecta(FichaAMover, Player,Tablero);//Se le asiga a la variable, la ficha que vamos a usar mediante la funcion que regresa la ficha que eligio el usuario en entrada de texto

    printf("Esta deberia de ser la impresion de la ficha que vas a mover: %c%d\n", fichaAManipular->Player,fichaAManipular->Id);

    //Hacer con un contador que no se pueda llamar a la funcion mas de dos veces y que de alguna forma solamente se pueda usar uno de los dados en la segunda corrida
}


void movimientoFicha(Dados *tiro , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player)
{

    printf("Cual dado quieres usar para mover la ficha : \nDado 1: %d\nDado 2: %d\n",tiro->die1,tiro->die2);
    int dadoAUsar;
    scanf("%d",&dadoAUsar);

    //-----------------------------JUGADOR ROJO------------------------------------

    if(Player== 'R')
    {
        if(dadoAUsar==1)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die1;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die1;
            //AQUI VAMOS A ENCESITAR UN FOCUSNOCE PARA ITERAR LOS NODOS DE LA CADENA (Y AGREGAR LA LINEA PARA QUE PASE)
            while(Tablero->inicio!=NULL)
            {

                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path)
                {

                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }

                }

            }
        }

        if(dadoAUsar==2)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die2;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die2;

            while(Tablero->inicio!=NULL)
            {

                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path)
                {

                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }

                }

            }
        }
    }
    //-----------------------------JUGADOR VERDE------------------------------------
    if(Player== 'G')
    {
        if(dadoAUsar==1)
        {


            fichaQueEstamosMoviendo->Path+=tiro->die1;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die1;


            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }

        if(dadoAUsar==2)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die2;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die2;
            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }
    }

    //-----------------------------JUGADOR AMARILLO------------------------------------
    if(Player== 'Y')
    {
        if(dadoAUsar==1)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die1;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die1;
            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path+34)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }
        if(dadoAUsar==2)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die2;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die2;
            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path+34)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }
    }
    //-----------------------------JUGADOR AZUL------------------------------------
    if(Player== 'B')
    {
        if(dadoAUsar==1)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die1;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die1;
            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path+51)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }

        if(dadoAUsar==2)
        {
            fichaQueEstamosMoviendo->Path+=tiro->die2;
            fichaQueEstamosMoviendo->PaGanar+=tiro->die2;
            while(Tablero->inicio!=NULL)
            {
                if(Tablero->inicio->NumCasilla==fichaQueEstamosMoviendo->Path+51)
                {
                    if(Tablero->inicio->ficha1==NULL)
                    {
                        Tablero->inicio->ficha1=fichaQueEstamosMoviendo;
                    }
                    else if(Tablero->inicio->ficha2==NULL)
                    {
                        Tablero->inicio->ficha2=fichaQueEstamosMoviendo;
                    }
                    else
                    {
                        printf("Existe una barrera, el tiro es invalido");
                    }
                }
            }
        }
    }
}

/*

	printf("Cuantas fichas quieres mover?\n [1] o [2]\n");
	int cuantasFichasSeMueven=0;
	scanf("%d",&cuantasFichasSeMueven);

	if(cuantasFichasSeMueven==1)
	{
		int sumTiro=tiro.die1+tiro.die2;
		char FichaAMover[2];
		if(Player=='R'){
		printf("Selecciona la ficha que quieres mover [%s],[%s],[%s],[%s] \n",Tablero->baseR->ficha1->Player,Tablero->baseR->ficha2->Player,Tablero->baseR->ficha3->Player,Tablero->baseR->ficha4->Player);

			for(int i =0;i<2;i++)
			{
				scanf("%c",&FichaAMover[i]);
			}
			//Aqui ya se escogio la ficha a mover, por ahora solo puede moverse con la suma de los dados y no hay restricciones

			//Se actualiza el path
			if(FichaAMover==Tablero->baseR->ficha1->Player){
				Tablero->baseR->ficha1->Path=Tablero->baseR->ficha1->Path+sumTiro;
			}
			else if(FichaAMover==Tablero->baseR->ficha2->Player){
				Tablero->baseR->ficha2->Path=Tablero->baseR->ficha2->Path+sumTiro;
			}
			else if(FichaAMover==Tablero->baseR->ficha3->Player){
				Tablero->baseR->ficha3->Path=Tablero->baseR->ficha3->Path+sumTiro;
			}
			else if(FichaAMover==Tablero->baseR->ficha4->Player){
				Tablero->baseR->ficha4->Path=Tablero->baseR->ficha4->Path+sumTiro;
			}
			int teEncontre=0;
			Casilla *focusnode =Tablero->inicio;
			Ficha *basura;
			while(focusnode->next!=NULL&&teEncontre==0)
			{
				if(focusnode->NumCasilla==Tablero->baseR->ficha1->Path)
				{
					focusnode->ficha1=Tablero->baseR->ficha1;
					Tablero->baseR->ficha1=NULL;
					teEncontre=1;
				}
				focusnode=focusnode->next;
			}
	}
		}
		else if(Player=='G')
		printf("Selecciona la ficha que quieres mover [%s],[%s],[%s],[%s] \n",Tablero->baseG->ficha1->Player,Tablero->baseG->ficha2->Player,Tablero->baseG->ficha3->Player,Tablero->baseG->ficha4->Player);
		else if(Player=='B')
		printf("Selecciona la ficha que quieres mover [%s],[%s],[%s],[%s] \n",Tablero->baseB->ficha1->Player,Tablero->baseB->ficha2->Player,Tablero->baseB->ficha3->Player,Tablero->baseB->ficha4->Player);
		else if(Player=='Y')
		printf("Selecciona la ficha que quieres mover [%s],[%s],[%s],[%s] \n",Tablero->baseY->ficha1->Player,Tablero->baseY->ficha2->Player,Tablero->baseY->ficha3->Player,Tablero->baseY->ficha4->Player);


  */