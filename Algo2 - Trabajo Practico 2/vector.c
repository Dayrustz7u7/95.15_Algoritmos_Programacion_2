#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "vector.h"
#define INICIAL 8
#define MULT 2

struct vector {
    void** datos;
    size_t cantidad;
    size_t capacidad;
};

vector_t *vector_crear() {
    vector_t *vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(INICIAL * sizeof(void*));

    if (vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->cantidad = 0;
    vector->capacidad = INICIAL;
    return vector;
}

bool vector_pos_existe(vector_t* vector, size_t pos){
    return pos < vector->cantidad;
}

void *vector_obtener(vector_t *vector, size_t pos){
    if (!vector_pos_existe(vector, pos)){
        return NULL;
    }
    void* dato = vector->datos[pos];
    return dato;
}

bool vector_redimensionar(vector_t *vector) {
    void** datos_nuevo = realloc(vector->datos, vector->capacidad * MULT * sizeof(void*));
    if (!datos_nuevo){
        return false;
    }
    vector->datos = datos_nuevo;
    vector->capacidad = vector->capacidad*MULT;
    return true;
}

bool vector_guardar_final(vector_t* vector, void* dato){
    if (vector->cantidad == vector->capacidad){
        bool ok = vector_redimensionar(vector);
        if (!ok){
            return false;
        }
    }
    vector->datos[vector->cantidad] = dato;
    vector->cantidad++;
    return true;
}

size_t vector_largo(vector_t *vector){
    return vector->cantidad;
}

void vector_destruir(vector_t *vector, vetor_destruir_dato_t fdest){
    if (vector == NULL){
        return;
    } else if (vector-> datos == NULL){
        free(vector);
        return;
    } else if (fdest != NULL){
        for (size_t i = 0; i < vector->cantidad; i++){
            fdest(vector->datos[i]);
        }
    }
    free(vector->datos);
    free(vector);
    return;
}
