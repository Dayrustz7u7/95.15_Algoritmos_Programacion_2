from random import choice

class Grafo:
    '''
    implementacion del TDA grafo (Diccionario de diccionarios)
    '''

    def __init__(self, dirigido = False, pesado = False):
        '''
        Crea un grafo vacio
        '''
        self.dirigido = dirigido
        self.pesado = pesado
        self.vertices = {}
    
    def vertice_existe(self, v):
        '''
        verifica la existencia de un vertice en el grafo
        '''
        return v in self.vertices
    
    def arista_existe(self, v, w):
        '''
        verifica la existencia de una arista en el grafo
        '''
        if not self.vertice_existe(v) or not self.vertice_existe(w):
            return False
        return w in self.vertices[v]

    def agregar_vertice(self, v):
        '''
        agrega un vertice al grafo
        '''
        if self.vertice_existe(v):
            return False
        self.vertices[v] = self.vertices.get(v,{})
        return True
    
    def agregar_arista(self, v, w, peso = 1):
        '''
        agrega una arista al grafo
        '''

        if not self.vertice_existe(v) or not self.vertice_existe(w):
            return False
        if self.arista_existe(v, w):
            return False
        self.vertices[v][w] = peso
        if not self.dirigido:
            self.vertices[w][v] = peso
        return True
    
    def adyacentes(self, v):
        '''
        devuelve una lista con todos los adyacentes al grafo
        '''

        adyacentes = []
        if not self.vertice_existe(v):
            return adyacentes
        for w in self.vertices[v]:
            adyacentes.append(w)
        return adyacentes

    def borrar_arista(self, v, w):
        '''
        borra la arista en el grafo, devuelve el contenido del peso
        '''
        
        if not self.arista_existe(v,w):
            return None
        if not self.es_dirigido():
            self.vertices[w].pop(v)
        return self.vertices[v].pop(w)

    def borrar_vertice(self, v):
        '''
        borra un vertice indicado dentro del grafo
        '''

        if not self.vertice_existe(v):
            return False
        adyacentes = self.adyacentes(v)
        for w in adyacentes:
            self.borrar_arista(v, w)
            if not self.es_dirigido():
                self.borrar_arista(w,v)
        return self.vertices.pop(v)
    
    def peso_arista(self, v, w):
        '''
        devuelve el peso de una arista indicada
        '''
        if not self.pesado or not self.arista_existe(v,w):
            return None
        return self.vertices[v][w]

    def obtener_vertices(self):
        '''
        devuelve una lista con los vertices del grafo
        '''

        vertix = []
        for v in self.vertices:
            vertix.append(v)
        return vertix

    def vertice_aleatorio(self):
        '''
        devuelve un vertic aleatorio del grafo
        '''
        return choice([v for v in self.vertices for w in self.vertices])

    def cantidad_adyacentes(self, v):
        if not v in self.vertices:
            return 0
        return len(self.vertices[v])
    
    def cantidad_vertices(self):
        return len(self.vertices)