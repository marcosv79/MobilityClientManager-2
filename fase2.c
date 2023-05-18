#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestor.h"

#include "grafo.h"

int menuLoginGestor()
{
    Meio* meios = NULL;
    int op, cod, cst, novoCst;
    float bat, aut, novaBat, novaAut;
    char tipo[50], novoTipo[50], loc[50], novaLoc[50];
    do
    {
        printf("========== GESTOR ==========\n");
        printf("1 - Inserir meio\n");
        printf("2 - Listar meios\n");
        printf("3 - Listar meios por autonomia decrescente\n");
        printf("4 - Listar meios por localizacao\n");
        printf("5 - Remover meio\n");
        printf("6 - Alterar dados de um meio\n");
        printf("7 - Ler meios\n");
        printf("0 - Sair\n");
        printf("Opcao: \n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
            	system("cls");
                printf("Insira o codigo: \n");
                scanf("%d", &cod);
                scanf("%*c");
                printf("Insira o tipo de meio de mobilidade: \n");
                scanf("%[^\n]s", tipo);
                printf("Insira o nivel de bateria: \n");
                scanf("%f", &bat);
                printf("Insira a autonomia: \n");
                scanf("%f", &aut);
                printf("Insira o custo do meio de mobilidade: \n");
                scanf("%d", &cst);
                scanf("%*c");
                printf("Insira a localizacao do meio de mobilidade: ");
                scanf("%[^\n]s", loc);
                meios = inserirMeio(meios, cod, tipo, bat, aut, cst, loc);
                guardarMeios(meios);
                guardarMeiosBinario(meios);
                break;
            case 2:
            	system("cls");
                listarMeios(meios);
                break;
            case 3:
            	system("cls");
            	listarMeiosPorAutonomia(meios);
            	break;
            case 4:
                system("cls");
                listarMeiosPorLocalizacao(meios);
                break;
            case 5:
            	system("cls");
                printf("Codigo do meio de mobilidade a remover?\n");
                scanf("%d", &cod);
                meios = removerMeio(meios, cod);
                guardarMeios(meios);
                break;
            case 6:
            	system("cls");
			    printf("Codigo do meio a alterar?\n");
			    scanf("%d", &cod);
			    printf("Insira o novo tipo: ");
			    scanf("%s", novoTipo);
			    printf("Insira a nova bateria: ");
			    scanf("%f", &novaBat);
			    printf("Insira a nova autonomia: ");
			    scanf("%f", &novaAut);
			    printf("Insira o novo custo: \n");
			    scanf("%d", &novoCst);
                printf("Insira a nova localizacao: \n");
			    scanf("%s", novaLoc);
			    meios = atualizarMeio(meios, cod, novoTipo, novaBat, novaAut, novoCst, novaLoc);
			    guardarMeios(meios);
			    break;
            case 7:
                meios = lerMeios();
                break;
        }
    } while (op != 0);

    return op;
}

void loginGestor(Gestor* inicio){
    int idGestor, existe = 0;
    char senha[50];
    Gestor* atual = inicio;
    printf("Insira o seu ID de gestor: ");
    scanf("%d", &idGestor);
    while (atual != NULL)
    {
        if (atual->idGestor == idGestor)
        {
           existe = 1;
           break;
        }
        atual = atual->seguinte;
    }
    if (!existe)
    {
        printf("Gestor com o ID %d nao encontrado\n", idGestor);
        return;
    }
    printf("Insira a sua senha: ");
    scanf("%s", senha);
    printf("Bem-vindo!\n");
    if (strcmp(atual->senhaGestor, senha) != 0) {
        printf("Senha incorreta\n");
        return;
    }
    system("pause");
    menuLoginGestor();
}

