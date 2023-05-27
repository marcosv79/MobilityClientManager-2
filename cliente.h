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
 * @brief Insere um novo cliente na lista ligada
 * 
 * @param inicio
 * @param nifC
 * @param saldoC
 * @param nomeC
 * @param moradaC
 * @param senhaC
 * @param locC
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* inserirCliente(Cliente* inicio, int nifC, int saldoC, char nomeC[], char moradaC[], char senhaC[], char locC[50]);


/**
 * @brief Lista na consola o conteúdo da lista ligada
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarCliente(Cliente* inicio); 


/**
 * @brief Determina a existência de um cliente na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param nifCliente
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int existeCliente(Cliente* inicio, int nifCliente);


/**
 * @brief Remove um cliente na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param nifC
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* removerCliente(Cliente* inicio, int nifC); // Remover um meio a partir do seu código


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro de texto
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarClientes(Cliente* inicio);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro binário
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarClienteBinario(Cliente* inicio);


/**
 * @brief Faz a leitura dos dados do ficheiro binário e insere-os na lista ligada
 * 
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* lerClientes();


/**
 * @brief Atualiza os dados do cliente na lista ligada
 * 
 * @param inicio
 * @param nifC
 * @param novoNomeC
 * @param novaMoradaC
 * @param novaSenhaC
 * @param novaLocC
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* atualizarCliente(Cliente* inicio, int nifC, char novoNomeC[], char novaMoradaC[], char novaSenhaC[], char novaLocC[50]);


/**
 * @brief Atualiza o valor do saldo do cliente
 * 
 * @param inicio
 * @param nifC
 * @param novoSaldoC
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Cliente* carregarSaldo(Cliente* inicio, int nifC, int novoSaldoC);