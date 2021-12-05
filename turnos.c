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
    char PaGanar;
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


//------------------------------------------------------------------------
Dados tiroDados()
{
    Dados Dice={0,0};
    srand(time(NULL));

    Dice.die1 = ( (rand() % 6)+1);
    Dice.die2 = ( (rand() % 6)+1);

    //rintf("%d,%d",Dice.die1,Dice.die2);

    return Dice;
}//Asigna aleatoriamente un valor a cada uno de los dados|Regresa la estructura de los dos dados.

char quienInicia(Board *juego)
{
    int jugadores = juego->currentPlayers;

    //Se tiran los dados para cada jugador
    Dados tiroR = tiroDados();
    Dados tiroB = tiroDados();
    Dados tiroG = tiroDados();
    Dados tiroY = tiroDados();

    //Variables para sumas
    int SDR = tiroR.die1+tiroR.die2;
    int SDG = tiroG.die1+tiroG.die2;
    int SDY = tiroY.die1+tiroY.die2;
    int SDB = tiroB.die1+tiroB.die2;

    //Se suman los dados para poder calcular el mas grande dependiendo de los que juegan
    if(jugadores == 2){
        SDG = 0;
        SDB = 0;
        while(SDR==SDY){
            tiroR = tiroDados();
            tiroY = tiroDados();
            SDR= tiroR.die1+tiroR.die2;
            SDY= tiroY.die1+tiroY.die2;
        }
    }
    if(jugadores == 3){
        SDB = 0;
        while(SDR==SDY || SDR==SDG || SDG==SDY){
            if(SDR==SDY || SDR==SDG){
                tiroR = tiroDados();
                SDR= tiroR.die1+tiroR.die2;
            }
            if(SDG==SDY){
                tiroG=tiroDados();
                SDG=tiroG.die1+tiroG.die2;
            }
        }
    }
    if(jugadores == 4){
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

    return 0;
}//Determina mediante comparaciones entre tiros aleatorios de los usuarios, cual saco el tiro mas grande, y regresa el jugador que iniciara la partida.

char cambiarJugador(char Player, Board *juego){
    int jugadores = juego->currentPlayers;
    if(jugadores == 2){
        if(Player == 'R')
            Player = 'Y';
        else if(Player == 'Y')
            Player = 'R';
    }
    if(jugadores == 3){
        if(Player == 'R')
            Player = 'G';
        else if (Player == 'G')
            Player = 'Y';
        else if(Player == 'Y')
            Player = 'R';
    }
    if(jugadores == 4){
        if(Player == 'R')
            Player = 'G';
        else if (Player == 'G')
            Player = 'Y';
        else if(Player == 'Y')
            Player = 'B';
        else if(Player == 'B')
            Player = 'R';
    }
    return Player;
}//Dependiendo del numero de jugadores, hace los cambios de jugador en turno.

//Este bloque de funciones, determina si existen fichas en cada base de los jugadores, asi como el numero que hay en cada una.
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

void Turno(char Player,Board *Tablero,Dados tiro)
{
    //Player='R';
    //pruebaDeBarreras(Tablero);
    //pruebaDeComer(Tablero);
    //pruebaDeVicLap(Tablero);
    //pruebaDeVictoria(Tablero);
    printf("Es el turno del jugador: %c\n\n",Player );
    int Dado1=valorDado1(tiro);
    int Dado2=valorDado2(tiro);
    //Dado1=2;
    //Dado2=2;
    printf("Tiro:Dado1= %d Dado2= %d\n\n",Dado1,Dado2);
    int numeroDeMovimientosPorTurno=0;
    int dadoUsado=0;
    int dadoAUsar;
    int sumaDados=Dado1+Dado2;
    int banderaDeBarrera=0;
    int casillaDeSalidaLlena=0;


    while(numeroDeMovimientosPorTurno<2)
    {
        casillaDeSalidaLlena=estaraLlenaLaCasillaDeSalida(Tablero,Player);
        int numeroDeFichasEnInicio=hayFichasEnInicio(Tablero,Player);
        //----------------PARA SACAR DE LA CASILLA INICIAL SI EXISTE UN 5-------------
        if(casillaDeSalidaLlena==0)
        {
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
            //_________Puede existir un bug aqui por como estan puestos los ifs________
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
                        movimientoFichaDelInicio(sumaDados, fichaR1SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaR2EnInicioTrue==1)
                    {
                        int fichaDeInicioR2=2;
                        Ficha *fichaR2SaleDeInicio=fichaElecta(fichaDeInicioR2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaR2SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaR3EnInicioTrue==1)
                    {
                        int fichaDeInicioR3=3;
                        Ficha *fichaR3SaleDeInicio=fichaElecta(fichaDeInicioR3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaR3SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaR4EnInicioTrue==1)
                    {
                        int fichaDeInicioR4=4;
                        Ficha *fichaR4SaleDeInicio=fichaElecta(fichaDeInicioR4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaR4SaleDeInicio, Tablero, Player);
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
                        movimientoFichaDelInicio(sumaDados, fichaG1SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaG2EnInicioTrue==1)
                    {
                        int fichaDeInicioG2=2;
                        Ficha *fichaG2SaleDeInicio=fichaElecta(fichaDeInicioG2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaG2SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaG3EnInicioTrue==1)
                    {
                        int fichaDeInicioG3=3;
                        Ficha *fichaG3SaleDeInicio=fichaElecta(fichaDeInicioG3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaG3SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaG4EnInicioTrue==1)
                    {
                        int fichaDeInicioG4=4;
                        Ficha *fichaG4SaleDeInicio=fichaElecta(fichaDeInicioG4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaG4SaleDeInicio, Tablero, Player);
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
                        movimientoFichaDelInicio(sumaDados, fichaB1SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaB2EnInicioTrue==1)
                    {
                        int fichaDeInicioB2=2;
                        Ficha *fichaB2SaleDeInicio=fichaElecta(fichaDeInicioB2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaB2SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaB3EnInicioTrue==1)
                    {
                        int fichaDeInicioB3=3;
                        Ficha *fichaB3SaleDeInicio=fichaElecta(fichaDeInicioB3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaB3SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaB4EnInicioTrue==1)
                    {
                        int fichaDeInicioB4=4;
                        Ficha *fichaB4SaleDeInicio=fichaElecta(fichaDeInicioB4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaB4SaleDeInicio, Tablero, Player);
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
                        movimientoFichaDelInicio(sumaDados, fichaY1SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaY2EnInicioTrue==1)
                    {
                        int fichaDeInicioY2=2;
                        Ficha *fichaY2SaleDeInicio=fichaElecta(fichaDeInicioY2, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaY2SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaY3EnInicioTrue==1)
                    {
                        int fichaDeInicioY3=3;
                        Ficha *fichaY3SaleDeInicio=fichaElecta(fichaDeInicioY3, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaY3SaleDeInicio, Tablero, Player);
                    }
                    else if(fichaY4EnInicioTrue==1)
                    {
                        int fichaDeInicioY4=4;
                        Ficha *fichaY4SaleDeInicio=fichaElecta(fichaDeInicioY4, Player, Player,Tablero,numeroDeFichasEnInicio,sumaDados);
                        movimientoFichaDelInicio(sumaDados, fichaY4SaleDeInicio, Tablero, Player);
                    }
                }
                numeroDeMovimientosPorTurno=2;
            }
        }
        if(numeroDeMovimientosPorTurno>=2)
            return;
        //-------------------LOGICA PARA ELEGIR DADOS--------------
        numeroDeFichasEnInicio=hayFichasEnInicio(Tablero,Player);
        if(numeroDeFichasEnInicio!=4)
        {
            //displayOpcionesDeFichaInicio(Player,Tablero);
            if(dadoUsado==0)
            {
                do{
                    displayOpcionesDeFichaInicio(Player,Tablero);//Desplieg al usuario las fichas que puede mover
                    printf("Referencia para que veas donde estan tus fichas, checa tu dado ;\n");
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

            if(dadoAUsar==1)
            {
                Ficha *fichaAManipular=validacionDeFichaElecta(Tablero,Dado1,Player);
                if(fichaAManipular==NULL)
                    return;
                movimientoFicha(Dado1, fichaAManipular, Tablero, Player);
                Dado1 = 0;
                sumaDados=Dado1+Dado2;
            }
            if(dadoAUsar==2)
            {
                Ficha *fichaAManipular=validacionDeFichaElecta(Tablero,Dado2,Player);
                if(fichaAManipular==NULL)
                    return;
                movimientoFicha(Dado2, fichaAManipular, Tablero, Player);
                Dado2 = 0;
                sumaDados=Dado1+Dado2;
            }
        }
        else
        {
            printf("\nLo siento, no sacaste un 5 para sacar una ficha de el tablero, de modo que no puedes hacer movimientos, intenta en la siguiente ronda :)\n");
            numeroDeMovimientosPorTurno=2;
        }
        numeroDeMovimientosPorTurno++;
    }

}//Funcion con la logica del turno, recibe el jugador en turno, el tablero y el tiro de dados. En funcion de los dados, saca una ficha del inicio si el tiro es 5, en caso de que no lo sea, permite al usuario elegir el dado que quiere mover y realiza el movimiento pertinente en la ficha que selecciono el usuario.
int valorDado1(Dados dados)
{
    return dados.die1;
}//Regresa el valor del primer dado de la estructura de dados.
int valorDado2(Dados dados)
{
    return dados.die2;
}//Regresa el valor del segundo dado de la estructura de dados.

//------------------------------- ARREGLAR DISPLAY --------------------------------
void displayOpcionesDeFichaInicio(char Player,Board *Tablero)//Imprime las fichas en el tablero, esta funcion es un referencia para el usuario en la terminal
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

void regresarFichaInvalidaAInicio(Board*Tablero,Ficha*ficha,char Player)
{
    if(Player=='R')
    {
        if(Tablero->baseR->ficha4==NULL)
            Tablero->baseR->ficha4=ficha;
        else if(Tablero->baseR->ficha3==NULL)
            Tablero->baseR->ficha3=ficha;
        else if(Tablero->baseR->ficha2==NULL)
            Tablero->baseR->ficha2=ficha;
        else if(Tablero->baseR->ficha1==NULL)
            Tablero->baseR->ficha1=ficha;
    }
    if(Player=='G')
    {
        if(Tablero->baseG->ficha4==NULL)
            Tablero->baseG->ficha4=ficha;
        else if(Tablero->baseG->ficha3==NULL)
            Tablero->baseG->ficha3=ficha;
        else if(Tablero->baseG->ficha2==NULL)
            Tablero->baseG->ficha2=ficha;
        else if(Tablero->baseG->ficha1==NULL)
            Tablero->baseG->ficha1=ficha;
    }
    if(Player=='Y')
    {
        if(Tablero->baseY->ficha4==NULL)
            Tablero->baseY->ficha4=ficha;
        else if(Tablero->baseY->ficha3==NULL)
            Tablero->baseY->ficha3=ficha;
        else if(Tablero->baseY->ficha2==NULL)
            Tablero->baseY->ficha2=ficha;
        else if(Tablero->baseY->ficha1==NULL)
            Tablero->baseY->ficha1=ficha;
    }
    if(Player=='B')
    {
        if(Tablero->baseB->ficha4==NULL)
            Tablero->baseB->ficha4=ficha;
        else if(Tablero->baseB->ficha3==NULL)
            Tablero->baseB->ficha3=ficha;
        else if(Tablero->baseB->ficha2==NULL)
            Tablero->baseB->ficha2=ficha;
        else if(Tablero->baseB->ficha1==NULL)
            Tablero->baseB->ficha1=ficha;
    }
}//Esta funcion, regresa una ficha que no se pudo mover de manera valida al inicio, para no perder la referencia

Ficha *fichaElecta(int IDfichaInputUsuario,char playerFichaUsuario,char Player,Board *Tablero,int hayFichasEnInicio,int Tiro)
{

    Ficha *fichaderetorno;
    if(hayFichasEnInicio!=0)
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
            if(Tablero->baseR->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha2->Id && playerFichaUsuario==Tablero->baseR->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha2;
                    Tablero->baseR->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseR->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseR->ficha3->Id && playerFichaUsuario==Tablero->baseR->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseR->ficha3;
                    Tablero->baseR->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseR->ficha4!=NULL)
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
            if(Tablero->baseG->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha2->Id && playerFichaUsuario==Tablero->baseG->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha2;
                    Tablero->baseG->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseG->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseG->ficha3->Id && playerFichaUsuario==Tablero->baseG->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseG->ficha3;
                    Tablero->baseG->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseG->ficha4!=NULL)
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
            if(Tablero->baseB->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha2->Id && playerFichaUsuario==Tablero->baseB->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha2;
                    Tablero->baseB->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseB->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseB->ficha3->Id && playerFichaUsuario==Tablero->baseB->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseB->ficha3;
                    Tablero->baseB->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseB->ficha4!=NULL)
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
            if(Tablero->baseY->ficha2!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha2->Id && playerFichaUsuario==Tablero->baseY->ficha2->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha2;
                    Tablero->baseY->ficha2=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseY->ficha3!=NULL)
            {
                if(IDfichaInputUsuario==Tablero->baseY->ficha3->Id && playerFichaUsuario==Tablero->baseY->ficha3->Player)
                {
                    fichaderetorno=Tablero->baseY->ficha3;
                    Tablero->baseY->ficha3=NULL;
                    return fichaderetorno;
                }
            }
            if(Tablero->baseY->ficha4!=NULL)
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
            if(focusnode->ficha1!=NULL){
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
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
            if(focusnode->ficha1!=NULL){
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
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
            if(focusnode->ficha1!=NULL){
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
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
            if(focusnode->ficha1!=NULL){
                if(IDfichaInputUsuario==focusnode->ficha1->Id && playerFichaUsuario==focusnode->ficha1->Player)
                {
                    fichaderetorno=focusnode->ficha1;
                    focusnode->ficha1=NULL;
                    return fichaderetorno;
                }
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
}//Recibe el input de la ficha que quiere mover el usuario y te regresa la estructura de la ficha para que la podamos manipular

void movimientoFicha(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player)
{
    Casilla *focusnode=Tablero->inicio;
    int posibilidadDeComer=0;
    //-----------------------------JUGADOR ROJO------------------------------------

    if(Player== 'R')
    {

        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;
        CasVicLap *focusVicLapR=Tablero->winR;
        if(fichaQueEstamosMoviendo->PaGanar>64)
        {
            if(fichaQueEstamosMoviendo->Path<101)
                fichaQueEstamosMoviendo->Path+=36;
            if(fichaQueEstamosMoviendo->PaGanar>=72)
            {
                printf("Felicidades una ficha llego al final");
                if(Tablero->winR->end->ficha1==NULL)
                    Tablero->winR->end->ficha1=fichaQueEstamosMoviendo;
                else if(Tablero->winR->end->ficha2==NULL)
                    Tablero->winR->end->ficha2=fichaQueEstamosMoviendo;
                else if(Tablero->winR->end->ficha3==NULL)
                    Tablero->winR->end->ficha3=fichaQueEstamosMoviendo;
                else if(Tablero->winR->end->ficha4==NULL)
                    Tablero->winR->end->ficha4=fichaQueEstamosMoviendo;
                return;
            }
            while(focusVicLapR!=NULL)
            {
                if(focusVicLapR->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(focusVicLapR->ficha1==NULL && focusVicLapR->ficha2==NULL)
                    {
                        focusVicLapR->ficha1=fichaQueEstamosMoviendo;
                        break;
                    }
                    else if(focusVicLapR->ficha2==NULL)
                    {
                        focusVicLapR->ficha2=fichaQueEstamosMoviendo;
                        break;
                    }
                }
                focusVicLapR=focusVicLapR->next;
            }


        }
        else{
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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);
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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                        break;
                    }

                }
                focusnode=focusnode->next;
            }
        }
    }
    //-----------------------------JUGADOR VERDE------------------------------------
    if(Player== 'G')
    {
        posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=17;

        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;

        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }
        CasVicLap *focusVicLapG=Tablero->winG;
        if(fichaQueEstamosMoviendo->PaGanar>64)
        {
            if(fichaQueEstamosMoviendo->Path<101)
                fichaQueEstamosMoviendo->Path+=53;
            if(fichaQueEstamosMoviendo->PaGanar>=72)
            {
                printf("Felicidades una ficha llego al final\n");
                if(Tablero->winG->end->ficha1==NULL)
                    Tablero->winG->end->ficha1=fichaQueEstamosMoviendo;
                else if(Tablero->winG->end->ficha2==NULL)
                    Tablero->winG->end->ficha2=fichaQueEstamosMoviendo;
                else if(Tablero->winG->end->ficha3==NULL)
                    Tablero->winG->end->ficha3=fichaQueEstamosMoviendo;
                else if(Tablero->winG->end->ficha4==NULL)
                    Tablero->winG->end->ficha4=fichaQueEstamosMoviendo;
                return;
            }
            while(focusVicLapG!=NULL)
            {
                if(focusVicLapG->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(focusVicLapG->ficha1==NULL && focusVicLapG->ficha2==NULL)
                    {
                        focusVicLapG->ficha1=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                    else if(focusVicLapG->ficha2==NULL)
                    {
                        focusVicLapG->ficha2=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                }
                focusVicLapG=focusVicLapG->next;
            }


        }
        else{
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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                        break;
                    }

                }
                focusnode=focusnode->next;
            }
        }

    }

    //-----------------------------JUGADOR AMARILLO------------------------------------
    if(Player== 'Y')
    {
        posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=34;

        fichaQueEstamosMoviendo->Path+=dado;
        fichaQueEstamosMoviendo->PaGanar+=dado;
        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }
        CasVicLap *focusVicLapY=Tablero->winY;
        if(fichaQueEstamosMoviendo->PaGanar>64)
        {
            if(fichaQueEstamosMoviendo->Path<101)
                fichaQueEstamosMoviendo->Path+=70;
            if(fichaQueEstamosMoviendo->PaGanar>=72)
            {
                printf("Felicidades una ficha llego al final\n");
                if(Tablero->winY->end->ficha1==NULL)
                    Tablero->winY->end->ficha1=fichaQueEstamosMoviendo;
                else if(Tablero->winY->end->ficha2==NULL)
                    Tablero->winY->end->ficha2=fichaQueEstamosMoviendo;
                else if(Tablero->winY->end->ficha3==NULL)
                    Tablero->winY->end->ficha3=fichaQueEstamosMoviendo;
                else if(Tablero->winY->end->ficha4==NULL)
                    Tablero->winY->end->ficha4=fichaQueEstamosMoviendo;
                return;
            }
            while(focusVicLapY!=NULL)
            {
                if(focusVicLapY->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(focusVicLapY->ficha1==NULL && focusVicLapY->ficha2==NULL)
                    {
                        focusVicLapY->ficha1=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                    else if(focusVicLapY->ficha2==NULL)
                    {
                        focusVicLapY->ficha2=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                }
                focusVicLapY=focusVicLapY->next;
            }


        }
        else{
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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                        break;
                    }

                }
                focusnode=focusnode->next;
            }
        }
    }
    //-----------------------------JUGADOR AZUL------------------------------------
    if(Player== 'B')
    {
        posibilidadDeComer=0;
        if(fichaQueEstamosMoviendo->Path==0)
            fichaQueEstamosMoviendo->Path=51;

        fichaQueEstamosMoviendo->Path += dado;
        fichaQueEstamosMoviendo->PaGanar += dado;
        if(fichaQueEstamosMoviendo->Path>68)
        {
            fichaQueEstamosMoviendo->Path-=68;
        }
        CasVicLap *focusVicLapB=Tablero->winB;
        if(fichaQueEstamosMoviendo->PaGanar>64)
        {
            if(fichaQueEstamosMoviendo->Path<101)
                fichaQueEstamosMoviendo->Path+=87;
            if(fichaQueEstamosMoviendo->PaGanar>=72)
            {
                printf("Felicidades una ficha llego al final\n");
                if(Tablero->winB->end->ficha1==NULL)
                    Tablero->winB->end->ficha1=fichaQueEstamosMoviendo;
                else if(Tablero->winB->end->ficha2==NULL)
                    Tablero->winB->end->ficha2=fichaQueEstamosMoviendo;
                else if(Tablero->winB->end->ficha3==NULL)
                    Tablero->winB->end->ficha3=fichaQueEstamosMoviendo;
                else if(Tablero->winB->end->ficha4==NULL)
                    Tablero->winB->end->ficha4=fichaQueEstamosMoviendo;
                return;
            }
            while(focusVicLapB!=NULL)
            {
                if(focusVicLapB->NumCasilla==fichaQueEstamosMoviendo->Path)
                {
                    if(focusVicLapB->ficha1==NULL && focusVicLapB->ficha2==NULL)
                    {
                        focusVicLapB->ficha1=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                    else if(focusVicLapB->ficha2==NULL)
                    {
                        focusVicLapB->ficha2=fichaQueEstamosMoviendo;
                        printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                        break;
                    }
                }
                focusVicLapB=focusVicLapB->next;
            }


        }
        else{
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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

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
                        comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                        break;
                    }

                }
                focusnode=focusnode->next;
            }
        }
    }
}//Realiza los movimientos de la ficha dentro del tablero , la victory lap y la casilla del final.|Dentro de esta funcion se realiza la funcion de comer.

void movimientoFichaDelInicio(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player)
{
    Casilla *focusnode=Tablero->inicio;
    int posibilidadDeComer=0;

    if(Player== 'R')
        fichaQueEstamosMoviendo->Path=1;
    if(Player== 'G')
        fichaQueEstamosMoviendo->Path=18;
    if(Player== 'Y')
        fichaQueEstamosMoviendo->Path=35;
    if(Player== 'B')
        fichaQueEstamosMoviendo->Path =52;

    fichaQueEstamosMoviendo->PaGanar=1;
    while(focusnode!=NULL)
    {
        if(focusnode->NumCasilla==fichaQueEstamosMoviendo->Path)
        {
            if(focusnode->ficha1==NULL)
            {
                focusnode->ficha1=fichaQueEstamosMoviendo;
                printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                return;
            }
            else if(focusnode->ficha1->Player!=Player && focusnode->BanSafe!=1)
            {
                posibilidadDeComer=1;
                comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                return;
            }
            else if(focusnode->ficha2==NULL)
            {
                focusnode->ficha2=fichaQueEstamosMoviendo;
                printf("La casilla queda como: \nNumero: %d\n Ficha: %c%d",focusnode->NumCasilla,fichaQueEstamosMoviendo->Player,fichaQueEstamosMoviendo->Id);
                return;
            }
            else if(focusnode->ficha2->Player!=Player && focusnode->BanSafe!=1)
            {
                posibilidadDeComer=2;
                comer(focusnode,posibilidadDeComer,Tablero,Player,fichaQueEstamosMoviendo);

                return;
            }
            else
            {
                regresarFichaInvalidaAInicio(Tablero,fichaQueEstamosMoviendo,Player);
                printf("Lo siento, tu casilla de salida esta llena, por lo que tu dado se pierde :(\n");
                return;
            }
        }
        focusnode=focusnode->next;
    }

}//Realiza los movimientos del usuario, UNICAMENTE cuando se trata de movimientos desde la casilla de inicio.|Dentro de esta funcion se realiza la funcion de comer.

void comer(Casilla *casillaComida,int cualFicha,Board *Tablero,char Player,Ficha* fichaQueComio)
{
    if(cualFicha==1)
    {
        casillaComida->ficha1->Path=0;
        casillaComida->ficha1->PaGanar=0;
        if(casillaComida->ficha1->Player=='R')
        {
            if(Tablero->baseR->ficha1==NULL)
                Tablero->baseR->ficha1=casillaComida->ficha1;
            else if(Tablero->baseR->ficha2==NULL)
                Tablero->baseR->ficha2=casillaComida->ficha1;
            else if(Tablero->baseR->ficha3==NULL)
                Tablero->baseR->ficha3=casillaComida->ficha1;
            else if(Tablero->baseR->ficha4==NULL)
                Tablero->baseR->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='G')
        {
            if(Tablero->baseG->ficha1==NULL)
                Tablero->baseG->ficha1=casillaComida->ficha1;
            else if(Tablero->baseG->ficha2==NULL)
                Tablero->baseG->ficha2=casillaComida->ficha1;
            else if(Tablero->baseG->ficha3==NULL)
                Tablero->baseG->ficha3=casillaComida->ficha1;
            else if(Tablero->baseG->ficha4==NULL)
                Tablero->baseG->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='B')
        {
            if(Tablero->baseB->ficha1==NULL)
                Tablero->baseB->ficha1=casillaComida->ficha1;
            else if(Tablero->baseB->ficha2==NULL)
                Tablero->baseB->ficha2=casillaComida->ficha1;
            else if(Tablero->baseB->ficha3==NULL)
                Tablero->baseB->ficha3=casillaComida->ficha1;
            else if(Tablero->baseB->ficha4==NULL)
                Tablero->baseB->ficha4=casillaComida->ficha1;
        }
        if(casillaComida->ficha1->Player=='Y')
        {
            if(Tablero->baseY->ficha1==NULL)
                Tablero->baseY->ficha1=casillaComida->ficha1;
            else if(Tablero->baseY->ficha2==NULL)
                Tablero->baseY->ficha2=casillaComida->ficha1;
            else if(Tablero->baseY->ficha3==NULL)
                Tablero->baseY->ficha3=casillaComida->ficha1;
            else if(Tablero->baseY->ficha4==NULL)
                Tablero->baseY->ficha4=casillaComida->ficha1;
        }
        casillaComida->ficha1=fichaQueComio;
    }
    else if(cualFicha==2)
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
        casillaComida->ficha2=fichaQueComio;
    }

    Ficha *fichaAManipular=validacionDeFichaElecta(Tablero,20,Player);
    if(fichaAManipular==NULL)
        return;
    movimientoFicha(20,fichaAManipular,Tablero,Player);
}//Funcion que regresa la ficha comida a su slot de inicio, asigna el valor de la ficha que comio a la casilla y le otorga al jugador la oportunidad de avanzar 20 casillas.
int Revisarbarreras(Board* Tablero,Ficha *fichaAMover,int tiro)
{
    Casilla *focusnode=Tablero->inicio;
    Casilla *casillaBandera=NULL;
    int banderaDeBarrera=0;
    int banderaparaquepuedasmoverelinicio=0;

    while(focusnode!=NULL)
    {
        if(casillaBandera==focusnode)
            break;
        if(focusnode->NumCasilla==fichaAMover->Path)
        {
            casillaBandera=focusnode;
            for(int i=0;i<tiro+1;i++)
            {	if(focusnode->NumCasilla==68)
                {
                    focusnode=Tablero->inicio;
                }
                if(focusnode->ficha1!=NULL&&focusnode->ficha2!=NULL)
                {
                    if(focusnode->ficha1 == fichaAMover || focusnode->ficha2 == fichaAMover)
                        banderaparaquepuedasmoverelinicio=1;

                    else if(focusnode->ficha1 != fichaAMover || focusnode->ficha2 != fichaAMover)
                        banderaDeBarrera=1;
                }
                focusnode=focusnode->next;
            }
            if(banderaparaquepuedasmoverelinicio==1 && banderaDeBarrera==1)
                return 1;
            else if(banderaDeBarrera==1)
                return 1;
        }
        focusnode=focusnode->next;
    }
    return 0;
}//Revisa el tablero para igualar a la ficha que pretende hacer un movimiento, si apartir de esta existe una barrera, regresa 1 , lo que evita que el jugador pueda hacer ese movimiento.
int revisarVictoria(Board *Tablero)
{
    int fichaR1EnEndTrue=existeFichaR1EnEnd(Tablero);
    int fichaR2EnEndTrue=existeFichaR2EnEnd(Tablero);
    int fichaR3EnEndTrue=existeFichaR3EnEnd(Tablero);
    int fichaR4EnEndTrue=existeFichaR4EnEnd(Tablero);
    int fichaG1EnEndTrue=existeFichaG1EnEnd(Tablero);
    int fichaG2EnEndTrue=existeFichaG2EnEnd(Tablero);
    int fichaG3EnEndTrue=existeFichaG3EnEnd(Tablero);
    int fichaG4EnEndTrue=existeFichaG4EnEnd(Tablero);
    int fichaB1EnEndTrue=existeFichaB1EnEnd(Tablero);
    int fichaB2EnEndTrue=existeFichaB2EnEnd(Tablero);
    int fichaB3EnEndTrue=existeFichaB3EnEnd(Tablero);
    int fichaB4EnEndTrue=existeFichaB4EnEnd(Tablero);
    int fichaY1EnEndTrue=existeFichaY1EnEnd(Tablero);
    int fichaY2EnEndTrue=existeFichaY2EnEnd(Tablero);
    int fichaY3EnEndTrue=existeFichaY3EnEnd(Tablero);
    int fichaY4EnEndTrue=existeFichaY4EnEnd(Tablero);

    if(fichaR1EnEndTrue==1 && fichaR2EnEndTrue==1 && fichaR3EnEndTrue==1 && fichaR4EnEndTrue==1)
        return 1;
    else if(fichaG1EnEndTrue==1 && fichaG2EnEndTrue==1 && fichaG3EnEndTrue==1 && fichaG4EnEndTrue==1)
        return 2;
    else if(fichaB1EnEndTrue==1 && fichaB2EnEndTrue==1 && fichaB3EnEndTrue==1 && fichaB4EnEndTrue==1)
        return 3;
    else if(fichaY1EnEndTrue==1 && fichaY2EnEndTrue==1 && fichaY3EnEndTrue==1 && fichaY4EnEndTrue==1)
        return 4;
    else
        return 0;
}//Revisa si algun jugador ha ganado el juego.
//Este bloque de funciones, revisan si en la casilla de victoria existen fichas.
int existeFichaR1EnEnd(Board*Tablero)
{
    if(Tablero->winR->end->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR2EnEnd(Board*Tablero)
{
    if(Tablero->winR->end->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR3EnEnd(Board*Tablero)
{
    if(Tablero->winR->end->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaR4EnEnd(Board*Tablero)
{
    if(Tablero->winR->end->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG1EnEnd(Board*Tablero)
{
    if(Tablero->winG->end->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG2EnEnd(Board*Tablero)
{
    if(Tablero->winG->end->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG3EnEnd(Board*Tablero)
{
    if(Tablero->winG->end->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaG4EnEnd(Board*Tablero)
{
    if(Tablero->winG->end->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB1EnEnd(Board*Tablero)
{
    if(Tablero->winB->end->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB2EnEnd(Board*Tablero)
{
    if(Tablero->winB->end->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB3EnEnd(Board*Tablero)
{
    if(Tablero->winB->end->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaB4EnEnd(Board*Tablero)
{
    if(Tablero->winB->end->ficha4!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY1EnEnd(Board*Tablero)
{
    if(Tablero->winY->end->ficha1!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY2EnEnd(Board*Tablero)
{
    if(Tablero->winY->end->ficha2!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY3EnEnd(Board*Tablero)
{
    if(Tablero->winY->end->ficha3!=NULL)
        return 1;
    else
        return 0;
}
int existeFichaY4EnEnd(Board*Tablero)
{
    if(Tablero->winY->end->ficha4!=NULL)
        return 1;
    else
        return 0;
}

void hacerTiempo()
{
    printf("\nPresiona ENTER para cambiar de turno\n");
    char enter;
    scanf("%c",&enter);

    if(enter==10)
        return;

}//Funcion que pide un enter al usuario entre turno
int estaraLlenaLaCasillaDeSalida(Board*Tablero,char Player)
{
    Casilla *focusnode=Tablero->inicio;
    if(Player=='R')
    {
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==1)
            {
                if(focusnode->ficha1!=NULL && focusnode->ficha2 != NULL)
                    return 1;
                else
                    return 0;
            }
            focusnode=focusnode->next;
        }
    }

    if(Player=='G')
    {
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==18)
            {
                if(focusnode->ficha1!=NULL && focusnode->ficha2 != NULL)
                    return 1;
                else
                    return 0;
            }
            focusnode=focusnode->next;
        }
    }

    if(Player=='Y')
    {
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==35)
            {
                if(focusnode->ficha1!=NULL && focusnode->ficha2 != NULL)
                    return 1;
                else
                    return 0;
            }
            focusnode=focusnode->next;
        }
    }

    if(Player=='B')
    {
        while(focusnode!=NULL)
        {
            if(focusnode->NumCasilla==52)
            {
                if(focusnode->ficha1!=NULL && focusnode->ficha2 != NULL)
                    return 1;
                else
                    return 0;
            }
            focusnode=focusnode->next;
        }
    }

    return 0;
}//Funcion que revisa si la casilla a donde salen las fichas desde su base esta llena.
void pruebaDeBarreras(Board*Tablero)
{
    Casilla* focusnode=Tablero->inicio;

    while(focusnode!=NULL)
    {
        if(focusnode->NumCasilla==2)
        {
            focusnode->ficha1=Tablero->baseB->ficha1;
            focusnode->ficha2=Tablero->baseB->ficha2;
            Tablero->baseB->ficha1=NULL;
            Tablero->baseB->ficha2=NULL;

        }
        focusnode=focusnode->next;
    }
}//Funcion para crear una prueba de barreras.
Ficha* validacionDeFichaElecta(Board*tablero,int tiro,char Player)
{
    Ficha *fichaderetorno=NULL;
    int slotdefichausado=0;
    Casilla * focusnode=NULL;
    int banderaQueNoEncontroLaFicha=1;
    int existenFichasEnVicLap=0;
    int teQuedasteTrabado=0;

    int existenBarreras=0;

    do{
        do{
            do {
                int FichaAMover = 0;
                do {
                    displayOpcionesDeFichaInicio(Player, tablero);
                    printf("\nSelecciona la ficha que quieras mover,que no este en el inicio\n");
                    printf("Input:");
                    scanf("%d", &FichaAMover);
                    if (FichaAMover < 0 || FichaAMover > 4)
                        printf("\nSelecciona una ficha valida, entre 1 y 4\n");
                } while (FichaAMover < 0 || FichaAMover > 4);
                teQuedasteTrabado++;
                if(teQuedasteTrabado==6)
                {
                    printf("Parece que te quedaste trabado, sorry ahi se fue tu turno\n");
                    return NULL;
                }
                existenFichasEnVicLap = hayFichasEnVicLap(tablero, Player);
                if (existenFichasEnVicLap > 0) {
                    fichaderetorno = revisarVicLap(tablero, tiro, Player, FichaAMover);
                    if(fichaderetorno!=NULL)
                        banderaQueNoEncontroLaFicha=0;
                }
                if (fichaderetorno == NULL) {
                    focusnode = tablero->inicio;
                    while (focusnode != NULL) {
                        if (focusnode->ficha1 != NULL) {
                            if (FichaAMover == focusnode->ficha1->Id && Player == focusnode->ficha1->Player) {
                                banderaQueNoEncontroLaFicha = 0;
                                fichaderetorno = focusnode->ficha1;
                                slotdefichausado = 1;
                                break;
                            }
                        }
                        if (focusnode->ficha2 != NULL) {
                            if (FichaAMover == focusnode->ficha2->Id && Player == focusnode->ficha2->Player) {
                                banderaQueNoEncontroLaFicha = 0;
                                fichaderetorno = focusnode->ficha2;
                                slotdefichausado = 2;
                                break;
                            }
                        }
                        focusnode = focusnode->next;

                    }
                }
            }while(banderaQueNoEncontroLaFicha!=0);
        }while(fichaderetorno->PaGanar==0);

        existenBarreras=Revisarbarreras(tablero,fichaderetorno,tiro);

        if(existenBarreras==1)
            printf("\nExiste una barrera, selecciona otra ficha\n");
    }while(existenBarreras==1);

    if(slotdefichausado==1)
    {
        focusnode->ficha1=NULL;
    }
    else if(slotdefichausado==2)
    {
        focusnode->ficha2=NULL;
    }
    return fichaderetorno;
}//Funcion que revisa que la ficha que se eligio no tiene barreras enfrente, que sea valida asi como busca la ficha en el tablero, y la regresa al usuario.
void pruebaDeComer(Board*Tablero)
{
    Casilla* focusnode=Tablero->inicio;

    while(focusnode!=NULL)
    {
        if(focusnode->NumCasilla==2)
        {
            focusnode->ficha1=Tablero->baseB->ficha1;
            //focusnode->ficha2=Tablero->baseB->ficha2;
            Tablero->baseB->ficha1=NULL;
            //Tablero->baseB->ficha2=NULL;

        }
        focusnode=focusnode->next;
    }
}//Funcion para crear un escenario para comer.
Ficha *revisarVicLap(Board*tablero,int tiro,char Player,int FichaAMover)
{
    CasVicLap *focuslap=NULL;
    Ficha *fichaderetorno=NULL;

    if(Player=='R')
        focuslap=tablero->winR;
    if(Player=='G')
        focuslap=tablero->winG;
    if(Player=='Y')
        focuslap=tablero->winY;
    if(Player=='B')
        focuslap=tablero->winB;

    while(focuslap!=NULL)
    {
        if (focuslap->ficha1 != NULL) {
            if (FichaAMover == focuslap->ficha1->Id && Player == focuslap->ficha1->Player) {

                fichaderetorno = focuslap->ficha1;
                focuslap->ficha1=NULL;
                return fichaderetorno;
            }
        }
        if (focuslap->ficha2 != NULL) {
            if (FichaAMover == focuslap->ficha2->Id && Player == focuslap->ficha2->Player) {

                fichaderetorno = focuslap->ficha2;
                focuslap->ficha2=NULL;
                return fichaderetorno;
            }
        }
        focuslap = focuslap->next;
    }
    fichaderetorno=NULL;
    return fichaderetorno;
}//Revisa si la ficha que quiere mover el usuario existe en victoryLap, esta funcion apoya a la funcion evaluacionFichaElecta.
void pruebaDeVicLap(Board*Tablero)
{
    CasVicLap *focuslap=Tablero->winR;

    while(focuslap!=NULL)
    {
        if(focuslap->NumCasilla==102)
        {
            focuslap->ficha1=Tablero->baseR->ficha1;
            //focusnode->ficha2=Tablero->baseB->ficha2;
            Tablero->baseR->ficha1=NULL;
            //Tablero->baseB->ficha2=NULL;
            focuslap->ficha1->Path=102;
            focuslap->ficha1->PaGanar=66;

        }
        focuslap=focuslap->next;
    }
}//Funcion que crea un escenario para revisar el movimiento en VicLap.

int hayFichasEnVicLap(Board*tablero,char Player)
{
    CasVicLap *focuslap=NULL;
    Ficha *fichaderetorno=NULL;
    int cont=0;

    if(Player=='R')
        focuslap=tablero->winR;
    if(Player=='G')
        focuslap=tablero->winG;
    if(Player=='Y')
        focuslap=tablero->winY;
    if(Player=='B')
        focuslap=tablero->winB;

    while(focuslap!=NULL) {
        if (focuslap->ficha1 != NULL) {
            cont++;
        }
        if (focuslap->ficha2 != NULL) {
            cont++;
        }
        focuslap = focuslap->next;
    }
    return cont;
}//Funcion que revisa cuantas fichas existen en VicLap.

void pruebaDeVictoria(Board*Tablero)
{
    CasVicLap *focuslap=Tablero->winR;
    Tablero->winR->end->ficha1=Tablero->baseR->ficha2;
    Tablero->winR->end->ficha2=Tablero->baseR->ficha3;
    Tablero->winR->end->ficha3=Tablero->baseR->ficha4;
    Tablero->baseR->ficha2=NULL;
    Tablero->baseR->ficha3=NULL;
    Tablero->baseR->ficha4=NULL;
    while(focuslap!=NULL)
    {
        if(focuslap->NumCasilla==107)
        {
            focuslap->ficha1=Tablero->baseR->ficha1;
            //focusnode->ficha2=Tablero->baseB->ficha2;
            Tablero->baseR->ficha1=NULL;
            //Tablero->baseB->ficha2=NULL;
            focuslap->ficha1->Path=107;
            focuslap->ficha1->PaGanar=71;

        }
        focuslap=focuslap->next;
    }
}//Funcion que revisa que el juego termina cuando todas las fichas del usuario llegan al final.