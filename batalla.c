#include "batalla.h"
#include "perfil.h"
#include <math.h>
//PRE : Recibe 2 numeros enteros positivos
//POST : Devuelve un numero aleatorio entre ellos
int numeroRandom(int a, int b){
    return rand() % (b - a + 1) + a;
}

void imprimirVariasVeces(char* string, int n){
    for (int i = 0; i < n; i++){
        printf("%s", string);
    }
}

//PRE : Recibe una intensidad proveniente del perfil de cada jugador
//POST : Devuelve el valor de PLUS segun la intensidad
int calcularPlus(int intensidad){
    return intensidad * numeroRandom(0,5);
}
// Funciones para dar outputs de diferente color en la terminal
//-------------------------------------------------------------
void red() {
  printf("\033[0;31m");
}

void boldRed() {
  printf("\033[1;31m");
}

void green() {
  printf("\033[0;32m");
}

void blue() {
  printf("\033[0;34m");
}

void boldBlue() {
  printf("\033[1;34m");
}

void boldGreen() {
  printf("\033[1;32m");
}

void resetColor() {
  printf("\033[0m");
}
//-------------------------------------------------------------

void imprimirStats(juego_t* juego , char bando){
    if (bando == OFENSIVO_ISENGARD){
        printf(" |ISENGARD|");
        printf("|Llegadas: ");
        printf("%i", juego -> llegadas_isengard);
        printf("|Energia: ");
        printf("%i", juego -> energiaIsengard);
        printf("|Personajes: ");
        printf("%i", juego -> cantidad_isengard);
        printf("|\n");
    }else{
        printf(" |ROHAN|");
        printf("|LLegadas: ");
        printf("%i", juego -> llegadas_rohan);
        printf("|Energia: ");
        printf("%i", juego -> energiaRohan);
        printf("|Personajes: ");
        printf("%i", juego -> cantidad_rohan);
        printf("|\n");
    }
}

void imprimirTerreno(juego_t* juego){
    system("clear");
    boldRed();
    imprimirStats(juego, OFENSIVO_ISENGARD);
    resetColor();                                  
    for (int i = 0; i < MAX_TERRENO_FIL; i++){           
        for (int j = 0; j < MAX_TERRENO_COL; j++){
            if (j == 0)
                printf("%i", i);
            printf("|");
            if (juego -> terreno[i][j] == HUMANO || juego -> terreno[i][j] == ELFO){
                blue();
                printf("%c",juego -> terreno[i][j]);
                resetColor();
            }
            else if (juego -> terreno[i][j] == ORCO || juego -> terreno[i][j] == URUKHAI){
                red();
                printf("%c",juego -> terreno[i][j]);
                resetColor();
            }
            else{
                printf("%c",juego -> terreno[i][j]);
            }
        }                                                             
        printf("|\n");
        if(i == MAX_TERRENO_FIL / 2 - 1) {
            printf(" |");
            imprimirVariasVeces("==", MAX_TERRENO_COL - 1);
            printf("=|\n");
        }
        if (i == MAX_TERRENO_FIL - 1){
            printf(" ");
            for (int z = 0; z < MAX_TERRENO_COL; z++){
                printf("|");
                printf("%i", z );
            }
        }
    }
    printf("|\n");
    boldBlue();
    imprimirStats(juego, DEFENSIVO_ROHAN);
    resetColor();
                                   
}

//PRE : Recibe el valor de cantidad de jugadores por refencia
//POST : Modifica el valor de cantJugadores por la cantidad de jugadores de la partida 1 o 2
void validarJugadores(int *cantJugadores){
    while(*cantJugadores != 1 && *cantJugadores != 2){
        printf("Numero ingresado es invalido, ingrese el numero de jugadores (1 / 2): ");
        scanf ("%i",cantJugadores);
    }
}

//PRE : -
//POST : Pregunta al usuario y devuelve la cantidad de jugadores
int preguntarJugadores(){
    int cantJugadores = 1;
    printf("Ingrese la cantidad de jugadores (1 / 2): ");
    scanf("%i", &cantJugadores);
    validarJugadores(&cantJugadores);
    return cantJugadores;
}

