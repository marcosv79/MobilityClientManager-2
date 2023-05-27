/*****************************************************************
 * @file   grafo.h
 * @brief  Estrutura para representar grafos, nós e arestas e suas funções
 * @author Marcos Vasconcelos
 * @date   Maio 2023
 ****************************************************************/

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


/**
 * @brief Cria e adiciona um novo nó ao grafo
 * 
 * @param grafo
 * @param localizacao
 * @return
 * @author Marcos Vasconcelos
 * 
*/
No* criarAdicionarNo(Grafo* grafo, const char* localizacao);


/**
 * @brief Verifica a existência de uma aresta entre dois nós
 * 
 * @param origem
 * @param destino
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int existeAresta(No* origem, No* destino);


/**
 * @brief Cria uma aresta entre dois nós
 * 
 * @param origem
 * @param destino
 * @param peso
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int adicionarAresta(No* origem, No* destino, int peso);


/**
 * @brief Adiciona as arestas à estrutura do grafo
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int adicionarArestas(Grafo* grafo);


/**
 * @brief Inicializa o grafo
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int inicializarGrafo(Grafo* grafo);


/**
 * @brief Cria o grafo a partir do arquivo de localizações
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void criarGrafoLocalizacoes(Grafo* grafo);


/**
 * @brief Imprime o conteúdo do grafo
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void imprimirGrafo(Grafo* grafo);


/**
 * @brief Procura nas listas de clientes e meios as localizações e escreve-as no ficheiro de localizações
 * 
 * @param clientes
 * @param meios
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void buscaLocalizacoes(Cliente* clientes, Meio* meios);


/**
 * @brief Lista os meios de um determinado tipo e num determinado raio
 * 
 * @param grafo
 * @param localizacaoAtual
 * @param raio
 * @param tipo
 * @param listaMeios
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarMeiosPorRaioETipo(Grafo* grafo, const char* localizacaoAtual, int raio, const char* tipo, Meio* listaMeios);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro de texto
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarGrafo(Grafo* grafo);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro binário
 * 
 * @param grafo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void guardarGrafoBinario(Grafo* grafo);