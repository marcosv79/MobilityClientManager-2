#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "meio.h"

typedef struct Aresta Aresta;

typedef struct No {
    char nome[50];
    Aresta* arestas;
    struct No* seguinte;
} No;

struct Aresta {
    No* destino;
    int peso;
    struct Aresta* prox;
};

typedef struct Grafo {
    No* cabeca;
} Grafo;


No* criarAdicionarNo(Grafo* grafo, const char* localizacao);
void inicializarGrafo(Grafo* grafo);
void imprimirGrafo(Grafo* grafo);
void criarGrafoLocalizacoes(Grafo* grafo);
void buscaLocalizacoes(Cliente* clientes, Meio* meios);
void adicionarAresta(No* origem, No* destino, int peso);
void adicionarArestas(Grafo* grafo);