//PRE : Recibe informacion del perfil del primer jugador
//POST : Modifica tipoContrario y intensidadOpuesta de el jugador 2 con informacion del jugador 1
void asignarBandoOpuesto(char tipo,char *tipoContrario,int intensidad, int *intensidadOpuesta){

    *tipoContrario = (tipo == OFENSIVO_ISENGARD) ? DEFENSIVO_ROHAN: OFENSIVO_ISENGARD;
    *intensidadOpuesta = 10 - intensidad;
}

//PRE : Recibe variables de inicial de personaje y fila
//POST : Devuelve el numero de fila apropiado para el personaje
int preguntarFila(char inicialDePersonaje){
    int fila = 0;
    if (inicialDePersonaje == URUKHAI){
        do{
            printf("Ingrese la fila del urukhai: ");
            scanf("%i", &fila);
        }while((fila < 1) || (fila >= MAX_TERRENO_FIL/2));
    }
    else{
        do{
            printf("Ingrese la fila del elfo: ");
            scanf("%i", &fila);
        }while((fila < MAX_TERRENO_FIL/2) || (fila > MAX_TERRENO_FIL - 2));
    }
    return fila;
}

//PRE : Recibe la inicial del personaje (H , O, E, U)
//POST : Devuelve el valor del ataque de las unidades melee o range
int ataqueDePersonaje(char inicialDePersonaje){
    if (inicialDePersonaje == HUMANO || inicialDePersonaje == ORCO)
        return 50;
    return 10;
}

//PRE : Recibe la inicial del personaje (H , O, E, U)
//POST : Devuelve el valor de la vida de las unidades melee o range
int vidaDePersonaje(char inicialDePersonaje){
    if (inicialDePersonaje == HUMANO || inicialDePersonaje == ORCO)
        return 100;
    return 200;
}

//PRE : Recibe un struct juego y la inicial de un personaje
//POST : Devuelve el plus de el bando correspondiente a la inicial de personaje
int plusDePersonaje(juego_t juego, char inicialDePersonaje){
    if(inicialDePersonaje == HUMANO || inicialDePersonaje == ELFO)
        return juego.plus_rohan;
    return juego.plus_isengard;
}

//PRE : Recibe la inicial del personaje
//POST : Devuelve la fila donde incia el personaje o pregunta al usuario si es URAKHAI o ELFO
int filaDePersonaje(char inicialDePersonaje){
    if(inicialDePersonaje == HUMANO)
        return MAX_TERRENO_FIL - 1;
    else if (inicialDePersonaje == ORCO)
        return 0;
    else    
        return preguntarFila(inicialDePersonaje); 
}

//PRE : Recibe una instancia del juego original y un inicial de un personaje
//POST : Disminuye la energia del jugador al cual corresponde el personaje
void consumirEnergia(juego_t *juego, char inicialDePersonaje){
    if(inicialDePersonaje == HUMANO)
        juego -> energiaRohan -= ENERGIA_HUMANO;
    else if (inicialDePersonaje == ORCO)
        juego -> energiaIsengard -= ENERGIA_ORCO;
    else if (inicialDePersonaje == ELFO)
        juego -> energiaRohan -= ENERGIA_ELFO;
    else
        juego -> energiaIsengard -= ENERGIA_URUKHAI;
}

//PRE : Recibe la incial de un personaje
//POST : Devuelve el rango del personaje con la inicial ingresada
int rangoDePersonaje(char inicialDePersonaje){
    if(inicialDePersonaje == ELFO || inicialDePersonaje == URUKHAI)
        return RANGO_RANGED;
    return RANGO_MELEE;
}

int filaRandom(char inicialDePersonaje){
    if (inicialDePersonaje == URUKHAI)
        return numeroRandom(1, MAX_TERRENO_FIL / 2 - 1);
    else
        return numeroRandom(MAX_TERRENO_FIL / 2 , MAX_TERRENO_FIL - 2);
}

