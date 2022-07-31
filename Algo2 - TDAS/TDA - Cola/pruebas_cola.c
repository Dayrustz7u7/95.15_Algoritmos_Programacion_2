#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VOLUMEN 800
#define DIVISOR 3

void wrapper_pila_destruir(void*  dato){
    pila_destruir(dato);
}

static void prueba_cola_vacia(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA SI ESTA VACIA UNA COLA\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola = cola_crear();
    print_test("cola no cuenta con ningun elemento",cola_esta_vacia(cola));
    print_test("Accion Desacolar a una cola Vacia es invalido",cola_desencolar(cola) == NULL);
    print_test("Accion VER_PRIMERO a una cola Vacia es invalido",cola_ver_primero(cola)==NULL);
    printf("\n");
    cola_destruir(cola,free);
}
static void prueba_cola_crear(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA CREAR UNA COLA CORRECTAMENTE\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola = cola_crear();
    print_test("La cola fue creada correctamente", cola != NULL);
    printf("\n");
    cola_destruir(cola,free);
}
static void prueba_cola_destruir_null(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR COLA VACIA CON NULL\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_a = cola_crear();
    cola_destruir(cola_a,NULL);
    print_test("La cola se destruyo por el parametro NULL",true);
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR COLA CON NULL\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_b = cola_crear();
    int un_elemento = 8;
    cola_encolar(cola_b,&un_elemento);
    cola_destruir(cola_b,NULL);
    print_test("La cola se destruyo correctamente",true);
    printf("\n");
}
static void prueba_cola_destruir_free(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR COLA VACIA CON FREE\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_a = cola_crear();
    print_test("cola no cuenta con ningun elemento",cola_esta_vacia(cola_a));
    cola_destruir(cola_a,free);
    print_test("La cola se destruyo por el parametro free",true);
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR CON FREE COLA CON ELEMENTOS RESERVADOS DINAMICAMENTE\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_b = cola_crear();
    int *un_elemento = malloc(sizeof(int));
    cola_encolar(cola_b,un_elemento);
    print_test("La cola cuenta con un elemento",!cola_esta_vacia(cola_b));
    cola_destruir(cola_b,free);

    printf("\n");
}
static void prueba_cola_destruir_funcion(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR COLA VACIA CON FUNCION DESTRUCTIVA\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_a = cola_crear();
    print_test("Cola no cuenta con ningun elemento",cola_esta_vacia(cola_a));
    cola_destruir(cola_a,wrapper_pila_destruir);
    print_test("La cola se destruyo con la funcion destructiva",true); //duda :c
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESTRUIR COLA CON FUNCION DESTRUCTIVA\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola_b = cola_crear();
    pila_t* pila = pila_crear();
    cola_encolar(cola_b,pila);
    cola_destruir(cola_b,wrapper_pila_destruir);
    print_test("La cola no esta vacia y se destruyo correctamente",true); // duda :c

    printf("\n");
}
static void prueba_ver_primero(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA VER_PRIMERO DE UNA COLA RECIEN CREADA\n");
    printf("----------------------------------------------------------------\n");
    /*Prueba de Ver primero cuando no tiene ningun elemento*/

    cola_t* cola=cola_crear();
    print_test("Accion de VER_primero a una cola recien creada es invalido",cola_ver_primero(cola)== NULL);

    /*Prueba cuando la cola tiene elementos y devuelve el primero*/

    size_t un_elemento;
    cola_encolar(cola,&un_elemento);
    print_test("El primero coincide con el ultimo elemento agregado",&un_elemento == cola_ver_primero(cola));
    cola_desencolar(cola);
    printf("\n");
    cola_destruir(cola,free);
}
static void prueba_encolar_un_elemento(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA ENCOLAR Y DESENCOLAR UN SOLO UN ELEMENTO \n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola = cola_crear();
    int un_elemento = 8;
    print_test("Encolar unico elemento a la cola",cola_encolar(cola,&un_elemento));
    print_test("El primero coincide con el unico elemento de la cola",cola_ver_primero(cola)== &un_elemento);
    print_test("Desencolar el unico elemento",cola_desencolar(cola) == &un_elemento);
    print_test("Cola no cuenta con ningun elemento",cola_esta_vacia(cola));
    print_test("Accion VER_PRIMERO a una cola vacia",cola_ver_primero(cola)== NULL);
    printf("\n");
    cola_destruir(cola,free);
}
static void prueba_encolar_null(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA ENCOLAR UN ELEMENTO NULL\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola=cola_crear();
    print_test("Accion encolar un elemento NULL a la cola es valido",cola_encolar(cola,NULL));
    print_test("Accion VER_PRIMERO a una cola con un elemento NULL",cola_ver_primero(cola) == NULL);
    print_test("Accion Desencolar a una cola con un elemento es valido",cola_desencolar(cola) == NULL);
    print_test("Cola no cuenta con ningun elemento",cola_esta_vacia(cola));
    print_test("Accion VER_PRIMERO a una cola vacia",cola_ver_primero(cola)== NULL);
    printf("\n");
    cola_destruir(cola,free);
}
static void prueba_encolar_varios_elemetos(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA ENCOLAR Y DESENCOLAR VARIOS ELEMENTOS Y QUE COINCIDAN PRIMERO \n");
    printf("----------------------------------------------------------------\n");
    
    cola_t* cola=cola_crear();
    int cantidad = 0;
    void* elementos[MAX];
    int primero = 0;
    bool primero_coincide = true;
    for(int i = 0; i < MAX && primero_coincide;i++){
        primero_coincide = cola_encolar(cola,&elementos[i]);
        if(cola_ver_primero(cola)!=&elementos[primero]){
            primero_coincide = false;
        }
        cantidad++;
        print_test("El primero coincide con el elemento recien agregado a la cola",cola_ver_primero(cola)==&elementos[primero]);
        if( i%DIVISOR == 0){
            if(cola_desencolar(cola) != &elementos[primero]){
                primero_coincide = false;
            }
            cantidad--;
            primero++;
            if(i-1 > 0){
                print_test("El Nuevo primero coincide con el primer elemento de la cola ya desencolado",cola_ver_primero(cola)==&elementos[primero]);
            }
        }   
    }
    printf("Esta es la cantidad en prueba: %i\n",cantidad);
    printf("\n");

    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESENCOLAR POR COMPLETO HASTA QUE TENGA 0 ELEMENTOS\n");
    printf("----------------------------------------------------------------\n");
    for(int i = cantidad;i > 0;i--){
        cola_desencolar(cola);
    }
    print_test("Total de elementos luego de desencolar se comporta como vacia",cola_esta_vacia(cola));
    print_test("La cola se comporta como recien creada luego de desencolar por completo",cola_desencolar(cola) == NULL && cola_esta_vacia(cola));
    print_test("Accion Desencolar a una cola Vacia es invalido",cola_desencolar(cola) == NULL);
    print_test("Accion VER_PRIMERO a una cola desacolado totalmente es invalido",cola_ver_primero(cola)==NULL);
    printf("\n"); 
    cola_destruir(cola,free);
}
static void prueba_volumen_cola(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA VOLUMEN DE LA COLA\n");
    printf("----------------------------------------------------------------\n");
    cola_t* cola = cola_crear();
    void* elementos[VOLUMEN];
    int cantidad = 0;
    int primero = 0;
    bool encolo = true;
    for(int i = 0; i < VOLUMEN && encolo;i++){
        encolo = cola_encolar(cola,&elementos[i]);
        cantidad++;
    }
    print_test("Accion acolar mayor a la capacidad inicial de la cola hasta un VOLUMEN es valido",cantidad == VOLUMEN);
    print_test("El primero coincide con el elemento recien agregado a la cola",cola_ver_primero(cola)==&elementos[primero]);
    for(int i = VOLUMEN;i > 0;i--){
        cola_desencolar(cola);
    }
    print_test("Accion desacolar hasta que este vacia",cola_esta_vacia(cola));
    print_test("La cola se comporta como recien creada luego de desacolar por completo",cola_desencolar(cola) == NULL && cola_esta_vacia(cola));
    print_test("Accion Desacolar a una cola Vacia es invalido",cola_desencolar(cola) == NULL);
    print_test("Accion VER_PRIMERO a una cola desacolado totalmente es invalido",cola_ver_primero(cola)==NULL);
    printf("\n");
    cola_destruir(cola,free);
}


void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_cola_crear();
    prueba_ver_primero();
    prueba_encolar_un_elemento();
    prueba_encolar_null();
    prueba_encolar_varios_elemetos();
    prueba_volumen_cola();
    prueba_cola_destruir_null();
    prueba_cola_destruir_free();
    prueba_cola_destruir_funcion();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
