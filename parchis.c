#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parchis.h"
#include "turnos.h"

//Crea un tablero con la casilla 1 implementada.
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

//Añade 67 casillas restantes al tablero.
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

//Añade los espacios de inicio donde se almacenan las 4 fichas de salida de cada color.
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
    juego->baseR->ficha1->PaGanar = 0;
    juego->baseR->ficha2->PaGanar = 0;
    juego->baseR->ficha3->PaGanar = 0;
    juego->baseR->ficha4->PaGanar = 0;

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
    juego->baseB->ficha1->PaGanar = 0;
    juego->baseB->ficha2->PaGanar = 0;
    juego->baseB->ficha3->PaGanar = 0;
    juego->baseB->ficha4->PaGanar = 0;

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
    juego->baseG->ficha1->PaGanar = 0;
    juego->baseG->ficha2->PaGanar = 0;
    juego->baseG->ficha3->PaGanar = 0;
    juego->baseG->ficha4->PaGanar = 0;

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
    juego->baseY->ficha1->PaGanar = 0;
    juego->baseY->ficha2->PaGanar = 0;
    juego->baseY->ficha3->PaGanar = 0;
    juego->baseY->ficha4->PaGanar = 0;

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

//Añade las otras 6 casillas al recorrido ganador de cada color.
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

//Creacion de casillas de gane de cada color.
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

