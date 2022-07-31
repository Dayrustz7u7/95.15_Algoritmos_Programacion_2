#include "cola.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct nodo nodo_t;

struct cola{
    nodo_t* primero;
    nodo_t* ultimo;
};
struct nodo{
    void* dato;
    nodo_t* prox;
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA ENLADA
 * *****************************************************************/

nodo_t* nodo_crear(void *valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}
void nodo_destruir(nodo_t* nodo){
    free(nodo);
}
cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));
    if(cola == NULL){
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}
bool cola_esta_vacia(const cola_t *cola){
    return cola->primero == NULL && cola->ultimo == NULL;
}
void *cola_desencolar(cola_t *cola){
    if(cola_esta_vacia(cola)){
        return NULL;
    }
    nodo_t *nodo_a_destruir = cola->primero;
    void *dato_a_extraer = cola->primero->dato;
    if(cola->primero == cola->ultimo){
        cola->primero = NULL;
        cola->ultimo = NULL;
    }else{
        cola->primero = cola->primero->prox;
    }
    nodo_destruir(nodo_a_destruir);

    return dato_a_extraer;
}
void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    while(cola->primero != NULL){
        if(destruir_dato != NULL){
            destruir_dato(cola->primero->dato);
        }
        cola_desencolar(cola);
    }
    free(cola);
}
bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nodo = nodo_crear(valor);
    if(nodo == NULL){
        return false;
    }
    if(cola_esta_vacia(cola)){
        cola->primero = nodo;
    }else{
        cola->ultimo->prox = nodo;
    }
    cola->ultimo = nodo;

    return true;
}
void *cola_ver_primero(const cola_t *cola){
    if(cola_esta_vacia(cola)){
        return NULL;
    }
    return cola->primero->dato;
}