//PRE : Recibe un char inicial del personaje y el juego
//POST : Devuelve un personaje con todos sus datos cargados en una posicion aleatoria valida al inicio del juego
personaje_t generarPersonajesEspecialesIniciales(char inicialDePersonaje, juego_t *juego){
    personaje_t personaje;
    int columna = 0;
    int fila = 0;
    personaje.codigo = inicialDePersonaje;
    do{
        fila = filaRandom(inicialDePersonaje);
        columna = numeroRandom(0,MAX_TERRENO_COL - 1);
    } while(juego -> terreno[fila][columna] == ELFO || juego -> terreno[fila][columna] == URUKHAI);
    personaje.ataque = ataqueDePersonaje(inicialDePersonaje) + plusDePersonaje(*juego, inicialDePersonaje);
    personaje.vida = vidaDePersonaje(inicialDePersonaje) - plusDePersonaje(*juego, inicialDePersonaje);
    personaje.fila = fila;
    personaje.columna = columna;
    personaje.rango = RANGO_RANGED;
    return personaje;
}

//PRE : Recibe la columna por referencia
//POST : Le pregunta al usuario por una columna donde inicia el personaje
void validarColumna(int *columna){
    while (*columna < 0 || *columna > MAX_TERRENO_COL - 1){
        printf("Columna invalida, porfavor ingrese una columna en la cual iniciara el personaje: ");
        scanf("%i", columna);
    } 
}

int preguntarColumna(){
    int columna = 0;
    printf("Ingrese la columna: ");
    scanf("%i", &columna);
    validarColumna(&columna);
    return columna;
}

bool esMelee(char inicialDePersonaje){
    if(inicialDePersonaje == ORCO || inicialDePersonaje == HUMANO)
        return true;
    return false;
}

int columnaDePersonaje(juego_t *juego, bool isPvP, char bando){
    if(isPvP || juego -> bandoAutomatico != bando){
        return preguntarColumna();
    }else
        return numeroRandom(0, MAX_TERRENO_FIL - 1);
}

//PRE : Recibe una inicial de un personaje 
//POST : Devuelve el personaje con todos sus datos cargados
personaje_t generarPersonaje( juego_t *juego, char inicialDePersonaje, char bando){
    personaje_t personaje;
    personaje.codigo = inicialDePersonaje;
    personaje.ataque = ataqueDePersonaje(inicialDePersonaje) + plusDePersonaje(*juego, inicialDePersonaje);
    personaje.vida = vidaDePersonaje(inicialDePersonaje) - plusDePersonaje(*juego, inicialDePersonaje);
    personaje.fila = filaDePersonaje(inicialDePersonaje);
    personaje.columna = columnaDePersonaje(juego, juego -> isPvP, bando);
    personaje.rango = rangoDePersonaje(inicialDePersonaje);
    consumirEnergia(juego, inicialDePersonaje);
    return personaje;
}
// PRE : recibe el numero de personajes especiales maximos y un juego inicializado
// POST : agrega al terreno y a los arrays de personajes de cada jugador sus respectivos personajes especiales
void asignarPersonajesEspeciales( juego_t *juego){
    personaje_t elfo;
    personaje_t urukhai;
    for (int i = 0 ; i < MAX_PERSONAJES_ESPECIALES_INICIALES; i++){
        // genera 3 elfos en posiciones aleatorias del lado de rohan
        elfo = generarPersonajesEspecialesIniciales(ELFO, juego);
        juego -> rohan[i] = elfo;
        juego -> cantidad_rohan++;
        juego -> terreno[elfo.fila][elfo.columna] = ELFO;
        //genera 3 urukhai en posiciones aleatorias del lado de isengard
        urukhai = generarPersonajesEspecialesIniciales(URUKHAI, juego);
        juego -> isengard[i] = urukhai;
        juego -> cantidad_isengard++;
        juego -> terreno[urukhai.fila][urukhai.columna] = URUKHAI;
    }
}

