#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parchis.h"
#include "turnos.h"

struct ficha{
    char Player[2];//Determina el color del jugador (b, y, r, g)
    char Path;//Path es un acumulador de el progreso de la ficha
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


//Crea un tablero vacío
Board *newBoard(){
    Board *juego = malloc(sizeof(Board));
    juego->inicio = NULL;

    return juego;
}

//Añade 68 casillas al tablero vacío
void finishBoard(Board* juego, int contador)
{
    if(juego->inicio==NULL)
    {
        juego->inicio=malloc(sizeof(Casilla));
        juego->inicio->NumCasilla = contador;
        juego->inicio->BanSafe = 1;
        juego->inicio->BanSalida = 'R';
        juego->inicio->ficha1 = NULL;
        juego->inicio->ficha2 = NULL;
        //juego->inicio->next=malloc(sizeof(Casilla));
        juego->inicio->next = NULL;

        return;
    }
    Casilla *focusNode = juego->inicio;
    while(focusNode->next != NULL){
        focusNode = focusNode->next;
    }

    focusNode->next = malloc(sizeof(Casilla));

    focusNode->NumCasilla = contador;

    //---------------------Se Puede Comer?---------------------------------------

    //Asignamos las casillas en donde se puede comer (0) y donde no (1)
    if(focusNode->NumCasilla==1||focusNode->NumCasilla==8||focusNode->NumCasilla==13||focusNode->NumCasilla==18||focusNode->NumCasilla==25||focusNode->NumCasilla==30||focusNode->NumCasilla==35||focusNode->NumCasilla==42||focusNode->NumCasilla==47||focusNode->NumCasilla==52||focusNode->NumCasilla==59||focusNode->NumCasilla==64)
    {
        focusNode->BanSafe = 1;
    }
    else
        focusNode->BanSafe = 0;

    //printf("La casilla es segura? %d\n",focusNode->BanSafe);
    //----------------------------------------------------------------------------

    //---------------------------Es salida?---------------------------------------

    //Asignamos a las casillas correspondeintes la bandera de si son la salida de que jugador son
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


    //printf("Es una salida? %c\n",focusNode->BanSalida);
    //----------------------------------------------------------------------------
    //------------Asigna como nulos los dos espacios de cada casilla -------------
    focusNode->ficha1=NULL;
    focusNode->ficha2=NULL;

    focusNode->next->next = NULL;
}

//Añade los espacios de inicio
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
    juego->baseR->ficha1->Player[0] = 'R'; juego->baseR->ficha1->Player[1] = '1';
    juego->baseR->ficha2->Path=0;
    juego->baseR->ficha2->Player[0] = 'R'; juego->baseR->ficha2->Player[1] = '2';
    juego->baseR->ficha3->Path=0;
    juego->baseR->ficha3->Player[0] = 'R'; juego->baseR->ficha3->Player[1] = '3';
    juego->baseR->ficha4->Path=0;
    juego->baseR->ficha4->Player[0] = 'R'; juego->baseR->ficha4->Player[1] = '4';

    //---------------------------Posiciones iniciales BLUE-----------------------
    juego->baseB=malloc(sizeof(Base));
    juego->baseB->NumCasilla=0;
    juego->baseB->Player='B';
    juego->baseB->ficha1=malloc(sizeof(Ficha));
    juego->baseB->ficha2=malloc(sizeof(Ficha));
    juego->baseB->ficha3=malloc(sizeof(Ficha));
    juego->baseB->ficha4=malloc(sizeof(Ficha));
    juego->baseB->ficha1->Path=0;
    juego->baseB->ficha1->Player[0] = 'B'; juego->baseB->ficha1->Player[1] = '1';
    juego->baseB->ficha2->Path=0;
    juego->baseB->ficha2->Player[0] = 'B'; juego->baseB->ficha2->Player[1] = '2';
    juego->baseB->ficha3->Path=0;
    juego->baseB->ficha3->Player[0] = 'B'; juego->baseB->ficha3->Player[1] = '3';
    juego->baseB->ficha4->Path=0;
    juego->baseB->ficha4->Player[0] = 'B'; juego->baseB->ficha4->Player[1] = '4';

