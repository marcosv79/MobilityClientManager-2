# Estruturas de Dados Avançadas (ESI)


## Controlo de versões
Durante o desenvolvimento deste projeto, foi utilizada uma ferramenta apropriada para o controlo de versões, o **GitHub**.
O código-fonte do projeto está disponível no repositório do GitHub, no seguinte link: *https://github.com/marcosv79/TP_EDA_2.git*.

## Projeto de gestão de meios de mobilidade

Este projeto implementa um sistema de gestão de meios de mobilidade, onde são é possível gerir **clientes**, **gestores** e diferentes tipos de **meios de mobilidade**.
O sistema permite realizar operações como inserir, listar, remover e atualizar dados de clientes, gestores e meios, além de permitir a realização de aluguer e devolução de meios por parte dos clientes.

## Estrutura do projeto

O projeto está dividido em vários ficheiros fonte e seus respectivos *header files*, que contêm as definições das estruturas e as assinaturas das funções implementadas:
- cliente.c e cliente.h: contêm as estruturas de dados e as funções relacionadas aos clientes, como inserir, listar, remover e atualizar dados de clientes, além de funções específicas como carregar saldo.
- gestor.c e gestor.h: contêm as estruturas de dados e as funções relacionadas aos gestores, como inserir, listar, remover e atualizar dados de gestores.
- meio.c e meio.h: contêm as estruturas de dados e as funções relacionadas aos meios de mobilidade, como inserir, listar, remover e atualizar dados de meios, além de funções para realizar operações de aluguer e devolução.
- grafo.c e grafo.h: contêm as estruturas de dados e as funções relacionadas ao grafo de localizações, e também utilizado para realizar operações de procura e listagem de meios em um determinado raio e de um determinado tipo.
- fase2.c: contém a função principal do programa, onde é realizado o menu principal do sistema e sub-menus.


## Autor

Marcos Vasconcelos