#include "pila.h"

#include <stdlib.h>
#include <stdio.h>
/* Definición del struct pila proporcionado por la cátedra.
 */
#define CAPACIDAD_INICIAL 8
#define PRIMER_OPERANDO 2
#define SEGUNDO_OPERANDO 4
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
bool redimensionar_pila(pila_t *pila,size_t nueva_capacidad){
    void **ampliar_datos = realloc(pila->datos, nueva_capacidad * sizeof(void*));
    if(ampliar_datos == NULL){
        return false;
    }
    pila->datos = ampliar_datos;
    pila->capacidad = nueva_capacidad;
    return true;
}
pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if(pila==NULL){
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_INICIAL;
    pila->datos= malloc(sizeof(void*) * pila->capacidad);
    if(pila->datos == NULL){
        free(pila);
        return NULL;
    }
    return pila;
}
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}
bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}
bool pila_apilar(pila_t *pila,void *valor){
    bool redimensiono;
    if(pila->cantidad >= pila->capacidad){
        size_t nueva_capacidad = pila->capacidad * PRIMER_OPERANDO;
        redimensiono = redimensionar_pila(pila,nueva_capacidad);
        if(!redimensiono){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}
void *pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}
void *pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    if(pila->cantidad * SEGUNDO_OPERANDO <= pila->capacidad){
        size_t nueva_capacidad = pila->capacidad / PRIMER_OPERANDO;
        if(nueva_capacidad >= CAPACIDAD_INICIAL){
            redimensionar_pila(pila,nueva_capacidad); 
        }
    }
    void* tope = pila_ver_tope(pila);
    pila->cantidad--;
    return tope;
}