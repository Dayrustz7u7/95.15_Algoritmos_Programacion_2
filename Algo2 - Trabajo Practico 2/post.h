#ifndef POST_H
#define POST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "user.h"

typedef struct post post_t;

/* 
 * Crea un post con un mensaje y una referencia a su creador
 * Post: devuelve un puntero al post creado
 * 
*/
post_t* post_crear(const char* mensaje, size_t id, void* user);

/* 
 * Devuelve el id del post recibido
 * Pre: el post existe
 * Post: devuelve el numero identificador del post
*/
size_t post_id(const post_t* post);

/* 
 * Devuelve la referencia al autor creador del post 
 * Pre: el post existe
 * Post: devuelve la referencia al autor 
*/
void* post_autor(post_t* post);

/*
 * Agrega un like al post 
 * Pre: el post existe
 * Post: Devuelve true si se ha podido dar like, false en caso de fallar
*/
bool post_dar_like(post_t* post, const char* nombre);

/*
 * Agrega un like al post 
 * Pre: el post existe
 * Post: devuelve la cantidad de like del post
*/
size_t post_cantidad_likes(post_t* post);

/*
 * Printea por pantalla los likes dados previamente a un post
 * Pre: recibe un post
 * Post: muestra por pantalla los likes 
*/
void post_ver_likes(post_t* post);

/* 
 * Devuelve el mensaje almacenado en el post 
 * Pre: recibe un post
 * Post: devuelve una cadena con el mensaje del post
*/
char* post_mensaje(const post_t* post);

/*
 * Muestra por pantalla el contenido de un post
 * Pre: recibe un post
 * Post: muestra por pantalla el contenido del post
*/ 
void post_printear(post_t* post, char* autor);

/* 
 * Destruye el post que se le pasa
 * Post: el post es destruido
*/
void post_destruir(post_t* post);

#endif //POST_H
