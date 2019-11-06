#ifndef __BATALLA_H__
#define __BATALLA_H__
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// El numero de filas debe de ser par
// Creara una matriz de 10 x 10 o (FIL x COL)
#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES 1000
#define MAX_VIDA_ROHAN 10
#define MAX_VIDA_ISENGARD 10
#define MAX_ENERGIA_INICIAL 5
#define MAX_ENERGIA 10
#define RANGO_MELEE 1
#define MAX_PERSONAJES_ESPECIALES_INICIALES 3
#define RANGO_RANGED 3
#define ELFO 'E'
#define URUKHAI 'U'
#define ORCO 'O'
#define HUMANO 'H'
#define OFENSIVO_ISENGARD 'I'
#define DEFENSIVO_ROHAN 'R'
#define ENERGIA_HUMANO 3
#define ENERGIA_ORCO 3
#define ENERGIA_ELFO 8
#define ENERGIA_URUKHAI 8
#define MAX_ENEMIGOS 500
#define TERRENO '#'
typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
	int rango;

} personaje_t;

typedef struct juego {
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];

	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	int energiaRohan;

	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	int energiaIsengard;

	int cantidadJugadores;
	char bandoAutomatico;
	char bandoManual;
	bool isPvP;
} juego_t;
//Agregar a la estructura n bool is pvp que viene de preguntar en incializar

/*
 * Inicializará todos los valores del juego, dejándolo en un estado 
 * inicial válido.
 */
void inicializar_juego(juego_t* juego);// listo

/*
 * Recibirá un personaje, con todos sus campos correctamente cargados y
 * lo dará de alta en el juego, sumándolo al vector correspondiente,
 * posicionándolo también en la matriz.
 */
void posicionar_personaje(juego_t* juego, personaje_t personaje);

/*
 * Realizará la jugada del personaje del bando recibido que
 * se encuentra en la posición posicion_personaje.
 * Se moverá o atacará dependiento lo que corresponda.
 * Actualizará el juego según los efectos del movimiento del
 * personaje, matar rivales, actualizar la matriz, restar vida, etc.
 */
void jugar(juego_t* juego, char bando, int posicion_personaje);

//PRE : Recibe una inicial de un personaje 
//POST : Devuelve el personaje con todos sus datos cargados
personaje_t generarPersonaje( juego_t *juego, char inicialDePersonaje, char bando);

//PRE : Recibe 2 numeros enteros positivos
//POST : Devuelve un numero aleatorio entre ellos
int numeroRandom(int a, int b);

//PRE : Recibe una instancia del juego  y un bando
//POST: Remueve a todos los personajes de los array rohan y isengard que tengan vida menor  0
void removerHeridos( juego_t* juego, char bando);

void imprimirTerreno( juego_t* juego);

#endif /* __BATALLA_H__ */