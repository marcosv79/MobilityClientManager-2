/*****************************************************************
 * @file   gestor.h
 * @brief  Estrutura para representar gestores e suas funções
 * @author Marcos Vasconcelos
 * @date   Maio 2023
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct gestor
{
	int idGestor; 
 	char nomeGestor[50];
 	char moradaGestor[50];
 	char senhaGestor[50];
 	struct gestor* seguinte;
} Gestor;


/**
 * @brief Insere um novo gestor na lista ligada
 * 
 * @param inicio
 * @param idG
 * @param nomeG
 * @param moradaG
 * @param senhaG
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Gestor* inserirGestor(Gestor* inicio, int idG, char nomeG[], char moradaG[], char senhaG[]);


/**
 * @brief Lista na consola o conteúdo da lista ligada
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarGestor(Gestor* inicio);


/**
 * @brief Determina a existência de um gestor na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param idGestor
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int existeGestor(Gestor* inicio, int idGestor);


/**
 * @brief Remove um gestor na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param idG
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Gestor* removerGestor(Gestor* inicio, int idG); // Remover um meio a partir do seu código


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro de texto
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarGestor(Gestor* inicio);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro binário
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarGestorBinario(Gestor* inicio);


/**
 * @brief Faz a leitura dos dados do ficheiro binário e insere-os na lista ligada
 * 
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Gestor* lerGestor();


/**
 * @brief Atualiza os dados do gestor na lista ligada
 * 
 * @param inicio
 * @param idG
 * @param novoNomeG
 * @param novaMoradaG
 * @param novaSenhaG
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Gestor* atualizarGestor(Gestor* inicio, int idG, char novoNomeG[], char novaMoradaG[], char novaSenhaG[]);