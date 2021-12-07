*********************************************************SUPER PARCHIS****************************************************************
*ajustar .txt al tamaño del borde superior del título
para una mejor lectura

--> INSTRUCCIONES DE COMPILACIÓN Y REQUISITOS
Debido a la utilización de la libreria "Windows.h", el programa sólo puede compilarse en computadoras con Windows como SO.
 CLion como IDE preferiblemente para verlo directo de consola. O utilizar el .exe en su lugar (poco recomendado por contrastes
 de color).
 Asegurarse de descargar la carpeta de 'juegosGuardados\' y que quede dentro de la principal (parchisV).

--> INTERFAZ
La implementación del programa queda a nivel consola (stdout) con interacción del usuario en stdin.
Las reglas se encuentran dentro del programa, al seleccionar la opción '2' en el menú.

**************************************************************************************************************************************

--> ESTRUCTURAS

typedef struct board Board;
	Data fields:
		 int currentPlayers;		//Número de jugadores jugando (2-4)

    		 struct casilla *inicio;	//Estructura que almacena los nodos de la lista de casillas
    		 struct casVicLap *winR;	//Estructura que almacena los nodos de la lista de casillas de victory lap para el 
						  jugador rojo
  		 struct casVicLap *winY;	//Estructura que almacena los nodos de la lista de casillas de victory lap para el 
						  jugador amarillo
    		 struct casVicLap *winB;	//Estructura que almacena los nodos de la lista de casillas de victory lap para el 
						  jugador azul
   		 struct casVicLap *winG;	//Estructura que almacena los nodos de la lista de casillas de victory lap para el 
						  jugador verde

   		 struct casInicio *baseR;	//Estructura que almacena las fichas en el inicio del tablero, funciona como la 
						  casilla de base para el equipo rojo
   		 struct casInicio *baseY;	//Estructura que almacena las fichas en el inicio del tablero, funciona como la 
						  casilla de base para el equipo amarillo
   		 struct casInicio *baseB;	//Estructura que almacena las fichas en el inicio del tablero, funciona como la 
						  casilla de base para el equipo azul
   		 struct casInicio *baseG;	//Estructura que almacena las fichas en el inicio del tablero, funciona como la 
					 	  casilla de base para el equipo verde


typedef struct casilla Casilla;
	Data fields:
		int NumCasilla;		//Indica el numero de la casilla (1-68)
   		char BanSafe;		//Indica si es una casilla donde se pueda comer
    		char BanSalida;		//Indica si la casilla es una salida para alguno de los jugadores (R, B, Y, G)
   		struct ficha *ficha1;	//Almacena una ficha
   		struct ficha *ficha2;	//Almacena una ficha
    		struct casilla *next;	//Hace referencia a la siguiente casilla


typedef struct ficha Ficha;
	Data fields:
		 char Player;		//Determina el color del jugador (b, y, r, g)
   		 char Path;		//Path es un acumulador de el progreso de la ficha que se utiliza para determinar su posición 
					  en el tablero
   		 int Id;		//Determina el numero de la ficha (1,2,3,4)
    		 char PaGanar;		//PaGanar es un acumulador que rastrea el progreso de la ficha para validar si esta llega a 
					  la victoria


typedef struct casInicio Base;
	Data fields:
		char Player;		//Almacena la letra del equipo que le corresponde (R,G,Y,B)
   		 char NumCasilla;	//Almacena el valor de la casilla, esta es constante y siempre es 0
   		 struct ficha *ficha1;	//Almacena una ficha
   		 struct ficha *ficha2;	//Almacena una ficha
    		 struct ficha *ficha3;	//Almacena una ficha
   		 struct ficha *ficha4;	//Almacena una ficha


typedef struct casEnd Final;
	Data fields:
		 char Player;		//Almacena la letra del equipo que le corresponde (R,G,Y,B)
   		 int NumCasilla;	//Almacena el numero de la casilla, este es constante y siempre es 108
   		 struct ficha *ficha1;	//Almacena una ficha
   		 struct ficha *ficha2;	//Almacena una ficha
    		 struct ficha *ficha3;	//Almacena una ficha
    		 struct ficha *ficha4;	//Almacena una ficha


typedef struct casVicLap CasVicLap;
	Data fields:
		 char Player;			//Almacena la letra del equipo que le corresponde (R,G,Y,B)
  		 int NumCasilla;		//Almacena el numero de la casilla estos van del 101-107
   		 struct ficha *ficha1;		//Almacena una ficha
  		 struct ficha *ficha2;		//Almacena una ficha
  		 struct casVicLap *next;	//Almacena la referencia a el siguiente nodo en la lista
  		 struct casEnd *end;		//Almacena la referencia a la casilla final (de victoria) esta sólo se almacena 
						  en la primera casilla (101) a pesar de que se crea en las siguientes 6

