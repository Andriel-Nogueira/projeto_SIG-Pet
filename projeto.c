//////////////////////////////////////////////////////////////////////////////////////////////////
//    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------. ///
//  ,-.'-  _\  /==/_ /   _.='.'-,  \                    .-`.' ,`.    ,-.--` , \ /==/,  -   , -\ //
// /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \  |==|-  _.-` \==\.-.  - ,-./ //
// \==\  \    |==|  |  /==/ -   .-'   /==/,  -   , -\ |==| _ .=. |  |==|   `.-.  `--`\==\- | /////
//  \==\ -\   |==|- |  |==|_   /_,-.  \==\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \==\_ | ////
//  _\==\ ,\  |==| ,|  |==|  , \_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- | ////
// /==/\/ _ | |==|- |  \==\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, | ////
// \==\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/ ////
//  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--` ////
//////////////////////////////////////////////////////////////////////////////////////////////////
///                       Universidade Federal do Rio Grande do Norte                          ///
///                          Centro de Ensino Superior do Seridó                               ///
///                            Disciplina DCT1106 -- Programação                               ///
///                        Projeto Sistema de Atendimento de Pet Shop                          ///
///              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista         ///
//////////////////////////////////////////////////////////////////////////////////////////////////
///                                         Versão 0.2.0                                          ///
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "clientes/clientes.h"
#include "servicos/servicos.h"
#include "agendamentos/agendamentos.h"
#include "produtos/produtos.h"
#include "vendas/vendas.h"
#include "relatorios/relatorios.h"
#include "utilitarios/utilitarios.h"

// Funções Principais
void m_principal(void);
void t_sobre(void);
void t_equipe(void);

void t_final(void);

// Versão atual

char versao[10] = "0.2.0";

// Programa Principal
int main(void)
{
    int op;
    system("clear");
    do
    {
        system("clear");
        printf("\n");
        printf("╔═════════════════════════════════════╗\n");
        printf("║           Sistema SIG-Pet           ║\n");
        printf("╠═════════════════════════════════════╣\n");
        printf("║ 1 - Menu Principal                  ║\n");
        printf("║ 2 - Sobre o sistema                 ║\n");
        printf("║ 3 - Equipe de desenvolvimento       ║\n");
        printf("║ 0 - Sair                            ║\n");
        printf("╚═════════════════════════════════════╝\n");
        printf("\n");
        op = escolha();
        switch (op)
        {
        case 1:
            m_principal();
            break;
        case 2:
            t_sobre();
            break;
        case 3:
            t_equipe();
            break;
        case 0:
            t_final();
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);

    return 0;
}

void m_principal(void)
{
    int op;
    system("clear");

    do
    {
        exibir_logo();
        exibir_titulo("Menu Principal");

        printf("║                                                                                              ║\n");
        printf("║          1 - Módulo Clientes                                                                 ║\n");
        printf("║          2 - Módulo Serviços                                                                 ║\n");
        printf("║          3 - Módulo Agendamentos                                                             ║\n");
        printf("║          4 - Módulo Produtos                                                                 ║\n");
        printf("║          5 - Módulo Vendas                                                                   ║\n");
        printf("║          6 - Módulo Relatórios                                                               ║\n");
        printf("║          0 - Sair                                                                            ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        op = escolha();
        switch (op)
        {
        case 1:
            m_clientes();
            break;
        case 2:
            m_servicos();
            break;
        case 3:
            m_agendamento();
            break;
        case 4:
            m_produtos();
            break;
        case 5:
            m_vendas();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void t_sobre(void)
{
    exibir_logo();
    exibir_titulo("Sobre o Sistema");

    printf("║                                         Versão %s                                         ║\n", versao);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║          Este é um sistema de atendimento para Pet Shop, desenvolvido como parte de uma      ║\n");
    printf("║          atividade acadêmica. O sistema é dividido em módulos que permitem o gerenciamento   ║\n");
    printf("║          de clientes, serviços, produtos, vendas, estoque e relatórios.                      ║\n");
    printf("║          O objetivo é proporcionar uma experiência de aprendizado prática e funcional,       ║\n");
    printf("║          permitindo que os usuários gerenciem eficientemente as operações de um Pet Shop.    ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...\n");
    getchar();
}

void t_equipe(void)
{
    exibir_logo();
    exibir_titulo("Equipe de Desenvolvimento");

    printf("║                                         Versão %s                                         ║\n", versao);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║          Equipe de Desenvolvimento:                                                          ║\n");
    printf("║          - Andriel Nogueira                                                                  ║\n");
    printf("║            Email: andriel.pereiraufrn@gmail.com                                              ║\n");
    printf("║            GitHub: @Andriel-Nogueira                                                         ║\n");
    printf("║          - Jefferson Willame                                                                  ║\n");
    printf("║            Email: jeffersonwillamern@gmail.com                                               ║\n");
    printf("║            GitHub: @JeffWill                                                                 ║\n");
    printf("║          - Repositório da Equipe: https://github.com/Andriel-Nogueira/projeto_SIG-Pet.git    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...\n");
    getchar();
}

void t_final(void)
{
    exibir_logo();
    exibir_titulo("Finalizando...");

    printf("║                                          Versão %s                                        ║\n", versao);
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║          Obrigado por utilizar o Sistema SIG-Pet!                                            ║\n");
    printf("║          Esperamos ter proporcionado uma ótima experiência!                                  ║\n");
    printf("║          Volte Sempre!                                                                       ║\n");
    printf("║            __    __                                                ||      _,,,---,,_        ║\n");
    printf("║          o-''))_____\\                                        ZzZzz /,`.-'`'    -.  ;-;;,_    ║\n");
    printf("║          z--__/ * * * )                                           |,4-  ) )-,_. ,/ (  `'-'   ║\n");
    printf("║          c_c__/-c____/                                           '---''(_/--'  `-'/_)        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}
