#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PARAMETRO_MINIMO 2
#define PARAMETRO_MAXIMO 3
#define MODO_APERTURA "r"
#define ERROR -1

/*
 * Funcion que se encargar de comparar si el char pasado por parametro es un 
 * numero de 0 al 9 de tipo de dato char. Retornara true si es igual a uno de
 * esos numeros o false caso contrario.
*/
bool es_numero(char digito){
    return(digito=='0'||digito=='1'||digito=='2'||digito=='3'||digito=='4'||digito=='5'||digito=='6'||digito=='7'||digito=='8'||digito=='9');
}
/*
 * Se encarga de recorrer el string pasado por parametro y evaluar por cada iteracion
 * si es un numero.
 * Retornara True -> Si todo los elementos del string son numeros.
 * Retornara False -> Si alguno de sus elementos no es un numero.
*/
bool validar_numero(char* numero){
    int i = 0;
    bool dato_valido = true;
    while(numero[i] != '\0' && dato_valido){
        if(!es_numero(numero[i])){
            dato_valido = false;
        }
        i++;
    }
    return dato_valido;
}
/*
 * Procedimiento que se encargara de imprimir un string de largo Maximo -> "cant_caracteres"
 * o menor a dicha cantidad.
 * Eventualmente se llenara una cadena auxiliar manualmente y segun las iteraciones "i" se 
 * imprimira con o sin "/n".
 * -> Si i < Cantidad_caracteres:  Print sin \n.
 * -> Si i >= Cantidad_caracteres: Print con \n.
*/
void imprimir_cadena(char*linea,int* iniciar,int cant_caracteres){
    char cadena[cant_caracteres];
    int i = 0;
    while( i < cant_caracteres && linea[*iniciar] !='\0'){
        cadena[i] = linea[*iniciar];
        (*iniciar) += 1;
        i++;
    }
    cadena[i] = '\0'; 
    if( i  <  cant_caracteres || linea[*iniciar] == '\n'){
        printf("%s",cadena);
    }else{
        printf("%s\n",cadena);
    }
}
/*
 * Procedimiento que se encargara de separar por cada caso segun 
 * la diferencia de Longitud(El largo de la cadena Linea) y la 
 * Cantidad_caracteres e imprimira de forma diferente.
 * -> Si longitud > cantidad_caracteres: Se divide la linea  y printeara.
 * -> Si longitud <= cantidad_caracteres:No hace falta dividir y solo printeara sin \n.
*/
void dividir_cadena(char* linea,int longitud,int cant_caracteres){ 
    if(longitud > cant_caracteres + 1 ){
        int inicio = 0;
        while(inicio < longitud){
            imprimir_cadena(linea,&inicio,cant_caracteres); 
        }
    }
    else{
        printf("%s",linea);
    }
}
/*
 * Funcion que se encarga de abrir el archivo con el string pasado por parametro
 * su modo de apertura sera de acuerdo el 2do parametro.
 * Pre: modo_de_apertura posibles : "w","r","a".
 * Post: Devuelve el archivo creado.
*/
FILE* abrir_archivo(char* archivo_txt,char* modo_de_apertura){
    FILE* archivo = fopen(archivo_txt,modo_de_apertura);
    if(!archivo){
        fprintf(stderr,"%s\n","Error: archivo fuente inaccesible");
        return NULL;
    }
    return archivo;
}
/*
 * Procedimiento que cierra el archivo 
 * Pre: El archivo esta abierto.
*/
void cerrar_archivo(FILE* archivo){
    fclose(archivo);
}
/*
 * Procedimiento que se encargar de leer el contenido del archivo
 * e imprimir segun la cantidad de caracteres pasado por parametro -> cant_caracteres.
 * Pre:El archivo debe estar abierto en modo lectura -> "r"
*/
void ejecutar_archivo(FILE* archivo,int cant_caracteres){
    char* linea = NULL;
    size_t tamnio;
    while(getline(&linea , &tamnio , archivo) !=  EOF){
        int longitud = (int)strlen(linea);
        dividir_cadena(linea,longitud,cant_caracteres);
    }
    free(linea);
}
int main(int argc, char* argv[]){

    if(argc < PARAMETRO_MINIMO || argc > PARAMETRO_MAXIMO || validar_numero(argv[1]) == false){
        fprintf(stderr,"%s\n","Error: Cantidad erronea de parametros");
        return ERROR;
    }
    int cant_caracteres = atoi(argv[1]);
    if( argc == PARAMETRO_MAXIMO){
        FILE* archivo = abrir_archivo(argv[2],MODO_APERTURA);
        if(archivo == NULL){
            return ERROR;
        }
        ejecutar_archivo(archivo,cant_caracteres);
        cerrar_archivo(archivo);
    }
    else{
        ejecutar_archivo(stdin,cant_caracteres);
    }
    return 0;
}