typedef struct dados Dados;
	Data fields:
		int die1;	//Almacena el valor del primer dado
    		int die2;	//Almacena el valor del segundo dado

*********************************************************************************************************************************
--> FUNCIONES
                -----------------
	           "turnos.c"  
                -----------------

int cuantosJugadores();
    Recibe input del usuario (2-4) y lo devuelve

Dados tiroDados();
    Asigna aleatoriamente un valor a cada uno de los dados. Regresa la estructura de los dos dados.					 

char quienInicia();
    Determina mediante comparaciones entre tiros aleatorios de los usuarios, cual sacó el tiro mas grande, y regresa el jugador 
    que iniciará la partida				 

char cambiarJugador(char Player, Board *juego);
    Dependiendo del numero de jugadores, hace los cambios de jugador en turno y retorna el caracter del jugador.

void Turno(char Player,Board *Tablero,Dados tiro);
    Turno: Funcion con la logica del turno, recibe el jugador en turno, el tablero y el tiro de dados. En funcion de los dados, 
    saca una ficha del inicio si el tiro es 5, en caso de que no lo sea, permite al usuario elegir el dado que quiere mover y 
    realizar el movimiento pertinente en la ficha que selecciono el usuario.

void displayOpcionesDeFichaInicio(char Player,Board *Tablero);
    Imprime las fichas en el tablero, esta funcion es un referencia para el usuario en la terminal (creada antes de colorBoard).

Ficha *fichaElecta(int fichaInput,char playerFichaUsuario,char Player,Board *Tablero,int hayFichasEnInicio,int Tiro);
    Esta función recibe un indicador int para determinar el número de la ficha, un indicador char, para determinar su color, 
    el tablero, el jugador en turno, un valor para determinar si existen fichas en el inicio del juego, así como los valores de 
    los dados. Con estos valores, la función busca en el tablero la ficha que quieres, copia su referencia, la borra de su 
    posición anterior y la regresa al usuario.

void movimientoFicha(int Dado,Ficha *ficha,Board *Tablero,char Player);
    Esta función realiza el movimiento de la ficha en el tablero tras recibir el valor del dado que se usa, y la ficha que
    se pretende mover, a su vez, dentro de ella, si se cumplen las condiciones para que se coma otra ficha, se hace el llamado 
    a esa función.

int valorDado1(Dados dados);	Recibe la estructura de dados y regresa el valor del primero
int valorDado2(Dados dados);	Recibe la estructura de dados y regresa el valor del segundo

void movimientoFichaDelInicio(int dado , Ficha *fichaQueEstamosMoviendo , Board *Tablero , char Player);
    Esta función, realiza los movimientos exclusivamente de las fichas del inicio, ya que requiere cumplir con una serie de 
    condiciones diferentes a las de una ficha normal, recibe los mismos parámetros que la función mover ficha.

void comer(Casilla *casillaComida,int cualCasilla,Board *Tablero,char Player,Ficha * fichaquecomio);
    Esta función recibe el nodo en el cual se va a realizar el movimiento, la ficha que va a comer, así como el tablero, el 
    jugador en turno, y una bandera para determinar que slot de ficha que comerá. La función reinicia los valores  de path 
    y PaGanar de la ficha que se comio, y la regresa al inicio a su posicion original, asigna la ficha que iba a hacer el 
    movimiento a la casilla y otorga al jugador un movimiento de una ficha de 20 espacios mediante el uso de la función 
    movimientoDeFicha().

int Revisarbarreras(Board* Tablero,Ficha *fichaAMover,int tiro);
    Esta función recibe el tablero así como la ficha que pretendemos mover y el tiro de dados que se usará. Una vez en la 
    función, ésta encuentra la ficha que se pretende mover, cuando la encuentra revisa si en las siguientes 'n' posiciones 
    (determinadas por el tiro del dado) existe una barrera que evita el progreso, en caso de que exista, regresa 1.

int revisarVictoria(Board *Tablero);
    Esta función recibe el tablero y revisa el que se cumpla la condición de victoria (que las 4 fichas de un jugador dado estén
    en la casilla final)

void hacerTiempo();
    Esta función le pide al usuario que oprima enter (Su función es evitar que los turnos sean consecutivos para permitir al 
    usuario un pequenio descanso entre turnos).

