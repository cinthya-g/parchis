//
// Created by cinth on 01/12/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "graphics.h"
#include "parchis.h"

void Color(int Background, int Text){

    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); //Toma consola
    int    New_Color= Text + (Background * 16);

    SetConsoleTextAttribute(Console, New_Color); // Guardar cambios en consola
}

void validarColor(char Player){
    if(Player == 'R')
        Color(BLACK, RED);
    if(Player == 'Y')
        Color(BLACK, YELLOW);
    if(Player == 'B')
        Color(BLACK, BLUE);
    if(Player == 'G')
        Color(BLACK, GREEN);
}

//Funciones que establecen colores especificos de letra y fondo de letra en consola.
void consoleColor(){
    Color(BLACK, LGREEN);
}
void cmagenta(){
    Color(BLACK, MAGENTA);
}
void cgreen(){
    Color(GREEN, BLACK);
}
void cblue(){
    Color(BLUE, BLACK);
}
void cred(){
    Color(RED, BLACK);
}
void cyellow(){
    Color(YELLOW, BLACK);
}
void cgrey(){
    Color(LGREY, BLACK);
}

//Títulos utilizados en el tablero.
void tBlue(){
    cblue();
    printf(" B L U E ");
    cmagenta();
    printf("                       ");
}
void tRed(){
    cred();
    printf(" R E D ");
    cmagenta();
    printf("                         ");
}
void tGreen(){
    cgreen();
    printf(" G R E E N ");
    cmagenta();
    printf("                     ");
}
void tYellow(){
    cyellow();
    printf(" Y E L L O W ");
    cmagenta();
    printf("                   ");
}
void tBase(){
    printf(" Base: ");
}
void tWinners(){
    printf("Final: ");
}

/*
 * Impresiones de tipos de casilla en el tablero.
 * Slot es para casillas normales.
 * SafeSlot para casillas donde no se puede comer a otro.
 * middleSlot sólo rellena la parte de en medio del tablero (asemeja el fin).
 * exitSlot indica la salida de cada jugador.
 * viclap imprime las casillas del recorrido ganador de cada jugador.
 */
void slot(Board *juego, int num){

    Casilla *focusnode = juego->inicio;
    char jugador;

    while(focusnode->NumCasilla != num)
        focusnode = focusnode->next;

    if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
        jugador = focusnode->ficha1->Player;
        validarColor(jugador);
        printf("%c%d   ", jugador, focusnode->ficha1->Id);
        cmagenta();
    }
    if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
        jugador = focusnode->ficha2->Player;
        validarColor(jugador);
        printf("   %c%d", jugador, focusnode->ficha2->Id);
        cmagenta();
    }
    if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
        jugador = focusnode->ficha1->Player;
        validarColor(jugador);
        printf("%c%d ", jugador, focusnode->ficha1->Id);
        cmagenta();

        jugador = focusnode->ficha2->Player;
        validarColor(jugador);
        printf("%c%d", jugador, focusnode->ficha2->Id);
        cmagenta();
    }

    if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
        printf("     ");
}
void safeSlot(Board *juego, int num){
    Casilla *focusnode = juego->inicio;
    char jugador;


    while(focusnode->NumCasilla != num)
        focusnode = focusnode->next;
    cgrey();

    if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
        jugador = focusnode->ficha1->Player;
        printf("%c%d   ", jugador, focusnode->ficha1->Id);
        cmagenta();
    }
    if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
        jugador = focusnode->ficha2->Player;
        printf("   %c%d", jugador, focusnode->ficha2->Id);
        cmagenta();
    }
    if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
        jugador = focusnode->ficha1->Player;
        printf("%c%d ", jugador, focusnode->ficha1->Id);

        jugador = focusnode->ficha2->Player;
        printf("%c%d", jugador, focusnode->ficha2->Id);
        cmagenta();
    }
    if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
        printf("     ");

    cmagenta();

}
void middleSlot(){
    printf("  X  ");
}
void exitSlot(Board *juego, int num, char player){
    Casilla *focusnode = juego->inicio;
    char jugador;

    while(focusnode->NumCasilla != num)
        focusnode = focusnode->next;

    if(player == 'R'){
        cred();
        if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d   ", jugador, focusnode->ficha1->Id);
        }
        if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
            jugador = focusnode->ficha2->Player;
            printf("   %c%d", jugador, focusnode->ficha2->Id);

        }
        if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d ", jugador, focusnode->ficha1->Id);

            jugador = focusnode->ficha2->Player;
            printf("%c%d", jugador, focusnode->ficha2->Id);
        }
        if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
            printf("     ");

        cmagenta();
    }

    if(player == 'G'){
        cgreen();
        if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d   ", jugador, focusnode->ficha1->Id);
        }
        if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
            jugador = focusnode->ficha2->Player;
            printf("   %c%d", jugador, focusnode->ficha2->Id);

        }
        if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d ", jugador, focusnode->ficha1->Id);

            jugador = focusnode->ficha2->Player;
            printf("%c%d", jugador, focusnode->ficha2->Id);
        }
        if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
            printf("     ");

        cmagenta();
    }

    if(player == 'B'){
        cblue();
        if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d   ", jugador, focusnode->ficha1->Id);
        }
        if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
            jugador = focusnode->ficha2->Player;
            printf("   %c%d", jugador, focusnode->ficha2->Id);

        }
        if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d ", jugador, focusnode->ficha1->Id);

            jugador = focusnode->ficha2->Player;
            printf("%c%d", jugador, focusnode->ficha2->Id);
        }
        if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
            printf("     ");

        cmagenta();
    }

    if(player == 'Y'){
        cyellow();
        if(focusnode->ficha1 != NULL && focusnode->ficha2 == NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d   ", jugador, focusnode->ficha1->Id);
        }
        if(focusnode->ficha2 != NULL && focusnode->ficha1 == NULL){
            jugador = focusnode->ficha2->Player;
            printf("   %c%d", jugador, focusnode->ficha2->Id);

        }
        if(focusnode->ficha1 != NULL && focusnode->ficha2 != NULL){
            jugador = focusnode->ficha1->Player;
            printf("%c%d ", jugador, focusnode->ficha1->Id);

            jugador = focusnode->ficha2->Player;
            printf("%c%d", jugador, focusnode->ficha2->Id);
        }
        if(focusnode->ficha1 == NULL && focusnode->ficha2 == NULL)
            printf("     ");

        cmagenta();
    }
}
void viclap(Board *juego, char player, int num){
    CasVicLap *focuslap;

    if(player == 'R'){
        focuslap = juego->winR;
        while(focuslap->NumCasilla != num)
            focuslap = focuslap->next;

        if(focuslap->ficha1 != NULL){
            cred();
            printf("%c%d   ", player, focuslap->ficha1->Id);
            cmagenta();
        }
        if(focuslap->ficha2 != NULL){
            cred();
            printf("   %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 != NULL && focuslap->ficha2 != NULL){
            cred();
            printf("%c%d ", player, focuslap->ficha1->Id);
            printf(" %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 == NULL && focuslap->ficha2 == NULL){
            cred();
            printf("     ");
            cmagenta();
        }
    }

    if(player == 'G'){
        focuslap = juego->winG;
        while(focuslap->NumCasilla != num)
            focuslap = focuslap->next;

        if(focuslap->ficha1 != NULL){
            cgreen();
            printf("%c%d   ", player, focuslap->ficha1->Id);
            cmagenta();
        }
        if(focuslap->ficha2 != NULL){
            cgreen();
            printf("   %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 != NULL && focuslap->ficha2 != NULL){
            cgreen();
            printf("%c%d ", player, focuslap->ficha1->Id);
            printf(" %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 == NULL && focuslap->ficha2 == NULL){
            cgreen();
            printf("     ");
            cmagenta();
        }
    }

    if(player == 'B'){
        focuslap = juego->winB;
        while(focuslap->NumCasilla != num)
            focuslap = focuslap->next;

        if(focuslap->ficha1 != NULL){
            cblue();
            printf("%c%d   ", player, focuslap->ficha1->Id);
            cmagenta();
        }
        if(focuslap->ficha2 != NULL){
            cblue();
            printf("   %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 != NULL && focuslap->ficha2 != NULL){
            cblue();
            printf("%c%d ", player, focuslap->ficha1->Id);
            printf(" %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 == NULL && focuslap->ficha2 == NULL){
            cblue();
            printf("     ");
            cmagenta();
        }

    }
    if(player == 'Y'){
        focuslap = juego->winY;
        while(focuslap->NumCasilla != num)
            focuslap = focuslap->next;

        if(focuslap->ficha1 != NULL){
            cyellow();
            printf("%c%d   ", player, focuslap->ficha1->Id);
            cmagenta();
        }
        if(focuslap->ficha2 != NULL){
            cyellow();
            printf("   %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 != NULL && focuslap->ficha2 != NULL){
            cyellow();
            printf("%c%d ", player, focuslap->ficha1->Id);
            printf(" %c%d", player, focuslap->ficha2->Id);
            cmagenta();
        }
        if(focuslap->ficha1 == NULL && focuslap->ficha2 == NULL){
            cyellow();
            printf("     ");
            cmagenta();
        }
    }
}

/*
 * Imprime las fichas disponibles en la base de cada jugador (fichas que no han salido
 * al tablero).
 */
void baseR(Board *juego, char player, int num){
    validarColor(player);
        if(juego->baseR->ficha1 != NULL && num == 1)
            printf("       %c%d       ", player, juego->baseR->ficha1->Id);
        if(juego->baseR->ficha1 == NULL && num == 1)
            printf("         -      ");

        if(juego->baseR->ficha2 != NULL && num == 2)
            printf("       %c%d       ", player, juego->baseR->ficha2->Id);
        if(juego->baseR->ficha2 == NULL && num == 2)
            printf("         -      ");

        if(juego->baseR->ficha3 != NULL && num == 3)
            printf("       %c%d       ", player, juego->baseR->ficha3->Id);
        if(juego->baseR->ficha3 == NULL && num == 3)
            printf("         -      ");

        if(juego->baseR->ficha4 != NULL && num == 4)
            printf("       %c%d       ", player, juego->baseR->ficha4->Id);
        if(juego->baseR->ficha4 == NULL && num == 4)
            printf("         -      ");

        cmagenta();
}
void baseG(Board *juego, char player, int num){
    validarColor(player);

        if(juego->baseG->ficha1 != NULL && num == 1)
            printf("       %c%d       ", player, juego->baseG->ficha1->Id);
        if(juego->baseG->ficha1 == NULL && num == 1)
            printf("         -      ");

        if(juego->baseG->ficha2 != NULL && num == 2)
            printf("       %c%d       ", player, juego->baseG->ficha2->Id);
        if(juego->baseG->ficha2 == NULL && num == 2)
            printf("         -      ");

        if(juego->baseG->ficha3 != NULL && num == 3)
            printf("       %c%d       ", player, juego->baseG->ficha3->Id);
        if(juego->baseG->ficha3 == NULL && num == 3)
            printf("         -      ");

        if(juego->baseG->ficha4 != NULL && num == 4)
            printf("       %c%d       ", player, juego->baseG->ficha4->Id);
        if(juego->baseG->ficha4 == NULL && num == 4)
            printf("         -      ");


        cmagenta();

}
void baseB(Board *juego, char player, int num){
    validarColor(player);
    if(juego->baseB->ficha1 != NULL && num == 1)
        printf("       %c%d       ", player, juego->baseB->ficha1->Id);
    if(juego->baseB->ficha1 == NULL && num == 1)
        printf("         -      ");

    if(juego->baseB->ficha2 != NULL && num == 2)
        printf("       %c%d       ", player, juego->baseB->ficha2->Id);
    if(juego->baseB->ficha2 == NULL && num == 2)
        printf("         -      ");

    if(juego->baseB->ficha3 != NULL && num == 3)
        printf("       %c%d       ", player, juego->baseB->ficha3->Id);
    if(juego->baseB->ficha3 == NULL && num == 3)
        printf("         -      ");

    if(juego->baseB->ficha4 != NULL && num == 4)
        printf("       %c%d       ", player, juego->baseB->ficha4->Id);
    if(juego->baseB->ficha4 == NULL && num == 4)
        printf("         -      ");

    cmagenta();
}
void baseY(Board *juego, char player, int num){
    validarColor(player);
    if(juego->baseY->ficha1 != NULL && num == 1)
        printf("       %c%d       ", player, juego->baseY->ficha1->Id);
    if(juego->baseY->ficha1 == NULL && num == 1)
        printf("         -      ");

    if(juego->baseY->ficha2 != NULL && num == 2)
        printf("       %c%d       ", player, juego->baseY->ficha2->Id);
    if(juego->baseY->ficha2 == NULL && num == 2)
        printf("         -      ");

    if(juego->baseY->ficha3 != NULL && num == 3)
        printf("       %c%d       ", player, juego->baseY->ficha3->Id);
    if(juego->baseY->ficha3 == NULL && num == 3)
        printf("         -      ");

    if(juego->baseY->ficha4 != NULL && num == 4)
        printf("       %c%d       ", player, juego->baseY->ficha4->Id);
    if(juego->baseY->ficha4 == NULL && num == 4)
        printf("         -      ");

    cmagenta();

}


//Imprime las fichas que han llegado al final del recorrido de cada jugador.
void finalR(Board *juego, char player, int num){
    validarColor(player);
    if(juego->winR->end->ficha1 != NULL && num == 1)
        printf("       %c%d                ", player, juego->winR->end->ficha1->Id);
    if(juego->winR->end->ficha1 == NULL && num == 1)
        printf("        -                ");

    if(juego->winR->end->ficha2 != NULL && num == 2)
        printf("       %c%d                ", player, juego->winR->end->ficha2->Id);
    if(juego->winR->end->ficha2 == NULL && num == 2)
        printf("        -                ");

    if(juego->winR->end->ficha3 != NULL && num == 3)
        printf("       %c%d                ", player, juego->winR->end->ficha3->Id);
    if(juego->winR->end->ficha3 == NULL && num == 3)
        printf("        -                ");

    if(juego->winR->end->ficha4 != NULL && num == 4)
        printf("       %c%d                ", player, juego->winR->end->ficha4->Id);
    if(juego->winR->end->ficha4 == NULL && num == 4)
        printf("        -                ");


    cmagenta();
}
void finalG(Board *juego, char player, int num){
    validarColor(player);
    if(juego->winG->end->ficha1 != NULL && num == 1)
        printf("       %c%d                ", player, juego->winG->end->ficha1->Id);
    if(juego->winG->end->ficha1 == NULL && num == 1)
        printf("        -                ");

    if(juego->winG->end->ficha2 != NULL && num == 2)
        printf("       %c%d                ", player, juego->winG->end->ficha2->Id);
    if(juego->winG->end->ficha2 == NULL && num == 2)
        printf("        -                ");

    if(juego->winG->end->ficha3 != NULL && num == 3)
        printf("       %c%d                ", player, juego->winG->end->ficha3->Id);
    if(juego->winG->end->ficha3 == NULL && num == 3)
        printf("        -                ");

    if(juego->winG->end->ficha4 != NULL && num == 4)
        printf("       %c%d                ", player, juego->winG->end->ficha4->Id);
    if(juego->winG->end->ficha4 == NULL && num == 4)
        printf("        -                ");

    cmagenta();
}
void finalB(Board *juego, char player, int num){
    validarColor(player);
    if(juego->winB->end->ficha1 != NULL && num == 1)
        printf("       %c%d                ", player, juego->winB->end->ficha1->Id);
    if(juego->winB->end->ficha1 == NULL && num == 1)
        printf("        -                ");

    if(juego->winB->end->ficha2 != NULL && num == 2)
        printf("       %c%d                ", player, juego->winB->end->ficha2->Id);
    if(juego->winB->end->ficha2 == NULL && num == 2)
        printf("        -                ");

    if(juego->winB->end->ficha3 != NULL && num == 3)
        printf("       %c%d                ", player, juego->winB->end->ficha3->Id);
    if(juego->winB->end->ficha3 == NULL && num == 3)
        printf("        -                ");

    if(juego->winB->end->ficha4 != NULL && num == 4)
        printf("       %c%d                ", player, juego->winB->end->ficha4->Id);
    if(juego->winB->end->ficha4 == NULL && num == 4)
        printf("        -                ");

    cmagenta();
}
void finalY(Board *juego, char player, int num){
    validarColor(player);
        if(juego->winY->end->ficha1 != NULL && num == 1)
            printf("       %c%d                ", player, juego->winY->end->ficha1->Id);
        if(juego->winY->end->ficha1 == NULL && num == 1)
            printf("        -                ");

        if(juego->winY->end->ficha2 != NULL && num == 2)
            printf("       %c%d                ", player, juego->winY->end->ficha2->Id);
        if(juego->winY->end->ficha2 == NULL && num == 2)
            printf("        -                ");

        if(juego->winY->end->ficha3 != NULL && num == 3)
            printf("       %c%d                ", player, juego->winY->end->ficha3->Id);
        if(juego->winY->end->ficha3 == NULL && num == 3)
            printf("        -                ");

        if(juego->winY->end->ficha4 != NULL && num == 4)
            printf("       %c%d                ", player, juego->winY->end->ficha4->Id);
        if(juego->winY->end->ficha4 == NULL && num == 4)
            printf("        -                ");

    cmagenta();
}

//Imprime caracteres y espacios para desplegar el tablero.
void bigdiv(){
    printf("#######################################################################################################");
}
void tag(){
    printf("#");
}
void hdiv(){
    printf("-----");
}
void vdiv(){
    printf("|");
}
void space(){
    printf("                                         ");
}
void spacetags(){
    printf("###########################################");
}
void tagsmiddle(){
    printf("###########################################");
}
void lspace(){
    printf("         ");
}
void spacewhenfinal(){
    printf("                  ");
}
void enter(){
    printf("\n");
}

//Pantalla de inicio.
void titleScreen() {
    cmagenta();
    bigdiv();
    enter();
    space();
    cred(); printf("S U");
    cyellow(); printf(" P E R");
    cmagenta(); printf(" ");
    cblue(); printf("P A R");
    cgreen(); printf(" C H I S");
    cmagenta();
    space();
    enter();
    bigdiv();
    enter();
}

//Conjunto de funciones anteriores que imprime el tablero en consola.
void displayColorBoard(Board *juego){

    //Franja superior
    Color(BLACK, MAGENTA);
    bigdiv();
    enter();
    //48-46
    tag(); space(); tag(); slot(juego, 48); vdiv(); safeSlot(juego, 47); vdiv(); slot(juego, 46); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //49-45
    tag(); space(); tag(); slot(juego, 49); tag(); viclap(juego, 'B', 101); tag(); slot(juego, 45); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //50-44
    tag(); lspace(); tBlue(); tag(); slot(juego, 50); tag(); viclap(juego, 'B', 102); tag(); slot(juego, 44); tag(); lspace(); tYellow(); tag();
    enter();
    tag(); tBase(); lspace(); tWinners(); spacewhenfinal(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag();
    tBase(); lspace(); tWinners(); spacewhenfinal(); tag();
    enter();
    //51-43
    tag(); baseB(juego, 'B', 1); finalB(juego, 'B', 1);
    tag(); slot(juego, 51); tag(); viclap(juego, 'B', 103); tag(); slot(juego, 43);
    tag(); baseY(juego, 'Y', 1); finalY(juego, 'Y', 1); tag();
    enter();
    tag(); baseB(juego, 'B', 2); finalB(juego, 'B', 2);
    tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag();
    baseY(juego, 'Y', 2); finalY(juego, 'Y', 2); tag();
    enter();
    //52-42
    tag(); baseB(juego, 'B', 3); finalB(juego, 'B', 3);
    tag(); exitSlot(juego, 52, 'B'); tag(); viclap(juego, 'B', 104); tag(); safeSlot(juego, 42);
    tag(); baseY(juego, 'Y', 3); finalY(juego, 'Y', 3); tag();
    enter();
    tag(); baseB(juego, 'B', 4); finalB(juego, 'B', 4);
    tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag();
    baseY(juego, 'Y', 4); finalY(juego, 'Y', 4); tag();
    enter();
    //53-41
    tag(); space(); tag(); slot(juego, 53); tag(); viclap(juego, 'B', 105); tag(); slot(juego, 41); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //54-40
    tag(); space(); tag(); slot(juego, 54); tag(); viclap(juego, 'B', 106); tag(); slot(juego, 40); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //55-39
    tag(); space(); tag(); slot(juego, 55); tag(); viclap(juego, 'B', 107); tag(); slot(juego, 39); tag(); space(); tag();
    enter();
    spacetags(); hdiv(); tag(); hdiv(); tag(); hdiv(); spacetags();
    enter();
    //63-31
    tag(); slot(juego, 63); vdiv(); slot(juego, 62); vdiv(); slot(juego, 61); vdiv(); slot(juego, 60); vdiv();
    safeSlot(juego, 59); vdiv(); slot(juego, 58); vdiv(); slot(juego, 57); vdiv(); slot(juego, 56); tag();
    middleSlot(); tag();
    slot(juego, 38); vdiv(); slot(juego, 37); vdiv(); slot(juego, 36); vdiv(); exitSlot(juego, 35, 'Y'); vdiv();
    slot(juego, 34); vdiv(); slot(juego, 33); vdiv(); slot(juego, 32); vdiv(); slot(juego, 31); tag();
    enter();
    tag(); hdiv(); tagsmiddle(); hdiv(); tagsmiddle(); hdiv(); tag();
    enter();
    //64-30
    tag(); safeSlot(juego, 64); vdiv(); viclap(juego, 'R', 101); vdiv(); viclap(juego, 'R', 102); vdiv();
    viclap(juego, 'R', 103); vdiv(); viclap(juego, 'R', 104); vdiv(); viclap(juego, 'R', 105); vdiv();
    viclap(juego, 'R', 106); vdiv(); viclap(juego, 'R', 107); vdiv();
    middleSlot(); vdiv();
    viclap(juego, 'Y', 107); vdiv(); viclap(juego, 'Y', 106); vdiv(); viclap(juego, 'Y', 105); vdiv();
    viclap(juego, 'Y', 104); vdiv(); viclap(juego, 'Y', 103); vdiv(); viclap(juego, 'Y', 102); vdiv();
    viclap(juego, 'Y', 101); vdiv(); safeSlot(juego, 30); tag();
    enter();
    tag(); hdiv(); tagsmiddle(); hdiv(); tagsmiddle(); hdiv(); tag();
    enter();
    //65-29
    tag(); slot(juego, 65); vdiv(); slot(juego, 66); vdiv(); slot(juego, 67); vdiv();
    slot(juego, 68); vdiv(); exitSlot(juego, 1, 'R'); vdiv(); slot(juego, 2); vdiv();
    slot(juego, 3); vdiv(); slot(juego, 4); vdiv();
    middleSlot(); vdiv();
    slot(juego, 22); vdiv(); slot(juego, 23); vdiv(); slot(juego, 24); vdiv();
    safeSlot(juego, 25); vdiv(); slot(juego, 26); vdiv(); slot(juego, 27); vdiv();
    slot(juego, 28); vdiv(); slot(juego, 29); tag();
    enter();
    spacetags(); hdiv(); tag(); hdiv(); tag(); hdiv(); spacetags();
    enter();
    //5-21
    tag(); space(); tag(); slot(juego, 5); tag(); viclap(juego, 'G', 107); tag(); slot(juego, 21); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //6-20
    tag(); space(); tag(); slot(juego, 6); tag(); viclap(juego, 'G', 106); tag(); slot(juego, 20); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //7-19
    tag(); lspace(); tRed(); tag(); slot(juego, 7); tag(); viclap(juego, 'G', 105); tag(); slot(juego, 19); tag(); lspace(); tGreen(); tag();
    enter();
    tag(); tBase(); lspace(); tWinners(); spacewhenfinal(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag();
    tBase(); lspace(); tWinners(); spacewhenfinal(); tag();
    enter();
    //8-18
    tag(); baseR(juego, 'R', 1); finalR(juego, 'R', 1);
    tag(); safeSlot(juego, 8); tag(); viclap(juego, 'G', 104); tag(); exitSlot(juego, 18, 'G');
    tag(); baseG(juego, 'G', 1); finalG(juego, 'G', 1); tag();
    enter();
    tag(); baseR(juego, 'R', 2); finalR(juego, 'R', 2);
    tag(); hdiv(); tag(); hdiv(); tag(); hdiv();
    tag(); baseG(juego, 'G', 2); finalG(juego, 'G', 2); tag();
    enter();
    //9-17
    tag(); baseR(juego,'R', 3); finalR(juego, 'R', 3);
    tag(); slot(juego, 9); tag(); viclap(juego, 'G', 103); tag(); slot(juego, 17);
    tag(); baseG(juego, 'G', 3); finalG(juego, 'G', 3); tag();
    enter();
    tag(); baseR(juego, 'R', 4); finalR(juego, 'R', 4);
    tag(); hdiv(); tag(); hdiv(); tag(); hdiv();
    tag(); baseG(juego, 'G', 4); finalG(juego, 'G', 4); tag();
    enter();
    //10-16
    tag(); space(); tag(); slot(juego, 10); tag(); viclap(juego, 'G', 102); tag(); slot(juego, 16); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //11-15
    tag(); space(); tag(); slot(juego, 11); tag(); viclap(juego, 'G', 101); tag(); slot(juego, 15); tag(); space(); tag();
    enter();
    tag(); space(); tag(); hdiv(); tag(); hdiv(); tag(); hdiv(); tag(); space(); tag();
    enter();
    //12-14
    tag(); space(); tag(); slot(juego, 12); vdiv(); safeSlot(juego, 13); vdiv(); slot(juego, 14); tag(); space(); tag();
    enter();
    bigdiv();
    enter();

    consoleColor();
}
