#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h"
#define MINIMO 1
#define MAXIMO 2
#define ERROR -1
#define MODO_APERTURA "r"

int main(int argc, char* argv[]){
    if(argc < MINIMO || argc > MAXIMO){
        fprintf(stderr,"%s\n","Error: Cantidad erronea de parametros");
        return ERROR;
    }
    FILE* archivo = abrir_archivo(argv[1], MODO_APERTURA);
    if(archivo == NULL){
        return ERROR;
    }
    gram_t* red = algogram_crear();
    if (!red){
        fclose(archivo);
        return 0;
    }
    lectura_de_usuarios(archivo,red);
    lectura_instrucciones(stdin, red);
    fclose(archivo);
    gram_destruir(red);
    return 0;
}