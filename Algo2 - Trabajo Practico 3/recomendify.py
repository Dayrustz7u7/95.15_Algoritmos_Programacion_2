#!/usr/bin/python3
from sys import *
from recomendify_logica import creacion_grafo, crear_ranking
from interfaz_modi import INSTRUCCIONES
LONG_MINIMA = 2
POS_DATOS = 1
POS_COMAND = 0

def lectura_archivo(archivo, datos):
    for linea in archivo:
        linea = linea.strip("\n")
        linea = linea.split(maxsplit=1)
        try:
            if linea[POS_COMAND] not in INSTRUCCIONES:
                print("Error instruccion no valida")
                continue
            INSTRUCCIONES[linea[POS_COMAND]](linea[POS_DATOS], datos)
        except IndexError:
            print("Debes insertar algun comando")
            continue

def main():
    condicion = False
    rank_ord = None
    if (len(argv) < LONG_MINIMA):
        return 0
    canciones, users_canciones, usuarios = creacion_grafo(argv[POS_DATOS])
    rank = crear_ranking(users_canciones, canciones)
    datos = [users_canciones, canciones, rank, condicion, rank_ord, usuarios]
    if(len(argv) == LONG_MINIMA):
        lectura_archivo(stdin, datos)
    else:
        with open(argv[LONG_MINIMA]) as origen:
            lectura_archivo(origen, datos)
    return 0

main()