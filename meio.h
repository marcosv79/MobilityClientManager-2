/*****************************************************************
 * @file   meio.h
 * @brief  Estrutura para representar meios e suas funções
 * @author Marcos Vasconcelos
 * @date   Maio 2023
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registo
{
    int codigo;
    char tipo[50];
    float bateria;
    float autonomia;
    int custo;
    int alugado;
    char locMeio[50];
    struct registo* seguinte;
} Meio;


/**
 * @brief Insere um novo meio na lista ligada
 * 
 * @param inicio
 * @param cod
 * @param tipo
 * @param bat
 * @param aut
 * @param cst
 * @param locM
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, int cst, char locM[]);


/**
 * @brief Lista na consola o conteúdo da lista ligada
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarMeios(Meio* inicio);


/**
 * @brief Determina a existência de um meio na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param codigo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int existeMeio(Meio* inicio, int codigo);


/**
 * @brief Remove um meio na lista ligada a partir do seu código
 * 
 * @param inicio
 * @param cod
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Meio* removerMeio(Meio* inicio, int cod);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro de texto
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarMeios(Meio* inicio);


/**
 * @brief Guarda o conteúdo da lista ligada num ficheiro binário
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int guardarMeiosBinario(Meio* inicio);


/**
 * @brief Faz a leitura dos dados do ficheiro binário e insere-os na lista ligada
 * 
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Meio* lerMeios();


/**
 * @brief Atualiza os dados do meio na lista ligada
 * 
 * @param inicio
 * @param cod
 * @param novoTipo
 * @param novaBat
 * @param novaAut
 * @param novoCst
 * @param novaLocM
 * @return
 * @author Marcos Vasconcelos
 * 
*/
Meio* atualizarMeio(Meio* inicio, int cod, char novoTipo[], float novaBat, float novaAut, int novoCst, char novaLocM[]);


/**
 * @brief Cria uma nova lista de forma ordenada para listar os meios por autonomia decrescente
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarMeiosPorAutonomia(Meio* inicio);


/**
 * @brief Devolve o meio que foi anteriormente alugado
 * 
 * @param inicio
 * @param codigo
 * @return
 * @author Marcos Vasconcelos
 * 
*/
int devolverMeio(Meio* inicio, int codigo);


/**
 * @brief Lista os meios existentes numa determinada localização
 * 
 * @param inicio
 * @return
 * @author Marcos Vasconcelos
 * 
*/
void listarMeiosPorLocalizacao(Meio * inicio);


void listarMeiosCargaBaixa(Meio* inicio);