//PRE : Recibe una instancia del juego inicial
//POST : Llena la matriz terreno de chars #
void llenarTerreno(juego_t *juego){
    //Recorre filas
    for (int i = 0; i < MAX_TERRENO_FIL ; i++){
        //Recorre columnas
        for(int j = 0; j < MAX_TERRENO_COL; j++){
            juego -> terreno[i][j] = TERRENO;
        }
    }
}

//PRE : Recibe una instancia del juego inicial
//POST : Carga los datos iniciales del juego : jugadores, personajes iniciales, terreno , plus, etc 
void inicializar_juego(juego_t* juego){
    int intensidad1 = 0;
    int intensidad2 = 0;
    char bando1 = ' ';
    char bando2 = ' ';
    perfil(&bando1, &intensidad1);
    asignarBandoOpuesto(bando1, &bando2, intensidad1, &intensidad2);
    int jugadores = preguntarJugadores();
    juego->isPvP = jugadores == 2;
    llenarTerreno(juego);
    juego -> cantidadJugadores = jugadores;
    juego -> cantidad_rohan = 0;
    juego -> energiaRohan = MAX_ENERGIA_INICIAL;
    juego -> energiaIsengard = MAX_ENERGIA_INICIAL;
    juego -> cantidad_isengard = 0;
    juego -> llegadas_rohan = 0;
    juego -> llegadas_isengard = 0;
    if (bando1 == DEFENSIVO_ROHAN){
        juego -> plus_rohan = calcularPlus(intensidad1);
        juego -> plus_isengard = calcularPlus(intensidad2);
    }else{
        juego -> plus_rohan = calcularPlus(intensidad2);
        juego -> plus_isengard = calcularPlus(intensidad1);
    }
    if(!juego -> isPvP) juego->bandoAutomatico = bando2;
    asignarPersonajesEspeciales(juego);
}
// PRE : recibe una instancia del  juego ya inicializado y un personaje con sus datos cargados
// POST : agrega al terreno y al array de personajes el personaje respectivo si en la posicion estaba disponible
void posicionar_personaje(juego_t* juego, personaje_t personaje){
    juego -> terreno[personaje.fila][personaje.columna] = personaje.codigo;
    if (personaje.codigo == ELFO){
        juego -> rohan[juego ->cantidad_rohan] = personaje;
        juego -> cantidad_rohan++;
    }else if (personaje.codigo == URUKHAI){
        juego -> isengard[juego ->cantidad_isengard] = personaje;
        juego -> cantidad_isengard++;
    }else if (personaje.codigo == HUMANO){
        juego -> rohan[juego ->cantidad_rohan] = personaje;
        juego -> cantidad_rohan++;
    }else{
        juego -> isengard[juego ->cantidad_isengard] = personaje;
        juego -> cantidad_isengard++;
    }
}
//PRE : recibe una instancia del juego la posicion del personaje a eliminar y el bando
//POST : mueve el elemento a 'destruir' al final del array y disminuye 1 a la cantidad para simular su destruccion
void destruirPersonaje(juego_t *juego, int posicionDePersonaje, char bando){
    int *cantidad = (bando == DEFENSIVO_ROHAN) ? &juego -> cantidad_rohan : &juego -> cantidad_isengard;
    personaje_t personajeAuxiliar;
    personaje_t *arrayPersonajes = (bando == DEFENSIVO_ROHAN) ? juego -> rohan : juego -> isengard;
    for (int i = posicionDePersonaje; i < *cantidad - 1 ; i++){
        personajeAuxiliar = arrayPersonajes[i];
        arrayPersonajes[i] = arrayPersonajes[i + 1];
        arrayPersonajes[i + 1] = personajeAuxiliar;
    }
    *cantidad -= 1;
}

//PRE : recibe fila y columna de un  personaje en el terreno ademas del juego y bando
//POST :  Devuelve una direccion personaje_t enemigo del bando dentro del array rohan o isengard del struct juego 
personaje_t* personajeDeBandoSegunPosicion(int fila, int columna, juego_t *juego, char bando){
    personaje_t* direccionDePersonaje;
    if (bando == DEFENSIVO_ROHAN){
        for (int i = 0; i < juego -> cantidad_isengard; i++){
            if (juego -> isengard[i].fila == fila && juego -> isengard[i].columna == columna)
                direccionDePersonaje = &(juego -> isengard[i]);
        }
    }
    else{ 
        for (int i = 0; i < juego -> cantidad_rohan; i++){
            if (juego -> rohan[i].fila == fila && juego -> rohan[i].columna == columna)
                direccionDePersonaje = &(juego -> rohan[i]);
        }
    }
    return direccionDePersonaje;
}

