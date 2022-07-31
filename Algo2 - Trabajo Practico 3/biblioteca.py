from grafo import Grafo
from queue import Queue
from random import choice

ITERACION = 5
AMORTIGUADOR = 0.80
CONST_CAMINO = 30
LARGO_CAMINO = 50
CONS_DATO = 2
INDICADOR = "pares"

def camino_mas_corto_bfs(grafo, origen):
    '''
    Bfs para calcular el orden de los vertices a partir de un vertice origen
    '''
    
    padres = {}
    orden = {}
    visitados = set()
    elementos = Queue()
    for v in grafo.obtener_vertices():
        orden[v] = float("Inf")
    orden[origen] = 0
    padres[origen] = None
    visitados.add(origen)
    elementos.put(origen)
    while not elementos.empty():
        v = elementos.get()
        for w in grafo.adyacentes(v):
            if not w in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                elementos.put(w)
    return padres, orden

def generar_grafo_completo(grafo, aristas):
    '''
    recibe un grafo sin aristas y relaciona todos los elementos mediante una lista de aristas
    '''
    contador = 0
    for i in range(len(aristas)):
        for j in range(contador, len(aristas)):
            if i == j: continue
            grafo.agregar_arista(aristas[i], aristas[j])
        contador += 1
    
def _ciclo_cerrado_n(grafo, camino, v, origen, n, paso, camino_aux):
    '''
    Una funcion busca una un ciclo cerrado de longitud n en un grafo
    '''

    if v == origen and paso == n:
        return True
    elif v != origen and paso == n:
        return False
    nuevo_paso = paso + 1
    for w in grafo.adyacentes(v):
        if w in camino_aux: continue
        if w == origen and paso < n - 1: continue
        camino.append(w)
        camino_aux.add(w)
        resultado = _ciclo_cerrado_n(grafo, camino, w, origen, n, nuevo_paso, camino_aux)
        if resultado:
            return True
        else:
            aux = camino.pop(-1)
            camino_aux.discard(aux)
            

def ciclo_cerrado_n(grafo, long, origen):
    '''
    Wrapper de la funcion _ciclo_cerrado_n, devuelve una lista con los elementos del ciclo, o None en caso de no haber
    '''

    camino = []
    camino_aux = set()
    if _ciclo_cerrado_n(grafo, camino, origen, origen, long, 0, camino_aux):
        nuevo_camino = [origen] + camino[:]
        return nuevo_camino
    else: 
        return None

def sumatoria_page_rank(grafo, page_rank, v):
    '''
    Calcula el page rank de un vertice en particular
    '''
    cuenta = 0
    adyacentes = grafo.adyacentes(v)
    for w in adyacentes:
        cuenta += page_rank[w]/grafo.cantidad_adyacentes(w)
    return cuenta
    

def _page_rank(grafo, page_rank):
    '''
    Calcula el page rank de todos los vertices de un grafo
    '''
    vertices = grafo.obtener_vertices()
    for v in vertices:
        page_rank[v] =  (1 - AMORTIGUADOR)/len(vertices) +  AMORTIGUADOR*sumatoria_page_rank(grafo, page_rank, v)

def page_rank(grafo):
    '''
    Itera el calculo de un page rank
    '''
    datos_page_rank = {}
    vertices = grafo.obtener_vertices()
    proba_ini = 1/len(vertices)
    for v in vertices:
        datos_page_rank[v] = proba_ini
    for _ in range(ITERACION):
        _page_rank(grafo, datos_page_rank)
    return datos_page_rank

def _random_walks(grafo, v, paso, pares, impares, valor, tope):
    '''
    Realiza un recorrido random walks a partir del vertice v
    '''

    if paso == tope:
        return 
    adyacentes = grafo.adyacentes(v)
    if len(adyacentes) == 0:
        #random walks sobre un vertice aislado
        pares[v] = valor
        return
    nuevo_valor = valor/len(adyacentes)
    if paso%2 == 0:
        pares[v] = pares.get(v, 0) + nuevo_valor
    else:
        impares[v] = impares.get(v, 0) + nuevo_valor
    nuevo_vertice = choice(adyacentes)
    _random_walks(grafo, nuevo_vertice, paso + 1, pares, impares, nuevo_valor, tope)

def separar_elementos(hash, lista, set_descartados):
    for w in hash:
        if w in set_descartados: continue
        lista.append((w, hash[w]))

def random_walk_personalizado(grafo, set_vertices, cadena):
    '''
    realiza un page rank personalizado sobre un vertice, considerando 
    '''

    recomendaciones = []
    pares = {} 
    impares = {} 
    for v in set_vertices:
        for _ in range(CONST_CAMINO):
            _random_walks(grafo, v, 0, pares, impares, CONS_DATO, LARGO_CAMINO)
    if cadena == INDICADOR:
        separar_elementos(pares, recomendaciones, set_vertices)
    else:
        separar_elementos(impares, recomendaciones, set_vertices)
    return recomendaciones