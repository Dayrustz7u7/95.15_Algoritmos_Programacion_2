#ifndef ALGOGRAM_T
#define ALGOGRAM_T

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "hash.h"
#include "post.h"
#include "user.h"

typedef struct algogram gram_t;

/*
 * Crea una Red "algogram"
 * Post: Devuelve un puntero a la red Creada.
*/
gram_t* algogram_crear(void);

/*
 * Recibe un usuario y verifica que pertenezca a la red
 * Pre: La red debe estar creada 
 * Post: devuelve true si el usuario pertenece, false en caso contrario
*/ 
bool gram_usuario_existe(gram_t* red, const char* nombre);

/* 
 * Pre: la red debe existir
 * Post: devuelve true si hay un usuario activo, false en el caso contrario
 * Verifia que el usuario este logeado en la red
*/
bool gram_hay_user_activo(gram_t* red);

/*
 * Funcion que agrega todos los usuarios de un .txt a la red
 * -> Pre: La red Debe estar creada.
 * -> Post: Devuelve True si agrega al ususario o false en caso contrario
*/
bool gram_agregar_user(gram_t* red, const char* user, size_t afinidad);

/*
 * Funcion que devuelve el nombre del usuario activo
 * -> Pre: La red Debe estar creada
 * -> Post: Devuelve el nombre del usuario actual, NULL en caso de no haber un activo
*/ 
char* gram_actual_nombre(gram_t* red);

/*
 * Funcion que Logea al usuario en la red con su respectivo Nombre
 * -> Pre: La red debe estar creada
 * -> Post: Devuelve true si todo sale bien o false en caso contrario
*/
bool gram_logear_user(gram_t* red, const char* nombre);

/*
 * Funcion que Cierra Sesion del usuario Activo en la Red
 * -> Pre: La red Debe de existir
 * -> Post: Devuelve true si hace logout en caso contrario
 *          false.
*/
bool gram_logut(gram_t* red);

/*
 * Funcion que se encarga de Publicar el Mensaje en la Red 
 * -> Pre: La red debe estar creada
 * -> Post: devuelve true si se publica el mensaje, false en caso de fallar
*/
bool gram_publicar(gram_t* red, const char* mensaje);

/*
 * Funcion que se encarga de Dar Like al Post en la red
 * mediante el ID
 *  -> Pre : La Red debe estar creada
 *  -> Post: Devuelve False si no hay usuario activo en la red o 
 *     si el Post no existe
*/
bool gram_dar_like(gram_t* red, size_t id);

/*
 * Muestra al Usuario, quienes han dado Like al Posteo mediante El ID
 * -> Pre: La red debe estar creada.
*/
bool gram_ver_likes(gram_t* red, size_t id);

/*
 * Se encarga de ver los posteos de un Usuario logeado
 *  -> Pre: La red debe estar creada
 *  -> Post: devuelve true si se puede visualizar el mensaje, false en caso de que no
*/
bool gram_ver_feed(gram_t* red);
/*
 * Destruye la Red
 * -> Pre: La red debe estar creada
 * -> Post: Destruye la estructura Red
*/
void gram_destruir(gram_t* red);

#endif // ALGOGRAM_T