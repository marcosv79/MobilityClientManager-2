#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestor.h"

int guardarGestorBinario(Gestor* inicio) {
    FILE* fp;
    fp = fopen("gestores.bin", "wb"); // Abre o arquivo em modo de escrita binária
    if (fp != NULL) { 
        Gestor* aux = inicio; // Ponteiro aux para percorrer a lista
        while (aux != NULL) {
            fwrite(aux, sizeof(Gestor), 1, fp); // Escreve uma struct Gestor inteira no arquivo
            aux = aux->seguinte;
        }
        fclose(fp);
        return 1;
    }
    else {
        return 0;
    }
}

int guardarGestor(Gestor* inicio)
{FILE* fp;
 fp = fopen("gestores.txt","w");
 if (fp!=NULL)
 {
 Gestor* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d; %s; %s; %s\n", aux->idGestor, aux->nomeGestor, aux->moradaGestor, aux->senhaGestor);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}


Gestor* lerGestor() {
    FILE* fp;
    Gestor* aux = NULL;
    fp = fopen("gestores.bin", "rb"); // Abre o arquivo em modo de leitura binária
    if (fp != NULL) {
        Gestor gestor; // Cria o elemento gestor para guardar os dados lidos
        while (fread(&gestor, sizeof(Gestor), 1, fp) == 1) { // Lê uma struct Gestor inteira do arquivo
            aux = inserirGestor(aux, gestor.idGestor, gestor.nomeGestor, gestor.moradaGestor, gestor.senhaGestor);
        }
        fclose(fp);
    }
    return aux; // Retorna o ponteiro para o inicio da lista 
}

Gestor* inserirGestor(Gestor * inicio, int idG, char nomeG[], char moradaG[], char senhaG[])
{
 if (!existeGestor(inicio, idG))
 {Gestor * novo = malloc(sizeof(struct gestor)); // Alocar memória para o novo registo
  if (novo != NULL)
  // Preenche os campos do novo gestor com os valores passados
  {novo->idGestor = idG;
   strcpy(novo->nomeGestor,nomeG);
   strcpy(novo->moradaGestor,moradaG);
   strcpy(novo->senhaGestor,senhaG);
   novo->seguinte = inicio; // Insere o novo registo no inicio da lista
   return(novo);
  }
 } else return(inicio);
}

void listarGestor(Gestor * inicio)
{while (inicio != NULL)
 {printf("%d %s %s %s\n",inicio->idGestor, inicio->nomeGestor, inicio->moradaGestor, inicio->senhaGestor);
  inicio = inicio->seguinte;
 }
}

int existeGestor(Gestor* inicio, int idG)
{while(inicio!=NULL)
  {if (inicio->idGestor == idG) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Gestor* removerGestor(Gestor* inicio, int idG) 
{
 Gestor *anterior=inicio, *atual=inicio, *aux; // Três ponteiros para o inicio da lista

 if (atual==NULL) return(NULL);
 else if (atual->idGestor == idG) // Se o primeiro elemento da lista tem o ID que se deseja remover
 {aux = atual->seguinte; // Atualiza o ponteiro aux para apontar para o seguinte elemento da lista
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->idGestor!=idG)) // Percorre a lista até encontrar o gestor com o código desejado
  {anterior = atual; // Ponteiro anterior a apontar para o elemento atual
   atual = atual->seguinte; // Atual a apontar para o seguinte elemento da lista
  }
  if (atual==NULL) return(inicio); // ID não encontrado na lista
  else
  {anterior->seguinte = atual->seguinte; // Ponteiro anterior a apontar para o elemento seguinte ao elemento que se deseja remover
   free(atual);
   return(inicio);
  }
 }
}

Gestor* atualizarGestor(Gestor* inicio, int idG, char novoNomeG[], char novaMoradaG[], char novaSenhaG[]) {
    Gestor* atual = inicio;

    while (atual != NULL) {
        if (atual->idGestor == idG) {

            if (strlen(novoNomeG) > 0) {
                strcpy(atual->nomeGestor, novoNomeG);
            }
            if (strlen(novaMoradaG) > 0) {
                strcpy(atual->moradaGestor, novaMoradaG);
            }
            if (strlen(novaSenhaG) > 0) {
                strcpy(atual->senhaGestor, novaSenhaG);
            }

            return inicio;
        }
        atual = atual->seguinte;
    }

    printf("Gestor com o ID %d nao existe na lista.\n", idG);
    return inicio;
}