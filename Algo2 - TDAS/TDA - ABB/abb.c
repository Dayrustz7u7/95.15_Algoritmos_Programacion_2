#include "abb.h"
#include "pila.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo nodo_abb_t;
typedef struct reemplazante reemplazante_t;

void *_abb_borrar(char* clave, abb_t* abb);

struct nodo 
{
    nodo_abb_t* der;
    nodo_abb_t* izq;
    char* clave;
    void* dato;
};

struct abb
{
    nodo_abb_t* raiz;
    abb_comparar_clave_t fcomp;
    abb_destruir_dato_t fdest;
    size_t cantidad;
};

struct reemplazante
{
    char* clave;
    void* dato;

};

struct abb_iter
{
    pila_t* pila;
};  

reemplazante_t *reemplazante_crear(char* clave, void* dato){
    reemplazante_t *aux = malloc(sizeof(reemplazante_t));
    if (!aux){
        return NULL;
    }
    aux->clave = malloc(sizeof(char)*(strlen(clave) + 1));
    if (!aux->clave){
        free(aux);
        return NULL;
    }
    strcpy(aux->clave, clave);
    aux->dato = dato;
    return aux;
}

nodo_abb_t *nodo_abb_crear(char* clave, void* dato){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if (!nodo){
        return NULL;
    }
    nodo->clave = malloc(sizeof(char)*(strlen(clave) + 1));
    if (!nodo->clave){
        free(nodo);
        return NULL;
    }
    strcpy(nodo->clave, clave);
    nodo->dato = dato;
    nodo->der = NULL;
    nodo->izq = NULL;
    return nodo;
}

void nodo_abb_destruir(nodo_abb_t *nodo){
    free(nodo->clave);
    free(nodo);
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *arbol = malloc(sizeof(abb_t));
    if (!arbol){
        return NULL;
    }
    arbol->cantidad = 0;
    arbol->fcomp = cmp;
    arbol->fdest = destruir_dato;
    arbol->raiz = NULL;
    return arbol;
}

char* abb_copiar_clave(const char* clave){
    char* copia = malloc(sizeof(char)*(strlen(clave)+1));
    if (!copia){
        return NULL;
    }
    strcpy(copia, clave);
    return copia;
}

nodo_abb_t* nodo_buscar(nodo_abb_t* actual, const char* clave, abb_comparar_clave_t fcomp, nodo_abb_t** anterior){
    if (actual == NULL){
        return NULL;
    } else if ( fcomp(actual->clave, clave) == 0 ){
        return actual;
    };
    (*anterior) = actual;
    if (fcomp(actual->clave, clave) < 0){
        return nodo_buscar(actual->der, clave, fcomp, anterior);
    } else if (fcomp(actual->clave, clave) > 0){
        return nodo_buscar(actual->izq, clave, fcomp, anterior);
    } 
    return NULL;
} 

bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = arbol->raiz;
    nodo_abb_t* buscado = nodo_buscar(arbol->raiz, clave, arbol->fcomp, &padre);
    return buscado != NULL;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = arbol->raiz;
    nodo_abb_t* buscado = nodo_buscar(arbol->raiz, clave, arbol->fcomp, &padre);
    if (!buscado){
        return NULL;
    }
    return buscado->dato;
}

bool abb_guardar_en_existente(nodo_abb_t* hijo, void* dato, abb_destruir_dato_t fdest, char* clave){
    void* dato_viejo = hijo->dato;
    hijo->dato = dato;
    if (fdest){
        fdest(dato_viejo);
    }
    free(clave);
    return true;
}

void abb_guardar_no_existente(nodo_abb_t* padre, nodo_abb_t* nuevo_hijo, abb_t* arbol){
    if (!padre){
        arbol->raiz = nuevo_hijo;
    } else {
         if (arbol->fcomp(padre->clave, nuevo_hijo->clave) > 0){
            padre->izq = nuevo_hijo;
        } else {
            padre->der = nuevo_hijo;
        }
    }
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    char* copia = abb_copiar_clave(clave);
    nodo_abb_t* padre = arbol->raiz;
    nodo_abb_t* buscado = nodo_buscar(arbol->raiz, copia, arbol->fcomp, &padre);
    if (buscado){
        return abb_guardar_en_existente(buscado, dato, arbol->fdest, copia);
    }
    nodo_abb_t* nodo = nodo_abb_crear(copia, dato);
    if (nodo == NULL){
        free(copia);
        return false;
    }
    abb_guardar_no_existente(padre, nodo, arbol);
    free(copia);
    arbol->cantidad ++;
    return true;
}

nodo_abb_t *abb_izq(nodo_abb_t* nodo){
    if (!nodo->izq){
        return nodo;
    }
    return abb_izq(nodo->izq);
}

reemplazante_t *abb_buscar_reemplazante(nodo_abb_t* nodo){
    nodo = nodo->der;
    nodo = abb_izq(nodo);
    reemplazante_t *aux = reemplazante_crear(nodo->clave, nodo->dato);
    if (!aux){
        return NULL;
    }
    return aux;
}

