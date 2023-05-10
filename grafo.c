#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"

void criarArquivoLocalizacoes() {
    FILE* arquivo = fopen("localizacoes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Abrir o arquivo de clientes
    FILE* clientes = fopen("clientes.txt", "r");
    if (clientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        fclose(arquivo);
        return;
    }

    // Percorrer o arquivo de clientes e escrever cada localização no arquivo de localizações
    char linha[256];
    while (fgets(linha, sizeof(linha), clientes) != NULL) {
        char localizacao[50];
        if (sscanf(linha, "%*d;%*d;%*[^;];%*[^;];%*[^;];%49[^\n]", localizacao) == 1) {
            if (fprintf(arquivo, "%s\n", localizacao) < 0) {
                printf("Erro ao escrever no arquivo de localizações!\n");
                fclose(clientes);
                fclose(arquivo);
                return;
            }
        }
    }

    fclose(clientes);

    // Abrir o arquivo de meios
    FILE* meios = fopen("meios.txt", "r");
    if (meios == NULL) {
        printf("Erro ao abrir o arquivo de meios.\n");
        fclose(arquivo);
        return;
    }

    // Percorrer o arquivo de meios e escrever cada localização no arquivo de localizações
    while (fgets(linha, sizeof(linha), meios) != NULL) {
        char localizacao[50];
        if (sscanf(linha, "%*d;%*[^;];%*[^;];%*[^;];%*[^;];%49[^\n]", localizacao) == 1) {
            if (fprintf(arquivo, "%s\n", localizacao) < 0) {
                printf("Erro ao escrever no arquivo de localizações!\n");
                fclose(meios);
                fclose(arquivo);
                return;
            }
        }
    }
    fclose(meios);
    fclose(arquivo);
}