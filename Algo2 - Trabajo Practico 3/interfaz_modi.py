from recomendify_logica import *
POS_USER_CANCIONES = 0
POS_CANCIONES = 1
POS_RANK = 2
POS_CONDICION = 3
POS_RANK_ORD = 4
POS_USUARIOS = 5

def verificar_aristas(datos):
    if datos[POS_CONDICION]:
        return
    else:
        agregar_aristas(datos[POS_USER_CANCIONES], datos[POS_CANCIONES], datos[POS_USUARIOS])
        datos[POS_CONDICION] = True

def _camino(linea, datos):
    linea = linea.split(" >>>> ")
    resultado = camino_mas_corto(datos[POS_USER_CANCIONES], datos[POS_CANCIONES], linea[0], linea[1])
    if resultado:
        print(resultado)
    return 0

def _mas_importantes(linea, datos):
    if datos[POS_RANK_ORD] == None:
        datos[POS_RANK_ORD] = sorted(datos[POS_RANK], key=lambda ranking: ranking[1], reverse = True)
    resultado = mas_importantes(int(linea), datos[POS_RANK_ORD])
    print(resultado)
    return 0

def _recomendacion(linea, datos):
    linea = linea.split(maxsplit = 2)
    lista_canciones = linea[2].split(" >>>> ")
    conjunto_canciones = set()
    for cancion in lista_canciones:
        conjunto_canciones.add(cancion)
    print(recomendacion(datos[POS_USER_CANCIONES], int(linea[1]), conjunto_canciones, linea[0]))
    return 0

def _ciclo(linea, datos):
    linea = linea.split(maxsplit = 1)
    verificar_aristas(datos)
    resultado = ciclo_n_canciones(datos[POS_CANCIONES], int(linea[0]), linea[1])
    if resultado == None:
        return 0
    print(" --> ".join(resultado))
    return 0

def _rango(linea, datos):
    linea = linea.split(maxsplit=1)
    verificar_aristas(datos)
    print(rango_n_canciones(datos[POS_CANCIONES], linea[1], int(linea[0])))
    return 0

INSTRUCCIONES = {"camino": _camino, "mas_importantes": _mas_importantes, "recomendacion": _recomendacion, "ciclo": _ciclo, "rango": _rango}
