#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

// Função para criar um novo nó
No* criarNo(const char* localizacao) {
    No* novoNo = (No*) malloc(sizeof(No));
    strcpy(novoNo->localizacao, localizacao);
    novoNo->prox = NULL;
    return novoNo;
}

// Função para verificar se a localização já existe no grafo
int localizacaoJaExisteNoArquivo(const char* localizacao) {
    FILE* arquivo = fopen("localizacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de localizações.\n");
        return 0;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char localizacaoArquivo[50];
        if (sscanf(linha, "%49[^\n]", localizacaoArquivo) == 1) {
            if (strcmp(localizacaoArquivo, localizacao) == 0) {
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}


// Função para adicionar nó ao grafo, caso a localização ainda não exista
void adicionarNo(Grafo* grafo, const char* localizacao) {
    No* novoNo = criarNo(localizacao);
    novoNo->prox = grafo->cabeca;
    grafo->cabeca = novoNo;
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
        adicionarNo(grafo, localizacao);
    }

    fclose(arquivo);
}

// Função para imprimir todas as localizações do grafo
void imprimirGrafo(Grafo* grafo) {
    No* noAtual = grafo->cabeca;
    printf("Localizações (nós) do grafo: \n");
    while (noAtual != NULL) {
        printf("%s\n", noAtual->localizacao);
        noAtual = noAtual->prox;
    }
}

void criarArquivoLocalizacoes() {
    FILE* arquivo = fopen("localizacoes.txt", "w+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    FILE* clientes = fopen("clientes.txt", "r");
    if (clientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), clientes) != NULL) {
        char localizacao[50];
        if (sscanf(linha, "%*d;%*d;%*[^;];%*[^;];%*[^;];%49[^\n]", localizacao) == 1) {
            if (!localizacaoJaExisteNoArquivo(localizacao)) {
                if (fprintf(arquivo, "%s\n", localizacao) < 0) {
                    printf("Erro ao escrever no arquivo de localizações!\n");
                    fclose(clientes);
                    fclose(arquivo);
                    return;
                }
            }
        }
    }

    fclose(clientes);

    FILE* meios = fopen("meios.txt", "r");
    if (meios == NULL) {
        printf("Erro ao abrir o arquivo de meios.\n");
        fclose(arquivo);
        return;
    }

    while (fgets(linha, sizeof(linha), meios) != NULL) {
        char localizacao[50];
        if (sscanf(linha, "%*d;%*[^;];%*[^;];%*[^;];%*[^;];%49[^\n]", localizacao) == 1) {
            if (!localizacaoJaExisteNoArquivo(localizacao)) {
                if (fprintf(arquivo, "%s\n", localizacao) < 0) {
                    printf("Erro ao escrever no arquivo de localizações!\n");
                    fclose(meios);
                    fclose(arquivo);
                    return;
                }
            }
        }
    }

    fclose(meios);
    fclose(arquivo);
}
