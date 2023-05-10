#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "meio.h"

typedef struct No {
    char localizacao[50];
    struct No* proximo;
    struct Aresta* listaArestas;
} No;

typedef struct Aresta {
    struct No* destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct Grafo {
    int numNos;
    No* listaNos;
} Grafo;

No* criarNo(Grafo* grafo, char* localizacao, Cliente* listaClientes, Meio* listaMeios);
void criarAresta(Grafo* grafo);
void gerarGrafo(Grafo* grafo);
