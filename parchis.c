#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>
#include "parchis.h"

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

//----------------------------------------------------------------------------
int numPlayers(){
    int p;
    do{
        p = GetKeyPressed();
    }while(p<0 || p>4);
    return p;
}


//----------------------------------------------------------------------------



//Crea un tablero con la casilla 1 implementada
Board *newBoard(){
    Board *juego = malloc(sizeof(Board));
    juego->inicio=malloc(sizeof(Casilla));
    juego->inicio->NumCasilla = 1;
    juego->inicio->BanSafe = 1;
    juego->inicio->BanSalida = 'R';
    juego->inicio->ficha1 = NULL;
    juego->inicio->ficha2 = NULL;

    juego->inicio->next = NULL;

    return juego;
}

//Añade 67 casillas restantes al tablero
void finishBoard(Board* juego, int contador)
{
    Casilla *focusNodeFirst = juego->inicio;
    while(focusNodeFirst->next != NULL){
        focusNodeFirst = focusNodeFirst->next;
    }

    focusNodeFirst->next = malloc(sizeof(Casilla));
    Casilla *focusNode = focusNodeFirst->next;

    focusNode->NumCasilla = contador;

    //---------------------Se Puede Comer?---------------------------------------

    //Asignamos las casillas en donde se puede comer (0) y donde no (1)
    if(focusNode->NumCasilla==1||focusNode->NumCasilla==8||focusNode->NumCasilla==13||focusNode->NumCasilla==18
    ||focusNode->NumCasilla==25||focusNode->NumCasilla==30||focusNode->NumCasilla==35||focusNode->NumCasilla==42
    ||focusNode->NumCasilla==47||focusNode->NumCasilla==52||focusNode->NumCasilla==59||focusNode->NumCasilla==64)
    {
        focusNode->BanSafe = 1;
    }
    else
        focusNode->BanSafe = 0;

    //----------------------------------------------------------------------------

    //---------------------------Es salida?---------------------------------------

    //Asignamos a las casillas correspondientes la bandera de si son la salida de que jugador son
    if(focusNode->NumCasilla==1||focusNode->NumCasilla==18||focusNode->NumCasilla==35||focusNode->NumCasilla==52)
    {
        if (focusNode->NumCasilla==1){
            focusNode->BanSalida = 'R';
        } else if (focusNode->NumCasilla==18){
            focusNode->BanSalida = 'G';
        } else if(focusNode->NumCasilla==35){
            focusNode->BanSalida = 'Y';
        } else if(focusNode->NumCasilla==52){
            focusNode->BanSalida = 'B';
        }
    }
    else
        focusNode->BanSalida = '0';
    //----------------------------------------------------------------------------
    //------------Asigna como nulos los dos espacios de cada casilla -------------
    focusNode->ficha1=NULL;
    focusNode->ficha2=NULL;

    focusNode->next = NULL;
}

