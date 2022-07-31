#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U
#define INICIAL 17
#define OCUPADO 1
#define VACIO 0
#define BORRADO -1
#define CONSTBORRADO 0.70
#define MULT 2

typedef struct campo {
    int estado;
    char* clave;
    void*  dato;
}campo_t;

struct hash {
    campo_t *tabla;
    size_t capacidad;      
    size_t  cantidad;
    size_t  borrados;
    hash_destruir_dato_t func_destruccion;
};

struct hash_iter {
    size_t pos;
    size_t capacidad;
    campo_t* campo;
};

// La funcion de hash fue obtenida del link: http://ctips.pbworks.com/w/page/7277591/FNV%20Hash

size_t jenkins_one_at_a_time_hash(const char *key)
{
    size_t len = strlen(key) + 1;
    size_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {                                    
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

campo_t* hash_iniciar_tabla(size_t capacidad){
    campo_t* tabla = malloc(sizeof(campo_t)*capacidad);
    if (!tabla){
        return NULL;
    }
    for (size_t i = 0; i<capacidad; i++){
        tabla[i].estado = VACIO;
        tabla[i].clave = NULL;
    }
    return tabla;
}

void hash_inicializar(hash_t* hash, campo_t* tabla, size_t capacidad){
    hash->capacidad = capacidad;
    hash->tabla = tabla;
    hash->cantidad = 0;
    hash->borrados = 0;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));

    if(!hash){
        return NULL;
    }
    campo_t* tabla = hash_iniciar_tabla(INICIAL);
    if(!tabla){
        free(hash);
        return NULL;
    }
    hash_inicializar(hash, tabla, INICIAL);
    hash->func_destruccion = destruir_dato;
    return hash;
}

size_t hash_buscar_posicion(const hash_t* hash, const char* clave){
    size_t pos =  jenkins_one_at_a_time_hash(clave)%hash->capacidad;
    while(pos < hash->capacidad && hash->tabla[pos].estado != VACIO){

        if (strcmp(clave, hash->tabla[pos].clave) == 0){
            return pos;
        }
        if ( (pos) == (hash->capacidad - 1) && hash->tabla[pos].estado == OCUPADO){
            pos = 0;
            continue;
        }
        pos++;
        if (pos == hash->capacidad){
        pos = 0;
        }
    }
    return pos;
}

bool _hash_pertenece(const hash_t* hash, const char* clave, size_t* pos){
    size_t posicion = hash_buscar_posicion(hash, clave);
    *pos = posicion;
    if ( hash->tabla[*pos].estado != OCUPADO ){
        return false;
    }
    return strcmp(hash->tabla[*pos].clave, clave) == 0;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    size_t pos = 0;
    return _hash_pertenece(hash, clave, &pos);
}

bool hash_almacenar(hash_t *hash, const char *clave, void *dato){
    size_t pos = 0;
    if (_hash_pertenece(hash, clave, &pos)){
        //esta
        void* dato_aux = hash->tabla[pos].dato;
        if (hash->func_destruccion){
            hash->func_destruccion(dato_aux);
        }
    } else {
        /// esta borrado
        if (hash->tabla[pos].estado == BORRADO && (strcmp(clave, hash->tabla[pos].clave) == 0)){
            hash->tabla[pos].estado = OCUPADO;
            hash->borrados--;
        } else {
        //no esta
            hash->tabla[pos].clave = malloc(sizeof(char)*(strlen(clave)+1));
            if (!hash->tabla[pos].clave)
            {
                return false;
            }
            hash->tabla[pos].estado = OCUPADO;
            strcpy(hash->tabla[pos].clave, clave);
            
        }
        hash->cantidad++;
    }
    hash->tabla[pos].dato = dato;
    return true;
}

bool hash_condicion_redimencion(const hash_t* hash){
    bool condicion1 = (float)((hash->borrados + hash->cantidad)/hash->capacidad) >= CONSTBORRADO;
    bool condicion2 = hash->cantidad < hash->borrados;
    return (condicion1||condicion2);
}

bool hash_redimencionar(hash_t *hash, size_t nueva_capacidad){
    campo_t* nuevo_campo = hash_iniciar_tabla(nueva_capacidad);
    campo_t* aux = hash->tabla;
    size_t j = hash->capacidad;
    if (!nuevo_campo){
        return false;
    }
    hash_inicializar(hash, nuevo_campo, nueva_capacidad);
    for (size_t i = 0; i < j; i++){
        if (aux[i].estado == OCUPADO){
            hash_almacenar(hash, aux[i].clave, aux[i].dato);
        }
        if (aux[i].clave){
            free(aux[i].clave);
        }
    }
    free(aux);
    return true;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    if (hash_condicion_redimencion(hash)){
        bool estado = hash_redimencionar(hash, hash->capacidad*MULT);
        if (!estado){
            return false;
        }
    }
    return hash_almacenar(hash, clave, dato);
}

void *hash_obtener(const hash_t *hash, const char *clave){
    size_t pos = 0;
    if (!_hash_pertenece(hash, clave, &pos)){
        return NULL;
    }
    return hash->tabla[pos].dato;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t pos = 0;
    if (!_hash_pertenece(hash, clave, &pos)){
        return NULL;
    }
    void* dato = hash->tabla[pos].dato;
    hash->tabla[pos].dato = NULL;
    hash->tabla[pos].estado = BORRADO;
    hash->borrados++;
    hash->cantidad--;
    return dato;
}

void hash_destruir(hash_t *hash){
    
    for (size_t i = 0; i < hash->capacidad; i++){
        if (hash->tabla[i].estado == OCUPADO && hash->func_destruccion){
            hash->func_destruccion(hash->tabla[i].dato);
        }
        if (hash->tabla[i].clave){
            free(hash->tabla[i].clave);
        }
    }
    free(hash->tabla);
    free(hash);
    
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

///primitivas del iterador externo

size_t hash_iter_encontrar_dato(hash_iter_t *iter){
    size_t actual = iter->pos;
    while (actual < iter->capacidad){
        if (iter->campo[actual].estado == OCUPADO && actual == iter->pos){
            actual++;
            continue;
        } else if (iter->campo[actual].estado == OCUPADO){
            return actual;
        }
        actual++;
    }
    return actual;
    } 

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));
    if (!iter){
        return NULL;
    }
    iter->campo = hash->tabla;
    iter->capacidad = hash->capacidad;
    iter->pos = 0;
    iter->pos = hash_iter_encontrar_dato(iter);
    return iter;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->pos == iter->capacidad ;
}

bool hash_iter_avanzar(hash_iter_t *iter){
    if (hash_iter_al_final(iter)){
        return false;
    }
    iter->pos = hash_iter_encontrar_dato(iter);
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if (hash_iter_al_final(iter)){
        return NULL;
    }
    return iter->campo[iter->pos].clave;
}

void hash_iter_destruir(hash_iter_t* iter){
    free(iter);
}


