/*****************************************************************
 * @file   cliente.h
 * @brief  Estrutura para representar clientes e suas funções
 * @author Marcos Vasconcelos
 * @date   Maio 2023
 ****************************************************************/

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
	char locCliente[50];
 	struct cliente* seguinte;
} Cliente;


/**
 * @brief Insere um novo cliente na lista ligada 'inicio'
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* inserirCliente(Cliente* inicio, int nifC, int saldoC, char nomeC[], char moradaC[], char senhaC[], char locC[50]);


/**
 * @brief Lista na consola o conteúdo da lista ligada 'inicio'
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarCliente(Cliente* inicio); 


/**
 * @brief Determina a existência de um cliente na lista ligada 'inicio' a partir do seu código
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int existeCliente(Cliente* inicio, int nifCliente);


/**
 * @brief Remove um cliente na lista ligada 'inicio' a partir do seu código
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* removerCliente(Cliente* inicio, int nifC); // Remover um meio a partir do seu código


/**
 * @brief Guarda o conteúdo da lista ligada 'inicio' num ficheiro de texto
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarClientes(Cliente* inicio);


/**
 * @brief Guarda o conteúdo da lista ligada 'inicio' num ficheiro binário
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarClienteBinario(Cliente* inicio);


/**
 * @brief Faz a leitura dos dados do ficheiro binário e insere-os na lista ligada 'inicio'
 * 
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* lerClientes();


/**
 * @brief Atualiza os dados do cliente na lista ligada 'inicio'
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* atualizarCliente(Cliente* inicio, int nifC, char novoNomeC[], char novaMoradaC[], char novaSenhaC[], char novaLocC[50]);


/**
 * @brief Atualiza o valor do saldo do cliente
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* carregarSaldo(Cliente* inicio, int nifC, int novoSaldoC);