    //---------------------------Posiciones iniciales GREEN-------------------
    juego->baseG=malloc(sizeof(Base));
    juego->baseG->NumCasilla=0;
    juego->baseG->Player='G';
    juego->baseG->ficha1=malloc(sizeof(Ficha));
    juego->baseG->ficha2=malloc(sizeof(Ficha));
    juego->baseG->ficha3=malloc(sizeof(Ficha));
    juego->baseG->ficha4=malloc(sizeof(Ficha));
    juego->baseG->ficha1->Path=0;
    juego->baseG->ficha1->Player[0] = 'G'; juego->baseG->ficha1->Player[1] = '1';
    juego->baseG->ficha2->Path=0;
    juego->baseG->ficha2->Player[0] = 'G'; juego->baseG->ficha2->Player[1] = '2';
    juego->baseG->ficha3->Path=0;
    juego->baseG->ficha3->Player[0] = 'G'; juego->baseG->ficha3->Player[1] = '3';
    juego->baseG->ficha4->Path=0;
    juego->baseG->ficha4->Player[0] = 'G'; juego->baseG->ficha4->Player[1] = '4';

    //---------------------------Posiciones iniciales YELLOW-------------------
    juego->baseY=malloc(sizeof(Base));
    juego->baseY->NumCasilla=0;
    juego->baseY->Player='Y';
    juego->baseY->ficha1=malloc(sizeof(Ficha));
    juego->baseY->ficha2=malloc(sizeof(Ficha));
    juego->baseY->ficha3=malloc(sizeof(Ficha));
    juego->baseY->ficha4=malloc(sizeof(Ficha));
    juego->baseY->ficha1->Path=0;
    juego->baseY->ficha1->Player[0] = 'Y'; juego->baseY->ficha1->Player[1] = '1';
    juego->baseY->ficha2->Path=0;
    juego->baseY->ficha2->Player[0] = 'Y'; juego->baseY->ficha2->Player[1] = '2';
    juego->baseY->ficha3->Path=0;
    juego->baseY->ficha3->Player[0] = 'Y'; juego->baseY->ficha3->Player[1] = '3';
    juego->baseY->ficha4->Path=0;
    juego->baseY->ficha4->Player[0] = 'Y'; juego->baseY->ficha4->Player[1] = '4';

}

//----------------Creacion de 4 listas vacias para recorrido ganador -------------------

//FUNCION GENERAL
CasVicLap* emptyEnding(char Player)
{
    CasVicLap *firstEnding = malloc(sizeof(CasVicLap));
    firstEnding->NumCasilla = 101;
    firstEnding->ficha1 = NULL;
    firstEnding->ficha2 = NULL;
    firstEnding->Player = Player;
    firstEnding->next = NULL;

    return firstEnding;
}

void finishEnding(CasVicLap* recorridoFinal,int contador,char Player)
{
    while(recorridoFinal->next != NULL && contador < 108)
    {
        recorridoFinal = recorridoFinal->next;
    }
    recorridoFinal->next = malloc(sizeof(CasVicLap));
    recorridoFinal->NumCasilla = contador;
    recorridoFinal->Player = Player;
    recorridoFinal->ficha1 = NULL;
    recorridoFinal->ficha2 = NULL;
    recorridoFinal->end= NULL;

    recorridoFinal->next->next = NULL;
}

void ending(Board* juego)
{
    Final *finalR = juego->winR->end;
    finalR = malloc(sizeof(Final));
    finalR->Player = 'R';
    finalR->NumCasilla = 108;
    finalR->ficha1 = NULL; finalR->ficha2 = NULL;
    finalR->ficha3 = NULL; finalR->ficha4 = NULL;
    juego->winR->end=finalR;

    Final *finalB = juego->winB->end;
    finalB = malloc(sizeof(Final));
    finalB->Player = 'B';
    finalB->NumCasilla = 108;
    finalB->ficha1 = NULL; finalB->ficha2 = NULL;
    finalB->ficha3 = NULL; finalB->ficha4 = NULL;
    juego->winB->end=finalB;

    Final *finalG = juego->winG->end;
    finalG = malloc(sizeof(Final));
    finalG->Player = 'G';
    finalG->NumCasilla = 108;
    finalG->ficha1 = NULL; finalG->ficha2 = NULL;
    finalG->ficha3 = NULL; finalG->ficha4 = NULL;
    juego->winG->end=finalG;

    Final *finalY = juego->winY->end;
    finalY = malloc(sizeof(Final));
    finalY->Player = 'Y';
    finalY->NumCasilla = 108;
    finalY->ficha1 = NULL; finalY->ficha2 = NULL;
    finalY->ficha3 = NULL; finalY->ficha4 = NULL;
    juego->winY->end=finalY;
}

