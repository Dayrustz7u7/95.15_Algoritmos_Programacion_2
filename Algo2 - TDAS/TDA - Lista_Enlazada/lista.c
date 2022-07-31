#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct nodo nodo_t;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

struct nodo {
    void* dato;
    nodo_t* prox;
};

struct lista {
    nodo_t* prim;
    nodo_t* ulti;
    size_t cantidad;
};
struct lista_iter {
    nodo_t* actual;
    nodo_t* anterior;
    lista_t* lista;
};
nodo_t *nodo_crear(void* dato){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL){
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void* nodo_desempaquetar(nodo_t *nodo){
    void* aux = nodo->dato;
    free(nodo);
    return aux;
}

lista_t *lista_crear(void){
    lista_t *lista = malloc(sizeof(lista_t));
    if ( lista == NULL){
        return NULL;
    }
    lista->prim = NULL;
    lista->ulti = NULL;
    lista->cantidad = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->cantidad == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->ulti = nodo;
    } else {
        nodo->prox = lista->prim;
    }
    lista->prim = nodo;
    lista->cantidad += 1;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void* dato){
    if (lista_esta_vacia(lista)){
        return lista_insertar_primero(lista, dato);
    }
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo){
        return false;
    }
    lista->ulti->prox = nodo;
    lista->ulti = nodo;
    lista->cantidad += 1;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    } 
    nodo_t *nodo_aux = lista->prim;
    if (lista->cantidad == 1){
        lista->prim = NULL;
        lista->ulti = NULL;
    } else {
        lista->prim = lista->prim->prox;
    }
    lista->cantidad -= 1;
    return nodo_desempaquetar(nodo_aux);
}

void *lista_ver_primero(const lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t *lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->ulti->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->cantidad;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while (!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free(lista);
}
//FUNCIONES DE ITERACION INTERNO

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    
    nodo_t *actual = lista->prim;
    bool continuar = true;
    while (actual && continuar){
        if (visitar != NULL){
            continuar = visitar(actual->dato, extra);
        }
        actual = actual->prox;
    }
}

//FUNCIONES DE ITERACION EXTERNO

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t *iter =  malloc(sizeof(lista_iter_t));
    if (iter == NULL){
        return NULL;
    } 
    iter->lista = lista;
    iter->actual = iter->lista->prim;
    iter->anterior = NULL;
    return iter;
    
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true; 
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if (lista_iter_al_final(iter)){
        return NULL;
    }
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if (iter->lista == NULL){
        return false;
    }
    nodo_t *nodo = nodo_crear(dato);
    if (lista_esta_vacia(iter->lista)) {
        iter->lista->prim = nodo;
        iter->lista->ulti = nodo;
    } else if (lista_iter_al_final(iter)){
        iter->anterior->prox = nodo;
        iter->anterior = iter->anterior->prox;
        iter->lista->ulti = nodo;
    } else if (iter->actual == iter->lista->prim){
        nodo->prox = iter->actual;
        iter->lista->prim =  nodo;
        iter->actual =nodo;
    }else {
        iter->anterior->prox = nodo;
        nodo->prox = iter->actual;
    }
    iter->actual = nodo;
    iter->lista->cantidad++;
    return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
    if (lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)){
        return NULL;
    }
    nodo_t *actual = iter->actual;

    if (iter->actual == iter->lista->prim){
        iter->actual = iter->actual->prox;
        iter->lista->prim = iter->actual;
    } else if (iter->actual->prox == NULL){
        iter->actual = NULL;
        if (iter->anterior){
            iter->anterior->prox = NULL;
        }
        iter->lista->ulti = iter->anterior;
    } else {
        iter->anterior->prox = iter->actual->prox;
        iter->actual = iter->actual->prox;
    }
    iter->lista->cantidad--;
    return nodo_desempaquetar(actual);
}