//PRE : un rango valido menor a el tamaño del terreno
//POST devuelve true si las coordenadas i , j estan fuera del rango del personaje
bool fueraDeRangoManhattan(personaje_t personaje, int fila, int columna){
    if (abs(personaje.fila - fila) + abs(personaje.columna - columna) > personaje.rango)
        return true;
    return false;
} 

//PRE: recibe el struct personaje, el juego, el bando y el rango (manhattan) de ataque del personaje
//POST : analiza los casilleros adyacentes para saber cuales son validos segun el algoritmo de manhattan, 
//devuelve true si encuentra a un enemigo en su rango
bool enemigosEnRango(juego_t *juego, int posicionDePersonaje, char bando, personaje_t*enemigos[], int *cantidadEnemigos){
    bool enemigoEncontrado = false;
    personaje_t personaje = (bando == DEFENSIVO_ROHAN) ? juego -> rohan[posicionDePersonaje] : juego -> isengard[posicionDePersonaje];
    //Recorre columnas
    for (int i = personaje.fila - personaje.rango; i <= personaje.fila + personaje.rango; i++){
        //Recorre filas
        for(int j = personaje.columna - personaje.rango; j <= personaje.columna + personaje.rango; j++){
            // continua al siguiente casillero si se encuentra buscando fuera de la matriz
            if ( (i < 0 || i > MAX_TERRENO_FIL - 1) || (j < 0 || j > MAX_TERRENO_COL - 1))
                continue;
            if ( fueraDeRangoManhattan(personaje, i, j))
                continue;
            // continua al siguente si esta paradosobre si mismo o un personaje especial aliado
            if ((i == personaje.fila && j == personaje.columna) || juego -> terreno[i][j] == (bando == OFENSIVO_ISENGARD ? URUKHAI : ELFO))
                continue;
            if (juego -> terreno[i][j] == ((bando == OFENSIVO_ISENGARD) ? ELFO : URUKHAI)){
                enemigos[*cantidadEnemigos] = personajeDeBandoSegunPosicion(i, j, juego, bando);
                *cantidadEnemigos += 1;
                enemigoEncontrado = true;
            }
            else if (juego -> terreno[i][j] == ((bando == OFENSIVO_ISENGARD) ? HUMANO : ORCO)){
                enemigos[*cantidadEnemigos] = personajeDeBandoSegunPosicion(i, j, juego, bando);
                *cantidadEnemigos += 1;
                enemigoEncontrado = true;
            }
        }
    }
    return enemigoEncontrado;
}

//PRE : recibe un personaje dentro de el array de personajes y un bando
// POST : mueve al humano o orco una casilla arriba o abajo 
void moverPersonaje(juego_t *juego, char bando, int posicionDePersonaje){
    personaje_t *personaje = (bando == DEFENSIVO_ROHAN) ? &juego -> rohan[posicionDePersonaje] : &juego -> isengard[posicionDePersonaje];
    int *llegadasDeJugador = ((bando == DEFENSIVO_ROHAN ? &juego -> llegadas_rohan : &juego -> llegadas_isengard));

    juego -> terreno[personaje -> fila][personaje -> columna] = TERRENO;
    personaje -> fila += ((bando == OFENSIVO_ISENGARD) ? 1 : -1);
    juego -> terreno[personaje -> fila][personaje -> columna] = personaje -> codigo;
    if (personaje -> fila == MAX_TERRENO_FIL - 1 || personaje -> fila == 0){
        destruirPersonaje(juego, posicionDePersonaje, bando);
        juego -> terreno[personaje -> fila][personaje -> columna] = TERRENO;
        *llegadasDeJugador += 1;
    }
}

