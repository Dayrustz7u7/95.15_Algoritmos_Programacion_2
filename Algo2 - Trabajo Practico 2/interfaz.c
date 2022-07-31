#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "interfaz.h"
#define LOGIN "login\n"
#define LOGOUT "logout\n"
#define PUBLICAR "publicar\n"
#define SIG_FEED "ver_siguiente_feed\n"
#define LIKEAR "likear_post\n"
#define VER_LIKES "mostrar_likes\n"
#define COMD_LOGIN 0
#define COMD_PUBLICAR 1
#define COMD_LIKEAR 2
#define COMD_VER_LIKE 3
#define COMD_FEED 4
#define COMD_LOGOUT 5
#define NO_INSTRUCCION 9

FILE* abrir_archivo(char* archivo_txt,char* modo_de_apertura){
    FILE* archivo = fopen(archivo_txt,modo_de_apertura);
    if(!archivo){
        return NULL;
    }
    return archivo;
}

void lectura_de_usuarios(FILE* archivo, gram_t* red){
    char* linea = NULL;
    size_t size;
    size_t id = 0;
    bool ok = true;
    while(getline(&linea , &size , archivo) !=  EOF){
        ok &= gram_agregar_user(red, linea, id);
        id++;
    }
    free(linea);
}

size_t comparar_instruccion(char* linea){
    if (strcmp(linea, LOGIN) == 0){
        return COMD_LOGIN;
    } else if (strcmp(linea, PUBLICAR)== 0){
        return COMD_PUBLICAR;
    } else if (strcmp(LIKEAR, linea) == 0){
        return COMD_LIKEAR;
    } else if (strcmp(VER_LIKES, linea) == 0){
        return COMD_VER_LIKE;
    } else if (strcmp(linea, SIG_FEED)== 0){
        return COMD_FEED;
    } else if (strcmp(linea, LOGOUT)== 0){
        return COMD_LOGOUT;
    }
    return NO_INSTRUCCION;
}

void ejecutar_instruccion(size_t codigo, char* linea2, gram_t* red){
    bool ejecucion = true;
    switch (codigo)
    {
    case COMD_LOGIN:
        ejecucion &= gram_logear_user(red, linea2);
        if(!ejecucion){
            fprintf(stdout,"%s\n","Error: usuario no existente");
        } else {
            char* nombre = gram_actual_nombre(red);
            fprintf(stdout, "Hola %s", nombre);
        }
        break;
    case COMD_PUBLICAR:
        ejecucion &= gram_publicar(red, linea2);
        if (ejecucion){
            fprintf(stdout, "%s\n", "Post publicado");
        }
        break;
    case COMD_LIKEAR:
        ejecucion &= gram_dar_like(red, (size_t)atoi(linea2));
        if (!ejecucion){
            fprintf(stdout,"%s\n","Error: Usuario no loggeado o Post inexistente");
        } else {
            fprintf(stdout,"%s\n","Post likeado");
        }
        break;
    case COMD_VER_LIKE:
        ejecucion &= gram_ver_likes(red, (size_t)atoi(linea2));
        if (!ejecucion){
            fprintf(stdout,"%s\n","Error: Post inexistente o sin likes");
        }
        break;
    case COMD_FEED:
        ejecucion &= gram_ver_feed(red);
        if (!ejecucion){
            fprintf(stdout,"%s\n", "Usuario no loggeado o no hay mas posts para ver");
        }
        break;
    case COMD_LOGOUT:
        ejecucion &= gram_logut(red);
        if (ejecucion){
            fprintf(stdout, "%s\n", "Adios");
        } else {
            fprintf(stdout,"%s\n","Error: no habia usuario loggeado");
        }
        break;
    default:
        break;
    }
}

bool verificar(size_t codigo, gram_t* red){
    if (codigo == COMD_LOGIN ){
        if (gram_hay_user_activo(red)){
            fprintf(stdout,"%s\n","Error: Ya habia un usuario loggeado");
            return false;
        }
    } else if (codigo == COMD_LIKEAR){
        if (!gram_actual_nombre(red)){
            fprintf(stdout, "%s\n", "Error: Usuario no loggeado o Post inexistente");
            return false;
        }
    } else if (codigo == COMD_PUBLICAR){
        if (!gram_hay_user_activo(red)){
            fprintf(stdout,"%s\n","Error: no habia usuario loggeado");
            return false;
        }
    }
    return true;
}

void lectura_instrucciones(FILE* archivo, gram_t* red){
    char* linea = NULL;
    size_t size;
    size_t codigo = NO_INSTRUCCION;
    while(getline(&linea, &size, archivo) != EOF){
        if (codigo == NO_INSTRUCCION){
            codigo = comparar_instruccion(linea);
            if (codigo <= COMD_VER_LIKE){
                continue;
            }
        }
        if (codigo <= COMD_VER_LIKE){
            bool verificacion = verificar(codigo, red);
            if(!verificacion){
                codigo = NO_INSTRUCCION;
                continue;
            }
        }
        ejecutar_instruccion(codigo, linea, red);
        codigo = NO_INSTRUCCION;
    }
    free(linea);
}

