#include "tp0.h"
#include "stdio.h"
#include "stdbool.h"
#define VACIO -1
#define IGUAL 0
#define MAYOR 1
#define MENOR -1

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int valor = (*x);
    (*x) = (*y);
    (*y) = valor; 
}


int maximo(int vector[], int n) {
    int pos_max = 0;
    if(n == 0){
        return VACIO;
    }
    for(int i = 0;i < n-1;i++){
        if(vector[pos_max] < vector[i+1]){
           pos_max = i+1;
        }
    }
    return pos_max;
}
int comparar(int vector1[], int n1, int vector2[], int n2) {
    for(int i = 0; i < n1 && i < n2;i++){
        if(vector1[i] < vector2[i]){
            return MENOR;
        }else if(vector1[i] > vector2[i]){
            return MAYOR;
        }
    }
    if(n1 < n2){
        return MENOR; 
    }else if (n1 > n2){
        return MAYOR;
    }else{
        return IGUAL;
    }
}
void seleccion(int vector[], int n) {
    int pos_max;
    for(int i = n;i > 0;i--){
        pos_max = maximo(vector,i);
        swap(&vector[pos_max],&vector[i-1]);
    }
}
