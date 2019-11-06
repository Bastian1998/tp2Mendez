#include "perfil.h"
#include <stdio.h>
#define ACCION 'A'
#define COMEDIA 'C'
#define DRAMA 'D'
#define TERROR 'T'
const int FUEGO = 1;
const int TIERRA = 2;
const int AIRE = 3;
const int AGUA = 0;

//PRE: numero entero valido de signo de zodiaco segun la tabla
//POST: zodiaco guarda por referencia el numero correcto entre 1-12
void validarZodiaco(int* zodiaco){
    while (*zodiaco < 1 || *zodiaco > 12){
        printf("Numero incorrecto, ingrese su signo del zodiaco(1 - 12): \n");
        scanf("%i",zodiaco);
    }
}

//PRE: --
//POST: pregunta al usuario y devuelve el numero del signo del zodiaco segun la tabla
int preguntarZodiaco(){
    int zodiaco = 0;
    printf ("\n Seleccione su signo del zodiaco(1 - 12): \n");
    printf("1 - Aries \n2 - Tauro \n3 - Geminis \n4 - Cancer \n5 - Leo \n6 - Virgo \n7 - Libra \n8 - Escorpio \n9 - Sagitario \n10 - Capricornio \n11 - Acuario \n12 - Piscis \n");
    scanf("%i",&zodiaco);
    validarZodiaco(&zodiaco);
    return zodiaco;
}

//PRE: Letra que indica el tipo de genero valido( 'A' 'C' 'D' 'T')
//POST: genero guarda por referencia la letra correcta
void validarGenero(char* genero){
    while(*genero != ACCION && *genero != COMEDIA && *genero != DRAMA && *genero != TERROR){
        printf("Letra incorrecta, ingrese su genero de cine favorito: \n");
        scanf(" %c",genero);
    }
}

//PRE: --
//POST: pregunta al usuario y devuelve una letra valida de genero ('A' 'C' 'D' 'T')
char preguntarGeneroCine(){
    char genero = ' ';
    printf("Seleccione su genero de cine favorito: \n");
    printf("A - Accion \nC - Comedia \nD - Drama \nT - Terror\n");
    scanf(" %c",&genero);
    validarGenero(&genero);
    return genero;
}

//PRE: numero de mascotas valido (1 - 5 o mas) numeros mayores a 5 tienen el mismo valor
//POST: mascotas guarda por referencia un numero valido
void validarMascotas(int* mascotas){
    while (*mascotas < 0 || *mascotas > 5){
        printf("Numero de mascotas invalido, ingrese la cantidad de mascotas que tiene: \n");
        scanf("%i", mascotas);
    }
}

//PRE: --
//POST: pregunta al usuario y devuelve un numero de mascotas valido (1 - 5 o mas) numeros mayores a 5 tienen el mismo valor
int preguntarCantidadMascotas(){
    int mascotas = 0;
    printf("Indique la cantidad de mascotas que tiene (0 - 5): \n");
    scanf("%i",&mascotas);
    validarMascotas(&mascotas);
    return mascotas;
}

//PRE:numero de maldades valido ( 0 - 99)
//POST: maldades guarda por referencia un numero valido
void validarMaldades(int* maldades){
    while(*maldades < 0 || *maldades > 99){
        printf("Numero de maldades invalido, porfavor ingrese su cantidad de maldades en el ultimo mes: \n");
        scanf("%i",maldades);
    }
}

//PRE: --
//POST: devuelve un numero valido de maldades ( 0- 99)
int preguntarCantidadMaldades(){
    int maldades = 0;
    printf("Ingrese la cantidad de maldades que hizo este mes (0 - 99): \n");
    scanf("%i", &maldades);
    validarMaldades(&maldades);
    return maldades;
}

//PRE: valores validos de zodiaco , genero y maldades
//POST: devuelve un numero entero 1 o 2 o 0 si no pertenece a ningun bando
char determinarBando(int zodiaco, char genero, int maldades){
    //Indico los bandos ofensivo y defensivo como 1 y 2 respectivamente
    char bando = 'N';
    if((zodiaco % 4 == FUEGO || zodiaco % 4 == AIRE) && (genero == COMEDIA || genero == TERROR) && maldades >= 50)
        bando = 'I';
    else if ((zodiaco % 4 == AGUA || zodiaco % 4 == TIERRA) && (genero == ACCION || genero == DRAMA) && maldades < 50)
        bando = 'R';
    return bando;
}
//PRE: maldades y cantidad de mascotas son valores validos
//POST: Devuelve el calculo de intensidad segun la tabla de puntajes
int determinarIntensidad(int maldades, int cantidadMascotas){
    return((maldades/10)%5 + 1 + cantidadMascotas);
}

//PRE : recibe un char que representa el bando de usuario (O)fensivo o (D)efensivo y un entero para la intensidad.
//POST : cambia el valor de tipo e intensidad para determinar el bando del usuario 
void perfil ( char * tipo , int * intensidad ){
    int zodiaco = 0, maldades = 0, cantidadMascotas = 0;
    char genero = ' ';
    do{
        zodiaco = preguntarZodiaco();
        genero = preguntarGeneroCine();
        maldades = preguntarCantidadMaldades();
        *tipo = determinarBando(zodiaco, genero, maldades);
        cantidadMascotas = preguntarCantidadMascotas();
        *intensidad = determinarIntensidad(maldades, cantidadMascotas);
        if (*tipo == 'N')
            printf("You don't belong anywhere, TRY AGAIN! (Bando indefinido) \n");
    }while(*tipo == 'N');
    if (*tipo == 'I')
        printf("ofensivo: STAND IN YOUR FEET ORCISH BROTHER!!, you have been drafted to assault ROHANS'S kingdom in the name of ISENGARD as a LV %i Berserker\n", *intensidad);
    else
        printf("defensivo: REJOICE WARRIOR!!, you haven been drafted to serve and  protect ROHAN'S kingdom from the orcish tyranny as a LV %i Paladin\n", *intensidad);
}
