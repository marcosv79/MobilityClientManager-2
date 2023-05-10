#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

No* criarNo(Grafo* grafo, char* localizacao, Cliente* clientes, Meio* meios) {
    // Verificar se um nó já foi criado para a localização
    No* noAtual = grafo->listaNos;
    while (noAtual != NULL) {
        if (strcmp(noAtual->localizacao, localizacao) == 0) {
            return noAtual;
        }
        noAtual = noAtual->proximo;
    }

    // Procurar a localização na lista de clientes
    Cliente* clienteAtual = clientes;
    while (clienteAtual != NULL) {
        if (strcmp(clienteAtual->locCliente, localizacao) == 0) {
            // Localização encontrada
            No* novoNo = (No*)malloc(sizeof(No));
            strcpy(novoNo->localizacao, localizacao);
            novoNo->proximo = NULL;
            novoNo->listaArestas = NULL;

            // Adicionar o novo nó à lista de nós do grafo
            if (grafo->listaNos == NULL) {
                grafo->listaNos = novoNo;
            } else {
                No* noAtual = grafo->listaNos;
                while (noAtual->proximo != NULL) {
                    noAtual = noAtual->proximo;
                }
                noAtual->proximo = novoNo;
            }
            grafo->numNos++;
            return novoNo;
        }
        clienteAtual = clienteAtual->seguinte;
    }

    // Procurar a localização na lista de meios
    Meio* meioAtual = meios;
    while (meioAtual != NULL) {
        if (strcmp(meioAtual->locMeio, localizacao) == 0) {
            // Localização encontrada
            No* novoNo = (No*)malloc(sizeof(No));
            strcpy(novoNo->localizacao, localizacao);
            novoNo->proximo = NULL;
            novoNo->listaArestas = NULL;

            // Adicionar o novo nó à lista de nós do grafo
            if (grafo->listaNos == NULL) {
                grafo->listaNos = novoNo;
            } else {
                No* noAtual = grafo->listaNos;
                while (noAtual->proximo != NULL) {
                    noAtual = noAtual->proximo;
                }
                noAtual->proximo = novoNo;
            }
            grafo->numNos++;
            return novoNo;
        }
        meioAtual = meioAtual->seguinte;
    }

    // Localização não encontrada
    return NULL;
}

void criarAresta(Grafo* grafo) {
    No* no1 = grafo->listaNos;
    while (no1 != NULL) {
        No* no2 = grafo->listaNos;
        while (no2 != NULL) {
            if (no1 != no2) {
                Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
                novaAresta->destino = no2;
                novaAresta->peso = rand() % 151 + 50; // Peso entre 50 e 200
                novaAresta->proxima = no1->listaArestas;
                no1->listaArestas = novaAresta;
            }
            no2 = no2->proximo;
        }
        no1 = no1->proximo;
    }
}

void gerarGrafo(Grafo* grafo) {
    printf("Localizações:\n");
    No* noAtual = grafo->listaNos;
    while (noAtual != NULL) {
        printf("%s\n", noAtual->localizacao);
        Aresta* arestaAtual = noAtual->listaArestas;
        while (arestaAtual != NULL) {
            printf("Distância entre %s e %s: %d\n", noAtual->localizacao, arestaAtual->destino->localizacao, arestaAtual->peso);
            arestaAtual = arestaAtual->proxima;
        }
        noAtual = noAtual->proximo;
    }
}
