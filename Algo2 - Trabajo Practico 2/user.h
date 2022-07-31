#ifndef USER_T
#define USER_T

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

typedef struct usuario user_t;

/*
 * Crea un Usuario 
 * Post: devuelve la referencia al usuario creado
 * 
*/
user_t* user_crear(const char* nombre, size_t afinidad);

/*
 * Recibe un usuario y devuelve su nombre
 * Pre: el usuario existe
 * Post: devuelve una cadena que contine el nombre
*/
char* user_nombre(user_t* user);

/*
 * Recibe un usuario, un post, y la afinidad entre estos y lo agrega al feed del usuario
 * Pre: el usuario existe
 * Post: devuelve true si se agrega con exito, false si falla
*/
bool user_insertar_post(user_t* user, void* post, size_t afinidad);

/*
 * Recibe un usuario y devuelve su constante de afinidad
 * Pre: el usuario existe
 * Post: devuelve su constante de afinidad
*/
size_t user_afinidad(user_t* user);

/*
 * Recibe dos usuarios y calcula la afinidad entre estos dos
 * Pre: ambos usuarios deben existir
 * Post: devuelve un numero que representa la afinidad entre ellos
*/
size_t user_calcular_afinidad(user_t* user1, user_t* user2);

/*
 * Recibe un usuario e indica si existen elementos en su feed
 * Pre: el usuario debe existir
 * Post: devuelve una referencia al contenido del feed
*/
bool user_feed_esta_vacio(user_t* user);

/*
 * Recibe un usuario y devuelve una referencia a un elemento del feed
 * Pre: el usuario debe existir
 * Post: devuelve una referencia al contenido del feed o NULL si no tiene elementos en su feed
*/
void* user_ver_feed(user_t* user);

/*
 * Recibe un usuario y lo destruye
 * Post: destruye el usuario 
*/
void user_destruir(user_t* user);

#endif //USER_T