#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "user.h"
#include "post.h"
#include "funciones.h"

typedef struct feed_data feed_data_t;

struct feed_data {
    void* post;
    size_t afinidad;
};

struct usuario {
    heap_t* feed;
    char* nombre;
    size_t const_afinidad;
};

int _prioridad_feed(feed_data_t *post1, feed_data_t *post2){
    if (post1->afinidad < post2->afinidad){
        return 1;
    } else if (post1->afinidad > post2->afinidad){
        return -1;
    } else {
        post_t* primero = (post_t*)post1->post;
        post_t* segundo = (post_t*)post2->post;
        if (post_id(primero) > post_id(segundo)){
            return -1;
        }
    }
    return 1;
}

int prioridad_feed(const void* post1, const void* post2){
    return _prioridad_feed((feed_data_t*)post1, (feed_data_t*)post2);
}

user_t* user_crear(const char* nombre, size_t afinidad){
    user_t* user = malloc(sizeof(user_t));
    if (!user){
        return NULL;
    }
    char* copia_nombre = copiar_string(nombre);
    if (!copia_nombre){
        free(user);
        return NULL;
    }
    heap_t* feed = heap_crear(prioridad_feed);
    if (!feed){
        free(user);
        free(copia_nombre);
        return NULL;
    }
    user->const_afinidad = afinidad;
    user->feed = feed;
    user->nombre = copia_nombre;
    return user;
}

char* user_nombre(user_t* user){
    if (user == NULL){
        return NULL; 
    }
    return user->nombre;
}

feed_data_t* feed_data_crear(void* post, size_t afinidad){
    feed_data_t* data = malloc(sizeof(feed_data_t));
    if (!data){
        return NULL;
    }
    data->post = post;
    data->afinidad = afinidad;
    return data;
}

bool user_insertar_post(user_t* user, void* post, size_t afinidad){
    feed_data_t* data = feed_data_crear(post, afinidad);
    if (!data){
        return false;
    }
    return heap_encolar(user->feed, data);
}

size_t user_afinidad(user_t* user){
    return user->const_afinidad;
}

size_t user_calcular_afinidad(user_t* user1, user_t* user2){
    return (size_t)abs((int)(user1->const_afinidad - user2->const_afinidad));
}

bool user_feed_esta_vacio(user_t* user){
    return heap_esta_vacio(user->feed);
}

void* user_ver_feed(user_t* user){
    if (user_feed_esta_vacio(user)){
        return NULL;
    }
    feed_data_t* data = (feed_data_t*) heap_desencolar(user->feed);
    void* dato = data->post;
    free(data);
    return dato;
}

void user_destruir(user_t* user){
    heap_destruir(user->feed, free);
    free(user->nombre);
    free(user);
}