int alugarMeio(Meio* inicio, int codigo, int saldoCliente) {
    Meio* atual = inicio;
    FILE* fp;

    fp = fopen("meios.txt", "r");

    if (fp == NULL) {
        printf("O arquivo meios.txt nao foi encontrado.\n");
        return 0;
    }

    // Percorre a lista de meios
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (atual->alugado == 0) {
                // Lê a linha inteira do arquivo
                char linha[100];
                while (fgets(linha, 100, fp)) {
                    // Separa o código e o custo da linha (separados por ;)
                    int cod = atoi(strtok(linha, ";")); // strtok para separar os valores
                    int custo = atoi(strtok(NULL, ";"));
                    if (cod == codigo) {
                        printf("Custo do meio: %d\n", custo);
                        if (saldoCliente >= custo) {
                            atual->alugado = 1; // Atualiza o estado do meio 
                            saldoCliente -= custo; // Atualiza o saldo do cliente
                            printf("Meio alugado com sucesso! Saldo atual: %d.\n", saldoCliente);
                            fclose(fp);
                            return 1;
                        } else {
                            printf("Saldo insuficiente para alugar o meio.\n");
                            fclose(fp);
                            return 0;
                        }
                    }
                }
                printf("Nao foi possivel encontrar o meio com o codigo %d.\n", codigo);
                fclose(fp);
                return 0;
            } else {
                printf("O meio escolhido nao esta disponivel para aluguer.\n");
                fclose(fp);
                return 0;
            }
        }
        atual = atual->seguinte;
    }

    printf("Nao foi possivel encontrar o meio com o codigo %d.\n", codigo);
    fclose(fp);
    return 0;
}

int menuLoginCliente(int saldoCliente) {
    Meio* inicio = lerMeios(); // Ler meios disponíveis
    Cliente* cliente = malloc(sizeof(Cliente)); // Aloca a memória para a estrutura Cliente
    cliente->saldoCliente = saldoCliente;
    printf("Saldo do cliente: %d\n", cliente->saldoCliente);
    int op, codigo;
    do {
        printf("========== CLIENTE ==========\n");
        printf("1 - Alugar meio\n");
        printf("2 - Devolver meio\n");
        printf("3 - Gerar grafo\n");
        printf("4 - Listar localizações num determinado raio\n");
        printf("0 - Sair\n");
        printf("Opcao:\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Digite o codigo do meio a ser alugado: ");
                scanf("%d", &codigo);

                if(alugarMeio(inicio, codigo, cliente->saldoCliente)) {
                    printf("Meio alugado com sucesso!\n");
                } else {
                    printf("Erro ao alugar meio.\n");
                }
                break;
            case 2: 
                printf("Digite o codigo do meio a ser devolvido: ");
                scanf("%d", &codigo);
                if (devolverMeio(inicio, codigo)) {
                    printf("Meio devolvido com sucesso.\n");
                } else {
                    printf("Erro ao devolver o meio.\n");
                }
                break;
            case 3:
                Grafo grafo;
                cliente = lerClientes();
                inicio = lerMeios();
                buscaLocalizacoes(cliente,inicio);
                inicializarGrafo(&grafo);
                criarGrafoLocalizacoes(&grafo);
                imprimirGrafo(&grafo);
                break;
            case 4:
                int raio;
                printf("Digite o raio desejado: ");
                scanf("%d", &raio);
                listarLocalizacoesPorRaio(&grafo, cliente->locCliente, raio);
                break;
        }
    } while (op != 0);

    return op;
}

void loginCliente(Cliente* inicio) {
    int nifCliente, existe = 0;
    int saldoCliente = 0;
    char senha[50];
    Cliente* atual = inicio;
    printf("Insira o seu NIF de cliente: ");
    scanf("%d", &nifCliente);
    while (atual != NULL) {
        if (atual->nifCliente == nifCliente) {
            existe = 1;
            saldoCliente = atual->saldoCliente; 
            break;
        }
        atual = atual->seguinte;
    }
    if (!existe) {
        printf("Cliente com o NIF %d nao encontrado\n", nifCliente);
        return;
    }
    printf("Insira a sua senha: ");
    scanf("%s", senha);
    printf("Bem-vindo!\n");
    if (strcmp(atual->senhaCliente, senha) != 0) {
        printf("Senha incorreta\n");
        return;
    }
    system("pause");
    menuLoginCliente(saldoCliente); 
}