//Añade los espacios de inicio donde se almacenan las 4 fichas de salida de cada color
void beginning(Board* juego)
{
    //-----------------------------Casillas de Inicio-------------------------------------

    //---------------------------Posiciones iniciales RED---------------------------
    juego->baseR=malloc(sizeof(Base));
    juego->baseR->NumCasilla=0;
    juego->baseR->Player='R';
    juego->baseR->ficha1=malloc(sizeof(Ficha));
    juego->baseR->ficha2=malloc(sizeof(Ficha));
    juego->baseR->ficha3=malloc(sizeof(Ficha));
    juego->baseR->ficha4=malloc(sizeof(Ficha));
    juego->baseR->ficha1->Path=0;
    juego->baseR->ficha1->Player = 'R';
    juego->baseR->ficha2->Path=0;
    juego->baseR->ficha2->Player = 'R';
    juego->baseR->ficha3->Path=0;
    juego->baseR->ficha3->Player = 'R';
    juego->baseR->ficha4->Path=0;
    juego->baseR->ficha4->Player = 'R';
    juego->baseR->ficha1->Id=1;
    juego->baseR->ficha2->Id=2;
    juego->baseR->ficha3->Id=3;
    juego->baseR->ficha4->Id=4;

    //---------------------------Posiciones iniciales BLUE-----------------------
    juego->baseB=malloc(sizeof(Base));
    juego->baseB->NumCasilla=0;
    juego->baseB->Player='B';
    juego->baseB->ficha1=malloc(sizeof(Ficha));
    juego->baseB->ficha2=malloc(sizeof(Ficha));
    juego->baseB->ficha3=malloc(sizeof(Ficha));
    juego->baseB->ficha4=malloc(sizeof(Ficha));
    juego->baseB->ficha1->Path=0;
    juego->baseB->ficha1->Player = 'B';
    juego->baseB->ficha2->Path=0;
    juego->baseB->ficha2->Player = 'B';
    juego->baseB->ficha3->Path=0;
    juego->baseB->ficha3->Player = 'B';
    juego->baseB->ficha4->Path=0;
    juego->baseB->ficha4->Player = 'B';
    juego->baseB->ficha1->Id=1;
    juego->baseB->ficha2->Id=2;
    juego->baseB->ficha3->Id=3;
    juego->baseB->ficha4->Id=4;

    //---------------------------Posiciones iniciales GREEN-------------------
    juego->baseG=malloc(sizeof(Base));
    juego->baseG->NumCasilla=0;
    juego->baseG->Player='G';
    juego->baseG->ficha1=malloc(sizeof(Ficha));
    juego->baseG->ficha2=malloc(sizeof(Ficha));
    juego->baseG->ficha3=malloc(sizeof(Ficha));
    juego->baseG->ficha4=malloc(sizeof(Ficha));
    juego->baseG->ficha1->Path=0;
    juego->baseG->ficha1->Player = 'G';
    juego->baseG->ficha2->Path=0;
    juego->baseG->ficha2->Player = 'G';
    juego->baseG->ficha3->Path=0;
    juego->baseG->ficha3->Player = 'G';
    juego->baseG->ficha4->Path=0;
    juego->baseG->ficha4->Player = 'G';
    juego->baseG->ficha1->Id=1;
    juego->baseG->ficha2->Id=2;
    juego->baseG->ficha3->Id=3;
    juego->baseG->ficha4->Id=4;

    //---------------------------Posiciones iniciales YELLOW-------------------
    juego->baseY=malloc(sizeof(Base));
    juego->baseY->NumCasilla=0;
    juego->baseY->Player='Y';
    juego->baseY->ficha1=malloc(sizeof(Ficha));
    juego->baseY->ficha2=malloc(sizeof(Ficha));
    juego->baseY->ficha3=malloc(sizeof(Ficha));
    juego->baseY->ficha4=malloc(sizeof(Ficha));
    juego->baseY->ficha1->Path=0;
    juego->baseY->ficha1->Player = 'Y';
    juego->baseY->ficha2->Path=0;
    juego->baseY->ficha2->Player = 'Y';
    juego->baseY->ficha3->Path=0;
    juego->baseY->ficha3->Player = 'Y';
    juego->baseY->ficha4->Path=0;
    juego->baseY->ficha4->Player = 'Y';
    juego->baseY->ficha1->Id=1;
    juego->baseY->ficha2->Id=2;
    juego->baseY->ficha3->Id=3;
    juego->baseY->ficha4->Id=4;

}

//----------------Creacion de 4 listas para recorrido ganador de cada color-------------------
void emptyEnding(Board *juego, char Player)
{
    if(Player == 'R'){
        juego->winR = malloc(sizeof(CasVicLap));
        juego->winR->NumCasilla = 101;
        juego->winR->Player = 'R';
        juego->winR->ficha1 = NULL; juego->winR->ficha2 = NULL;
        juego->winR->next = NULL;
        juego->winR->end = NULL;
    }

    if(Player == 'G'){
        juego->winG = malloc(sizeof(CasVicLap));
        juego->winG->NumCasilla = 101;
        juego->winG->Player = 'G';
        juego->winG->ficha1 = NULL; juego->winG->ficha2 = NULL;
        juego->winG->next = NULL;
        juego->winG->end = NULL;
    }
    if(Player == 'B'){
        juego->winB = malloc(sizeof(CasVicLap));
        juego->winB->NumCasilla = 101;
        juego->winB->Player = 'B';
        juego->winB->ficha1 = NULL; juego->winB->ficha2 = NULL;
        juego->winB->next = NULL;
        juego->winB->end = NULL;
    }
    if(Player == 'Y'){
        juego->winY = malloc(sizeof(CasVicLap));
        juego->winY->NumCasilla = 101;
        juego->winY->Player = 'Y';
        juego->winY->ficha1 = NULL; juego->winY->ficha2 = NULL;
        juego->winY->next = NULL;
        juego->winY->end = NULL;
    }
}

