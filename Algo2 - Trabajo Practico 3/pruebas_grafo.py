from grafo import Grafo
vertices = ["Venezuela", "Argentina", "Brasil", "Uruguay", "Ecuador", "Colombia", "Honduras"]
from biblioteca import *

#Archivo de pruebas cortos para el TDA grafo
def prueba_creacion():
    print("Pruebas creando un grafo")
    grafo = Grafo()
    assert (grafo is not None)
    print("Todo OK")
    return 0

def prueba_agregando_vertices():
    print("Pruebas agregando vertices")
    grafo = Grafo()
    for vertice in vertices:
        grafo.agregar_vertice(vertice)
    assert (grafo.vertice_existe(vertices[0]))
    assert (grafo.vertice_existe(vertices[1]))
    assert (grafo.vertice_existe(vertices[2]))
    assert (grafo.vertice_existe(vertices[3]))
    assert (grafo.vertice_existe(vertices[4]))
    print("Todo OK")
    return 0

def pruebas_agregando_aristas():
    print("Pruebas agregando Aristas")
    grafo = Grafo()
    for vertice in vertices:
        grafo.agregar_vertice(vertice)
    grafo.agregar_arista(vertices[0],vertices[1])
    grafo.agregar_arista(vertices[1],vertices[0])
    assert(grafo.arista_existe(vertices[0],vertices[1]))
    assert(grafo.arista_existe(vertices[1],vertices[0]))
    assert(grafo.arista_existe(vertices[1],vertices[2]) == False)
    assert(grafo.arista_existe(vertices[2],vertices[1]) == False)
    print("Todo OK")
    return 0

def pruebas_grafo_pesado():
    print("Pruebas con grafo pesado")
    grafo = Grafo(False, True)
    for vertice in vertices:
        grafo.agregar_vertice(vertice)
    grafo.agregar_arista(vertices[0], vertices[1], "Hola")
    grafo.agregar_arista(vertices[0], vertices[2], "Peter")
    grafo.agregar_arista(vertices[0], vertices[3], "Mundo")
    assert(grafo.peso_arista(vertices[0], vertices[1]) == "Hola" )
    assert(grafo.peso_arista(vertices[0], vertices[2]) == "Peter" )
    assert(grafo.peso_arista(vertices[0], vertices[3]) == "Mundo" )
    assert(grafo.peso_arista(vertices[1], vertices[0]) == "Hola" )
    assert(grafo.peso_arista(vertices[2], vertices[0]) == "Peter" )
    assert(grafo.peso_arista(vertices[3], vertices[0]) == "Mundo" )
    print("Todo OK")
    return 0

def prueba_vertice_aleatorio():
    print("Pruebas usando vertices alatorios")
    grafo = Grafo()
    for vertice in vertices:
        grafo.agregar_vertice(vertice)
    assert(grafo.vertice_aleatorio() is not None)
    print("Todo OK")
    return 0

def main():
    prueba_creacion()
    prueba_agregando_vertices()
    pruebas_agregando_aristas()
    pruebas_grafo_pesado()
    prueba_vertice_aleatorio()
    return 0

main()