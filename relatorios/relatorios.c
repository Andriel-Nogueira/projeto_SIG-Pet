#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../clientes/clientes.h"
#include "../pets/pets.h"
#include "../produtos/produtos.h"
#include "../servicos/servicos.h"
#include "../vendas/vendas.h"
#include "../agendamentos/agendamentos.h"
#include "relatorios.h"
#include "../utilitarios/utilitarios.h"

void m_relatorios(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Relatórios");

        printf("║                                                                                              ║\n");
        printf("║          1 - Relatórios de Clientes                                                          ║\n");
        printf("║          2 - Relatórios de Pets                                                              ║\n");
        printf("║          3 - Relatórios de Produtos                                                          ║\n");
        printf("║          4 - Relatórios de Serviços                                                          ║\n");
        printf("║          5 - Relatórios de Vendas                                                            ║\n");
        printf("║          6 - Relatórios de Agendamentos                                                      ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            relatorio_clientes();
            break;
        case 2:
            relatorio_pets();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void relatorio_clientes(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatórios de Clientes");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de clientes                                                      ║\n");
        printf("║          3 - Listagem de clientes por idade                                                  ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_clientes();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void relatorio_pets(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatórios de Pets");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de pets                                                          ║\n");
        printf("║          2 - Listagem por espécie                                                            ║\n");
        printf("║          3 - Listagem por cliente (CPF do dono)                                              ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_pets();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void listar_pets(void)
{
    FILE *arq;
    Pets pet;
    int encontrou = 0, contador = 0;

    system("clear");
    exibir_logo();
    exibir_titulo("Listagem Geral de Pets");

    arq = fopen("pets/pets.dat", "rb");
    if (arq == NULL)
    {
        printf("\nNenhum pet cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-25s │ %-15s │ %-15s ║\n", "Nome do Pet", "Espécie", "CPF do Dono");
    printf("╠═══════╪═════════════════════════════════╪═════════════════╪═════════════════╣\n");

    while (fread(&pet, sizeof(Pets), 1, arq))
    {
        if (pet.status == True)
        {
            printf("║ %-25s │ %-15s │ %-15s ║\n",
                   pet.nome,
                   pet.especie,
                   pet.cpf);
            encontrou = 1;
            contador++;
        }
    }

    fclose(arq);

    if (!encontrou)
    {
        printf("║ Nenhum pet ativo encontrado.                                                  ║\n");
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de pets listados: %d\n", contador);

    pressione_enter();
}