//Añade las otras 6 casillas al recorrido ganador de cada color
void finishEnding(Board* juego, int contador,char Player)
{
    CasVicLap *recorridoFinalFirst;
    if(Player == 'R')
        recorridoFinalFirst = juego->winR;
    if(Player == 'G')
        recorridoFinalFirst = juego->winG;
    if(Player == 'B')
        recorridoFinalFirst = juego->winB;
    if(Player == 'Y')
        recorridoFinalFirst = juego->winY;

    while(recorridoFinalFirst->next != NULL)
    {
        recorridoFinalFirst = recorridoFinalFirst->next;
    }

    recorridoFinalFirst->next = malloc(sizeof(CasVicLap));
    CasVicLap *recorridoFinal = recorridoFinalFirst->next;

    recorridoFinal->NumCasilla = contador;
    recorridoFinal->Player = Player;
    recorridoFinal->ficha1 = NULL;
    recorridoFinal->ficha2 = NULL;

    recorridoFinal->next = NULL;
}

//Creacion de casillas de gane de cada color
void ending(Board* juego)
{
    Final *finalR = juego->winR->end;
    finalR = malloc(sizeof(Final));
    finalR->Player = 'R';
    finalR->NumCasilla = 108;
    finalR->ficha1 = NULL; finalR->ficha2 = NULL;
    finalR->ficha3 = NULL; finalR->ficha4 = NULL;
    //printf("Jugador: %c\n Numero de Casilla: %d\n",finalR->Player,finalR->NumCasilla);
    juego->winR->end=finalR;

    Final *finalB = juego->winB->end;
    finalB = malloc(sizeof(Final));
    finalB->Player = 'B';
    finalB->NumCasilla = 108;
    finalB->ficha1 = NULL; finalB->ficha2 = NULL;
    finalB->ficha3 = NULL; finalB->ficha4 = NULL;
    //printf("Jugador: %c\n Numero de Casilla: %d\n",finalB->Player,finalB->NumCasilla);
    juego->winB->end=finalB;

    Final *finalG = juego->winG->end;
    finalG = malloc(sizeof(Final));
    finalG->Player = 'G';
    finalG->NumCasilla = 108;
    finalG->ficha1 = NULL; finalG->ficha2 = NULL;
    finalG->ficha3 = NULL; finalG->ficha4 = NULL;
    //printf("Jugador: %c\n Numero de Casilla: %d\n",finalG->Player,finalG->NumCasilla);
    juego->winG->end=finalG;

    Final *finalY = juego->winY->end;
    finalY = malloc(sizeof(Final));
    finalY->Player = 'Y';
    finalY->NumCasilla = 108;
    finalY->ficha1 = NULL; finalY->ficha2 = NULL;
    finalY->ficha3 = NULL; finalY->ficha4 = NULL;
    //printf("Jugador: %c\n Numero de Casilla: %d\n",finalY->Player,finalY->NumCasilla);
    juego->winY->end=finalY;
}

//Crea en su totalidad el tablero
void creacionMaestra(Board *juego)
{
    //Se crean las 68 casillas
    for(int i = 2; i < 69; i++){
        finishBoard(juego, i);
    }
    //Se crean las 4 casillas base de cada color (inicio)
    beginning(juego);

    //Crea recorrido final de cada color
    emptyEnding(juego, 'R');
    emptyEnding(juego, 'B');
    emptyEnding(juego, 'G');
    emptyEnding(juego, 'Y');

    for(int i = 102;i < 108;i++)
    {
        finishEnding(juego, i,'R');
        finishEnding(juego, i,'B');
        finishEnding(juego, i,'G');
        finishEnding(juego, i,'Y');
    }
    //Se guarda en Board
    juego->winR->end = NULL;
    juego->winG->end = NULL;
    juego->winB->end = NULL;
    juego->winY->end = NULL;

//Crea casillas ganadoras de cada color
    ending(juego);
}

