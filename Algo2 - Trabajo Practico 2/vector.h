#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "vector.h"

typedef struct vector vector_t;
typedef void (*vetor_destruir_dato_t)(void *);


/* Se crea un vector vacio
 * Post: se devuelve un vector vacio
*/
vector_t *vector_crear();

/* 
 * Evalua si la posicion solicitada se encuentra ocupada
 * Pre: el vector debe estar inicializado
 * Post: devuelve true si la posicion esta ocupada dentro del vector
*/
bool vector_pos_existe(vector_t* vector, size_t pos);

/* 
 * Obtiene el dato contenido en la posicion, en caso de estar vacia devuelve NULL 
 * Pre: el vector debe estar inicializado
 * Post: devuelve la referencia al contenido o NULL si esta vacio
*/
void *vector_obtener(vector_t *vector, size_t pos);

/* 
 * Almacena al final del vector un dato
 * Pre: el vector debe estar inicializado
 * Post: devuelve true si se almacena, false en caso contrario
*/
bool vector_guardar_final(vector_t* vector, void* dato);

/* Devuelve la longitud del vector
 * Pre: el vector debe estar inicializado
 * Post: devuelve la longitud
*/
size_t vector_largo(vector_t *vector);

/* 
 * Destruye un vector
 * Pre: el vector debe estar inicializado
 * Post: Se destruye el vector y sus datos si se pasa alguna funcion de destruccion
*/
void vector_destruir(vector_t *vector, vetor_destruir_dato_t fdest);

#endif //VECTOR_H