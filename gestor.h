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


Gestor* inserirGestor(Gestor* inicio, int idG, char nomeG[], char moradaG[], char senhaG[]); // Inserção de um novo registo
void listarGestor(Gestor* inicio); // listar na consola o conteúdo da lista ligada
int existeGestor(Gestor* inicio, int idGestor); // Determinar existência do 'codigo' na lista ligada 'inicio'
Gestor* removerGestor(Gestor* inicio, int idG); // Remover um meio a partir do seu código

int guardarGestor(Gestor* inicio);
Gestor* lerGestor();

Gestor* atualizarGestor(Gestor* inicio, int idG, char novoNomeG[], char novaMoradaG[], char novaSenhaG[]);

int guardarGestorBinario(Gestor* inicio);