//Crea en su totalidad el tablero.
void creacionMaestra(Board *juego,int jugadores)
{
    juego->currentPlayers = jugadores;
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
    while(focusLapR!=NULL)
    {
        printf("\nR Numero de casillaVL: %d\t",focusLapR->NumCasilla);
        if(focusLapR->ficha1!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapR->ficha1->Player, focusLapR->ficha1->Id);
        if(focusLapR->ficha2!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapR->ficha1->Player, focusLapR->ficha1->Id);
        if(focusLapR->ficha1==NULL && focusLapR->ficha2==NULL)
            printf("Slots vacios");
        focusLapR=focusLapR->next;
    }
    printf("\nNumero de Casilla: %d\n", juego->winR->end->NumCasilla);
    if(juego->winR->end->ficha1 != NULL)
        printf("[%c%d]", juego->winR->end->ficha1->Player, juego->winR->end->ficha1->Id);
    if(juego->winR->end->ficha2 != NULL)
        printf("  [%c%d]", juego->winR->end->ficha2->Player, juego->winR->end->ficha2->Id);
    if(juego->winR->end->ficha3 != NULL)
        printf("  [%c%d]", juego->winR->end->ficha3->Player, juego->winR->end->ficha3->Id);
    if(juego->winR->end->ficha4 != NULL)
        printf("  [%c%d]", juego->winR->end->ficha4->Player, juego->winR->end->ficha4->Id);

    printf("\n\n");

    //--------------GREEN------------------------------------------------------
    CasVicLap *focusLapG=juego->winG;
    while(focusLapG!=NULL){
        printf("\nG Numero de casillaVL: %d\t",focusLapG->NumCasilla);
        if(focusLapG->ficha1!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapG->ficha1->Player, focusLapG->ficha1->Id);
        if(focusLapG->ficha2!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapG->ficha1->Player, focusLapG->ficha1->Id);
        if(focusLapG->ficha1==NULL && focusLapG->ficha2==NULL)
            printf("Slots vacios");
        focusLapG=focusLapG->next;
    }

    printf("\nNumero de Casilla: %d\n",juego->winG->end->NumCasilla);
    if(juego->winG->end->ficha1 != NULL)
        printf("[%c%d]", juego->winG->end->ficha1->Player, juego->winG->end->ficha1->Id);
    if(juego->winG->end->ficha2 != NULL)
        printf("  [%c%d]", juego->winG->end->ficha2->Player, juego->winG->end->ficha2->Id);
    if(juego->winG->end->ficha3 != NULL)
        printf("  [%c%d]", juego->winG->end->ficha3->Player, juego->winG->end->ficha3->Id);
    if(juego->winG->end->ficha4 != NULL)
        printf("  [%c%d]", juego->winG->end->ficha4->Player, juego->winG->end->ficha4->Id);
    printf("\n\n");


    //-------------BLUE------------------------------------------------------
    CasVicLap *focusLapB=juego->winB;
    while(focusLapB!=NULL){
        printf("\nB Numero de casillaVL: %d\t",focusLapB->NumCasilla);
        if(focusLapB->ficha1!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapB->ficha1->Player, focusLapB->ficha1->Id);
        if(focusLapB->ficha2!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapB->ficha1->Player, focusLapB->ficha1->Id);
        if(focusLapB->ficha1==NULL && focusLapB->ficha2==NULL)
            printf("Slots vacios");
        focusLapB=focusLapB->next;
    }

    printf("\nNumero de Casilla: %d\n",juego->winB->end->NumCasilla);
    if(juego->winB->end->ficha1 != NULL)
        printf("[%c%d]", juego->winB->end->ficha1->Player, juego->winB->end->ficha1->Id);
    if(juego->winB->end->ficha2 != NULL)
        printf("  [%c%d]", juego->winB->end->ficha2->Player, juego->winB->end->ficha2->Id);
    if(juego->winB->end->ficha3 != NULL)
        printf("  [%c%d]", juego->winB->end->ficha3->Player, juego->winB->end->ficha3->Id);
    if(juego->winB->end->ficha4 != NULL)
        printf("  [%c%d]", juego->winB->end->ficha4->Player, juego->winB->end->ficha4->Id);
    printf("\n\n");


    //------------YELLOW----------------------------------------------------------
    CasVicLap *focusLapY=juego->winY;
    while(focusLapY!=NULL){
        printf("\nY Numero de casillaVL: %d\t",focusLapY->NumCasilla);
        if(focusLapY->ficha1!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapY->ficha1->Player, focusLapY->ficha1->Id);
        if(focusLapY->ficha2!=NULL)
            printf("SLOT1 [%c%d]\n", focusLapY->ficha1->Player, focusLapY->ficha1->Id);
        if(focusLapY->ficha1==NULL && focusLapY->ficha2==NULL)
            printf("Slots vacios");
        focusLapY=focusLapY->next;
    }

    printf("\nNumero de Casilla: %d\n",juego->winY->end->NumCasilla);
    if(juego->winY->end->ficha1 != NULL)
        printf("[%c%d]", juego->winY->end->ficha1->Player, juego->winY->end->ficha1->Id);
    if(juego->winY->end->ficha2 != NULL)
        printf("  [%c%d]", juego->winY->end->ficha2->Player, juego->winY->end->ficha2->Id);
    if(juego->winY->end->ficha3 != NULL)
        printf("  [%c%d]", juego->winY->end->ficha3->Player, juego->winY->end->ficha3->Id);
    if(juego->winY->end->ficha4 != NULL)
        printf("  [%c%d]", juego->winY->end->ficha4->Player, juego->winY->end->ficha4->Id);
    printf("\n\n");

}//Funcion para imprimir el tablero completo, asi como las posiciones de las fichas.
void Savefile(Board*Tablero,char *Nombre)
{
    int arregloParaVerSiSeGuardoAlgo[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    FILE* Save=fopen("juegosGuardados\\save.dat","wb+");
    if(Save){
        fwrite(Tablero,sizeof(Board),1,Save);
        fwrite(Tablero->baseR,sizeof(Base),1,Save);
        fwrite(Tablero->baseG,sizeof(Base),1,Save);
        fwrite(Tablero->baseY,sizeof(Base),1,Save);
        fwrite(Tablero->baseB,sizeof(Base),1,Save);
        int i=0;
        if(Tablero->baseR->ficha1!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseR->ficha2!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;
        if(Tablero->baseR->ficha3!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;
        if(Tablero->baseR->ficha4!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;

        if(Tablero->baseG->ficha1!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;
        if(Tablero->baseG->ficha2!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;
        if(Tablero->baseG->ficha3!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;
        if(Tablero->baseG->ficha4!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;

        if(Tablero->baseY->ficha1!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseY->ficha2!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseY->ficha3!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseY->ficha4!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }
        i++;

        if(Tablero->baseB->ficha1!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseB->ficha2!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseB->ficha3!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;
        }
        i++;
        if(Tablero->baseB->ficha4!=NULL) {
            arregloParaVerSiSeGuardoAlgo[i]=1;

        }

        fwrite(arregloParaVerSiSeGuardoAlgo,sizeof(arregloParaVerSiSeGuardoAlgo),1,Save);
        if(Tablero->baseR->ficha1!=NULL)
            fwrite(Tablero->baseR->ficha1,sizeof(Ficha),1,Save);
        if(Tablero->baseR->ficha2!=NULL)
            fwrite(Tablero->baseR->ficha2,sizeof(Ficha),1,Save);
        if(Tablero->baseR->ficha3!=NULL)
            fwrite(Tablero->baseR->ficha3,sizeof(Ficha),1,Save);
        if(Tablero->baseR->ficha4!=NULL)
            fwrite(Tablero->baseR->ficha4,sizeof(Ficha),1,Save);

        if(Tablero->baseG->ficha1!=NULL)
            fwrite(Tablero->baseG->ficha1,sizeof(Ficha),1,Save);
        if(Tablero->baseG->ficha2!=NULL)
            fwrite(Tablero->baseG->ficha2,sizeof(Ficha),1,Save);
        if(Tablero->baseG->ficha3!=NULL)
            fwrite(Tablero->baseG->ficha3,sizeof(Ficha),1,Save);
        if(Tablero->baseG->ficha4!=NULL)
            fwrite(Tablero->baseG->ficha4,sizeof(Ficha),1,Save);

        if(Tablero->baseY->ficha1!=NULL)
            fwrite(Tablero->baseY->ficha1,sizeof(Ficha),1,Save);
        if(Tablero->baseY->ficha2!=NULL)
            fwrite(Tablero->baseY->ficha2,sizeof(Ficha),1,Save);
        if(Tablero->baseY->ficha3!=NULL)
            fwrite(Tablero->baseY->ficha3,sizeof(Ficha),1,Save);
        if(Tablero->baseY->ficha4!=NULL)
            fwrite(Tablero->baseY->ficha4,sizeof(Ficha),1,Save);

        if(Tablero->baseB->ficha1!=NULL)
            fwrite(Tablero->baseB->ficha1,sizeof(Ficha),1,Save);
        if(Tablero->baseB->ficha2!=NULL)
            fwrite(Tablero->baseB->ficha2,sizeof(Ficha),1,Save);
        if(Tablero->baseB->ficha3!=NULL)
            fwrite(Tablero->baseB->ficha3,sizeof(Ficha),1,Save);
        if(Tablero->baseB->ficha4!=NULL)
            fwrite(Tablero->baseB->ficha4,sizeof(Ficha),1,Save);


        int arregloParaSaberDondeHayFichasEnVicLapYEndR[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int j=0;
        CasVicLap *focuslapR=Tablero->winR;
        int banderaR=1;
        while(focuslapR!=NULL)
        {
            if(focuslapR->ficha1!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
            j++;
            if(focuslapR->ficha2!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
            j++;

            if(banderaR==1)
            {
                if(Tablero->winR->end->ficha1!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
                j++;
                if(Tablero->winR->end->ficha2!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
                j++;
                if(Tablero->winR->end->ficha3!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
                j++;
                if(Tablero->winR->end->ficha4!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndR[j]=1;
                j++;
                banderaR=0;
            }
            focuslapR=focuslapR->next;
        }
        fwrite(arregloParaSaberDondeHayFichasEnVicLapYEndR,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndR),1,Save);

        focuslapR=Tablero->winR;
        banderaR=1;
        while(focuslapR!=NULL)
        {
            fwrite(focuslapR,sizeof (CasVicLap),1,Save);
            if(focuslapR->ficha1!=NULL)
                fwrite(focuslapR->ficha1,sizeof(Ficha),1,Save);
            if(focuslapR->ficha2!=NULL)
                fwrite(focuslapR->ficha2,sizeof(Ficha),1,Save);

            if(banderaR==1)
            {
                fwrite(Tablero->winR->end,sizeof(Final),1,Save);
                if(Tablero->winR->end->ficha1!=NULL)
                    fwrite(Tablero->winR->end->ficha1,sizeof(Ficha),1,Save);
                if(Tablero->winR->end->ficha2!=NULL)
                    fwrite(Tablero->winR->end->ficha2,sizeof(Ficha),1,Save);
                if(Tablero->winR->end->ficha3!=NULL)
                    fwrite(Tablero->winR->end->ficha3,sizeof(Ficha),1,Save);
                if(Tablero->winR->end->ficha4!=NULL)
                    fwrite(Tablero->winR->end->ficha4,sizeof(Ficha),1,Save);
                banderaR=0;
            }
            focuslapR=focuslapR->next;
        }
        int arregloParaSaberDondeHayFichasEnVicLapYEndG[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int k=0;
        CasVicLap *focuslapG=Tablero->winG;
        int banderaG=1;
        while(focuslapG!=NULL)
        {
            if(focuslapG->ficha1!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
            j++;
            if(focuslapG->ficha2!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
            j++;

            if(banderaG==1)
            {
                if(Tablero->winG->end->ficha1!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
                j++;
                if(Tablero->winG->end->ficha2!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
                j++;
                if(Tablero->winG->end->ficha3!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
                j++;
                if(Tablero->winG->end->ficha4!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndG[k]=1;
                j++;
                banderaG=0;
            }
            focuslapG=focuslapG->next;
        }
        fwrite(arregloParaSaberDondeHayFichasEnVicLapYEndG,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndG),1,Save);

        focuslapG=Tablero->winG;
        banderaG=1;
        while(focuslapG!=NULL)
        {
            fwrite(focuslapG,sizeof (CasVicLap),1,Save);
            if(focuslapG->ficha1!=NULL)
                fwrite(focuslapG->ficha1,sizeof(Ficha),1,Save);
            if(focuslapG->ficha2!=NULL)
                fwrite(focuslapG->ficha2,sizeof(Ficha),1,Save);

            if(banderaG==1)
            {
                fwrite(Tablero->winG->end,sizeof(Final),1,Save);
                if(Tablero->winG->end->ficha1!=NULL)
                    fwrite(Tablero->winG->end->ficha1,sizeof(Ficha),1,Save);
                if(Tablero->winG->end->ficha2!=NULL)
                    fwrite(Tablero->winG->end->ficha2,sizeof(Ficha),1,Save);
                if(Tablero->winG->end->ficha3!=NULL)
                    fwrite(Tablero->winG->end->ficha3,sizeof(Ficha),1,Save);
                if(Tablero->winG->end->ficha4!=NULL)
                    fwrite(Tablero->winG->end->ficha4,sizeof(Ficha),1,Save);
                banderaG=0;
            }
            focuslapG=focuslapG->next;
        }


        int arregloParaSaberDondeHayFichasEnVicLapYEndY[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int h=0;
        CasVicLap *focuslapY=Tablero->winY;
        int banderaY=1;
        while(focuslapY!=NULL)
        {
            if(focuslapY->ficha1!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
            j++;
            if(focuslapY->ficha2!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
            j++;

            if(banderaY==1)
            {
                if(Tablero->winY->end->ficha1!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
                j++;
                if(Tablero->winY->end->ficha2!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
                j++;
                if(Tablero->winY->end->ficha3!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
                j++;
                if(Tablero->winY->end->ficha4!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndY[h]=1;
                j++;
                banderaY=0;
            }
            focuslapY=focuslapY->next;
        }
        fwrite(arregloParaSaberDondeHayFichasEnVicLapYEndY,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndY),1,Save);



        focuslapY=Tablero->winY;
        banderaY=1;
        while(focuslapY!=NULL)
        {
            fwrite(focuslapY,sizeof (CasVicLap),1,Save);
            if(focuslapY->ficha1!=NULL)
                fwrite(focuslapY->ficha1,sizeof(Ficha),1,Save);
            if(focuslapY->ficha2!=NULL)
                fwrite(focuslapY->ficha2,sizeof(Ficha),1,Save);

            if(banderaY==1)
            {
                fwrite(Tablero->winY->end,sizeof(Final),1,Save);
                if(Tablero->winY->end->ficha1!=NULL)
                    fwrite(Tablero->winY->end->ficha1,sizeof(Ficha),1,Save);
                if(Tablero->winY->end->ficha2!=NULL)
                    fwrite(Tablero->winY->end->ficha2,sizeof(Ficha),1,Save);
                if(Tablero->winY->end->ficha3!=NULL)
                    fwrite(Tablero->winY->end->ficha3,sizeof(Ficha),1,Save);
                if(Tablero->winY->end->ficha4!=NULL)
                    fwrite(Tablero->winY->end->ficha4,sizeof(Ficha),1,Save);
                banderaY=0;
            }
            focuslapY=focuslapY->next;
        }


        int arregloParaSaberDondeHayFichasEnVicLapYEndB[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int l=0;
        CasVicLap *focuslapB=Tablero->winB;
        int banderaB=1;
        while(focuslapB!=NULL)
        {
            if(focuslapB->ficha1!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
            j++;
            if(focuslapB->ficha2!=NULL)
                arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
            j++;

            if(banderaB==1)
            {
                if(Tablero->winB->end->ficha1!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
                j++;
                if(Tablero->winB->end->ficha2!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
                j++;
                if(Tablero->winB->end->ficha3!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
                j++;
                if(Tablero->winB->end->ficha4!=NULL)
                    arregloParaSaberDondeHayFichasEnVicLapYEndB[l]=1;
                j++;
                banderaB=0;
            }
            focuslapB=focuslapB->next;
        }
        fwrite(arregloParaSaberDondeHayFichasEnVicLapYEndB,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndB),1,Save);


        focuslapB=Tablero->winB;
        banderaB=1;
        while(focuslapB!=NULL)
        {
            fwrite(focuslapB,sizeof (CasVicLap),1,Save);
            if(focuslapB->ficha1!=NULL)
                fwrite(focuslapB->ficha1,sizeof(Ficha),1,Save);
            if(focuslapB->ficha2!=NULL)
                fwrite(focuslapB->ficha2,sizeof(Ficha),1,Save);

            if(banderaB==1)
            {
                fwrite(Tablero->winB->end,sizeof(Final),1,Save);
                if(Tablero->winB->end->ficha1!=NULL)
                    fwrite(Tablero->winB->end->ficha1,sizeof(Ficha),1,Save);
                if(Tablero->winB->end->ficha2!=NULL)
                    fwrite(Tablero->winB->end->ficha2,sizeof(Ficha),1,Save);
                if(Tablero->winB->end->ficha3!=NULL)
                    fwrite(Tablero->winB->end->ficha3,sizeof(Ficha),1,Save);
                if(Tablero->winB->end->ficha4!=NULL)
                    fwrite(Tablero->winB->end->ficha4,sizeof(Ficha),1,Save);
                banderaB=0;
            }
            focuslapB=focuslapB->next;
        }


        int arrayPaLasCasillasBrodiYaAyudamePlis[136]={0};
        int g=0;
        Casilla*focusnode=Tablero->inicio;
        while(focusnode!=NULL)
        {
            if(focusnode->ficha1!=NULL)
                arrayPaLasCasillasBrodiYaAyudamePlis[g]=1;
            g++;
            if(focusnode->ficha2!=NULL)
                arrayPaLasCasillasBrodiYaAyudamePlis[g]=1;
            g++;
            focusnode=focusnode->next;
        }

        fwrite(arrayPaLasCasillasBrodiYaAyudamePlis,sizeof(arrayPaLasCasillasBrodiYaAyudamePlis),1,Save);

        focusnode=Tablero->inicio;
        while(focusnode!=NULL)
        {
            fwrite(focusnode,sizeof(Casilla),1,Save);

            if(focusnode->ficha1!=NULL)
                fwrite(focusnode->ficha1,sizeof(Ficha),1,Save);

            if(focusnode->ficha2!=NULL)
                fwrite(focusnode->ficha2,sizeof(Ficha),1,Save);


            focusnode=focusnode->next;
        }

        fclose(Save);

    }

}//Funcion para salvar el juego.
Board* loadGame(Board *Tablero,int jugadores){
    FILE *Save = fopen("juegosGuardados\\save.dat", "r+b");
    //Si existe, se abre y se recupera el juego
    if(Save != NULL){
        printf(" - - Loading Game - - \n");
        Tablero = malloc(sizeof(Board)); //Crea memoria dinámica
        fread(Tablero, sizeof(Board), 1, Save);
        Tablero->baseR=malloc(sizeof(Base));
        Tablero->baseG=malloc(sizeof(Base));
        Tablero->baseY=malloc(sizeof(Base));
        Tablero->baseB=malloc(sizeof(Base));

        fread(Tablero->baseR,sizeof(Base),1,Save);
        fread(Tablero->baseG,sizeof(Base),1,Save);
        fread(Tablero->baseY,sizeof(Base),1,Save);
        fread(Tablero->baseB,sizeof(Base),1,Save);

        int arregloParaVerSiSeGuardoAlgo[16];
        int i=0;
        fread(arregloParaVerSiSeGuardoAlgo,sizeof(arregloParaVerSiSeGuardoAlgo),1,Save);
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseR->ficha1=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseR->ficha2=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseR->ficha3=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseR->ficha4=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseG->ficha1=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseG->ficha2=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseG->ficha3=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseG->ficha4=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseY->ficha1=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseY->ficha2=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseY->ficha3=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseY->ficha4=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseB->ficha1=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseB->ficha2=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseB->ficha3=malloc(sizeof(Ficha));
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            Tablero->baseB->ficha4=malloc(sizeof(Ficha));

        i=0;

        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseR->ficha1,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseR->ficha2,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseR->ficha3,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseR->ficha4,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseG->ficha1,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseG->ficha2,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseG->ficha3,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseG->ficha4,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseY->ficha1,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseY->ficha2,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseY->ficha3,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseY->ficha4,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseB->ficha1,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseB->ficha2,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseB->ficha3,sizeof (Ficha),1,Save);
        i++;
        if(arregloParaVerSiSeGuardoAlgo[i]==1)
            fread(Tablero->baseB->ficha4,sizeof (Ficha),1,Save);

        int arregloParaSaberDondeHayFichasEnVicLapYEndR[18];
        int j=0;
        fread(arregloParaSaberDondeHayFichasEnVicLapYEndR,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndR),1,Save);

        Tablero->winR=malloc(sizeof(CasVicLap));
        fread(Tablero->winR,sizeof(CasVicLap),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winR->ficha1, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winR->ficha2, sizeof(Ficha), 1, Save);
        }
        j++;

        Tablero->winR->end = malloc(sizeof(Final));
        fread(Tablero->winR->end,sizeof (Final),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->end->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winR->end->ficha1, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->end->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winR->end->ficha2, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->end->ficha3 = malloc(sizeof(Ficha));
            fread(Tablero->winR->end->ficha3, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
            Tablero->winR->end->ficha4 = malloc(sizeof(Ficha));
            fread(Tablero->winR->end->ficha4, sizeof(Ficha), 1, Save);
        }
        j++;

        Tablero->winR->next=malloc(sizeof(CasVicLap));
        CasVicLap *focuslapR=Tablero->winR->next;
        for(int i=0;i<=6;i++)
        {
            if(i<6) {
                fread(focuslapR, sizeof(CasVicLap), 1, Save);
                focuslapR->end = NULL;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
                    focuslapR->ficha1= malloc(sizeof(Ficha));
                    fread(focuslapR->ficha1, sizeof(Ficha), 1, Save);
                }
                j++;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndR[j]==1) {
                    focuslapR->ficha2 = malloc(sizeof(Ficha));
                    fread(focuslapR->ficha2, sizeof(Ficha), 1, Save);
                }
                j++;
                if(i<5) {
                    focuslapR->next = malloc(sizeof(CasVicLap));
                    focuslapR = focuslapR->next;
                }
            }
            if(i==5) {
                focuslapR->next = NULL;
            }
        }

        int arregloParaSaberDondeHayFichasEnVicLapYEndG[18];
        int k=0;
        fread(arregloParaSaberDondeHayFichasEnVicLapYEndG,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndG),1,Save);

        Tablero->winG=malloc(sizeof(CasVicLap));
        fread(Tablero->winG,sizeof(CasVicLap),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winG->ficha1, sizeof(Ficha), 1, Save);
        }
        k++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winG->ficha2, sizeof(Ficha), 1, Save);
        }
        k++;

        Tablero->winG->end = malloc(sizeof(Final));
        fread(Tablero->winG->end,sizeof (Final),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->end->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winG->end->ficha1, sizeof(Ficha), 1, Save);
        }
        k++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->end->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winG->end->ficha2, sizeof(Ficha), 1, Save);
        }
        k++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->end->ficha3 = malloc(sizeof(Ficha));
            fread(Tablero->winG->end->ficha3, sizeof(Ficha), 1, Save);
        }
        k++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
            Tablero->winG->end->ficha4 = malloc(sizeof(Ficha));
            fread(Tablero->winG->end->ficha4, sizeof(Ficha), 1, Save);
        }
        k++;

        Tablero->winG->next=malloc(sizeof(CasVicLap));
        CasVicLap *focuslapG=Tablero->winG->next;
        for(int i=0;i<=6;i++)
        {
            if(i<6) {
                fread(focuslapG, sizeof(CasVicLap), 1, Save);
                focuslapG->end = NULL;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
                    focuslapG->ficha1= malloc(sizeof(Ficha));
                    fread(focuslapG->ficha1, sizeof(Ficha), 1, Save);
                }
                k++;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndG[k]==1) {
                    focuslapG->ficha2 = malloc(sizeof(Ficha));
                    fread(focuslapG->ficha2, sizeof(Ficha), 1, Save);
                }
                k++;
                if(i<5) {
                    focuslapG->next = malloc(sizeof(CasVicLap));
                    focuslapG = focuslapG->next;
                }
            }
            if(i==5) {
                focuslapG->next = NULL;
            }
        }

        int arregloParaSaberDondeHayFichasEnVicLapYEndY[18];
        int h=0;
        fread(arregloParaSaberDondeHayFichasEnVicLapYEndY,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndY),1,Save);


        Tablero->winY=malloc(sizeof(CasVicLap));
        fread(Tablero->winY,sizeof(CasVicLap),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winY->ficha1, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winY->ficha2, sizeof(Ficha), 1, Save);
        }
        j++;

        Tablero->winY->end = malloc(sizeof(Final));
        fread(Tablero->winY->end,sizeof (Final),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->end->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winY->end->ficha1, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->end->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winY->end->ficha2, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->end->ficha3 = malloc(sizeof(Ficha));
            fread(Tablero->winY->end->ficha3, sizeof(Ficha), 1, Save);
        }
        j++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
            Tablero->winY->end->ficha4 = malloc(sizeof(Ficha));
            fread(Tablero->winY->end->ficha4, sizeof(Ficha), 1, Save);
        }
        j++;


        Tablero->winY->next=malloc(sizeof(CasVicLap));
        CasVicLap *focuslapY=Tablero->winY->next;
        for(int i=0;i<=6;i++)
        {
            if(i<6) {
                fread(focuslapY, sizeof(CasVicLap), 1, Save);
                focuslapY->end = NULL;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
                    focuslapY->ficha1 = malloc(sizeof(Ficha));
                    fread(focuslapY->ficha1, sizeof(Ficha), 1, Save);
                }
                j++;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndY[h]==1) {
                    focuslapY->ficha2 = malloc(sizeof(Ficha));
                    fread(focuslapY->ficha2, sizeof(Ficha), 1, Save);
                }
                j++;
                if(i<5) {
                    focuslapY->next = malloc(sizeof(CasVicLap));
                    focuslapY = focuslapY->next;
                }
            }
            if(i==5) {
                focuslapY->next = NULL;
            }
        }

        int arregloParaSaberDondeHayFichasEnVicLapYEndB[18];
        int l=0;
        fread(arregloParaSaberDondeHayFichasEnVicLapYEndB,sizeof(arregloParaSaberDondeHayFichasEnVicLapYEndB),1,Save);


        Tablero->winB=malloc(sizeof(CasVicLap));
        fread(Tablero->winB,sizeof(CasVicLap),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winB->ficha1, sizeof(Ficha), 1, Save);
        }
        l++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winB->ficha2, sizeof(Ficha), 1, Save);
        }
        l++;

        Tablero->winB->end = malloc(sizeof(Final));
        fread(Tablero->winB->end,sizeof (Final),1,Save);
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->end->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->winB->end->ficha1, sizeof(Ficha), 1, Save);
        }
        l++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->end->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->winB->end->ficha2, sizeof(Ficha), 1, Save);
        }
        l++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->end->ficha3 = malloc(sizeof(Ficha));
            fread(Tablero->winB->end->ficha3, sizeof(Ficha), 1, Save);
        }
        l++;
        if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
            Tablero->winB->end->ficha4 = malloc(sizeof(Ficha));
            fread(Tablero->winB->end->ficha4, sizeof(Ficha), 1, Save);
        }
        l++;

        Tablero->winB->next=malloc(sizeof(CasVicLap));
        CasVicLap *focuslapB=Tablero->winB->next;
        for(int i=0;i<=6;i++)
        {
            if(i<6) {
                fread(focuslapB, sizeof(CasVicLap), 1, Save);
                focuslapB->end = NULL;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
                    focuslapB->ficha1 = malloc(sizeof(Ficha));
                    fread(focuslapB->ficha1, sizeof(Ficha), 1, Save);
                }
                l++;
                if(arregloParaSaberDondeHayFichasEnVicLapYEndB[l]==1) {
                    focuslapB->ficha2 = malloc(sizeof(Ficha));
                    fread(focuslapB->ficha2, sizeof(Ficha), 1, Save);
                }
                l++;
                if(i<5) {
                    focuslapB->next = malloc(sizeof(CasVicLap));
                    focuslapB = focuslapB->next;
                }
            }
            if(i==5) {
                focuslapB->next = NULL;
            }
        }

        int arrayPaLasCasillasBrodiYaAyudamePlis[136]={0};
        int g=0;
        fread(arrayPaLasCasillasBrodiYaAyudamePlis,sizeof(arrayPaLasCasillasBrodiYaAyudamePlis),1,Save);

        Tablero->inicio=malloc(sizeof(Casilla));
        fread(Tablero->inicio,sizeof(Casilla),1,Save);
        if(arrayPaLasCasillasBrodiYaAyudamePlis[g]==1) {
            Tablero->inicio->ficha1 = malloc(sizeof(Ficha));
            fread(Tablero->inicio->ficha1, sizeof(Ficha), 1, Save);
        }
        g++;
        if(arrayPaLasCasillasBrodiYaAyudamePlis[g]==1) {
            Tablero->inicio->ficha2 = malloc(sizeof(Ficha));
            fread(Tablero->inicio->ficha2, sizeof(Ficha), 1, Save);
        }
        g++;

        Tablero->inicio->next=malloc(sizeof(Casilla));
        Casilla*focusnode=Tablero->inicio->next;
        for(int i=0;i<67;i++)
        {
            fread(focusnode,sizeof(Casilla),1,Save);
            if(arrayPaLasCasillasBrodiYaAyudamePlis[g]==1) {
                focusnode->ficha1 = malloc(sizeof(Ficha));
                fread(focusnode->ficha1, sizeof(Ficha), 1, Save);
            }
            g++;
            if(arrayPaLasCasillasBrodiYaAyudamePlis[g]==1) {
                focusnode->ficha2 = malloc(sizeof(Ficha));
                fread(focusnode->ficha2, sizeof(Ficha), 1, Save);
            }
            g++;
            if(i<66)
            {
                focusnode->next=malloc(sizeof(Casilla));
                focusnode=focusnode->next;
            }
            if(i==66)
            {
                focusnode->next=NULL;
            }
        }

        fclose(Save);

    }else{
        printf(" - - No saved games, creating a new one- - \n");
        Tablero = newBoard();
        creacionMaestra(Tablero,jugadores);
    }
    return Tablero;
}//Funcion para cargar el juego.
Board* iniciarEditor(int jugadores)
{
    Board*juegoEditado=newBoard();//Crea tablero nuevo
    creacionMaestra(juegoEditado,jugadores);//Completa el tablero nuevo
    editorDeJuego(juegoEditado);//Permite al usuario editar las posiciones de las fichas de acuerdo a movimientos de dados introducidos.
    displayBoard(juegoEditado);
    return juegoEditado;
}