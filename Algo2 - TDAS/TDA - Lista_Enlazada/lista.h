#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdio.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;
typedef struct nodo nodo_t;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

/*
  * Crea una lista
  * Post:Devuelve una lista_t vacia.
*/
lista_t *lista_crear(void);
/*
  *Devuelve true si la lista no tiene elementos(cantidad == 0), false en caso contrario.
  *Pre -> la lista fue creada.
*/
bool lista_esta_vacia(const lista_t *lista);
/*
  *Agrega el nuevo elemento pasado por parametro "void* dato" al inicio de la lista
  *Devuelve true si todo sale correcto o falso en caso contrario
  *Pre -> La lista debe estar creada.
  *Post -> El valor de elemento se encuentra al incio de la lista.
*/
bool lista_insertar_primero(lista_t *lista, void *dato);
/*
  *Agrega el nuevo elemento pasado por parametro "void* dato" al Final de la lista
  *Devuelve true si todo sale correcto o falso en caso contrario
  *Pre -> La lista debe estar creada.
  *Post -> El valor de elemento se encuentra al Final de la lista.
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);
/*
  *Devuelve el primer elemento de la lista y luego lo borra de la lista.
   ->Si la lista esta vacia devuelve NULL
   ->Si contiene un unico elemento,luego del proceso,vuelve hacer lista recien creada.
  * Pre-> La lista debe estar creada.
  * Post-> Se devuelve el primer elemento de la lista si no esta vacia.
*/
void *lista_borrar_primero(lista_t *lista);
/*
  *Obtiene el valor del primer elemento de la lista. Si la lista tiene
  *elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
  * Pre->la lista fue creada.
  * Post-> Se devolvió el primer elemento de la lista, cuando no está vacía.
*/
void *lista_ver_primero(const lista_t *lista);
/*
  *Se Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
  *elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
  * Pre ->la lista fue creada.
  * Post -> Se devolvió el ultimo elemento de la lista, cuando no está vacía.
*/
void *lista_ver_ultimo(const lista_t* lista);
/*
  *Devuelve la cantidad de elementos de la lista.
  *Pre -> la lista debe estar creada.
*/
size_t lista_largo(const lista_t *lista);
/*
  *Destruye la lista. Si se recibe la función destruir_dato por parámetro,
  *para cada uno de los elementos de la lista llama a destruir_dato.
  *  Pre-> La lista fue creada. "Destruir_dato" es una función capaz de destruir
  *   los datos de la lista, o NULL en caso de que no se la utilice.
  *  Post-> Se eliminaron todos los elementos de la lista.
*/
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                PRIMITIVA DE LISTA_ITERAR_INTERNO
 * *****************************************************************/

/*
  * Itera la lista y ejecuta la funcion visitar a los elementos segun lo
  * lo que devuelva dicha funcion.
  *  ->Si dentro de la funcion visitar usa void* extra esta como condicion
  *     de corte. Hay un limite de iteraciones a la lista.
  *  ->Si No contiene una condicion de corte, itera toda la lista
  *     ejecutando la funcion visitar.
  *  ->Si la Funcion visitar es NULL solo recorre toda la lista.
  * 
  * Pre-> Lista debe estar creada
  * Post-> Modifica cada elemento de la lista segun la funcion visitar.
*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                PRIMITIVA DE LISTA_ITERAR_EXTERNO
 * *****************************************************************/

/*
  * Crea una iterador_externo
  * Pre-> La Lista debe estar creaa
  * Post-> Devuelve una lista_iter_t apuntando al inicio de la lista.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);
/*
  * Avanza en la lista por elemento una sola vez devolvera true si todo sale
  * correcto, caso contrario Devuelve false.
  *  Pre-> La Lista_iter debe estar creada.
  *  Post-> Avanza en la lista un elemento y devuelve true.
*/
bool lista_iter_avanzar(lista_iter_t *iter);
/*
  * Obtiene el valor elemento de la lista donde se encuentre posicionado el iterador. 
  * Si el iterador apunta a NULL, se devuelve NULL
  *  Pre-> La Lista_iter debe estar creada.
  *  Post-> Devuelve el valor del elemento de la lista.
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);
/*
  * Evalua si el iterador llego al final de la lista.
  * Devuelve true si es asi o false caso contrario
  *  Pre-> Lista_iter debe estar creado.
*/
bool lista_iter_al_final(const lista_iter_t *iter);
/*
  * Destruye el iterador externo
  *  Pre-> Lista_iter debe estar creada.
*/
void lista_iter_destruir(lista_iter_t *iter);
/*
  * Inserta el elemento a la lista segun la ubicacion del iterador
  * interno y se actualiza la cantidad de dicha lista.
  * Devuelve true si es asi o false caso contrario
  *  Pre-> Lista_iter debe estar creado.
  *  Post-> Devuelve true si se inserto bien el elemento a la lista
  *    Caso contrario false.
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
/*
  * Borra el elemento a la lista segun la ubicacion del iterador
  * interno y se actualiza la cantidad de dicha lista.
  * Devuelve true si es asi o false caso contrario
  *  Pre-> Lista_iter debe estar creado.
  *  Post-> Devuelve true si se borro bien el elemento a la lista
  *    Caso contrario false.
*/
void* lista_iter_borrar(lista_iter_t *iter);

void pruebas_lista_estudiante(void);

#endif //LISTA_ENLAZADA_H


