#include "abb.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define OK true
#define ELEMENTOS 5
#define VOL 100
#define TAM 10
#define DATO1 8
#define DATO2 4
#define DATO3 9
#define DATO4 3
#define DATO5 6

void destruir_pila_wrapper(void* dato){
    pila_destruir(dato);
}

bool duplicar_valores(const char* clave,void* valor,void* extra){
    *(int*)valor = *(int*)valor * 2;
    return true;
}
bool dividir_3_valores(const char* clave,void* valor,void* extra){
    if(*(int*)extra == 3){
        return false;
    }
    *(int*)valor = *(int*)valor / 2;
    (*(int*)extra)++;
    return true;
}
bool sumar_mayores_a_3_menores_a_7(const char* clave,void* valor,void* extra){
    if(atoi(clave)< 7 && atoi(clave) > 3){
        *(int*)valor = *(int*)valor + 10;
        return true;
    }
    if(atoi(clave) <= 3){
        return true;
    }
    return false;
}

static void pruebas_abb_vacio(){

    printf("Pruebas con ABB vacio \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    print_test("Se crea un arbol", arbol != NULL);
    print_test("La cantidad del arbol es 0", abb_cantidad(arbol) == 0);
    print_test("El arbol no posee una clave aleatoria", !abb_pertenece(arbol, "Hola mundo"));
    print_test("Borrar una clave que no pertenece devuelve null", abb_borrar(arbol, "Hola Algo2") == NULL);
    print_test("Arbol obtener de una clave que no pertenece devuelve null", abb_obtener(arbol, "Hola mundo") == NULL);
    abb_destruir(arbol);
    printf("\n");
}
static void prueba_abb_valor_vacio(){
    abb_t* arbol = abb_crear(strcmp,NULL);
    char *clave1 = "", *valor = "";

    printf("Pruebas con ABB Insertando Clave con valor VACIO y luego borrandolo\n");
    print_test("Se crea un arbol", arbol != NULL);
    print_test("Insertar clave vacia valor Vacio", abb_guardar(arbol, clave1, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Obtener clave1 vacia es valor Vacio", abb_obtener(arbol, clave1) == valor);
    print_test("Pertenece clave1 vacia, es true", abb_pertenece(arbol, clave1));
    print_test("Borrar clave1 vacia, es valor Vacio", abb_borrar(arbol, clave1) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
    printf("\n");
}
static void prueba_abb_valor_null(){
    abb_t* arbol = abb_crear(strcmp,NULL);
    char *clave1 = "", *valor = NULL;

    printf("Pruebas con ABB Insertando Clave con valor NULL y luego borrandolo \n");
    print_test("Se crea un arbol", arbol != NULL);
    print_test("Insertar clave vacia valor NULL", abb_guardar(arbol, clave1, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(arbol) == 1);
    print_test("Obtener clave1 vacia es valor NULL", abb_obtener(arbol, clave1) == valor);
    print_test("Pertenece clave1 vacia, es true", abb_pertenece(arbol, clave1));
    print_test("Borrar clave1 vacia, es valor NULL", abb_borrar(arbol, clave1) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(arbol) == 0);

    abb_destruir(arbol);
}

static void pruebas_insertar_abb(){
    
    abb_t* arbol = abb_crear(strcmp, NULL);
    // Clave: Animal - Valor: Cantidad
    char* clave1 = "perro",  *valor1 = "2";
    char* clave2 = "gato",   *valor2 = "3";
    char* clave3 = "tortuga",   *valor3 = "1";

    printf("Pruebas con ABB Insertando una clave y luego borrandolo \n");
    print_test("Se crea un arbol", arbol != NULL);
    print_test("La cantidad del arbol es 0", abb_cantidad(arbol) == 0);
    print_test("Se guarda correctamente una clave con su valor",abb_guardar(arbol,clave1,valor1));
    print_test("La cantidad es 1",abb_cantidad(arbol) == 1);
    print_test("La clave 6 pertenece en el arbol",abb_pertenece(arbol,clave1));
    print_test("Prueba obtener el valor de la clave1",abb_obtener(arbol,clave1) == valor1);
    print_test("Prueba abb borrar el elemento",abb_borrar(arbol,clave1) == valor1);
    print_test("La clave 6 ya no pertenece en el arbol",!abb_pertenece(arbol,clave1));
    print_test("La cantidad es 0",abb_cantidad(arbol) == 0);
    printf("\n");

    printf("Pruebas con ABB Insertando Claves y no los borra (Destruye el ABB) \n");
    print_test("Se guarda correctamente clave1 con su valor",abb_guardar(arbol,clave1,valor1));
    print_test("Se guarda correctamente clave2 con su valor",abb_guardar(arbol,clave2,valor2));
    print_test("Se guarda correctamente clave3 con su valor",abb_guardar(arbol,clave3,valor3));
    print_test("La cantidad es 3",abb_cantidad(arbol) == 3);
    print_test("La clave1 pertenece en el arbol",abb_pertenece(arbol,clave1));
    print_test("La clave2 pertenece en el arbol",abb_pertenece(arbol,clave2));
    print_test("La clave3 pertenece en el arbol",abb_pertenece(arbol,clave3));
    print_test("Prueba obtener el valor de la clave1",abb_obtener(arbol,clave1) == valor1);
    print_test("Prueba obtener el valor de la clave2",abb_obtener(arbol,clave2) == valor2);
    print_test("Prueba obtener el valor de la clave3",abb_obtener(arbol,clave3) == valor3);

    abb_destruir(arbol);
    printf("\n");
}
static void pruebas_reemplazar_abb(){

    abb_t* arbol = abb_crear(strcmp,NULL);
    // Clave: Animal - Valor: Cantidad
    char* clave1 = "perro",   *valor1 = "2", *nuevo_valor1 = "3";
    char* clave2 = "gato",    *valor2 = "3", *nuevo_valor2 = "2";
    char* clave3 = "tortuga", *valor3 = "1", *nuevo_valor3 = "0";

    printf("Pruebas con ABB Reemplazando el valor de Claves\n");
    print_test("Se crea un arbol", arbol != NULL);
    print_test("Se guarda correctamente clave1 con su valor1",abb_guardar(arbol,clave1,valor1));
    print_test("La clave1 pertenece en el arbol",abb_pertenece(arbol,clave1));
    print_test("Prueba obtener el valor1 de la clave1",abb_obtener(arbol,clave1) == valor1);
    print_test("Se guarda correctamente clave2 con su valor2",abb_guardar(arbol,clave2,valor2));
    print_test("La clave2 pertenece en el arbol",abb_pertenece(arbol,clave2));
    print_test("Prueba obtener el valor2 de la clave2",abb_obtener(arbol,clave2) == valor2);
    print_test("Se guarda correctamente clave3 con su valor3",abb_guardar(arbol,clave3,valor3));
    print_test("La clave3 pertenece en el arbol",abb_pertenece(arbol,clave3));
    print_test("Prueba obtener el valor3 de la clave3",abb_obtener(arbol,clave3) == valor3);
    print_test("La cantidad es 3",abb_cantidad(arbol) == 3);

    print_test("Insertar nuevo_valor1 a clave1",abb_guardar(arbol,clave1,nuevo_valor1));
    print_test("Prueba obtener el nuevo_valor1 de la clave1",abb_obtener(arbol,clave1) == nuevo_valor1);
    print_test("Insertar nuevo_valor2 a clave2",abb_guardar(arbol,clave2,nuevo_valor2));
    print_test("Prueba obtener el nuevo_valor2 de la clave2",abb_obtener(arbol,clave2) == nuevo_valor2);
    print_test("Insertar nuevo_valor3 a clave3",abb_guardar(arbol,clave3,nuevo_valor3));
    print_test("Prueba obtener el nuevo_valor3 de la clave3",abb_obtener(arbol,clave3) == nuevo_valor3);
    print_test("La cantidad es 3",abb_cantidad(arbol) == 3);

    abb_destruir(arbol);
    printf("\n");
}
static void prueba_abb_borrar(){

    abb_t* arbol = abb_crear(strcmp, NULL);
    // Clave: Animal - Valor: Cantidad                        // Representacion Grafica:
    char* clave1 = "perro",   *valor1 = "2";                  //              [perro]
    char* clave2 = "gato" ,   *valor2 = "3";                  //      [gato]           [tortuga]
    char* clave3 = "tortuga", *valor3 = "1";                  //[conejo]  [iguana]            [vaca]
    char* clave4 = "conejo",   *valor4 = "4";                 //
    char* clave5 = "iguana" ,   *valor5 = "0";                
    char* clave6 = "vaca", *valor6 = "5";
    
    abb_guardar(arbol,clave1,valor1);
    abb_guardar(arbol,clave2,valor2);
    abb_guardar(arbol,clave3,valor3);
    abb_guardar(arbol,clave4,valor4);
    abb_guardar(arbol,clave5,valor5);
    abb_guardar(arbol,clave6,valor6);

    printf("Pruebas con ABB Borrando con 1 Hijo\n");                   
    print_test("Se crea un arbol", arbol != NULL);                                     // Representacion Grafica:
    print_test("Pertenece clave3, es verdadero", abb_pertenece(arbol, clave3));        //             [perro]
    print_test("Borrar clave3, es valor3", abb_borrar(arbol, clave3) == valor3);       //      [gato]        [vaca]
    print_test("Pertenece clave3, es falso", !abb_pertenece(arbol, clave3));           //[conejo]  [iguana]
    print_test("Obtener clave3, es NULL", !abb_obtener(arbol, clave3));                //
    print_test("La cantidad de elementos es 5", abb_cantidad(arbol) == 5);
    printf("\n");              
    printf("Pruebas con ABB Borrando con 0 Hijo\n");                                   // Representacion Grafica:
    print_test("Pertenece clave6, es verdadero", abb_pertenece(arbol, clave6));        //             [perro]
    print_test("Borrar clave6, es valor6", abb_borrar(arbol, clave6) == valor6);       //      [gato]        
    print_test("Pertenece clave6, es falso", !abb_pertenece(arbol, clave6));           //[conejo]  [iguana]
    print_test("Obtener clave6, es NULL", !abb_obtener(arbol, clave6));                //
    print_test("La cantidad de elementos es 4", abb_cantidad(arbol) == 4);
    printf("\n");                                                                      // ESTA FALLANDO ESTA PRUEBA ->
    printf("Pruebas con ABB Borrando con 2 Hijo\n");                                   // Representacion Grafica:
    print_test("Pertenece clave2, es verdadero", abb_pertenece(arbol, clave2));        //             [perro]
    print_test("Borrar clave2, es valor2", abb_borrar(arbol, clave2) == valor2);       //      [iguana]        
    print_test("Pertenece clave2, es falso", !abb_pertenece(arbol, clave2));           //[conejo] 
    print_test("Obtener clave2, es NULL", !abb_obtener(arbol, clave2));                //
    print_test("La cantidad de elementos es 3", abb_cantidad(arbol) == 3);

    abb_destruir(arbol);
    printf("\n");

}

int aleatorio_en_rango(int minimo, int maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void bongo_sort(char (*claves)[TAM], size_t longitud){
    for (int i = 0; i < VOL; i++) {
        int indiceAleatorio = aleatorio_en_rango(0, VOL - 1);
        if (indiceAleatorio == i){
            continue;
        }
        char clave[11];
        strcpy(clave, claves[i]);
        strcpy(claves[i], claves[indiceAleatorio]);
        strcpy(claves[indiceAleatorio],clave);
    }    
}

static void pruebas_volumen() {
    size_t largo = VOL;
    abb_t* arbol = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    bool prueba = OK;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    if (!claves){
        abb_destruir(arbol);
        return;
    }
    size_t valores[largo];

    for (size_t i = 0; i < largo; i++){
        sprintf(claves[i], "%08ld", i);
        valores[i] = i;
    }

    bongo_sort(claves, VOL);

    for (int i = 0; i<VOL; i++){
        prueba &= abb_guardar(arbol, claves[i], &valores[i]) && abb_pertenece(arbol, claves[i]);
    }

    print_test("Se almacenan todos los valores como se espera", prueba);
    printf("La cantidad de elementos en el arbol es %li \n", abb_cantidad(arbol));
    prueba = OK;

    for (int i = 0; i< VOL; i++){
        prueba &= abb_obtener(arbol, claves[i]) == &valores[i];
    }

    print_test("Los valores se guardan con las claves correspondientes", prueba);
    free(claves);
    abb_destruir(arbol);
    printf("\n");
}

static void pruebas_con_fdestruc() {
    printf("Pruebas de destruccion con funcion no nula \n");
    abb_t* arbol = abb_crear(strcmp, destruir_pila_wrapper);
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    abb_guardar(arbol, "2", pila2);
    abb_guardar(arbol, "3", pila3);
    abb_guardar(arbol, "1", pila1);
    abb_destruir(arbol);
    print_test("Pruebas de destruccion ABB lleno fdest no nula", OK);
    printf("\n");
}

static void pruebas_destruccion_free() {
    printf("Pruebas de destruccion usando free \n");
    abb_t* arbol = abb_crear(strcmp, free);
    void* puntaux1 = malloc(sizeof(void*));
    void* puntaux2 = malloc(sizeof(void*));
    void* puntaux3 = malloc(sizeof(void*));
    abb_guardar(arbol, "2", puntaux2);
    abb_guardar(arbol, "1", puntaux1);
    abb_guardar(arbol, "3", puntaux3);
    abb_destruir(arbol);
    print_test("Pruebas de destruccion usando free", OK);
    printf("\n");
}

static void pruebas_reemplazar_dinamica() {
    printf("Pruebas reemplazando en memoria dinamica \n");
    abb_t* arbol = abb_crear(strcmp, destruir_pila_wrapper);
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    pila_t* pila4 = pila_crear();
    abb_guardar(arbol, "2", pila2);
    abb_guardar(arbol, "3", pila3);
    abb_guardar(arbol, "1", pila1);
    abb_guardar(arbol, "1", pila4);
    print_test("Guardar reescribe el dato (usando memoria dinamica)", abb_obtener(arbol, "1") == pila4);
    abb_destruir(arbol);
    print_test("Pruebas de destruccion ABB lleno fdest no nula", OK);
    printf("\n");
}

static void pruebas_borrar_dinamica() { 
    printf("Pruebas borrando elementos en memoria dinamica \n");
    abb_t* arbol = abb_crear(strcmp, destruir_pila_wrapper);
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    abb_guardar(arbol, "2", pila2);
    abb_guardar(arbol, "3", pila3);
    abb_guardar(arbol, "1", pila1);
    print_test("abb borrar devuelve el dato", abb_borrar(arbol, "2") == pila2);
    print_test("abb borrar devuelve el dato", abb_borrar(arbol, "1") == pila1);
    print_test("abb borrar devuelve el dato", abb_borrar(arbol, "3") == pila3);
    print_test("El arbol tiene 0 elementos", abb_cantidad(arbol) == 0);
    abb_destruir(arbol);
    print_test("Destruir elimina los elementos del arbol pero no borra los datos", OK);
    print_test("Pila 1", pila1 != NULL);
    print_test("Pila 2", pila2 != NULL);
    print_test("Pila 3", pila3 != NULL);
    pila_destruir(pila1);
    pila_destruir(pila2);
    pila_destruir(pila3);
    printf("\n");
}

static void pruebas_iter_interno(){
    printf("Pruebas iter Interno \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    char* claves[ELEMENTOS] = {"8","4","9","3","6"};
    int datos[ELEMENTOS] ={DATO1,DATO2,DATO3,DATO4,DATO5}; 
    printf("\n");
    for(int i = 0;i< ELEMENTOS;i++){
        abb_guardar(arbol,claves[i],&datos[i]);
        printf("%i->",*(int*)abb_obtener(arbol,claves[i]));
    }
    printf("\n");
    printf("Pruebas Iterando todo el Arbol y modificandolo\n");
    abb_in_order(arbol,duplicar_valores,NULL);
    print_test("Obtener Primera clave, es el doble", *(int*)abb_obtener(arbol,claves[0]) == DATO1*2);
    print_test("Obtener Segunda clave, es el doble", *(int*)abb_obtener(arbol,claves[1]) == DATO2*2);
    print_test("Obtener Tercera clave, es el doble", *(int*)abb_obtener(arbol,claves[2]) == DATO3*2);
    print_test("Obtener Cuarta clave, es el doble", *(int*)abb_obtener(arbol,claves[3]) == DATO4*2);
    print_test("Obtener Quinta clave, es el doble", *(int*)abb_obtener(arbol,claves[4]) == DATO5*2);
    printf("\n");
    printf("Pruebas Iterando n de veces en el Arbol y modificandolo\n");
    int conteo = 0;
    abb_in_order(arbol,dividir_3_valores,&conteo);
    print_test("Obtener Primera clave, es el mismo", *(int*)abb_obtener(arbol,claves[0]) == DATO1*2);
    print_test("Obtener Segunda clave, es la mitad", *(int*)abb_obtener(arbol,claves[1]) == DATO2);
    print_test("Obtener Tercera clave, es el mismo", *(int*)abb_obtener(arbol,claves[2]) == DATO3*2);
    print_test("Obtener Cuarta clave, es la mitad", *(int*)abb_obtener(arbol,claves[3]) == DATO4);
    print_test("Obtener Quinta clave, es la mitad", *(int*)abb_obtener(arbol,claves[4]) == DATO5);
    printf("\n");
    printf("Pruebas Iterando por rangos en el Arbol y modificandolo\n");
    abb_in_order(arbol,sumar_mayores_a_3_menores_a_7,NULL);
    print_test("Obtener Primera clave, es el mismo", *(int*)abb_obtener(arbol,claves[0]) == DATO1*2);
    print_test("Obtener Segunda clave, es la mitad", *(int*)abb_obtener(arbol,claves[1]) == DATO2 + 10);
    print_test("Obtener Tercera clave, es el mismo", *(int*)abb_obtener(arbol,claves[2]) == DATO3*2);
    print_test("Obtener Cuarta clave, es la mitad", *(int*)abb_obtener(arbol,claves[3]) == DATO4);
    print_test("Obtener Quinta clave, es la mitad", *(int*)abb_obtener(arbol,claves[4]) == DATO5 + 10);
    abb_destruir(arbol);
    printf("\n");

}

static void pruebas_iter() {
    printf("Pruebas iter externo \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(arbol);
    print_test("Iter se crea exitosamente", iter != NULL);
    print_test("Iter ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);
    print_test("Iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("El iterador esta al final", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
    printf("\n");
}

static void pruebas_iter_elementos() {
    printf("Iter con elementos \n");
    abb_t* arbol = abb_crear(strcmp, NULL);
    abb_guardar(arbol, "8", NULL);
    abb_guardar(arbol, "4", NULL);
    abb_guardar(arbol, "9", NULL);
    abb_guardar(arbol, "3", NULL);
    abb_guardar(arbol, "6", NULL);
    abb_iter_t *iter = abb_iter_in_crear(arbol);
    print_test("El actual es 3", strcmp(abb_iter_in_ver_actual(iter),"3") == 0);
    print_test("El iter puede avanzar", abb_iter_in_avanzar(iter));
    print_test("El actual es 4", strcmp(abb_iter_in_ver_actual(iter),"4") == 0);
    print_test("El iter puede avanzar", abb_iter_in_avanzar(iter));
    print_test("El actual es 6", strcmp(abb_iter_in_ver_actual(iter),"6") == 0);
    print_test("El iter puede avanzar", abb_iter_in_avanzar(iter));
    print_test("El actual es 8", strcmp(abb_iter_in_ver_actual(iter),"8") == 0);
    print_test("El iter puede avanzar", abb_iter_in_avanzar(iter));
    print_test("El actual es 9", strcmp(abb_iter_in_ver_actual(iter),"9") == 0);
    print_test("Iter puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Iter al final", abb_iter_in_al_final(iter));
    abb_iter_in_destruir(iter);
    abb_destruir(arbol);
    printf("\n");
}

void pruebas_abb_estudiante(void){
    pruebas_abb_vacio();
    prueba_abb_valor_vacio();
    prueba_abb_valor_null();
    pruebas_insertar_abb();
    pruebas_reemplazar_abb();
    prueba_abb_borrar();
    pruebas_volumen();
    pruebas_con_fdestruc();
    pruebas_destruccion_free();
    pruebas_reemplazar_dinamica();
    pruebas_borrar_dinamica();
    pruebas_iter();
    pruebas_iter_elementos();
    pruebas_iter_interno();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