int estaraLlenaLaCasillaDeSalida(Board*Tablero,char Player);
    Esta función recibe el tablero así como el jugador en turno y revisa si la casilla de salida del usuario está ocupada por dos
    fichas, esto con el objetivo de evitar que se intenten sacar fichas de la casilla de inicio cuando no es posible.

void regresarFichaInvalidaAInicio(Board*Tablero,Ficha*ficha,char Player);
    Recibe el tablero, una ficha y el jugador en turno. Regresa la ficha que se pretendió sacar mediante la función fichaElecta()
    y la regresa a su posición original en inicio para evitar bugs.

void pruebaDeBarreras(Board* Tablero);
    Esta función meramente es una que acomoda las fichas de tal modo que se puede revisar el comportamiento de las barreras.

Ficha* validacionDeFichaElecta(Board*tablero,int tiro,char Player);
    Esta función recibe el tablero, el tiro de dados del jugador y el jugador en turno, en ella se le pide al usuario que seleccione 
    una ficha, a la cual se le harán las validaciones de que no existan barreras y sea una ficha válida para movimiento. Si la ficha
    pasa los criterios, la regresa.

void pruebaDeComer(Board*Tablero);
    Esta función es meramente una prueba que acomoda las fichas para que sea fácil probar la funcionalidad de comer.

Ficha *revisarVicLap(Board*tablero,int tiro,char Player,int FichaAMover);
    Esta función recibe el tablero, el tiro de dados, el jugador en turno y un ID de ficha, con lo que ésta revisa la existencia de
    fichas en las casillas de victory lap, en caso de que la encuentre en victory lap, regresa la ficha.

int hayFichasEnVicLap(Board*tablero,char Player);
    Función que revisa cuántas fichas existen en VicLap, recibe el tablero y el jugador en turno, regresa el número de fichas para
    futuras validaciones dentro de Turno();

void pruebaDeVicLap(Board*Tablero);
    Función que crea un escenario para revisar el movimiento en VicLap.

void pruebaDeVictoria(Board*Tablero);
    Función que revisa que el juego termina cuando todas las fichas del usuario llegan al final.

void editorDeJuego(Board*Tablero);
    Función para editar el juego, recibe el tablero y permite al usuario mediante el input de números el movimiento de las fichas para
    que éstas se acomoden como es necesario.


int existeFichaR1EnInicio(Board*Tablero,char Player);	
int existeFichaR2EnInicio(Board*Tablero,char Player);
int existeFichaR3EnInicio(Board*Tablero,char Player);
int existeFichaR4EnInicio(Board*Tablero,char Player);
int existeFichaG1EnInicio(Board*Tablero,char Player);
int existeFichaG2EnInicio(Board*Tablero,char Player);
int existeFichaG3EnInicio(Board*Tablero,char Player);	//Este bloque de funciones reciben el tablero
int existeFichaG4EnInicio(Board*Tablero,char Player);	  asi como al jugador en turno y regrsan un 1
int existeFichaB1EnInicio(Board*Tablero,char Player);	  si este existe y un 0 si no.
int existeFichaB2EnInicio(Board*Tablero,char Player);
int existeFichaB3EnInicio(Board*Tablero,char Player);
int existeFichaB4EnInicio(Board*Tablero,char Player);
int existeFichaY1EnInicio(Board*Tablero,char Player);
int existeFichaY2EnInicio(Board*Tablero,char Player);
int existeFichaY3EnInicio(Board*Tablero,char Player);
int existeFichaY4EnInicio(Board*Tablero,char Player);

int existeFichaR1EnEnd(Board*Tablero);
int existeFichaR2EnEnd(Board*Tablero);
int existeFichaR3EnEnd(Board*Tablero);
int existeFichaR4EnEnd(Board*Tablero);
int existeFichaG1EnEnd(Board*Tablero);
int existeFichaG2EnEnd(Board*Tablero);
int existeFichaG3EnEnd(Board*Tablero);	//Este bloque de funciones revisan la existencia de 
int existeFichaG4EnEnd(Board*Tablero);	  fichas en el las casillas finales devuelven 1 en
int existeFichaB1EnEnd(Board*Tablero);	  en caso de que existan y 0 que no, reciben el
int existeFichaB2EnEnd(Board*Tablero);	  tablero.
int existeFichaB3EnEnd(Board*Tablero);
int existeFichaB4EnEnd(Board*Tablero);
int existeFichaY1EnEnd(Board*Tablero);
int existeFichaY2EnEnd(Board*Tablero);
int existeFichaY3EnEnd(Board*Tablero);
int existeFichaY4EnEnd(Board*Tablero);
###################################################################################

	-----------------
	   "parchis.c"
	-----------------

