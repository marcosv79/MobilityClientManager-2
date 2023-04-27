#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int guardarClienteBinario(Cliente* inicio) {
    FILE* fp;
    fp = fopen("clientes.bin", "wb"); // Abre o arquivo em modo de escrita binária
    if (fp != NULL) { 
        Cliente* aux = inicio; // Ponteiro aux para percorrer a lista
        while (aux != NULL) {
            fwrite(aux, sizeof(Cliente), 1, fp); // Escreve uma struct Cliente inteira no arquivo
            aux = aux->seguinte;
        }
        fclose(fp);
        return 1;
    }
    else {
        return 0;
    }
}

int guardarClientes(Cliente* inicio)
{FILE* fp;
 fp = fopen("clientes.txt","w");
 if (fp!=NULL)
 {
 Cliente* aux= inicio;
 while (aux != NULL)
 {
  fprintf(fp,"%d; %d; %s; %s; %s\n", aux->nifCliente, aux->saldoCliente, aux->nomeCliente, aux->moradaCliente, aux->senhaCliente);
  aux = aux->seguinte;
 }
 fclose(fp);
 return(1);
 }
 else return(0);
}

Cliente* lerClientes() {
    FILE* fp;
    Cliente* aux = NULL;
    fp = fopen("clientes.bin", "rb"); // Abre o arquivo em modo de leitura binária
    if (fp != NULL) {
        Cliente cliente; // Cria o elemento cliente para guardar os dados lidos
        while (fread(&cliente, sizeof(Cliente), 1, fp) == 1) { // Lê uma struct Cliente inteira do arquivo
            aux = inserirCliente(aux, cliente.nifCliente, cliente.saldoCliente, cliente.nomeCliente, cliente.moradaCliente, cliente.senhaCliente);
        }
        fclose(fp);
    }
    return aux; // Retorna o ponteiro para o inicio da lista 
}

Cliente* inserirCliente(Cliente * inicio, int nifC, int saldoC, char nomeC[], char moradaC[], char senhaC[])
{
 if (!existeCliente(inicio, nifC))
 {Cliente * novo = malloc(sizeof(struct cliente)); // Alocar memória para o novo registo
  if (novo != NULL)
  // Preenche os campos do novo cliente com os valores passados
  {novo->nifCliente = nifC;
  novo->saldoCliente = saldoC;
   strcpy(novo->nomeCliente,nomeC);
   strcpy(novo->moradaCliente,moradaC);
   strcpy(novo->senhaCliente,senhaC);
   novo->seguinte = inicio; // Insere o novo registo no inicio da lista
   return(novo);
  }
 } else return(inicio);
}

void listarCliente(Cliente * inicio)
{while (inicio != NULL)
 {printf("%d %d %s %s %s\n",inicio->nifCliente, inicio->saldoCliente, inicio->nomeCliente, inicio->moradaCliente, inicio->senhaCliente);
  inicio = inicio->seguinte;
 }
}

int existeCliente(Cliente* inicio, int nifC)
{while(inicio!=NULL)
  {if (inicio->nifCliente == nifC) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Cliente* removerCliente(Cliente* inicio, int nifC) 
{
 Cliente *anterior=inicio, *atual=inicio, *aux; // Três ponteiros para o inicio da lista

 if (atual==NULL) return(NULL); 
 else if (atual->nifCliente == nifC) // Se o primeiro elemento da lista tem o ID que se deseja remover
 {aux = atual->seguinte; // Atualiza o ponteiro para o seguinte elemento da lista
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->nifCliente!=nifC)) // Percorre a lista até encontrar o cliente com o código desejado
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

Cliente* atualizarCliente(Cliente* inicio, int nifC, char novoNomeC[], char novaMoradaC[], char novaSenhaC[]) {
    Cliente* atual = inicio;

    while (atual != NULL) {
        if (atual->nifCliente == nifC) {

            if (strlen(novoNomeC) > 0) {
                strcpy(atual->nomeCliente, novoNomeC);
            }
            if (strlen(novaMoradaC) > 0) {
                strcpy(atual->moradaCliente, novaMoradaC);
            }
            if (strlen(novaSenhaC) > 0) {
                strcpy(atual->senhaCliente, novaSenhaC);
            }

            return inicio;
        }
        atual = atual->seguinte;
    }

    printf("Cliente com o NIF %d nao existe na lista.\n", nifC);
    return inicio;
}

Cliente* carregarSaldo(Cliente* inicio, int nifC, int novoSaldoC) {
    Cliente* atual = inicio;

    while (atual != NULL) {
        if (atual->nifCliente == nifC) { 
            atual->saldoCliente += novoSaldoC;
            printf("Saldo atualizado com sucesso.\n");
            printf("Novo saldo do cliente %s: %d\n", atual->nomeCliente, atual->saldoCliente);
            return inicio;
        }
        atual = atual->seguinte;
    }

    printf("Cliente com o NIF %d nao existe na lista.\n", nifC);
    return inicio;
}