void creacionMaestra(Board *juego)
{
    //Se crean las 68 casillas
    for(int i = 0; i < 69; i++){
        finishBoard(juego,i);
    }
    //Se crean las 4 casillas base de cada color (inicio)
    beginning(juego);

    //Crea recorrido final de cada color
    CasVicLap *finalR = emptyEnding('R');
    CasVicLap *finalB = emptyEnding('B');
    CasVicLap *finalG = emptyEnding('G');
    CasVicLap *finalY = emptyEnding('Y');
    for(int i=101;i < 108;i++)
    {
        finishEnding(finalR,i,'R');
        finishEnding(finalB,i,'B');
        finishEnding(finalG,i,'G');
        finishEnding(finalY,i,'Y');
    }
    //Se guarda en Board
    juego->winR=finalR;
    juego->winB=finalB;
    juego->winG=finalG;
    juego->winY=finalY;
//Crea casillas ganadoras de cada color
    ending(juego);
}


void displayBoard(Board *juego){
    printf("#####################  DISPLAY BOARD PERRO  ##############################\n");
    Casilla *focusnode =juego->inicio;
    //ROJO
    printf("\n#%d  Jugador: %c   Fichas: %s, %s, %s, %s",
           juego->baseR->NumCasilla, juego->baseR->Player,
           juego->baseR->ficha1->Player, juego->baseR->ficha2->Player,
           juego->baseR->ficha3->Player, juego->baseR->ficha4->Player);
    //AZUL
    printf("\n#%d  Jugador: %c   Fichas: %s, %s, %s, %s",
           juego->baseB->NumCasilla, juego->baseB->Player,
           juego->baseB->ficha1->Player, juego->baseB->ficha2->Player,
           juego->baseB->ficha3->Player, juego->baseB->ficha4->Player);

    //VERDE
    printf("\n#%d  Jugador: %c   Fichas: %s, %s, %s, %s",
           juego->baseG->NumCasilla, juego->baseG->Player,
           juego->baseG->ficha1->Player, juego->baseG->ficha2->Player,
           juego->baseG->ficha3->Player, juego->baseG->ficha4->Player);
    //Amarillo
    printf("\n#%d  Jugador: %c   Fichas: %s, %s, %s, %s\n",
           juego->baseY->NumCasilla, juego->baseY->Player,
           juego->baseY->ficha1->Player, juego->baseY->ficha2->Player,
           juego->baseY->ficha3->Player, juego->baseY->ficha4->Player);

    while(focusnode->next!=NULL)
    {
        printf("Casilla # %d\n",focusnode->NumCasilla);
        printf("La casilla es segura? %d\n",focusnode->BanSafe);
        printf("Es una salida? %c\n\n",focusnode->BanSalida);

        focusnode=focusnode->next;
    }
    //-----------------RED-------------------------------------------------
    CasVicLap *focusLapR=juego->winR;
    while(focusLapR->next!=NULL)
    {
        printf("R Numero de casillaVL: %d\t Color del player: %c\n",focusLapR->NumCasilla,focusLapR->Player);
        focusLapR=focusLapR->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winR->end->Player,juego->winR->end->NumCasilla);

    printf("\n\n");

    //--------------GREEN------------------------------------------------------
    CasVicLap *focusLapG=juego->winG;
    while(focusLapG->next!=NULL){
        printf("G Numero de casillaVL: %d\t Color del player: %c\n",focusLapG->NumCasilla,focusLapG->Player);
        focusLapG=focusLapG->next;
    }

    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winG->end->Player,juego->winG->end->NumCasilla);
    printf("\n\n");


    //-------------BLUE------------------------------------------------------
    CasVicLap *focusLapB=juego->winB;
    while(focusLapB->next!=NULL){
        printf("B Numero de casillaVL: %d\t Color del player: %c\n",focusLapB->NumCasilla,focusLapB->Player);
        focusLapB=focusLapB->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winB->end->Player,juego->winB->end->NumCasilla);
    printf("\n\n");


    //------------YELLOW----------------------------------------------------------
    CasVicLap *focusLapY=juego->winY;
    while(focusLapY->next!=NULL){
        printf("Y Numero de casillaVL: %d\t Color del player: %c\n",focusLapY->NumCasilla,focusLapY->Player);
        focusLapY=focusLapY->next;
    }
    printf("Jugador: %c\n Numero de Casilla: %d\n",juego->winY->end->Player,juego->winY->end->NumCasilla);
    printf("\n\n");

}