void abb_borrar_sin_hijo(nodo_abb_t *padre, nodo_abb_t* hijo, abb_comparar_clave_t fcomp) {
    if (fcomp(padre->clave, hijo->clave) > 0){
        padre->izq = NULL;
    } else {
        padre->der = NULL;
    }
    nodo_abb_destruir(hijo);
}

void abb_borrar_con_hijo(nodo_abb_t* padre, nodo_abb_t* hijo, abb_comparar_clave_t fcomp, abb_t* abb) {

    if (hijo == abb->raiz){
        if (hijo->der){
            abb->raiz = hijo->der;
        } else {
            abb->raiz = hijo->izq;
        }
    }

    if (padre->der &&  fcomp(padre->der->clave, hijo->clave) == 0) {
        //padre tiene hijo derecho
        if (hijo->der){ 
            padre->der = hijo->der;
        } else {
            padre->der = hijo->izq; 
        } 
    } else {
        //hijo es el izq del padre
        if (hijo->izq){
            padre->izq = hijo->izq;
        } else {
            padre->izq = hijo->der;
        }
    }
    nodo_abb_destruir(hijo);
}

void *abb_borrar_con_dos_hijos(abb_t* abb, nodo_abb_t* buscado, void* dato){
    reemplazante_t* aux = abb_buscar_reemplazante(buscado);
    if (!aux){
        return NULL;
    }
    _abb_borrar(aux->clave, abb);
    char* nuevo_espacio = realloc(buscado->clave, sizeof(char)*(strlen(aux->clave) +1));
    if (nuevo_espacio){
        buscado->clave = nuevo_espacio;
        strcpy(buscado->clave, aux->clave);
        buscado->dato = aux->dato;
    }
    free(aux->clave);
    free(aux);
    return dato;
}

void *_abb_borrar(char* clave, abb_t* abb){
    nodo_abb_t* padre = abb->raiz;
    nodo_abb_t* buscado = nodo_buscar(abb->raiz, clave, abb->fcomp, &padre);
    void* dato = buscado->dato;
    if ( !buscado->der && !buscado->izq ){
        abb_borrar_sin_hijo(padre, buscado, abb->fcomp);
    } else if (!buscado->izq || !buscado->der){
        abb_borrar_con_hijo(padre, buscado, abb->fcomp, abb);
    } else {
        return abb_borrar_con_dos_hijos(abb, buscado, dato);
    }
    return dato;
}

void* abb_borrar_raiz(abb_t* arbol){
    nodo_abb_t* nodo = arbol->raiz;
    void* dato = nodo->dato;
    nodo_abb_destruir(nodo);
    arbol->raiz = NULL;
    arbol->cantidad--;
    return dato;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (!abb_pertenece(arbol, clave)){
        return NULL;
    }
    if (abb_cantidad(arbol) == 1){
        return abb_borrar_raiz(arbol);
    }
    char* copia = abb_copiar_clave(clave);
    void* dato = _abb_borrar(copia, arbol);
    arbol->cantidad--;
    free(copia);
    return dato;
}


size_t abb_cantidad(const abb_t *arbol){
    return arbol->cantidad;
}

void _abb_destruir(nodo_abb_t* nodo, abb_destruir_dato_t fdest){
    if (nodo == NULL){
        return;
    }
    _abb_destruir(nodo->izq, fdest);
    _abb_destruir(nodo->der, fdest);
    void* dato = nodo->dato;
    if (fdest){
        fdest(dato);
    }
    nodo_abb_destruir(nodo);
}

void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol->raiz, arbol->fdest);
    free(arbol);
}

void _abb_in_order(nodo_abb_t *nodo, bool visitar(const char *, void *, void*), void* extra, bool* continuar){
    if (!nodo){
        return;
    }
    _abb_in_order(nodo->izq, visitar, extra, continuar);
    if (!(*continuar)){
        return;
    }
    if (!visitar(nodo->clave, nodo->dato, extra)){
        *continuar = false;
    }
    _abb_in_order(nodo->der, visitar, extra, continuar);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    bool continuar = true;
    _abb_in_order(arbol->raiz, visitar, extra, &continuar);
}

bool abb_iter_in_izq(pila_t* pila, nodo_abb_t* nodo){
    if (!nodo){
        return true;
    }
    if (nodo->izq == NULL){
        return pila_apilar(pila, nodo);
    } 
    pila_apilar(pila, nodo);
    return abb_iter_in_izq(pila, nodo->izq);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter){
        return NULL;
    }
    iter->pila = pila_crear();
    if (!iter->pila){
        free(iter);
        return NULL;
    }
    if (!arbol->raiz){
        return iter;
    }
    abb_iter_in_izq(iter->pila, arbol->raiz);
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if (abb_iter_in_al_final(iter)){
        return false;
    }
    nodo_abb_t* nodo = (nodo_abb_t*)(pila_desapilar(iter->pila));
    if (!nodo->der && !nodo->izq){
        return true;
    } else if ( nodo->der ){
        pila_apilar(iter->pila, nodo->der);
        return abb_iter_in_izq(iter->pila, nodo->der->izq);
    }
    return false;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if (abb_iter_in_al_final(iter)) {
        return NULL;
    }
    return ((nodo_abb_t*)(pila_ver_tope(iter->pila)))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}