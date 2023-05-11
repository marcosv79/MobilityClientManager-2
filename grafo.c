#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

No* criarAdicionarNo(Grafo* grafo, const char* localizacao) {
    No* novoNo = (No*) malloc(sizeof(No));
    strcpy(novoNo->nome, localizacao);
    novoNo->seguinte = grafo->cabeca;
    grafo->cabeca = novoNo;
    return novoNo;
}

// Função para inicializar o grafo
void inicializarGrafo(Grafo* grafo) {
    grafo->cabeca = NULL;
}

// Função para ler o arquivo de localizações e adicionar os nós ao grafo
void criarGrafoLocalizacoes(Grafo* grafo) {
    FILE* arquivo = fopen("localizacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de localizações.\n");
        return;
    }

    char localizacao[50];
    while (fgets(localizacao, sizeof(localizacao), arquivo) != NULL) {
        // Remover o caractere '\n' da localização
        localizacao[strcspn(localizacao, "\n")] = 0;
        criarAdicionarNo(grafo, localizacao);
    }

    fclose(arquivo);
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    No* noAtual = grafo->cabeca;
    printf("Localizações (nós) do grafo: \n");
    while (noAtual != NULL) {
        printf("%s\n", noAtual->nome);
        noAtual = noAtual->seguinte;
    }
}

void buscaLocalizacoes(Cliente* clientes, Meio* meios) {
    FILE* arquivo = fopen("localizacoes.txt", "w+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Cliente* clienteAtual = clientes;
    while (clienteAtual != NULL) {
            if (fprintf(arquivo, "%s\n", clienteAtual->locCliente) < 0) {
                printf("Erro ao escrever no arquivo de localizações!\n");
                fclose(arquivo);
                return;
            }
        clienteAtual = clienteAtual->seguinte;
    }

    Meio* meioAtual = meios;
    while (meioAtual != NULL) {
            if (fprintf(arquivo, "%s\n", meioAtual->locMeio) < 0) {
                printf("Erro ao escrever no arquivo de localizações!\n");
                fclose(arquivo);
                return;
            }
        meioAtual = meioAtual->seguinte;
    }

    fclose(arquivo);
}
