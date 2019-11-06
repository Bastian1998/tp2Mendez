#include "batalla.h"
//PRE : Recibe el bando del jugador en turno
//POST : Cambia el valor de bando al del jugdor del siguiente turno
void cambiarBando(char *bando){
    *bando = (*bando == OFENSIVO_ISENGARD) ? DEFENSIVO_ROHAN : OFENSIVO_ISENGARD;
}

//PRE : Recibe una  instancia del juego original y bando
//POST : Devuelve la cantidad de personajes dentro del array del jugador correspondiente
int obtenerCantidadDeBando(juego_t *juego, char *bando){
    return (*bando == OFENSIVO_ISENGARD) ? juego -> cantidad_isengard : juego -> cantidad_rohan;
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
    if (*energiaDeJugador < 10)
        *energiaDeJugador += 1;
}

void imprimirJugadorActual(char *bando){
    if ( *bando == DEFENSIVO_ROHAN)
        printf("ROHAN(H/E): \n");
    else{
        printf("ISENGARD(O/U): \n");
    }
}
//PRE : Recibe la energia de un bando y la inicial de personaje
//POST : devuelve True si la energia  es suficiente para generar el personaje
bool suficienteEnergia(int energia , char inicialDePersonaje){
    if ((inicialDePersonaje == 'O' || inicialDePersonaje == 'H') && energia < 3)
        return false;
    else if ((inicialDePersonaje == 'E' || inicialDePersonaje == 'U') && energia < 8)
        return false;
    return true;
}

//PRE : Recibe una instancia iniciada del juego y el bando(turno del que jugara)
//POST : Recorre todo el array de personajes de  un jugador y juega con cada personaje
void jugarTurno(juego_t* juego, char *bando){
    personaje_t personaje;
    int energia = (*bando == OFENSIVO_ISENGARD) ? juego -> energiaIsengard : juego -> energiaRohan;
    for (int i = 0; i < obtenerCantidadDeBando(juego, bando); i++){ 
        jugar(juego, *bando, i);
    }
    imprimirTerreno(juego);
    if (juego -> isPvP){
        sumarEnergia(juego, bando);
        imprimirJugadorActual(bando);
        char inicialDePersonaje = preguntarPersonaje(bando);
        if (inicialDePersonaje != '.' && suficienteEnergia(energia, inicialDePersonaje)){
            personaje = generarPersonaje(juego, inicialDePersonaje, *bando);
            posicionar_personaje(juego, personaje);
        }
    }else{
        sumarEnergia(juego, bando);
        if (*bando == juego -> bandoAutomatico && energia >= 3){
            personaje = generarPersonaje(juego, (juego -> bandoAutomatico == DEFENSIVO_ROHAN) ? HUMANO : ORCO, *bando);
            posicionar_personaje(juego, personaje);
        }
        else if (*bando == juego -> bandoManual){
            imprimirJugadorActual(bando);
            char inicialDePersonaje = preguntarPersonaje(bando);
            if (inicialDePersonaje != '.' && suficienteEnergia(energia, inicialDePersonaje)){
                personaje = generarPersonaje(juego, inicialDePersonaje, *bando);
                posicionar_personaje(juego, personaje);
            }
        }
    }
    cambiarBando(bando);
}

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

// removi personaje_t *personaje = (bando == DEFENSIVO_ROHAN) ? &juego -> rohan[posicion_personaje] : &juego -> isengard[posicion_personaje];
 //   juego -> terreno[personaje -> fila][personaje -> columna] = personaje -> codigo;
 // del jugar 