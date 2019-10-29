#include "batalla.h"
//PRE : Recibe el bando del jugador en turno
//POST : Cambia el valor de bando al del jugdor del siguiente turno
void cambiarBando(char *bando){
    *bando = (*bando == OFENSIVO_ISENGARD) ? DEFENSIVO_ROHAN : OFENSIVO_ISENGARD;
}

//PRE : Recibe una  instancia del juego original y bando
//POST : Devuelve la cantidad de personajes dentro del array del jugador correspondiente
int obtenerCantidadDeBando(juego_t *juego, char *bando){
    return (*bando == OFENSIVO_ISENGARD) ? juego -> cantidad_isengard : juego -> cantidad_rohan;;
}

//PRE : Recibe la inicial de un personaje y el bando
//POST : Devuelve true si el personaje pertenece al bando que ingresaste  
bool personajePerteneceBando(char inicialDePersonaje, char *bando){
    if (*bando == OFENSIVO_ISENGARD)
        return (inicialDePersonaje == ORCO || inicialDePersonaje == URUKHAI);
    return (inicialDePersonaje == HUMANO || inicialDePersonaje == ELFO);
}

//PRE :  Recibe  una inicial por referencia y el bando
//POST : Vuelve a preguntar al usuario para cambiar el valor de inicial de personaje hasta que sea el que pertence al bando
void validarPersonaje(char *inicialDePersonaje, char *bando){
    while(!personajePerteneceBando(*inicialDePersonaje, bando) && *inicialDePersonaje != '.'){
        printf("Inicial erronea, porfavor ingrese una inicial valida: \n");
        scanf(" %c", inicialDePersonaje);
    }
}

//PRE : Recibe el bando
//POST : Devuelve el la inicial de un personaje perteneciente al bando
char preguntarPersonaje(char *bando){
    printf("Ingrese la inicial de un personaje o (.) para saltar el turno: \n");
    char inicialDePersonaje;
    scanf(" %c", &inicialDePersonaje);
    validarPersonaje(&inicialDePersonaje, bando);
    return inicialDePersonaje;
}

void sumarEnergia(juego_t* juego, char* bando){
    int *energiaDeJugador = (*bando == DEFENSIVO_ROHAN) ? &juego -> energiaRohan : &juego -> energiaIsengard;
    if (energiaDeJugador < 10)
        *energiaDeJugador += 1;
}

void imprimirJugadorActual(char *bando){
    if ( *bando == DEFENSIVO_ROHAN)
        printf("ROHAN(H/E): \n");
    else{
        printf("ISENGARD(O/U): \n");
    }
}

//PRE : Recibe una instancia iniciada del juego y el bando(turno del que jugara)
//POST : Recorre todo el array de personajes de  un jugador y juega con cada personaje
void jugarTurno(juego_t* juego, char *bando){
    personaje_t personaje;
    for (int i = 0; i < obtenerCantidadDeBando(juego, bando); i++){ 
        jugar(juego, *bando, i);
    }
    imprimirTerreno(juego);
    if (juego -> isPvP){
        sumarEnergia(juego, bando);
        imprimirJugadorActual(bando);
        char inicialDePersonaje = preguntarPersonaje(bando);
        if (inicialDePersonaje != '.'){
            personaje = generarPersonaje(juego, inicialDePersonaje);
            posicionar_personaje(juego, personaje);
        }
    }else{
        sumarEnergia(juego, bando);
        if (*bando == juego -> bandoAutomatico){
            personaje = generarPersonaje(juego, (juego -> bandoAutomatico == DEFENSIVO_ROHAN) ? HUMANO : ORCO);
            posicionar_personaje(juego, personaje);
        }
        else{
            imprimirJugadorActual(bando);
            char inicialDePersonaje = preguntarPersonaje(bando);
            if (inicialDePersonaje != '.'){
                personaje = generarPersonaje(juego, inicialDePersonaje);
                posicionar_personaje(juego, personaje);
            }
        }
    }
    cambiarBando(bando);
}

//cosas por hacer:  los orcos y humanos no se mueven , mostrar energia vida etc , sumar un punto de energia al final del turno, agregar el turno del usuario duarante player vs pc

int main(){
    juego_t juego;

    srand ((unsigned) time(NULL));
    inicializar_juego(&juego);
    char bando = DEFENSIVO_ROHAN;
    while (juego.llegadas_isengard < MAX_VIDA_ISENGARD && juego.llegadas_rohan < MAX_VIDA_ROHAN){
        removerHeridos(&juego, bando);
        jugarTurno(&juego, &bando);
    }
    return 0;
}