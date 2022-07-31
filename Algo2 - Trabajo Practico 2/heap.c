#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#define CAPACIDAD_INICIAL 8
#define OPERADOR 2

struct heap{
    void** datos;
    size_t capacidad;
    size_t cantidad;
    cmp_func_t comparar;
};

size_t calcular_padre(size_t pos){
    return (pos-1)/OPERADOR;
}

size_t calcular_h_der(size_t pos){
    return (OPERADOR*pos)+OPERADOR;
}

size_t calcular_h_izq(size_t pos){
    return (OPERADOR*pos)+1;
}

void swap(void**datos,size_t x,size_t y ) {
    void* valor = datos[x];
    datos[x] = datos[y];
    datos[y] = valor; 
}

void heap_inicializar(heap_t* heap, size_t cantidad, size_t capacidad, void** datos, cmp_func_t cmp){
    heap->datos = datos;
    heap->capacidad = capacidad;
    heap->cantidad = cantidad;
    heap->comparar = cmp;
}

void down_heap(heap_t* heap,size_t pos){
    if (pos >= heap->cantidad){
        return;
    }
    size_t izq = calcular_h_izq(pos);
    if (izq >= heap->cantidad){
        return;
    }
    size_t der = calcular_h_der(pos);
    size_t pos_max = izq;
    if (der < heap->cantidad && heap->comparar(heap->datos[izq],heap->datos[der]) < 0 ){ // cmp(datos[izq], datos[der]) < 0
        pos_max = der;
    }
    if (heap->comparar(heap->datos[pos_max], heap->datos[pos]) > 0) {
        swap(heap->datos, pos_max, pos);
        down_heap(heap,pos_max);
    }
}

void heapify(heap_t* heap){    
    for (size_t i = heap->cantidad + 1; i > 0; i--){
        down_heap(heap,i-1);
    };
}

heap_t* _heap_crear(void *arreglo[],size_t longitud,cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap){
        return NULL;
    }
    void** datos = malloc(sizeof(void*)*longitud*OPERADOR);
    if(!datos){
        free(heap);
        return NULL;
    }
    if(arreglo){
        for (size_t i = 0; i < longitud; i++){
            datos[i] = arreglo[i];
        }
        heap_inicializar(heap,longitud,longitud*OPERADOR, datos, cmp);
        heapify(heap);
    } else {
        heap_inicializar(heap,0,longitud*OPERADOR,datos,cmp);
    }
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    return _heap_crear(arreglo, n ,cmp);
}

heap_t *heap_crear(cmp_func_t cmp){
    return _heap_crear(NULL,CAPACIDAD_INICIAL,cmp);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cantidad;
}

void up_heap(heap_t* heap, size_t pos){
    if(pos <= 0){
        return;
    }
    size_t padre = calcular_padre(pos);
    if (heap->comparar(heap->datos[pos], heap->datos[padre]) > 0) {  // heap_de maximos //sin cmp
        swap(heap->datos, pos, padre);
        up_heap(heap, padre);
    }
}

bool heap_esta_vacio(const heap_t *heap){
    return (heap->cantidad == 0);
}


void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    while (!heap_esta_vacio(heap) && destruir_elemento != NULL)
    {
        void* dato = heap_desencolar(heap);
        destruir_elemento(dato);
    }
    free(heap->datos);
    free(heap);
}

bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad){
    void **ampliar_datos = realloc(heap->datos, nueva_capacidad * sizeof(void*));
    if(!ampliar_datos){
        return false;
    }
    heap->datos = ampliar_datos;
    heap->capacidad = nueva_capacidad;
    return true;
}

bool heap_encolar(heap_t *heap, void *elem){
    if (heap->cantidad == heap->capacidad){
        bool redimension = heap_redimensionar(heap, heap->capacidad*OPERADOR);
        if (!redimension){
            return false;
        }
    }
    heap->datos[heap->cantidad] = elem;
    up_heap(heap, heap->cantidad);
    heap->cantidad++;
    return true;
}

void *heap_desencolar(heap_t *heap){
    if (heap_esta_vacio(heap)){
        return NULL;
    }
    swap(heap->datos, 0, heap->cantidad - 1);
    void* elemento = heap->datos[heap->cantidad-1];
    heap->cantidad--;
    down_heap(heap, 0);
    if (!heap_esta_vacio(heap) && heap->capacidad/heap->cantidad == OPERADOR*OPERADOR){
        heap_redimensionar(heap, heap->capacidad/OPERADOR);
    }
    return elemento;
}

void *heap_ver_max(const heap_t *heap){
    if (heap_esta_vacio(heap)){
        return NULL;
    }
    return heap->datos[0];
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heap_t* heap = heap_crear_arr(elementos, cant, cmp);
    if (!heap){
        return;
    }
    size_t i = cant-1;
    while(!heap_esta_vacio(heap)){
        elementos[i] = heap_desencolar(heap);
        i--;
    }
    heap_destruir(heap, NULL);
}