#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define OK true
#define TAM 10
#define VOL 100
#define MAXIMO_ITERACION 5
#define DATO1 1
#define DATO2 2
#define DATO3 3
#define DATO4 4
#define ELEMENTOS 10

bool duplicar_5_elementos(void* dato,void* extra){
    if(*(size_t*)extra >= MAXIMO_ITERACION){
        return false;
    }
    (*(int*)dato) = (*(int*)dato)*DATO2;
    (*(size_t*)extra)++;
    //printf("%d->" ,*(int*)dato);
    return true;
}

bool sumar_elementos(void* dato,void* extra){
    (*(int*)extra)++;
    (*(int*)dato) += DATO1;
    return true;
}

void destruir_pila_wrapper(void* dato){
    pila_destruir(dato);
}

void prueba_lista_vacia(void){
    printf("\n");
    printf("Pruebas con la lista vacia \n");
    lista_t *lista = lista_crear();
    print_test("Prueba crear lista vacia", lista != NULL);
    print_test("La lista creada esta vacia inicialmente", lista_esta_vacia(lista));
    print_test("Ver primero devuelve null", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo devuelve null", lista_ver_ultimo(lista) == NULL);
    print_test("La lista tiene longitud 0", lista_largo(lista) == 0);
    print_test("Borrar primero devuelve null", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    printf("\n");
}

void pruebas_insertar_ver_borrar(void){
    printf("Pruebas insertan, ver y borrar \n");
    lista_t* lista = lista_crear();
    int dato1 = DATO1;
    print_test("La lista esta vacia inicialmente", lista_esta_vacia(lista));
    print_test("Se inserta un elemento", lista_insertar_primero(lista, &dato1));
    print_test("El primero es el elemento", lista_ver_primero(lista) == &dato1);
    print_test("El ultimo es el elemento", lista_ver_ultimo(lista) == &dato1);
    print_test("La longitud de la lista es 1", lista_largo(lista) == 1);
    print_test("Se puede borrar el primero", lista_borrar_primero(lista));
    print_test("La lista vuelve a estar vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es 0", lista_largo(lista) == 0);
    print_test("Ver primero devuelve nuell", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo devuelve nuell", lista_ver_ultimo(lista) == NULL);
    print_test("Borrar primero devuelve null", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_con_varios_elementos(void){

    int dato1 = DATO1;
    char dato2 = 'H';
    char* dato3 = "Hola mundo";
    bool prueba = OK;
    lista_t *lista2 = lista_crear(); 
    printf("Pruebas con varios elementos insertandolos al final\n");
    print_test("Se agrega un elemento al final", lista_insertar_ultimo(lista2, &dato1));
    print_test("Se puede agregar un segundo dato al final", lista_insertar_ultimo(lista2, &dato2));
    prueba &= (lista_ver_primero(lista2) == &dato1) && (lista_ver_ultimo(lista2) == &dato2);
    print_test("El nuevo elemento es el ultimo y el primero agregado permanece al principo", prueba);
    print_test("La lista tiene longitud 2", lista_largo(lista2) == 2);
    print_test("Se agrega un nuevo elemento", lista_insertar_ultimo(lista2, &dato3));
    prueba &= (lista_ver_primero(lista2) == &dato1) && (lista_ver_ultimo(lista2) == &dato3);
    print_test("El nuevo elemento esta al final y se conserva el primero", prueba);
    print_test("La longitud de la lista es 3", lista_largo(lista2) == 3);
    print_test("La lista elimina el primer elemento", lista_borrar_primero(lista2) == &dato1);
    print_test("La lista elimina el segundo elemento", lista_borrar_primero(lista2) == &dato2);
    print_test("La lista elimina el tercer elemento", lista_borrar_primero(lista2) == &dato3);
    print_test("La lista vuelve a estar vacia", lista_esta_vacia(lista2));
    lista_destruir(lista2, NULL);
    printf("\n");
}

static void pruebas_con_elementos_dos(void){
    int dato1 = DATO1;
    char dato2 = 'H';
    char* dato3 = "Hola mundo";
    bool prueba = OK;
    lista_t *lista1 = lista_crear();
    printf("Pruebas con elementos insertandolos al principio \n");
    print_test("Se agrega un elemento al principio", lista_insertar_primero(lista1, &dato1));
    print_test("Se agrega un segundo elemento al principio", lista_insertar_primero(lista1, &dato2));
    prueba &= (lista_ver_primero(lista1) == &dato2) && (lista_ver_ultimo(lista1) == &dato1);
    print_test("El elemento recien agregado es el primero y el ultimo el que se agrego antes", prueba);
    print_test("Se agrega un elemento mas al principio", lista_insertar_primero(lista1, &dato3));
    prueba &= (lista_ver_primero(lista1) == &dato3) && (lista_ver_ultimo(lista1) == &dato1);
    print_test("El primer elemento es el recien elemento agregado y el primero permanece al final", prueba);
    print_test("La lista ahora posee 3 elementos", lista_largo(lista1) == 3);
    print_test("La elimina elimina el ultimo dato agregado y la longitud se reduce", lista_borrar_primero(lista1) == &dato3 && lista_largo(lista1) == 2);
    print_test("La elimina elimina el segundo dato agregado y ahora le queda un elemento", lista_borrar_primero(lista1) == &dato2 && lista_largo(lista1) == 1);
    print_test("La lista elimina el primer elemento que habia agregado", lista_borrar_primero(lista1) == &dato1);
    print_test("La lista vuelve a estar vacia", lista_esta_vacia(lista1));
    lista_destruir(lista1, NULL);
    printf("\n");
}

static void pruebas_con_null(void){
    printf("Pruebas insertando varios elementos null\n");
    bool prueba = OK;
    lista_t *lista = lista_crear();
    for (int i = 0; i < TAM; i++){
        prueba &= lista_insertar_ultimo(lista, NULL);
    }
    print_test("Se insertan en la lista multiples elementos null", prueba);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("La lista tiene la longitud esperada", lista_largo(lista) == TAM);
    prueba &= (lista_ver_primero(lista) == NULL) && (lista_ver_ultimo(lista) == NULL);
    print_test("El primero y el ultimo son el elemento null", prueba);
    for (int i = TAM; i > 0; i--){
        prueba &= lista_borrar_primero(lista) == NULL;
    }
    print_test("De la lista se eliminan solo elementos NULL", prueba);
    print_test("La lista vuelve a estar vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_volumen(void){
    printf("Pruebas de volumen \n");
    lista_t *lista = lista_crear();
    bool prueba = OK;
    int dato_extra = DATO1;
    int* vec = malloc(sizeof(int)*VOL);
    for (int i = 0; i<VOL; i++){
        vec[i] = i;
        prueba &= lista_insertar_ultimo(lista, &vec[i]) && lista_largo(lista) == i+1;
    }
    print_test("Se insertan mucho elementos en la lista y su volumen se altera", prueba);
    for (int i = VOL; i>0; i--){
        prueba &= (lista_borrar_primero(lista) == &vec[VOL - i]) && lista_largo(lista) == i-1;
    }
    print_test("La lista devuelve todos los elementos en orden y modifica su volumen", prueba);
    print_test("La lista vuelve a estar vacia", lista_esta_vacia(lista));
    print_test("Se puede volver a agregar un elemento", lista_insertar_primero(lista, &dato_extra));
    free(vec);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_destruccion_vacia_null(void){
    printf("Pruebas de destruccion: lista vacia con null \n");
    lista_t *lista = lista_crear();
    lista_destruir(lista, NULL);
    print_test("Se destruye la lista vacia con null", OK);
    printf("\n");
}

static void pruebas_destruccion_vacia_funcion(void){
    printf("Pruebas destruccion: lista vacia con funcion \n");
    lista_t *lista = lista_crear();
    lista_destruir(lista, destruir_pila_wrapper);
    print_test("Se destruye la lista vacia con funcion", OK);
    printf("\n");

}

static void pruebas_destruccion_llenas_null(void){
    printf("Destruccion de lista llena con null \n");
    lista_t *lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    lista_insertar_primero(lista, &dato1);
    lista_insertar_primero(lista, &dato2);
    lista_insertar_primero(lista, &dato3);
    lista_destruir(lista, NULL);
    print_test("Se destrulle la lista llena con NULL", OK);
    printf("\n");
}

static void pruebas_destruccion_llenas_funcion(void){
    printf("Pruebas de destruccion llena con funcion \n");
    pila_t *pila1 = pila_crear();
    pila_t *pila2 = pila_crear();
    pila_t *pila3 = pila_crear();
    lista_t *lista = lista_crear();
    lista_insertar_ultimo(lista, pila1);
    lista_insertar_ultimo(lista, pila2);
    lista_insertar_ultimo(lista, pila3);
    lista_destruir(lista, destruir_pila_wrapper);
    print_test("Se elimina una lista llena de pilas", OK);
    printf("\n");
}

static void pruebas_destruccion_free(void){
    printf("Pruebas de destruccion usando free \n");
    lista_t *lista = lista_crear();
    void* puntaux1 = malloc(sizeof(void*));
    void* puntaux2 = malloc(sizeof(void*));
    void* puntaux3 = malloc(sizeof(void*));
    lista_insertar_ultimo(lista, puntaux1);
    lista_insertar_ultimo(lista, puntaux2);
    lista_insertar_ultimo(lista, puntaux3);
    lista_destruir(lista, free);
    print_test("Se destruyen elementos usando free", OK);
    printf("\n");
}

static void pruebas_lista_iterar_inter_lleno(void){
    
    lista_t *lista = lista_crear();
    int* vec = malloc(sizeof(int)*ELEMENTOS);
    size_t conteo = 0;
    for(int i= 0; i < ELEMENTOS;i++){
        vec[i] = i+DATO1;
        lista_insertar_ultimo(lista,&vec[i]);
    }

    
    printf("Prueba Duplicar 5 elementos con Iterador Interno a la lista\n");
    lista_iterar(lista,duplicar_5_elementos,&conteo);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("La funcion de barbara no es NULL",duplicar_5_elementos != NULL);
    print_test("En la funcion Lista_iterar usa el extra para el corte de iteracion",conteo != 0);
    print_test("Itera solo hasta el Maximo de veces que define barbara en su funcion (duplicar_5_elementos)",conteo == MAXIMO_ITERACION);
    print_test("Se duplico el primer elemento de la lista",(*(int*)lista_ver_primero(lista)) == DATO2);
    print_test("No se duplico el ultimo elemento de la lista",(*(int*)lista_ver_ultimo(lista)) == ELEMENTOS);
    printf("\n");

    int conteo_2 = 0;
    printf("Prueba Sumar todos los elementos con Iterador Interno a la lista\n");
    lista_iterar(lista,sumar_elementos,&conteo_2);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("La funcion de barbara no es NULL",sumar_elementos != NULL);
    print_test("Itera todo la lista ",conteo_2 == ELEMENTOS);
    print_test("Se sumo el primer elemento de la lista",(*(int*)lista_ver_primero(lista)) == DATO3);
    print_test("Se sumo el ultimo elemento de la lista",(*(int*)lista_ver_ultimo(lista)) == ELEMENTOS+DATO1);
    printf("\n");

    printf("Prueba Funcion visitar es NULL con Iterador Interno a la lista\n");
    lista_iterar(lista,NULL,&conteo_2);
    print_test("El extra(contador) no se modifico",conteo_2 == ELEMENTOS);
    print_test("No se modifico el primer elemento de la lista",(*(int*)lista_ver_primero(lista)) == DATO3);
    print_test("No se modifico el ultimo elemento de la lista",(*(int*)lista_ver_ultimo(lista)) == ELEMENTOS+DATO1);
    printf("\n");
    free(vec);
    lista_destruir(lista,NULL);
}

static void pruebas_lista_iterar_inter_vacio(void){
    lista_t* lista = lista_crear();
    lista_iterar(lista,duplicar_5_elementos,NULL);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista,NULL);
    printf("\n");
}

static void pruebas_primitivas_iterador_externo(void){
    printf("Pruebas con el iterador \n");
    lista_t* lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("Se crea el iterador", iter != NULL);
    print_test("El iterador empieza en la primera posicion", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    print_test("El iterador permite avanzar", lista_iter_avanzar(iter));
    print_test("El iterador se encuentra en el segundo elemento", lista_iter_ver_actual(iter) == &dato2);
    print_test("El iterador permite avanzar nuevamente", lista_iter_avanzar(iter));
    print_test("El iterador se encuentra en el segundo elemento", lista_iter_ver_actual(iter) == &dato3);
    print_test("El iterador avanza y se encuentra al final", lista_iter_avanzar(iter) && lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_insertando(void){
    printf("Pruebas insertando elementos al inicio\n");
    lista_t *lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    int dato4 = DATO4;
    bool prueba = OK;
    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("Se puede insertar un elemento mediante el iterador", lista_iter_insertar(iter, &dato4));
    print_test("El iterador esta sobre el lemento insertado", lista_iter_ver_actual(iter) == &dato4);
    print_test("El elemento insertado es el primero de la lista", lista_ver_primero(lista) == &dato4);
    print_test("El iterador avanza y se encuentra sobre el anterior primero", lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == &dato1);
    lista_iter_destruir(iter);
    printf("\n");
    printf("Pruebas insertando elementos al final\n");
    lista_iter_t *iter2 = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter2)) {
        prueba &= lista_iter_avanzar(iter2);
    }
    print_test("El iterador avanza varias veces", prueba);
    print_test("El iterador llega al final", lista_iter_al_final(iter2));
    print_test("Inserta un elemento", lista_iter_insertar(iter2, &dato4));
    print_test("El elemento final de la lista es el recien insertado", lista_ver_ultimo(lista) == &dato4);
    lista_iter_destruir(iter2);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_eliminar_iterador(void){
    printf("Pruebas eliminando elementos \n");
    lista_t *lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    int dato4 = DATO4;
    //bool prueba = OK;
    lista_insertar_ultimo(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_insertar_ultimo(lista, &dato4);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("Se puede borrar un elemento", lista_iter_borrar(iter));
    print_test("el iterador esta en el nuevo primero", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    print_test("Se borra el ultimo elemento", lista_iter_borrar(iter));
    lista_iter_avanzar(iter);
    print_test("El iterador llega al final", lista_iter_al_final(iter));
    print_test("El iterador no puede borrar nada estando al final", !lista_iter_borrar(iter));
    lista_iter_destruir(iter);
    print_test("La lista tiene un nuevo final", lista_ver_ultimo(lista) == &dato3);
    lista_destruir(lista, NULL);
    printf("\n");
}

static void prueba_caso_borde(void){
    printf("\n");
    printf("Prueba de caso borde eliminar con un elemento usando iterador \n");
    lista_t *lista = lista_crear();
    int dato1 = DATO1;
    lista_insertar_primero(lista, &dato1);
    lista_iter_t *iter = lista_iter_crear(lista);
    lista_iter_borrar(iter);
    lista_iter_destruir(iter);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    printf("\n");
}

static void pruebas_insertando_medio(void){
    printf("Pruebas insertando en el medio \n");
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    int dato4 = DATO4;
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    lista_iter_insertar(iter, &dato1);
    //lista_iter_avanzar(iter);
    lista_iter_insertar(iter, &dato2);
    lista_iter_insertar(iter, &dato3);
    lista_iter_insertar(iter, &dato4);
    //lista_iter_destruir(iter);
    bool prueba = OK;
    prueba &= (lista_ver_primero(lista) == &dato4) && (lista_ver_ultimo(lista) == &dato1);
    print_test("Insertar elementos con el iterador cumple con lo esperado", prueba);
    while(!lista_iter_al_final(iter)){
        lista_iter_borrar(iter);
    }
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
    printf("\n");

}

static void pruebas_remover_iter_recien_creada(void){
    lista_t* lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    lista_insertar_primero(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("El iterador se creo correctamente", iter != NULL);
    print_test("Actual esta parado en el primer elemento",lista_iter_ver_actual(iter) == &dato1);
    print_test("Se cambia el primer elemento cuando el iterador es recien creado",lista_iter_borrar(iter));
    print_test("Luego de Borrar el primer elemento el iterador a punta al segundo",lista_iter_ver_actual(iter) == &dato2);
    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
    printf("\n");
}

static void pruebas_remover_el_ultimo_elemento_con_iter(void){
    lista_t* lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    lista_insertar_primero(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_iter_t *iter = lista_iter_crear(lista);
    lista_iter_avanzar(iter);
    lista_iter_avanzar(iter);
    print_test("El iterador se creo correctamente", iter != NULL);
    print_test("EL ultimo elemento de la lista es 3",lista_ver_ultimo(lista) == &dato3);
    print_test("El largo de la lista es 3",lista_largo(lista) == DATO3);
    print_test("El iterador se encuantra en el ultimo elemento", lista_iter_ver_actual(iter)== &dato3);
    print_test("El iterador borra con normalidad el ultimo elemento",lista_iter_borrar(iter));
    print_test("El iterador apunta a NULL", lista_iter_ver_actual(iter)== NULL);
    print_test("EL ultimo elemento de la lista luego de ahber borrado con el iterador es 2",lista_ver_ultimo(lista) == &dato2);
    print_test("El nuevo largo de la lista es 2",lista_largo(lista) == DATO2);
    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
    printf("\n");
}

static void pruebas_remover_medio_elemento_con_iter(void){
    lista_t* lista = lista_crear();
    int dato1 = DATO1;
    int dato2 = DATO2;
    int dato3 = DATO3;
    lista_insertar_primero(lista, &dato1);
    lista_insertar_ultimo(lista, &dato2);
    lista_insertar_ultimo(lista, &dato3);
    lista_iter_t *iter = lista_iter_crear(lista);
    lista_iter_avanzar(iter);
    print_test("El iterador se creo correctamente", iter != NULL);
    print_test("EL iterador apunta en el medio de la lista ",lista_iter_ver_actual(iter) == &dato2);
    print_test("El largo de la lista es 3",lista_largo(lista) == DATO3);
    print_test("El iterador borra con normalidad el elemento actual",lista_iter_borrar(iter));
    print_test("El iterador apunta al siguiente del elemento eliminado", lista_iter_ver_actual(iter)== &dato3);
    print_test("EL ultimo elemento de la lista sigue siendo el mismo",lista_ver_ultimo(lista) == &dato3);
    print_test("El nuevo largo de la lista es 2",lista_largo(lista) == DATO2);

    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
    printf("\n");
}


void pruebas_lista_estudiante(void){
    prueba_lista_vacia();
    pruebas_insertar_ver_borrar();
    pruebas_con_varios_elementos();
    pruebas_con_elementos_dos();
    pruebas_con_null();
    pruebas_volumen();
    pruebas_destruccion_vacia_null();
    pruebas_destruccion_vacia_funcion();
    pruebas_destruccion_llenas_null();
    pruebas_destruccion_llenas_funcion();
    pruebas_lista_iterar_inter_lleno();
    pruebas_lista_iterar_inter_vacio();
    pruebas_destruccion_free();
    pruebas_primitivas_iterador_externo();
    pruebas_insertando();
    pruebas_eliminar_iterador();
    prueba_caso_borde();
    pruebas_insertando_medio();
    pruebas_remover_iter_recien_creada();
    pruebas_remover_el_ultimo_elemento_con_iter();
    pruebas_remover_medio_elemento_con_iter();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif