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

int adicionarAresta(No* origem, No* destino, int peso) {
    if (existeAresta(origem, destino)) {
        return 0;
    }
    Aresta* novaAresta = (Aresta*) malloc(sizeof(Aresta));
    if (novaAresta == NULL) {
        return 0;
    }
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = origem->arestas;
    origem->arestas = novaAresta;

    return 1;
}

int adicionarArestas(Grafo* grafo) {
    int totalArestasAdicionadas = 0;

    No* noAtual = grafo->cabeca;
    while (noAtual != NULL) {
        No* noDestino = grafo->cabeca;
        while (noDestino != NULL) {
            if (noAtual != noDestino) {
                int peso = rand() % 100;
                if (adicionarAresta(noAtual, noDestino, peso)) {
                    totalArestasAdicionadas++;
                }
                if (adicionarAresta(noDestino, noAtual, peso)) {
                    totalArestasAdicionadas++;
                }
            }
            noDestino = noDestino->seguinte;
        }
        noAtual = noAtual->seguinte;
    }

    return totalArestasAdicionadas;
}

int inicializarGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return 0;
    }
    
    grafo->cabeca = NULL;
    
    return 1;
}

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
    adicionarArestas(grafo);
}

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

void listarMeiosPorRaioETipo(Grafo* grafo, char localizacaoAtual, int raio, char tipo, Meio* listaMeios) {
    printf("Meios no raio de %d a partir de %s do tipo %s:\n", raio, localizacaoAtual, tipo);

    // Encontrar o nó correspondente à localização atual
    No* noAtual = grafo->cabeca;
    while (noAtual != NULL && strcmp(noAtual->nome, localizacaoAtual) != 0) {
        noAtual = noAtual->seguinte;
    }

    if (noAtual == NULL) {
        printf("Localização atual não encontrada no grafo.\n");
        return;
    }

    // Percorrer as arestas do nó atual e imprimir os meios dentro do raio e do tipo correspondente
    Aresta* arestaAtual = noAtual->arestas;
    while (arestaAtual != NULL) {
        if (arestaAtual->peso <= raio) {
            // Encontrar o meio de mobilidade correspondente à localização atual
            Meio* meioAtual = listaMeios;
            while (meioAtual != NULL) {
                if (strcmp(meioAtual->tipo, tipo) == 0 && strcmp(meioAtual->locMeio, arestaAtual->destino->nome) == 0) {
                    printf("-> Código: %d, Tipo: %s, Bateria: %.2f, Autonomia: %.2f, Custo: %d, Localização: %s (distância: %d)\n", meioAtual->codigo, meioAtual->tipo, meioAtual->bateria, meioAtual->autonomia, meioAtual->custo, meioAtual->locMeio, arestaAtual->peso);
                    break;
                }
                meioAtual = meioAtual->seguinte;
            }
        }
        arestaAtual = arestaAtual->prox;
    }
}

int guardarGrafo(Grafo* grafo){
    FILE* fp;
    fp = fopen("grafo.txt","w");
    if(fp == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    No* noAtual = grafo->cabeca;
    while (noAtual != NULL) {
        if (fprintf(fp, "%s\n", noAtual->nome) < 0) {
            fclose(fp);
            return 0;
        }

        Aresta* arestaAtual = noAtual->arestas;
        while (arestaAtual != NULL) {
            if (fprintf(fp, "%s %d\n", arestaAtual->destino->nome, arestaAtual->peso) < 0) {
                fclose(fp);
                return 0;
            }
            arestaAtual = arestaAtual->prox;
        }
        noAtual = noAtual->seguinte;
    }
    fclose(fp);
    return 1; 
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