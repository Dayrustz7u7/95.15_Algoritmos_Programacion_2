#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "hash.h"
#include "post.h"
#include "user.h"
#include "algogram.h"

struct algogram {
    hash_t* users;
    vector_t* almacen;
    user_t* actual;
};

void _user_destruir(void* user){
    user_destruir((user_t*)user);
}

gram_t* algogram_crear(){
    gram_t* red = malloc(sizeof(gram_t));
    if (!red){
        return NULL;
    }
    vector_t* almacen = vector_crear();
    if (!almacen){
        return NULL;
    }
    hash_t* users = hash_crear(_user_destruir);
    if (!users){
        vector_destruir(almacen, NULL);
        free(red);
        return NULL;
    }
    red->actual = NULL;
    red->almacen = almacen;
    red->users = users;
    return red;
}

bool gram_usuario_existe(gram_t* red, const char* nombre){
    return hash_pertenece(red->users, nombre);
}

bool gram_hay_user_activo(gram_t* red){
    return red->actual != NULL;
}

bool gram_agregar_user(gram_t* red, const char* user, size_t afinidad){
    user_t* nuevo_user = user_crear(user, afinidad);
    if (!nuevo_user){
        return false;
    }
    return hash_guardar(red->users, user, nuevo_user);
}

char* gram_actual_nombre(gram_t* red){
    if (!gram_hay_user_activo(red)){
        return NULL;
    }
    return user_nombre(red->actual);
}

bool gram_logear_user(gram_t* red, const char* nombre){
    if (!gram_usuario_existe(red, nombre)){
        return false;
    }
    user_t* user = (user_t*)hash_obtener(red->users, nombre);
    red->actual = user;
    return true;
}

bool gram_logut(gram_t* red){
    if (!gram_hay_user_activo(red)){
        return false;
    }
    red->actual = NULL;
    return true;
}

bool gram_insertar_en_feeds(gram_t* red, post_t* nuevo_post){
    hash_iter_t* iter = hash_iter_crear(red->users);
    if (!iter){
        return false;
    }
    user_t* autor = red->actual;
    while (!hash_iter_al_final(iter)){
        const char* actual = hash_iter_ver_actual(iter);
        user_t* user = (user_t*)hash_obtener(red->users, actual);
        if (strcmp(user_nombre(autor), actual) == 0){
            hash_iter_avanzar(iter);
            continue;
        }
        size_t afinidad = user_calcular_afinidad(autor, user);
        // Si falla alguna vez, no detengo su ejecucion
        user_insertar_post(user, nuevo_post, afinidad);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return true;
}

bool gram_publicar(gram_t* red, const char* mensaje){
    post_t* nuevo_post = post_crear(mensaje, vector_largo(red->almacen), red->actual);
    if (!nuevo_post){
        return false;
    }
    bool ok = vector_guardar_final(red->almacen, nuevo_post);
    if (!ok){
        return false;
    }
    ok &= gram_insertar_en_feeds(red, nuevo_post);
    return ok;
}

bool gram_dar_like(gram_t* red, size_t id){
    if(!gram_hay_user_activo(red) || !vector_pos_existe(red->almacen, id)){
        return false;
    }
    post_t* post = (post_t*)vector_obtener(red->almacen, id);
    return post_dar_like(post, user_nombre(red->actual));
}

bool gram_ver_likes(gram_t* red, size_t id){
    post_t* post = (post_t*)vector_obtener(red->almacen, id);
    if (post == NULL || post_cantidad_likes(post) == 0){
        return false;
    }
    post_ver_likes(post);
    return true;
}

bool gram_ver_feed(gram_t* red){
    if (!gram_hay_user_activo(red) || user_feed_esta_vacio(red->actual)) {
        return false;
    }
    post_t* post = (post_t*)user_ver_feed(red->actual);
    user_t* autor = (user_t*)post_autor(post);
    post_printear(post, user_nombre(autor));
    return true;
}

void _post_destruir(void* post){
    post_destruir((post_t*)post);
}

void gram_destruir(gram_t* red){
    hash_destruir(red->users);
    vector_destruir(red->almacen, _post_destruir);
    free(red);
}

