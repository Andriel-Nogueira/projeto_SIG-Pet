#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../clientes/clientes.h"
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
        printf("║          1 - Listagem geral de clientes                                                      ║\n");
        printf("║          2 - Listagem geral de produtos                                                      ║\n");
        printf("║          3 - Listagem geral de serviços                                                      ║\n");
        printf("║          4 - Listagem geral de vendas                                                        ║\n");
        printf("║          5 - Listagem geral de agendamentos                                                  ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_clientes();
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            listar_servicos();
            break;
        case 4:
            listar_vendas();
            break;
        case 5:
            listar_agend();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}
