#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parchis.h"
#include "turnos.h"

struct dados{
    int die1;
    int die2;
};

Dados tiroDados()
{
    Dados Dice={0,0};
    time_t t;
    srand((unsigned)time(&t));

    Dice.die1 = ( (rand() % 6)+1);
    Dice.die2 = ( (rand() % 6)+1);

    return Dice;
}
void Turno()
{
    Dados tiro = tiroDados();
    printf("%d,%d",tiro.die1,tiro.die2);
}