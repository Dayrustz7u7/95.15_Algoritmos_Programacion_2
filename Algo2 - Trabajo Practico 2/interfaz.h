#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <stdio.h>
#include <stdbool.h>
#include "algogram.h"


// FUNCIONES DE INTERFAZ 

/*
 * Funcion que se encarga de abrir el archivo con el string pasado por parametro
 * su modo de apertura sera de acuerdo el 2do parametro.
 * Pre: modo_de_apertura posibles : "w","r","a".
 * Post: Devuelve el archivo creado.
*/
FILE* abrir_archivo(char* archivo_txt,char* modo_de_apertura);

/*
 * Procedimiento que se encargar de leer el contenido del archivo
 * y llenar la informacion en el algogram 
 * Pre: 1)El archivo debe estar abierto en modo lectura -> "r" o "stdin"
 * Post: la lectura del archivo cargo todos los usuarios al algogram
*/
void lectura_de_usuarios(FILE* archivo,gram_t* red);

/*
 * Recibe una cadena y evalua si es una orden y cual es, devuelve el codigo asociado a la orden
 * Pre: recibe una cadena
 * Post: devuelve el numero con el codido de la operacion
*/
size_t comparar_instruccion(char* linea);

/*
 * Recibe un codigo de ejecucion, una linea y la red y ejecuta la orden o devuelve error
 * Pre: la red debe existir
 * Post: Ejecuta la instruccion o devuelve error
*/
void ejecutar_instruccion(size_t codigo, char* linea2, gram_t* red);

/*
 * Funcion que verifica las precondiciones de ejecucion, devuelve true si hay error
 * Pre: la red debe existir
 * Post: devuelve la previa a la ejecucion de una instruccion
*/
bool verificar(size_t codigo, gram_t* red);

/*
 * Lee las instrucciones que se le pasan a la red
 * Pre: la red debe existir
 * Post: ejecuta todas las instrucciones
*/
void lectura_instrucciones(FILE* archivo, gram_t* red);
#endif //INTERFAZ_H