#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aresta Aresta;

typedef struct No {
    char localizacao[50];
    Aresta* arestas;
    struct No* prox;
} No;

struct Aresta {
    No* destino;
    int peso;
    struct Aresta* prox;
};

typedef struct Grafo {
    No* cabeca;
} Grafo;


No* criarNo(const char* localizacao);
void adicionarNo(Grafo* grafo, const char* localizacao);
void inicializarGrafo(Grafo* grafo);
void imprimirGrafo(Grafo* grafo);
void criarGrafoLocalizacoes(Grafo* grafo);
void criarArquivoLocalizacoes();
