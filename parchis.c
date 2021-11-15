#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parchis.h"

struct dados{
    int die1;
    int die2;
};

struct ficha{
    char Player;//Determina el color del jugador (b, y, r, g)
    char Path;//Path es un acumulador de el progreso de la ficha
};

struct casilla{
    char NumCasilla;//Indica el numero de la casilla | nuemros siempre entre 1-68
    char BanSafe;//Indica si es una casilla donde se pueda comer
    char BanSalida;//Indica si la casilla es una salida para alguno de los jugadores
    struct ficha *ficha1;//Almacena una ficha
    struct ficha *ficha2;//Almacena una ficha
    struct casilla *next;//Hace referencia a la siguiente casilla
};

struct casVicLap{
    char NumCasilla;//numero de casillas siempre esta entre 65-71
    struct ficha *ficha1;
    struct ficha *ficha2;
    struct casVicLap *next;
    struct casEnd *end;
};

struct casEnd{
    char Player;
    char NumCasilla;//Numero siempre es 72
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

/*
Dados tiroDados()
{
    Dados Dice={0,0};
    time_t t;
    srand((unsigned)time(&t));

    Dice.die1 = ( (rand() % 6)+1);
    Dice.die2 = ( (rand() % 6)+1);

    printf("%d,%d",Dice.die1,Dice.die2);

    return Dice;
}
*/


Board* newboard()
{
    Board *newBoard=malloc(sizeof(Board));

    newBoard->inicio=NULL;

    for(int i=0;i<68;i++)
    {
        //Creamos todas las casillas regulares del tablero

        Casilla *slot =malloc(sizeof(Casilla));
        slot->NumCasilla=i+1;
        printf("Casilla # %d\n",slot->NumCasilla);

        //---------------------Se Puede Comer?---------------------------------------

        //Asignamos las casillas que tienen que ser  donde no se puede comer y les agregamos el valor bandera de 1, en caso contrario se quedan con 0
        if(slot->NumCasilla==1||slot->NumCasilla==8||slot->NumCasilla==13||slot->NumCasilla==18||slot->NumCasilla==25||slot->NumCasilla==30||slot->NumCasilla==35||slot->NumCasilla==42||slot->NumCasilla==47||slot->NumCasilla==52||slot->NumCasilla==59||slot->NumCasilla==64)
        {
            slot->BanSafe=1;
        }
        else
            slot->BanSafe=0;

        printf("Se puede comer? %d\n",slot->BanSafe);
        //----------------------------------------------------------------------------


        //---------------------------Es salida?---------------------------------------

        //Asignamos a las casillas correspondeintes la bandera de si son la salida de que jugador son
        if(slot->NumCasilla==1||slot->NumCasilla==18||slot->NumCasilla==35||slot->NumCasilla==52)
        {
            if(slot->NumCasilla==1){
                slot->BanSalida = 'R';
            } else if (slot->NumCasilla==18){
                slot->BanSalida = 'G';
            } else if(slot->NumCasilla==35){
                slot->BanSalida = 'Y';
            } else if(slot->NumCasilla==52){
                slot->BanSalida = 'B';
            }
        }

        printf("Es una salida? %c\n",slot->BanSalida);
        //----------------------------------------------------------------------------
        //------------Asigna como nulos los dos espacios de cada casilla -------------

        slot->ficha1=NULL;
        slot->ficha2=NULL;
        slot = slot->next; //Va hacia la siguiente casilla
        printf("\n");
    }

    //---------------------------Posiciones iniciales RED---------------------------
    newBoard->baseR=malloc(sizeof(Base));
    newBoard->baseR->NumCasilla=0;
    newBoard->baseR->Player='R';
    newBoard->baseR->ficha1=malloc(sizeof(Ficha));
    newBoard->baseR->ficha2=malloc(sizeof(Ficha));
    newBoard->baseR->ficha3=malloc(sizeof(Ficha));
    newBoard->baseR->ficha4=malloc(sizeof(Ficha));
    newBoard->baseR->ficha1->Path=0;
    newBoard->baseR->ficha1->Player='R';
    newBoard->baseR->ficha2->Path=0;
    newBoard->baseR->ficha2->Player='R';
    newBoard->baseR->ficha3->Path=0;
    newBoard->baseR->ficha3->Player='R';
    newBoard->baseR->ficha4->Path=0;
    newBoard->baseR->ficha4->Player='R';
    printf("#%d  Jugador: %c   Fichas: 1%c, 2%c, 3%c, 4%c",
           newBoard->baseR->NumCasilla, newBoard->baseR->Player,
           newBoard->baseR->ficha1->Player, newBoard->baseR->ficha2->Player,
           newBoard->baseR->ficha3->Player, newBoard->baseR->ficha4->Player);
    //---------------------------Posiciones iniciales BLUE---------------------------
    newBoard->baseB=malloc(sizeof(Base));
    newBoard->baseB->NumCasilla=0;
    newBoard->baseB->Player='B';
    newBoard->baseB->ficha1=malloc(sizeof(Ficha));
    newBoard->baseB->ficha2=malloc(sizeof(Ficha));
    newBoard->baseB->ficha3=malloc(sizeof(Ficha));
    newBoard->baseB->ficha4=malloc(sizeof(Ficha));
    newBoard->baseB->ficha1->Path=0;
    newBoard->baseB->ficha1->Player='B';
    newBoard->baseB->ficha2->Path=0;
    newBoard->baseB->ficha2->Player='B';
    newBoard->baseB->ficha3->Path=0;
    newBoard->baseB->ficha3->Player='B';
    newBoard->baseB->ficha4->Path=0;
    newBoard->baseB->ficha4->Player='B';
    //---------------------------Posiciones iniciales GREEN---------------------------
    newBoard->baseG=malloc(sizeof(Base));
    newBoard->baseG->NumCasilla=0;
    newBoard->baseG->Player='G';
    newBoard->baseG->ficha1=malloc(sizeof(Ficha));
    newBoard->baseG->ficha2=malloc(sizeof(Ficha));
    newBoard->baseG->ficha3=malloc(sizeof(Ficha));
    newBoard->baseG->ficha4=malloc(sizeof(Ficha));
    newBoard->baseG->ficha1->Path=0;
    newBoard->baseG->ficha1->Player='G';
    newBoard->baseG->ficha2->Path=0;
    newBoard->baseG->ficha2->Player='G';
    newBoard->baseG->ficha3->Path=0;
    newBoard->baseG->ficha3->Player='G';
    newBoard->baseG->ficha4->Path=0;
    newBoard->baseG->ficha4->Player='G';
    //---------------------------Posiciones iniciales YELLOW---------------------------
    newBoard->baseY=malloc(sizeof(Base));
    newBoard->baseY->NumCasilla=0;
    newBoard->baseY->Player='Y';
    newBoard->baseY->ficha1=malloc(sizeof(Ficha));
    newBoard->baseY->ficha2=malloc(sizeof(Ficha));
    newBoard->baseY->ficha3=malloc(sizeof(Ficha));
    newBoard->baseY->ficha4=malloc(sizeof(Ficha));
    newBoard->baseY->ficha1->Path=0;
    newBoard->baseY->ficha1->Player='Y';
    newBoard->baseY->ficha2->Path=0;
    newBoard->baseY->ficha2->Player='Y';
    newBoard->baseY->ficha3->Path=0;
    newBoard->baseY->ficha3->Player='Y';
    newBoard->baseY->ficha4->Path=0;
    newBoard->baseY->ficha4->Player='Y';




    return newBoard;
}




void displayBoard(Board *juego){
    Casilla *focusnode =juego->inicio;

    while(focusnode!=NULL)
    {
        printf("Nuemro de casilla= %d",focusnode->NumCasilla);
        printf("Se puede comer= %d",focusnode->BanSafe);
        printf("Casilla de salida = %d",focusnode->BanSalida);
        focusnode=focusnode->next;

    }

}