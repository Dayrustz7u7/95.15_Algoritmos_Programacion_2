#include "pila.h"
#include "testing.h"
#include <stdio.h>
#define VOLUMEN 800

static void prueba_pila_vacia(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA SI ESTA VACIA UNA PILA\n");
    printf("----------------------------------------------------------------\n");
    pila_t* pila = pila_crear();
    print_test("Pila no cuenta con ningun elemento",pila_esta_vacia(pila));
    print_test("Accion Desapilar a una pila Vacia es invalido",pila_desapilar(pila) == NULL);
    print_test("Accion Ver_tope a una pila Vacia es invalido",pila_ver_tope(pila)==NULL);
    printf("\n");
    pila_destruir(pila);
}
static void prueba_pila_crear(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA CREAR UNA PILA CORRECTAMENTE\n");
    printf("----------------------------------------------------------------\n");
    pila_t* pila = pila_crear();
    print_test("La pila fue creada correctamente", pila != NULL);
    printf("\n");
    pila_destruir(pila);
}
static void prueba_pila_destruir(void){
    printf("----------------------------------------------------------------\n");
    pila_t* pila = pila_crear();
    pila_destruir(pila);
    print_test("La pila fue destruida correctamente",pila != NULL); // duda
    printf("\n");
}
static void prueba_apilar_un_elemento(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA APILAR Y DESAPILAR UN SOLO UN ELEMENTO \n");
    printf("----------------------------------------------------------------\n");
    pila_t* pila=pila_crear();
    int un_elemento;
    print_test("Apilar unico elemento a la pila",pila_apilar(pila,&un_elemento));
    print_test("El tope coincide con el unico elemento de la pila",pila_ver_tope(pila)==&un_elemento);
    print_test("Desapilar el unico elemento",pila_desapilar(pila) == &un_elemento);
    print_test("Pila no cuenta con ningun elemento",pila_esta_vacia(pila));
    print_test("Accion ver tope a una pila vacia",pila_ver_tope(pila)== NULL);
    printf("\n");
    pila_destruir(pila);
}
static void prueba_apilar_null(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA APILAR UN ELEMENTO NULL\n");
    printf("----------------------------------------------------------------\n");
    pila_t* pila=pila_crear();
    print_test("Accion apilar un elemento NULL a la pila es valido",pila_apilar(pila,NULL));
    print_test("Accion ver tope a una pila con un elemento",pila_ver_tope(pila) == NULL);
    print_test("Accion Desapilar a una pila con un elemento es valido",pila_desapilar(pila) == NULL);
    printf("\n");
    pila_destruir(pila);
}
static void prueba_apilar_varios_elemetos(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA APILAR Y DESAPILAR VARIOS ELEMENTOS Y QUE COINCIDAN TOPES \n");
    printf("----------------------------------------------------------------\n");
    
    pila_t* pila=pila_crear();
    int cantidad = 0;
    void* elementos[10];
    bool tope_coincide = true;
    for(int i = 0; i < 10 && tope_coincide;i++){
        tope_coincide = pila_apilar(pila,&elementos[i]);
        if(pila_ver_tope(pila)!=&elementos[i]){
            tope_coincide = false;
        }
        cantidad++;
        print_test("El tope coincide con el elemento recien agregado a la pila",pila_ver_tope(pila)==&elementos[i]);
        if( i%3 == 0){
            if(pila_desapilar(pila)!= &elementos[i]){
                tope_coincide = false;
            }
            cantidad--;
            if(i-1 > 0){
                print_test("El Nuevo tope coincide con el ultimo elemento de la pila ya restado",pila_ver_tope(pila)==&elementos[i-1]);
            }
        }   
    }
    printf("Esta es la cantidad en prueba: %i\n",cantidad);
    printf("\n");

    printf("----------------------------------------------------------------\n");
    printf("PRUEBA DESAPILAR POR COMPLETO HASTA QUE TENGA 0 ELEMENTOS\n");
    printf("----------------------------------------------------------------\n");
    for(int i = cantidad;i > 0;i--){
        pila_desapilar(pila);
    }
    print_test("Total de elementos luego de desapilar: pila->cantidad == 0",pila_esta_vacia(pila));
    print_test("La pila se comporta como recien creada luego de desapilar por completo",pila_desapilar(pila) == NULL && pila_esta_vacia(pila));
    print_test("Accion Desapilar a una pila Vacia es invalido",pila_desapilar(pila) == NULL);
    print_test("Accion Ver_tope a una pila desapilado totalmente es invalido",pila_ver_tope(pila)==NULL);
    printf("\n"); 
    pila_destruir(pila);
}
static void prueba_volumen_pila(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA VOLUMEN DE LA PILA\n");
    printf("----------------------------------------------------------------\n");
    pila_t* pila = pila_crear();
    void* elementos[VOLUMEN];
    int cantidad = 0;
    bool apilo=true;
    for(int i = 0; i < VOLUMEN && apilo;i++){
        apilo=pila_apilar(pila,&elementos[i]);
        cantidad++;
    }
    print_test("Accion apilar mayor a la capacidad inicial de la pila hasta un VOLUMEN es valido",cantidad == VOLUMEN);
    print_test("El tope coincide con el elemento recien agregado a la pila",pila_ver_tope(pila)==&elementos[cantidad-1]);
    for(int i = VOLUMEN;i > 0;i--){
        pila_desapilar(pila);
    }
    print_test("Accion desapilar hasta que este vacia: pila->cantidad == 0",pila_esta_vacia(pila));
    print_test("La pila se comporta como recien creada luego de desapilar por completo",pila_desapilar(pila) == NULL && pila_esta_vacia(pila));
    print_test("Accion Desapilar a una pila Vacia es invalido",pila_desapilar(pila) == NULL);
    print_test("Accion Ver_tope a una pila desapilado totalmente es invalido",pila_ver_tope(pila)==NULL);
    printf("\n");
    pila_destruir(pila);
}
static void prueba_ver_tope(void){
    printf("----------------------------------------------------------------\n");
    printf("PRUEBA VER_TOPE DE UNA PILA RECIEN CREADA\n");
    printf("----------------------------------------------------------------\n");
    /*Prueba de Ver tope cuando no tiene ningun elemento*/

    pila_t* pila=pila_crear();
    print_test("Accion de VER_TOPE a una Pila recien creada es invalido",pila_ver_tope(pila)== NULL);

    /*Prueba cuando la pila tiene elementos y devuelve el tope*/

    size_t un_elemento;
    pila_apilar(pila,&un_elemento);
    print_test("El tope coincide con el ultimo elemento agregado",&un_elemento == pila_ver_tope(pila));
    pila_desapilar(pila);
    printf("\n");
    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_crear();
    prueba_ver_tope();
    prueba_apilar_un_elemento();
    prueba_apilar_null();
    prueba_apilar_varios_elemetos();
    prueba_volumen_pila();
    prueba_pila_destruir();
    // ...
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
