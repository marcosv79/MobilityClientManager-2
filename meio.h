#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registo
{
    int codigo; // código do meio de mobilidade elétrica
    char tipo[50];
    float bateria;
    float autonomia;
    int custo;
    int alugado;
    char localizacao[50];
    struct registo* seguinte;
} Meio;

Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, int cst, char loc[]); // Inserção de um novo registo
void listarMeios(Meio* inicio); // listar na consola o conteúdo da lista ligada
int existeMeio(Meio* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Meio* removerMeio(Meio* inicio, int cod); // Remover um meio a partir do seu código

int guardarMeios(Meio* inicio);
Meio* lerMeios();

Meio* atualizarMeio(Meio* inicio, int cod, char novoTipo[], float novaBat, float novaAut, int novoCst, char novaLoc[]);

void listarMeiosPorAutonomia(Meio* inicio);
int devolverMeio(Meio* inicio, int codigo);

int guardarMeiosBinario(Meio* inicio);
void listarMeiosPorLocalizacao(Meio * inicio);