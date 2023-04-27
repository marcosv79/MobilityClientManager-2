#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meio.h"

int guardarMeiosBinario(Meio* inicio) {
    FILE* fp;
    fp = fopen("meios.bin", "wb"); // Abre o arquivo em modo de escrita binária
    if (fp != NULL) { 
        Meio* aux = inicio; // Ponteiro aux para percorrer a lista
        while (aux != NULL) {
            fwrite(aux, sizeof(Meio), 1, fp); // Escreve uma struct Meio inteira no arquivo
            aux = aux->seguinte; 
        }
        fclose(fp);
        return 1;
    }
    else {
        return 0;
    }
}

int guardarMeios(Meio* inicio)
{FILE* fp;
 fp = fopen("meios.txt","w");
 if (fp!=NULL)
 {
 Meio* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d;%f;%f;%s;%d;%s\n", aux->codigo, aux->bateria, 
	                      aux->autonomia, aux->tipo, aux->custo, aux->localizacao);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

Meio* lerMeios() {
    FILE* fp;
    Meio* aux = NULL;
    fp = fopen("meios.bin", "rb"); // Abre o arquivo em modo de leitura binária
    if (fp != NULL) {
        Meio meio; // Cria o elemento meio para guardar os dados lidos
        while (fread(&meio, sizeof(Meio), 1, fp) == 1) { // Lê uma struct Meio inteira do arquivo
            aux = inserirMeio(aux, meio.codigo, meio.tipo, meio.bateria, meio.autonomia, meio.custo, meio.localizacao);
        }
        fclose(fp);
    }
    return aux; // Retorna o ponteiro para o inicio da lista 
}

Meio* inserirMeio(Meio * inicio, int cod, char tipo[], float bat, float aut, int cst, char loc[])
{
 if (!existeMeio(inicio, cod))
 {Meio * novo = malloc(sizeof(struct registo)); // Alocar memória para o novo registo
  if (novo != NULL)
  // Preenche os campos do novo meio com os valores passados como argumentos
  {novo->codigo = cod;
   strcpy(novo->tipo,tipo);
   novo->bateria = bat;
   novo->autonomia = aut;
   novo->custo = cst;
   novo->alugado = 0;
   strcpy(novo->localizacao,loc);
   novo->seguinte = inicio; // Insere o novo registo no inicio da lista
   return(novo);
  }
 } else return(inicio);
}

void listarMeios(Meio * inicio)
{while (inicio != NULL)
 {printf("%d %s %.2f %.2f %d %s\n",inicio->codigo,inicio->tipo, 
		             inicio->bateria, inicio->autonomia, inicio->custo, inicio->localizacao); 
  inicio = inicio->seguinte;
 }
}

void listarMeiosPorLocalizacao(Meio * inicio) {
    char loc[50];
    printf("Digite a localização para listar os meios: ");
    scanf("%s", loc);
    while (inicio != NULL) {
        if (strcmp(loc, inicio->localizacao) == 0) {
            printf("%d %s %.2f %.2f %d %s\n",
                inicio->codigo, inicio->tipo, inicio->bateria,
                inicio->autonomia, inicio->custo,
                inicio->localizacao); 
        }
        inicio = inicio->seguinte;
    }
}

int existeMeio(Meio* inicio, int cod)
{while(inicio!=NULL)
  {if (inicio->codigo == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Meio* removerMeio(Meio* inicio, int cod) 
{
 Meio *anterior=inicio, *atual=inicio, *aux; // Três ponteiros para o inicio da lista

 if (atual==NULL) return(NULL);
 else if (atual->codigo == cod) // Se o primeiro elemento da lista tem o ID que se deseja remover
 {aux = atual->seguinte; // Atualiza o ponteiro aux para apontar para o seguinte elemento da lista
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->codigo!=cod)) // Percorre a lista até encontrar o meio com o código desejado
  {anterior = atual; // Ponteiro anterior a apontar para o elemento atual
   atual = atual->seguinte; // Ponteiro atual a apontar para o seguinte elemento da lista
  }
  if (atual==NULL) return(inicio); // ID não encontrado na lista
  else
  {anterior->seguinte = atual->seguinte; // Ponteiro anterior a apontar para o elemento seguinte ao elemento que se deseja remover
   free(atual);
   return(inicio);
  }
 }
}

Meio* atualizarMeio(Meio* inicio, int cod, char novoTipo[], float novaBat, float novaAut, int novoCst, char novaLoc[]) {
    Meio* atual = inicio;

    while (atual != NULL) {
        if (atual->codigo == cod) {

            if (strlen(novoTipo) > 0) 
            {
                strcpy(atual->tipo, novoTipo);
            }
            if (strlen(novaLoc) > 0)
            {
                strcpy(atual->localizacao,novaLoc);
            }
            atual->bateria = novaBat;
            atual->autonomia = novaAut;
            atual->custo = novoCst;
            return inicio;
        }
        atual = atual->seguinte;
    }

    printf("Meio com o codigo %d nao existe na lista.\n", cod);
    return inicio;
}

void listarMeiosPorAutonomia(Meio * inicio)
{
    Meio *nova_lista = NULL;

    // Percorre a lista original
    while (inicio != NULL)
    {
        if (nova_lista == NULL || inicio->autonomia > nova_lista->autonomia)
        {
            // Cria um novo elemento de meio ao copiar todos os dados da lista inicio
            Meio *novo_elemento = (Meio*) malloc(sizeof(Meio));
            novo_elemento->codigo = inicio->codigo;
            strcpy(novo_elemento->tipo, inicio->tipo);
            novo_elemento->bateria = inicio->bateria;
            novo_elemento->autonomia = inicio->autonomia;
            novo_elemento->custo = inicio->custo;
            strcpy(novo_elemento->localizacao, inicio->localizacao);
            novo_elemento->seguinte = nova_lista;
            // Novo elemento inserido no inicio da nova lista
            nova_lista = novo_elemento;
        }
        else
        {
            // Cria um novo elemento de meio e percorre a nova lista até encontrar a posição correta
            Meio *ponteiro = nova_lista;
            while (ponteiro->seguinte != NULL && inicio->autonomia <= ponteiro->seguinte->autonomia)
            {
                ponteiro = ponteiro->seguinte;
            }
            Meio *novo_elemento = (Meio*) malloc(sizeof(Meio));
            novo_elemento->codigo = inicio->codigo;
            strcpy(novo_elemento->tipo, inicio->tipo);
            novo_elemento->bateria = inicio->bateria;
            novo_elemento->autonomia = inicio->autonomia;
            novo_elemento->custo = inicio->custo;
            strcpy(novo_elemento->localizacao, inicio->localizacao);
            novo_elemento->seguinte = ponteiro->seguinte;
            ponteiro->seguinte = novo_elemento;
        }
        inicio = inicio->seguinte;
    }

    printf("Meios ordenados por autonomia (decrescente):\n");
    while (nova_lista != NULL)
    {
        printf("%d %s %.2f %.2f %d %s\n", nova_lista->codigo, nova_lista->tipo, nova_lista->bateria, nova_lista->autonomia, nova_lista->custo, nova_lista->localizacao);
        nova_lista = nova_lista->seguinte;
    }
}

int devolverMeio(Meio* inicio, int codigo) {
    Meio* atual = inicio;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (atual->alugado == 1) {
                atual->alugado = 0;
                return 1;
            } else {
                printf("O meio escolhido nao esta alugado.\n");
                return 0;
            }
        }
        atual = atual->seguinte;
    }

    printf("Nao foi possivel encontrar o meio com o codigo %d.\n", codigo);
    return 0;
}