int menuPrincipal(Meio* meios)
{
    Grafo grafo;
    Gestor* gestores = NULL;
    int idG;
    char nomeG[50], novoNomeG[50], moradaG[50], novaMoradaG[50], senhaG[50], novaSenhaG[50];
    Cliente* clientes = NULL;
    int nifC, saldoC, novoSaldoC;
    char nomeC[50], novoNomeC[50], moradaC[50], novaMoradaC[50], senhaC[50], novaSenhaC[50], locC[50], novaLocC[50];
    int op;

    do {
        printf("========== GESTOR ==========\n");
        printf("1 - Inserir gestor\n");
        printf("2 - Listar gestores\n");
        printf("3 - Remover gestor\n");
        printf("4 - Login gestor\n");
        printf("5 - Alterar dados de um gestor\n");
        printf("6 - Ler gestores\n");
        printf("\n");
        printf("========== CLIENTE ==========\n");
        printf("7 - Inserir cliente\n");
        printf("8 - Listar clientes\n");
        printf("9 - Remover cliente\n");
        printf("10 - Login cliente\n");
        printf("11 - Alterar dados de um cliente\n");
        printf("12 - Carregar saldo de um cliente\n");
        printf("13 - Ler clientes\n");
        printf("\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                system("cls");
                printf("ID do gestor: \n");
                scanf("%d", &idG);
                printf("Nome do gestor: \n");
                scanf("%s", nomeG);
                printf("Morada do gestor: \n");
                scanf("%s", moradaG);
                printf("Senha do gestor: \n");
                scanf("%s", senhaG);
                gestores = inserirGestor(gestores, idG, nomeG, moradaG, senhaG);
                guardarGestor(gestores);
                guardarGestorBinario(gestores);
                break;
            case 2:
                system("cls");
                listarGestor(gestores);
                break;
            case 3:
                system("cls");
                printf("ID do gestor a remover?\n");
                scanf("%d", &idG);
                gestores = removerGestor(gestores, idG);
                guardarGestor(gestores);
                guardarGestorBinario(gestores);
                break;
            case 4:
            	loginGestor(gestores);
            	break;
            case 5:
			    system("cls");
			    printf("ID do gestor a alterar?\n");
			    scanf("%d", &idG);
			    printf("Insira o novo nome: ");
			    scanf("%s", novoNomeG);
			    printf("Insira a nova morada: ");
			    scanf("%s", novaMoradaG);
			    printf("Insira a nova senha: ");
			    scanf("%s", novaSenhaG);
			    gestores = atualizarGestor(gestores, idG, novoNomeG, novaMoradaG, novaSenhaG);
			    guardarGestor(gestores);
                guardarGestorBinario(gestores);
			    break;
            case 6:
                gestores = lerGestor();
                break;
            case 7:
                system("cls");
                printf("NIF do cliente: \n");
                scanf("%d", &nifC);
                printf("Saldo do cliente: \n");
                scanf("%d", &saldoC);
                printf("Nome do cliente: \n");
                scanf("%s", nomeC);
                printf("Morada do cliente: \n");
                scanf("%s", moradaC);
                printf("Senha do cliente: \n");
                scanf("%s", senhaC);
                printf("Localização do cliente: \n");
                scanf("%s", locC);
                clientes = inserirCliente(clientes, nifC, saldoC, nomeC, moradaC, senhaC, locC);
                guardarClientes(clientes);
                guardarClienteBinario(clientes);
                break;
            case 8:
                system("cls");
                listarCliente(clientes);
                break;
            case 9:
                system("cls");
                printf("NIF do cliente a remover?\n");
                scanf("%d", &nifC);
                clientes = removerCliente(clientes, nifC);
                guardarClientes(clientes);
                guardarClienteBinario(clientes);
                break;
            case 10:
            	loginCliente(clientes);
            	break;
            case 11:
			    system("cls");
			    printf("NIF do cliente a alterar?\n");
			    scanf("%d", &nifC);
			    printf("Insira o novo nome: ");
			    scanf("%s", novoNomeC);
			    printf("Insira a nova morada: ");
			    scanf("%s", novaMoradaC);
			    printf("Insira a nova senha: ");
			    scanf("%s", novaSenhaC);
                printf("Insira a nova localização: ");
			    scanf("%s", novaLocC);
			    clientes = atualizarCliente(clientes, nifC, novoNomeC, novaMoradaC, novaSenhaC, novaLocC);
			    guardarClientes(clientes);
                guardarClienteBinario(clientes);
			    break;
            case 12:
                system("cls");
                printf("NIF do cliente a carregar o saldo?\n");
                scanf("%d", &nifC);
                printf("Valor a carregar: ");
                scanf("%d", &novoSaldoC);
                clientes = carregarSaldo(clientes, nifC, novoSaldoC);
                guardarClientes(clientes);
                guardarClienteBinario(clientes);
                break;
            case 13:
                clientes = lerClientes();
                break;
            case 0:
            	printf("A sair...\n");
            	break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (op != 0);

    return op;
}

int main(Meio* meios)
{
	menuPrincipal(meios);
	return 0;
}