void displayBoard(Board *juego){
    printf("\n#####################  DISPLAY BOARD PERRO  ##############################\n");
    Casilla *focusnode =juego->inicio;
    //ROJO
    printf("Numero de casilla: %d  Jugador: %c\n",
           juego->baseR->NumCasilla, juego->baseR->Player);
    if(juego->baseR->ficha1!=NULL)
        printf("Ficha: %c%d\n",juego->baseR->ficha1->Player,juego->baseR->ficha1->Id);
    if(juego->baseR->ficha2!=NULL)
        printf("Ficha: %c%d\n",juego->baseR->ficha2->Player,juego->baseR->ficha2->Id);
    if(juego->baseR->ficha3!=NULL)
        printf("Ficha: %c%d\n",juego->baseR->ficha3->Player,juego->baseR->ficha3->Id);
    if(juego->baseR->ficha4!=NULL)
        printf("Ficha: %c%d\n",juego->baseR->ficha4->Player,juego->baseR->ficha4->Id);

    //AZUL
    printf("\nNumero de casilla: %d  Jugador: %c\n",
           juego->baseB->NumCasilla, juego->baseB->Player);
    if(juego->baseB->ficha1!=NULL)
        printf("Ficha: %c%d\n",juego->baseB->ficha1->Player,juego->baseB->ficha1->Id);
    if(juego->baseB->ficha2!=NULL)
        printf("Ficha: %c%d\n",juego->baseB->ficha2->Player,juego->baseB->ficha2->Id);
    if(juego->baseB->ficha3!=NULL)
        printf("Ficha: %c%d\n",juego->baseB->ficha3->Player,juego->baseB->ficha3->Id);
    if(juego->baseB->ficha4!=NULL)
        printf("Ficha: %c%d\n",juego->baseB->ficha4->Player,juego->baseB->ficha4->Id);

    //VERDE
    printf("\nNumero de casilla: %d  Jugador: %c\n",
           juego->baseG->NumCasilla, juego->baseG->Player);
    if(juego->baseG->ficha1!=NULL)
        printf("Ficha: %c%d\n",juego->baseG->ficha1->Player,juego->baseG->ficha1->Id);
    if(juego->baseG->ficha2!=NULL)
        printf("Ficha: %c%d\n",juego->baseG->ficha2->Player,juego->baseG->ficha2->Id);
    if(juego->baseG->ficha3!=NULL)
        printf("Ficha: %c%d\n",juego->baseG->ficha3->Player,juego->baseG->ficha3->Id);
    if(juego->baseG->ficha4!=NULL)
        printf("Ficha: %c%d\n",juego->baseG->ficha4->Player,juego->baseG->ficha4->Id);

    //AMARILLO
    printf("\nNumero de casilla: %d  Jugador: %c\n",
           juego->baseY->NumCasilla, juego->baseY->Player);
    if(juego->baseY->ficha1!=NULL)
        printf("Ficha: %c%d\n",juego->baseY->ficha1->Player,juego->baseY->ficha1->Id);
    if(juego->baseY->ficha2!=NULL)
        printf("Ficha: %c%d\n",juego->baseY->ficha2->Player,juego->baseY->ficha2->Id);
    if(juego->baseY->ficha3!=NULL)
        printf("Ficha: %c%d\n",juego->baseY->ficha3->Player,juego->baseY->ficha3->Id);
    if(juego->baseY->ficha4!=NULL)
        printf("Ficha: %c%d\n",juego->baseY->ficha4->Player,juego->baseY->ficha4->Id);

    while(focusnode != NULL)
    {
        printf("Casilla # %d\n",focusnode->NumCasilla);
        printf("La casilla es segura? %d\n",focusnode->BanSafe);
        printf("Es una salida? %c\n",focusnode->BanSalida);
        if(focusnode->ficha1 != NULL)
            printf("SLOT1 [%c%d]\n", focusnode->ficha1->Player, focusnode->ficha1->Id);
        if(focusnode->ficha2 != NULL)
            printf("SLOT2 [%c%d]\n", focusnode->ficha2->Player, focusnode->ficha2->Id);
        if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
            printf("Slots vacios\n");

        printf("\n");

        focusnode=focusnode->next;
    }

    //-----------------RED-------------------------------------------------
    CasVicLap *focusLapR=juego->winR;
    while(focusLapR != NULL)
    {
        printf("R Numero de casillaVL: %d\t Color del player: %c\n",focusLapR->NumCasilla,focusLapR->Player);
        focusLapR=focusLapR->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winR->end->Player,juego->winR->end->NumCasilla);

    printf("\n\n");

    //--------------GREEN------------------------------------------------------
    CasVicLap *focusLapG=juego->winG;
    while(focusLapG != NULL){
        printf("G Numero de casillaVL: %d\t Color del player: %c\n",focusLapG->NumCasilla,focusLapG->Player);
        focusLapG=focusLapG->next;
    }

    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winG->end->Player,juego->winG->end->NumCasilla);
    printf("\n\n");


    //-------------BLUE------------------------------------------------------
    CasVicLap *focusLapB=juego->winB;
    while(focusLapB != NULL){
        printf("B Numero de casillaVL: %d\t Color del player: %c\n",focusLapB->NumCasilla,focusLapB->Player);
        focusLapB=focusLapB->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winB->end->Player,juego->winB->end->NumCasilla);
    printf("\n\n");


    //------------YELLOW----------------------------------------------------------
    CasVicLap *focusLapY=juego->winY;
    while(focusLapY != NULL){
        printf("Y Numero de casillaVL: %d\t Color del player: %c\n",focusLapY->NumCasilla,focusLapY->Player);
        focusLapY=focusLapY->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winY->end->Player,juego->winY->end->NumCasilla);
    printf("\n\n");

}

