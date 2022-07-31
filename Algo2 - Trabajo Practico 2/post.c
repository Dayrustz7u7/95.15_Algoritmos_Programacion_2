#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "post.h"
#include "funciones.h"

struct post {
    size_t id;
    abb_t* likes;
    char* mensaje;
    void* autor;  
};

post_t* post_crear(const char* mensaje, size_t id, void* user){
    post_t* post = malloc(sizeof(post_t));
    if (!post){
        return NULL;
    }
    abb_t* likes = abb_crear(strcmp, NULL);
    if (!likes){
        free(post);
        return NULL;
    }
    char* copia_mensaje = copiar_string(mensaje);
    if (!copia_mensaje){
        free(post);
        abb_destruir(likes);
        return NULL;
    }
    post->autor = user;
    post->id = id;
    post->mensaje = copia_mensaje;
    post->likes = likes;
    return post;
}

size_t post_id(const post_t* post){
    return post->id;
}

void* post_autor(post_t* post){
    return post->autor;
}

bool post_dar_like(post_t* post, const char* nombre){
    abb_t* likes = post->likes;
    if(abb_pertenece(likes, nombre)){
        return true;
    }
    return abb_guardar(likes, nombre, NULL);
}

size_t post_cantidad_likes(post_t* post){
    return abb_cantidad(post->likes);
}

void post_ver_likes(post_t* post){
    abb_iter_t* iter = abb_iter_in_crear(post->likes);
    if (!iter){
        return;
    }
    printf("El post tiene %li likes:\n", abb_cantidad(post->likes));
    while (!abb_iter_in_al_final(iter)) {
        printf("	%s", abb_iter_in_ver_actual(iter));
        abb_iter_in_avanzar(iter);
    }
    abb_iter_in_destruir(iter);
    return;
}

char* post_mensaje(const post_t* post){
    return post->mensaje;
}

void post_printear(post_t* post, char* autor){
    char* nombre = borrar_barra_n(autor);
    printf("Post ID %li\n", post->id);
    printf("%s dijo: %s", nombre, post->mensaje);
    printf("Likes: %li\n", abb_cantidad(post->likes));
    free(nombre);
}

void post_destruir(post_t* post){
    abb_destruir(post->likes);
    free(post->mensaje);
    free(post);
}


