from grafo import Grafo
from random import choice
from biblioteca import *
INDICADOR_C = "canciones"
LLAMADO = "pares"
USER = 1
CANCION = 2
ARTISTA = 3
PLAYLIST = 5

def creacion_grafo(archivo):
    canciones = Grafo()
    users_canciones = Grafo(False, True)
    usuarios = set()
    with open(archivo) as origen:
        user_actual = None
        origen.readline()
        for linea in origen:
            nueva_linea = linea.split("\t")
            user, cancion, artista, playlist = nueva_linea[USER], nueva_linea[CANCION], nueva_linea[ARTISTA], nueva_linea[PLAYLIST]
            if user != user_actual:
                user_actual = user
                usuarios.add(user_actual)
            nueva_cadena = cancion + " - " + artista
            users_canciones.agregar_vertice(user_actual)
            users_canciones.agregar_vertice(nueva_cadena)
            users_canciones.agregar_arista(user_actual, nueva_cadena, playlist)
            canciones.agregar_vertice(nueva_cadena)
    return canciones, users_canciones, usuarios

def reconstruir_camino(grafo, padres, fin):
    contador = 0
    actual = fin
    camino = []
    while actual is not None:
        if contador%2 == 0:
            camino.append("aparece en playlist")
            camino.append(actual)
            camino.append("donde aparece")
        else:
            camino.append("tiene una playlist")
            camino.append(actual)
            camino.append("de")
        if padres[actual] == None:
            camino.pop()
            camino.pop(0)
            break
        contador += 1
        camino.append(grafo.peso_arista(padres[actual], actual))
        actual = padres[actual]
    return camino

def camino_mas_corto(grafo, canciones,  inicio, fin):
    if not canciones.vertice_existe(inicio) or not canciones.vertice_existe(fin):
        print("Tanto el origen como el destino deben ser canciones")
        return False
    padres, _ = camino_mas_corto_bfs(grafo, inicio)
    if not fin in padres:
        print("No se encontro recorrido")
        return False
    camino = reconstruir_camino(grafo, padres, fin)
    camino = camino[::-1]
    return " --> ".join(camino)

def crear_ranking(grafo,grafo2):
    rank = []
    ranking = page_rank(grafo)
    for v in ranking:
        if grafo2.vertice_existe(v):
            rank.append((v, ranking[v]))
    return rank

def mas_importantes(n, rank):
    n_mas_importantes = []
    for i in range(0, n):
        n_mas_importantes.append(rank[i][0])
    return "; ".join(n_mas_importantes)

def recomendacion(grafo, n, inicios, cadena):
    if cadena == "canciones":
        recomendaciones = random_walk_personalizado(grafo, inicios, LLAMADO)
    else:
        recomendaciones = random_walk_personalizado(grafo, inicios, cadena)
    n_recomendaciones = sorted(recomendaciones, key = lambda ranking: ranking[1], reverse=True)
    lista = []
    for i in n_recomendaciones[:n:]:
        lista.append(i[0])
    return "; ".join(lista)

def ciclo_n_canciones(grafo, longitud, origen):
    if not grafo.vertice_existe(origen):
        print("No existe dicha cancion")
        return None
    resultado = ciclo_cerrado_n(grafo, longitud, origen)
    if resultado is None:
        print("No se encontro recorrido")
        return None
    return resultado

def rango_n_canciones(grafo, origen, rango):
    _, distancias = camino_mas_corto_bfs(grafo, origen)
    contador = 0
    for v in distancias:
        if distancias[v] == rango:
            contador += 1
    return contador

def agregar_aristas(user_canciones, canciones, usuarios):
    for v in usuarios:
        generar_grafo_completo(canciones, user_canciones.adyacentes(v))