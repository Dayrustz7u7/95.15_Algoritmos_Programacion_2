#include "pila.h"
#include <stdlib.h>

#define  SIZE 8
#define FACT 2


/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    
    if (pila == NULL){
        return NULL;
    }

    pila -> cantidad = 0;
    pila-> capacidad = SIZE;
    pila->datos = malloc((pila->capacidad) * sizeof(void*));

    if (pila->datos == NULL){
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

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

bool pila_redimensionar(pila_t *pila, size_t capacidad_nueva){
    void** nuevos_datos = realloc(pila->datos, capacidad_nueva*sizeof(void*));
    if (nuevos_datos == NULL){
        return false;
    }
    pila->datos = nuevos_datos;
    pila->capacidad = capacidad_nueva;
    return true;
}

void pila_almacenar_element(pila_t *pila, void* dato){
    pila->datos[pila->cantidad] = dato;
    pila->cantidad+=1;    
}

bool pila_apilar(pila_t *pila, void* dato){
    if(pila->cantidad == pila->capacidad){
        bool aux = pila_redimensionar(pila, pila->capacidad*FACT);
        if (!aux) return false;
    }
    pila_almacenar_element(pila, dato);
    return true;
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    if(pila->capacidad/pila->cantidad==4 && pila->cantidad != SIZE){
        pila_redimensionar(pila, pila->capacidad/FACT);
    }
    pila->cantidad -= 1;
    return pila->datos[pila->cantidad];
}