void imprimirHeridos(personaje_t personaje){
    if (personaje.codigo == HUMANO)
        printf("Un Humano ha caido en batalla.\n");
    else if(personaje.codigo == ELFO)
        printf("Un Elfo ha caido en batalla.\n");
    else if (personaje.codigo == ORCO)
        printf("Un Orco ha caido en batalla.\n");
    else
        printf("Un Urukhai ha caido en batalla.\n");
}

//PRE : Recibe una instancia del juego  y un bando
//POST: Remueve a todos los personajes de los array rohan y isengard que tengan vida menor  0
void removerHeridos(juego_t* juego, char bando){
    int cantidad = ((bando == DEFENSIVO_ROHAN) ? juego -> cantidad_rohan : juego -> cantidad_isengard);
    personaje_t *arrayPersonajes = ((bando == DEFENSIVO_ROHAN) ? juego -> rohan : juego -> isengard);
    for(int i = 0; i < cantidad; i++){
        if(arrayPersonajes[i].vida <= 0){
            destruirPersonaje(juego, i, bando);
            imprimirHeridos(arrayPersonajes[i]);
            juego -> terreno[arrayPersonajes[i].fila][arrayPersonajes[i].columna] = TERRENO;
        }
    }
}

//PRE : Recibe la cantidad de enemigos , un array con las direcciones de memoria de tus enemigos y el personaje que ataca
//POST : Disminuye la vida de un enemigo elegido al azar
void atacarEnemigos(int cantidadEnemigos, personaje_t* enemigos[], personaje_t personaje){
    personaje_t* enemigoRandom = enemigos[numeroRandom(0,cantidadEnemigos - 1)];
    enemigoRandom -> vida -= personaje.ataque;

}
//PRE : Recibe la cantidad de enemigos , un array con las direcciones de memoria de tus enemigos y el personaje que ataca
//POST : Disminuye la vida de todos los enemigos en rango
void ataqueEspecial( int cantidadEnemigos, personaje_t* enemigos[], personaje_t personaje){
    for (int i = 0; i < cantidadEnemigos; i++)
        enemigos[i] -> vida -= personaje.ataque;
}

void jugar(juego_t* juego, char bando, int posicion_personaje){
    personaje_t personajeIsengard = juego -> isengard[posicion_personaje];
    personaje_t personajeRohan = juego -> rohan[posicion_personaje];
    personaje_t* enemigos[MAX_ENEMIGOS];
    personaje_t *personaje = (bando == DEFENSIVO_ROHAN) ? &juego -> rohan[posicion_personaje] : &juego -> isengard[posicion_personaje];
    juego -> terreno[personaje -> fila][personaje -> columna] = personaje -> codigo;
    int cantidadEnemigos = 0;
    if (bando == OFENSIVO_ISENGARD && (personajeIsengard).codigo == ORCO ){
        if(enemigosEnRango(juego, posicion_personaje, bando, enemigos, &cantidadEnemigos)){
            atacarEnemigos(cantidadEnemigos, enemigos, personajeIsengard);
        }
        else
            moverPersonaje(juego, bando, posicion_personaje);
    }
    else if (bando == OFENSIVO_ISENGARD && (personajeIsengard).codigo == URUKHAI ){
        if(enemigosEnRango(juego,posicion_personaje, bando, enemigos, &cantidadEnemigos)){
            ataqueEspecial(cantidadEnemigos, enemigos, personajeIsengard);
        }
    }
    else if (bando == DEFENSIVO_ROHAN && (personajeRohan).codigo == HUMANO ){
        if(enemigosEnRango(juego,posicion_personaje, bando, enemigos, &cantidadEnemigos)){
            atacarEnemigos(cantidadEnemigos, enemigos, personajeRohan);
        }
        else
            moverPersonaje(juego, bando, posicion_personaje);
    }else{
        if(enemigosEnRango(juego,posicion_personaje, bando, enemigos, &cantidadEnemigos)){
            ataqueEspecial(cantidadEnemigos, enemigos, personajeRohan);
        }
    }
}
