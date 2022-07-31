#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

char* copiar_string(const char* nombre){
    char* copia = malloc(sizeof(char)*(strlen(nombre)+1));
    if (!copia){
        return NULL;
    }
    strcpy(copia, nombre);
    return copia;
}

char* borrar_barra_n(char* nombre){
    char* copia = malloc(sizeof(char)*(strlen(nombre)+1));
    if (!copia){
        return NULL;
    }
    strcpy(copia, nombre);
    copia[strlen(nombre)-1]= '\0';
    return copia;
}
