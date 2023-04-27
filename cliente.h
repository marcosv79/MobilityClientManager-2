#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente
{
	int nifCliente; 
	int saldoCliente;
 	char nomeCliente[50];
 	char moradaCliente[50];
 	char senhaCliente[50];
 	struct cliente* seguinte;
} Cliente;


Cliente* inserirCliente(Cliente* inicio, int nifC, int saldoC, char nomeC[], char moradaC[], char senhaC[]); // Inserção de um novo registo
void listarCliente(Cliente* inicio); // listar na consola o conteúdo da lista ligada
int existeCliente(Cliente* inicio, int nifCliente); // Determinar existência do 'codigo' na lista ligada 'inicio'
Cliente* removerCliente(Cliente* inicio, int nifC); // Remover um meio a partir do seu código

int guardarClientes(Cliente* inicio);
Cliente* lerClientes();

Cliente* atualizarCliente(Cliente* inicio, int nifC, char novoNomeC[], char novaMoradaC[], char novaSenhaC[]);

Cliente* carregarSaldo(Cliente* inicio, int nifC, int novoSaldoC);

int guardarClienteBinario(Cliente* inicio);