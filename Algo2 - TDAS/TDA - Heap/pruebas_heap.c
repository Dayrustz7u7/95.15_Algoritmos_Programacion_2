#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#define VOLUMEN 100
#define ELEMENTOS 5
#define OK true

int menor_a_mayor(int* dato1, int* dato2){
    if (*dato1 > *dato2){
        return 1;
    } else if (*dato1 == *dato2) {
        return 0;
    } 
    return -1;
}

int mayor_a_menor(int* dato1, int* dato2){
    if (*dato1 > *dato2){
        return -1;
    } else if (*dato1 == *dato2) {
        return 0;
    } 
    return 1;
}

int comparar_mayor_que(const void* dato1, const void* dato2){
    return menor_a_mayor((int*)dato1, (int*) dato2);
}

int comparar_menor_que(const void* dato1, const void* dato2){
    return mayor_a_menor((int*)dato1, (int*) dato2);
}

static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(comparar_mayor_que);
    printf("Pruebas con heap vacio \n");
    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap desencolar es NULL, no existe", !heap_desencolar(heap));
    print_test("Prueba heap ver Max es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
    printf("\n");
}

static void prueba_con_un_elemento()
{
    printf("Heap pruebas insertar con un elemento \n");
    heap_t* heap = heap_crear(comparar_mayor_que);
    int dato1 = 2;
    print_test("Prueba heap  insertar dato1", heap_encolar(heap, &dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap No esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap maximo dato1 es dato1", heap_ver_max(heap) == &dato1);
    print_test("Prueba heap desencolar dato1, es true", heap_desencolar(heap) == &dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio",heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
    printf("\n");
}

static void prueba_heap_insertar()
{
    printf("Pruebas Insertar heap Vacio: \n");
    heap_t* heap = heap_crear(comparar_mayor_que);

    int dato1 = 2;
    int dato2 = 3;
    int dato3 = 1;

    /* Inserta 1 dato y luego lo borra */
    print_test("Prueba heap  insertar dato1", heap_encolar(heap, &dato1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap No esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap maximo dato1 es dato1", heap_ver_max(heap) == &dato1);
    print_test("Prueba heap desencolar dato1, es true", heap_desencolar(heap) == &dato1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap esta vacio",heap_esta_vacio(heap));

    print_test("Prueba heap insertar dato1", heap_encolar(heap,&dato1));
    print_test("Prueba heap maximo dato1 es dato1", heap_ver_max(heap) == &dato1);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap insertar dato2", heap_encolar(heap,&dato2));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap maximo es dato2", heap_ver_max(heap) == &dato2);

    print_test("Prueba heap insertar dato3", heap_encolar(heap,&dato3));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba heap maximo es dato2", heap_ver_max(heap) == &dato2);

    printf("\n");

    heap_destruir(heap,NULL);
}
static void prueba_heap_desencolar(){
    printf("Pruebas Desencolar Todos los Elementos: \n");

    heap_t* heap = heap_crear(comparar_mayor_que);
    int datos[ELEMENTOS] = {6,1,10,8,3};
    for(int i = 0; i < ELEMENTOS; i++){
        heap_encolar(heap,&datos[i]);
    }
    print_test("Prueba heap la cantidad de elementos es 5", heap_cantidad(heap) == ELEMENTOS);
    print_test("Prueba heap maximo es el 10", heap_ver_max(heap) == &datos[2]);
    print_test("Prueba heap desencolar es true",heap_desencolar(heap));
    print_test("Prueba heap maximo es el 8", heap_ver_max(heap) == &datos[3]);
    print_test("Prueba heap la cantidad de elementos es 4", heap_cantidad(heap) == ELEMENTOS-1);
    print_test("Prueba heap desencolar es true",heap_desencolar(heap));
    print_test("Prueba heap maximo es el 6", heap_ver_max(heap) == &datos[0]);
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == ELEMENTOS-2);
    print_test("Prueba heap desencolar es true",heap_desencolar(heap));
    print_test("Prueba heap maximo es el 3", heap_ver_max(heap) == &datos[4]);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == ELEMENTOS-3);
    print_test("Prueba heap desencolar es true",heap_desencolar(heap));
    print_test("Prueba heap maximo es el 1", heap_ver_max(heap) == &datos[1]);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == ELEMENTOS-4);
    print_test("Prueba heap desencolar es true",heap_desencolar(heap));
    print_test("Prueba heap maximo es NULL", !heap_ver_max(heap));
    print_test("Prueba heap No esta vacio", heap_esta_vacio(heap));

    printf("\n");
    heap_destruir(heap,NULL);
}

static void prueba_heap_destruc(){
    printf("Pruebas Heap Destruct\n");
    heap_t* heap = heap_crear(comparar_mayor_que);
    void* dato1 = malloc(sizeof(void*));
    void* dato2 = malloc(sizeof(void*));
    void* dato3 = malloc(sizeof(void*));
    *(int*)(dato1) = 5;
    *(int*)(dato2) = 6;
    *(int*)(dato3) = 9;
    heap_encolar(heap, dato1);
    heap_encolar(heap, dato2);
    heap_encolar(heap, dato3);
    heap_destruir(heap,free);
    print_test("Pruebas de destruccion usando free", true);
    printf("\n");
}

void swap_aux(int *x, int *y) {
    int change = *x;
    *x = *y;
    *y = change;
}


int aleatorio_en_rango(int minimo, int maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void bongo_sort(int* vector, int longitud){
    for (int i = 0; i < longitud; i++) {
        int indiceAleatorio = aleatorio_en_rango(0, longitud - 1);
        if (indiceAleatorio == i){
            continue;
        }
        swap_aux(&vector[indiceAleatorio], &vector[i]);}    
}

static void prueba_heap_volumen(){
    printf("Pruebas Heap Volumen\n");
    heap_t* heap = heap_crear(comparar_mayor_que);

    int* vec = malloc(sizeof(int)*VOLUMEN);

    if (!vec){
        print_test("La prueba de volumen fallo", false);
        heap_destruir(heap, NULL);
        return;
    }

    bool prueba = OK;
    for (int i = 0; i<VOLUMEN; i++){
        vec[i] = i;
    }

    bongo_sort(vec, VOLUMEN);
    
    for (int i = 0; i<VOLUMEN; i++){
        prueba &= heap_encolar(heap, &vec[i]);
    }

    print_test("Se encolan muchos elementos como se espera", prueba);

    for (int i = VOLUMEN ; i > 0; i--){
        void* dato = heap_desencolar(heap);
        prueba &= *(int*)dato == i -1;
    }
    print_test("Se desencolan los elementos en el orden esperado", prueba);
    free(vec);
    heap_destruir(heap,NULL);
    printf("\n");
}

static void pruebas_heap_arr(){
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    void* vec[5] = {&dato1, &dato5, &dato3, &dato2, &dato4};
    heap_t* heap = heap_crear_arr(vec, 5, comparar_mayor_que);
    print_test("Se crea el heap a partir del arreglo", heap != NULL);
    print_test("Heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Heap crear tiene la cantidad de elementos esperados", heap_cantidad(heap) == 5);
    print_test("Heap ver maximo devuelve el elemento", heap_ver_max(heap) == &dato5);
    heap_destruir(heap, NULL);
}

static void pruebas_desencolar_heap_arr(){
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    void* vec[5] = {&dato1, &dato5, &dato3, &dato2, &dato4};
    heap_t* heap = heap_crear_arr(vec, 5, comparar_mayor_que);
    bool prueba = OK;
    while (!heap_esta_vacio(heap))
    {
        prueba &= heap_ver_max(heap) == heap_desencolar(heap);
    }
    print_test("Se desencolan los elementos como se espera", prueba);
    heap_destruir(heap, NULL);
    printf("\n");
}

static void heap_sort_pruebas(){
    printf("Pruebas de heapsort \n");
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    void* vec[5] = {&dato2, &dato5, &dato3, &dato1, &dato4};
    heap_sort(vec, 5, comparar_menor_que);
    bool prueba = OK;
    for (int i = 0; i < 5; i++){
        prueba &= *(int*)vec[i] == (5 - i);
    }
    print_test("El vector esta ordenado", prueba);
    printf("\n");
}

void pruebas_heap_estudiante()
{
    prueba_crear_heap_vacio();
    prueba_con_un_elemento();
    prueba_heap_insertar();
    prueba_heap_desencolar();
    prueba_heap_destruc();
    prueba_heap_volumen();
    pruebas_heap_arr();
    pruebas_desencolar_heap_arr();
    heap_sort_pruebas();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif


