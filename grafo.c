#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

No* criarAdicionarNo(Grafo* grafo, const char* localizacao) {
    No* novoNo = (No*) malloc(sizeof(No));
    strcpy(novoNo->nome, localizacao);
    novoNo->seguinte = grafo->cabeca;
    novoNo->arestas = NULL;
    grafo->cabeca = novoNo;
    return novoNo;
}

int existeAresta(No* origem, No* destino) {
    Aresta* arestaAtual = origem->arestas;
    while (arestaAtual != NULL) {
        if (arestaAtual->destino == destino) {
            return 1;
        }
        arestaAtual = arestaAtual->prox;
    }
    return 0;
}

void adicionarAresta(No* origem, No* destino, int peso) {
    if (existeAresta(origem, destino)) {
        return;
    }
    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = origem->arestas;
    origem->arestas = novaAresta;
}

void adicionarArestas(Grafo* grafo) {
    No* noAtual = grafo->cabeca;
    while (noAtual != NULL) {
        No* noDestino = grafo->cabeca;
        while (noDestino != NULL) {
            if (noAtual != noDestino) {
                int peso = rand() % 100;
                adicionarAresta(noAtual, noDestino, peso);
                adicionarAresta(noDestino, noAtual, peso); // Adiciona a aresta inversa com o mesmo peso
            }
            noDestino = noDestino->seguinte;
        }
        noAtual = noAtual->seguinte;
    }
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

    // Adicionar as arestas após adicionar os nós
    adicionarArestas(grafo);
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    No* noAtual = grafo->cabeca;
    printf("Localizações (nós) do grafo:\n");
    while (noAtual != NULL) {
        printf("%s\n", noAtual->nome);

        Aresta* arestaAtual = noAtual->arestas;
        while (arestaAtual != NULL) {
            printf("-> %s (distância: %d)\n", arestaAtual->destino->nome, arestaAtual->peso);
            arestaAtual = arestaAtual->prox;
        }

        noAtual = noAtual->seguinte;
        printf("\n");
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

void listarMeiosPorRaioETipo(Grafo* grafo, const char* localizacaoAtual, int raio, const char* tipo, Meio* listaMeios) {
    // Encontrar o nó correspondente à localização atual
    No* noAtual = grafo->cabeca;
    while (noAtual != NULL && strcmp(noAtual->nome, localizacaoAtual) != 0) {
        noAtual = noAtual->seguinte;
    }

    // Percorrer as arestas do nó atual e imprimir os meios dentro do raio e do tipo correspondente
    Aresta* arestaAtual = noAtual->arestas;
    while (arestaAtual != NULL) {
        if (arestaAtual->peso <= raio) {
            // Encontrar o meio de mobilidade correspondente à localização atual
            Meio* meioAtual = listaMeios;
            while (meioAtual != NULL) {
                if (strcmp(meioAtual->tipo, tipo) == 0 && strcmp(meioAtual->locMeio, arestaAtual->destino->nome) == 0) {
                    // Aqui você pode armazenar os resultados em uma estrutura de dados ou realizar qualquer outra operação desejada.
                    break;
                }
                meioAtual = meioAtual->seguinte;
            }
        }
        arestaAtual = arestaAtual->prox;
    }
}

void guardarGrafo(Grafo* grafo){
    FILE* fp;
    fp = fopen("grafo.txt","w");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    No* noAtual = grafo->cabeca;
    while (noAtual != NULL) {
        fprintf(fp, "%s\n", noAtual->nome);

        Aresta* arestaAtual = noAtual->arestas;
        while (arestaAtual != NULL) {
            fprintf(fp, "%s %d\n", arestaAtual->destino->nome, arestaAtual->peso);
            arestaAtual = arestaAtual->prox;
        }
        noAtual = noAtual->seguinte;
    }
    fclose(fp);
}

void guardarGrafoBinario(Grafo* grafo){
    FILE* fp;
    fp = fopen("grafo.bin","wb");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    No* noAtual = grafo->cabeca;
    while (noAtual != NULL) {
        fwrite(noAtual, sizeof(No), 1, fp);
        
        Aresta* arestaAtual = noAtual->arestas;
        while (arestaAtual != NULL) {
            fwrite(arestaAtual, sizeof(Aresta), 1, fp);
            arestaAtual = arestaAtual->prox;
        }

        noAtual = noAtual->seguinte;
    }
    fclose(fp);
}