Board* newBoard();						//Crea un tablero con la casilla 1 implementada
void emptyEnding(Board *juego, char Player);			//Creación de 4 listas para recorrido ganador de cada color

void finishBoard(Board* juego, int contador);			//Añade 67 casillas restantes al tablero.
void beginning(Board* juego);					//Añade los espacios de inicio donde se almacenan las 4 fichas de salida de 
								  cada color.
void ending(Board* juego);					//Creacion de casillas de gane de cada color.
void finishEnding(Board* juego, int contador,char Player);	//Añade las otras 6 casillas al recorrido ganador de cada color.
void creacionMaestra(Board *juego,int jugadores);		//Crea en su totalidad el tablero.
Board* loadGame(Board *Tablero,int jugadores);			//Función para cargar el juego.
void Savefile(Board*Tablero,char *name);			//Función para salvar el juego.
Board* iniciarEditor(int jugadores);				//Inicializa el editor de tablero



***********************************************************************************************************************************************************


	--------------------
	    "graphics.c"
	--------------------

void Color(int Background, int Text);
    Función necesaria en "Windows.h" para que se asigne el color en stdout en consola.

void validarColor(char Player);
    Recibe un jugador (char) y cambia el color del texto en el que se imprime esa parte hasta que se vuelva a llamar el color normal de la consola con
    la función consoleColor().

void consoleColor();
void cmagenta();	Este bloque de funciones asigna colores específicos al texto
void cgreen();		que se escribe después de ser llamada. El color cambia cada que 
void cblue();		se llama una distinta o se restablece el color consola con consoleColor(); 
void cred();
void cyellow();
void cgrey();

void tBlue();
void tRed();
void tGreen();		Este bloque de funciones imprimen texto en el tablero con sus respectivos espacios.
void tYellow();
void tBase();
void tWinners();

void slot(Board *juego, int num);
    Imprime un slot genérico al recibir un apuntador del tablero y el número de casilla a buscar. Itera hasta que encuentre la casilla con dicho número,
    y procede a imprimir los slots ocupados (1, 2 o ambos).

void safeSlot(Board *juego, int num);
    Imprime un slot seguro con fondo gris para indicar que es una casilla segura. Funciona igual que slot().

void middleSlot();
    Imprime un slot de relleno. Sólo hay 3 en el tablero y se denotan con 'X'.

void exitSlot(Board *juego, int num, char player);
    Imprime un slot que represente la salida de alguno de los 4 jugadores. Utiliza las funciones de colores de texto previas para asignarle un fondo
    a la casilla dependiendo del jugador que reciba. Itera de la misma manera que las dos funciones anteriores.

void viclap(Board *juego, char player, int num);
    Imprime un slot correspondiente a la Victory Lap de alguno de los 4 jugadores. Utiliza las funciones de colores para asignarles fondos
    correspondientes según el jugador. Itera de la misma forma que las anteriores e imprime también de manera idéntica.

void baseR(Board *juego, char player, int num);
void baseG(Board *juego, char player, int num);		Este bloque de funciones imprime la ficha existente en el inicio (base o casilla 0)
void baseB(Board *juego, char player, int num);		de cada color. Si no hay, imprime un '-'.
void baseY(Board *juego, char player, int num);

void finalR(Board *juego, char player, int num);
void finalG(Board *juego, char player, int num);	Este bloque de funciones imprime la ficha existente en el final (casilla 108)
void finalB(Board *juego, char player, int num);	de cada color. Si no hay, imprime un '-'.
void finalY(Board *juego, char player, int num);

void bigdiv();
void tag();
void hdiv();
void vdiv();			Este bloque de funciones imprime caracteres especiales (#), separaciones verticales (|)
void space();			y horizontales (-----), así como espacios predefenidos para imprimir el tablero completo
void spacetags();		junto con los slots de las funciones anteriores.
void tagsmiddle();
void lspace();
void spacewhenfinal();
void enter();

void rules();
    Imprime reglas del juego. Se llama en titleScreen().

titleScreen();
    Imprime el título inicial del juego y las opciones de reglas o empezar juego.

void displayColorBoard(Board *juego);
    Conjunto de llamadas de los bloques de funciones de todos los tipos de slots, bases, finales y caracteres especiales para imprimir el tablero en
    su totalidad.



***********************************************************************************************************************************************************


     