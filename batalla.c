#include "batalla.h"
#include "perfil.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numeroRandom(int a, int b){
    srand ((unsigned) time(NULL));
    return rand() % b + a;
}

int calcularPlus(int intensidad){
    return intensidad * numeroRandom(0,5);
}

void validarJugadores(int *cantJugadores){
    while(*cantJugadores != 1 || *cantJugadores != 2){
        printf("Numero ingresado es invalido, ingrese el numero de jugadores (1 / 2): ");
        scanf ("%i",cantJugadores);
    }
}

int preguntarJugadores(){
    int cantJugadores = 1;
    printf("Ingrese la cantidad de jugadores (1 / 2): ");
    scanf("%i", &cantJugadores);
    validarJugadores(&cantJugadores);
    return cantJugadores;
}
void asignarBandoOpuesto(char tipo,char *tipoContrario,int intensidad, int *intensidadOpuesta){

    *tipoContrario = (tipo == 'O') ? 'D': 'O';
    *intensidadOpuesta = 10 - intensidad;
}

personaje_t generarPersonajeEspecial(char inicialDePersonaje, juego_t *juego){
    personaje_t personaje;
    int coordX = 0, coordY = 0;
    personaje.codigo = inicialDePersonaje;
    if (inicialDePersonaje == ELFO){
        do{
            coordY = numeroRandom(1,MAX_TERRENO_FIL/2);
            coordX = numeroRandom(0,MAX_TERRENO_COL);
        } while(juego -> terreno[coordX][coordY] == ELFO);
        personaje.ataque = 10 + juego -> plus_rohan;
        personaje.vida = 200 - juego -> plus_rohan;
    }else{
        do{
            coordY = numeroRandom(MAX_TERRENO_FIL/2 + 1, MAX_TERRENO_FIL - 1);
            coordX = numeroRandom(0, MAX_TERRENO_COL);
        } while (juego -> terreno[coordX][coordY] == URUKHAI);
        personaje.ataque = 10 + juego -> plus_isengard;
        personaje.vida = 200 - juego -> plus_isengard;
    }
    personaje.fila = coordY;
    personaje.columna = coordX;
    return personaje;
}

personaje_t generarPersonaje( char inicialDePersonaje, juego_t *juego){
    personaje_t personaje;
    personaje.codigo = inicialDePersonaje;
    if (inicialDePersonaje == HUMANO){
        personaje.ataque = 50 + juego -> plus_rohan;
        personaje.vida = 100 - juego -> plus_rohan;
        personaje.fila = MAX_TERRENO_FIL;
        personaje.columna = numeroRandom(0, MAX_TERRENO_COL);
    }else{
        personaje.ataque = 50 + juego -> plus_isengard;
        personaje.vida = 100 - juego -> plus_isengard;
        personaje.fila = 0;
        personaje.columna = numeroRandom(0, MAX_TERRENO_COL);
    }
    return personaje;
}

void asignarPersonajesEspeciales(int maxPersonajesEspeciales, juego_t *juego){
    for (int i = 0 ; i < maxPersonajesEspeciales; i++){
        // genera 3 elfos en posiciones aleatorias del lado de rohan
        juego -> isengard[i] = generarPersonajeEspecial(ELFO, juego);
        juego -> cantidad_isengard++;
        //genera 3 urukhai en posiciones aleatorias del lado de isengard
        juego -> isengard[i] = generarPersonajeEspecial(URUKHAI, juego);
        juego -> cantidad_rohan++;
    }
}

void inicializar_juego(juego_t* juego){
    int intensidad1 = 0;
    int intensidad2 = 0;
    char bando1 = ' ';
    char bando2 = ' ';
    perfil(&bando1, &intensidad1);
    asignarBandoOpuesto(bando1, &bando2, intensidad1, &intensidad2);
    int jugadores = preguntarJugadores();
    juego -> cantidadJugadores = jugadores;
    juego -> cantidad_rohan = MAX_PERSONAJES_ESPECIALES;
    juego -> cantidad_isengard = MAX_PERSONAJES_ESPECIALES;
    juego -> llegadas_rohan = 0;
    juego -> llegadas_isengard = 0;
    if (bando1 == 'O'){
        juego -> plus_rohan = calcularPlus(intensidad1);
        juego -> plus_isengard = calcularPlus(intensidad2);
    }else{
        juego -> plus_rohan = calcularPlus(intensidad2);
        juego -> plus_isengard = calcularPlus(intensidad1);
    }
    asignarPersonajesEspeciales(MAX_PERSONAJES_ESPECIALES, juego);
}

void posicionar_personaje(juego_t* juego, personaje_t personaje){
    if (personaje.codigo == ELFO){
        juego -> terreno[personaje.columna][personaje.fila] = ELFO;
        juego -> rohan[juego ->cantidad_rohan] = personaje;
        juego -> cantidad_rohan++;
    }else if (personaje.codigo == URUKHAI){
        juego -> terreno[personaje.columna][personaje.fila] = URUKHAI;
        juego -> isengard[juego ->cantidad_isengard] = personaje;
        juego -> cantidad_isengard++;
    }else if (personaje.codigo == HUMANO){
        juego -> terreno[personaje.columna][personaje.fila] = HUMANO;
        juego -> rohan[juego ->cantidad_rohan] = personaje;
        juego -> cantidad_isengard++;
    }else{
        juego -> terreno[personaje.columna][personaje.fila] = ORCO;
        juego -> isengard[juego ->cantidad_isengard] = personaje;
        juego -> cantidad_isengard++;
    }
}