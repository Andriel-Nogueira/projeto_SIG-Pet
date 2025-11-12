#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
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
        case 4:
            relatorio_servicos();
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
        printf("║          2 - Listagem de clientes por idade                                                  ║\n");
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
        case 2:
            listar_clientes_por_idade();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

int calcular_idade(const char *data_nascimento)
{
    int dia, mes, ano;
    sscanf(data_nascimento, "%d/%d/%d", &dia, &mes, &ano);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int idade = tm.tm_year + 1900 - ano;
    if ((tm.tm_mon + 1 < mes) || ((tm.tm_mon + 1 == mes) && (tm.tm_mday < dia)))
    {
        idade--;
    }

    return idade;
}

void listar_clientes_por_idade(void)
{
    FILE *arq_clientes;
    Clientes cli;
    int idade_filtro, encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listagem de Clientes por Idade");

    printf("Digite a idade que deseja filtrar: ");
    scanf("%d", &idade_filtro);
    getchar(); // limpa buffer

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        printf("\nNenhum cliente cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("\n╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-35s │ %-12s │ %-15s │ %-5s ║\n", "CPF", "NOME", "NASCIMENTO", "TELEFONE", "IDADE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&cli, sizeof(Clientes), 1, arq_clientes))
    {
        if (cli.status == True)
        {
            int idade = calcular_idade(cli.data_nascimento);
            if (idade == idade_filtro)
            {
                printf("║ %-15s │ %-35s │ %-12s │ %-15s │ %-5d ║\n",
                       cli.cpf, cli.nome, cli.data_nascimento, cli.telefone, idade);
                encontrou = 1;
                contador++;
            }
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum cliente com %d anos encontrado.                                                                           ║\n", idade_filtro);
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de clientes com %d anos: %d\n", idade_filtro, contador);

    fclose(arq_clientes);
    pressione_enter();
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
        case 2:
            listar_pets_por_especie();
            break;
        case 3:
            listar_pets_por_cpf();
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

void listar_pets_por_especie(void)
{
    FILE *fp;
    Pets pet;
    char especie_busca;
    int encontrou = 0;

    system("clear");
    exibir_logo();
    exibir_titulo("Listar Pets por Espécie");

    printf("╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ LEGENDA: C - Cachorro | G - Gato | P - Pássaro | O - Outro              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════╝\n\n");

    printf("Digite a espécie que deseja listar (C/G/P/O): ");
    scanf(" %c", &especie_busca);
    especie_busca = toupper(especie_busca);

    fp = fopen("pets/pets.dat", "rb");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo de pets!\n");
        pressione_enter();
        return;
    }

    printf("\n╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-30s │ %-10s ║\n", "CPF DO DONO", "NOME DO PET", "ESPÉCIE");
    printf("╠══════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&pet, sizeof(Pets), 1, fp) == 1)
    {
        if (pet.status == True && toupper(pet.especie[0]) == especie_busca)
        {
            printf("║ %-15s │ %-30s │ %-10s ║\n", pet.cpf, pet.nome, pet.especie);
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum pet encontrado para a espécie '%c'.                         ║\n", especie_busca);
    }

    printf("╚══════════════════════════════════════════════════════════════════════════╝\n");

    fclose(fp);
    printf("\nPressione ENTER para voltar...");
    getchar();
    getchar();
}

void listar_pets_por_cpf(void)
{
    FILE *arq_pets;
    Pets pet;
    char cpf_busca[15];
    int encontrou = 0;

    exibir_logo();
    exibir_titulo("Listar Pets por CPF do Dono");

    input(cpf_busca, 15, "Digite o CPF do dono: ");

    arq_pets = fopen("pets/pets.dat", "rb");
    if (arq_pets == NULL)
    {
        printf("\nNenhum pet cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("\n╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-30s │ %-10s ║\n", "NOME DO PET", "ESPÉCIE");
    printf("╠══════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&pet, sizeof(Pets), 1, arq_pets))
    {
        if (pet.status == True && strcmp(pet.cpf, cpf_busca) == 0)
        {
            printf("║ %-30s │ %-10s ║\n", pet.nome, pet.especie);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("║ Nenhum pet encontrado para o CPF informado.                                 ║\n");

    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");

    fclose(arq_pets);
    pressione_enter();
}

void relatorio_servicos(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatório de Serviços Realizados");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de serviços                                                      ║\n");
        printf("║          2 - Listagem por faixa de preços                                                    ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_servicos();
            break;
        case 2:
            listar_servicos_por_preco();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void listar_servicos_por_preco(void)
{
    FILE *arq_servicos;
    Servicos serv;
    float preco_min, preco_max, preco_atual;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listar Serviços por Faixa de Preço");

    printf("Informe o preço mínimo: ");
    scanf("%f", &preco_min);
    printf("Informe o preço máximo: ");
    scanf("%f", &preco_max);

    arq_servicos = fopen("servicos/servicos.dat", "rb");
    if (arq_servicos == NULL)
    {
        printf("Nenhum serviço cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("\n╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-30s │ %-12s ║\n", "ID", "NOME", "DESCRIÇÃO", "PREÇO (R$)");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&serv, sizeof(Servicos), 1, arq_servicos))
    {
        preco_atual = atof(serv.preco_s); // converte o preço armazenado como string para float

        if (serv.status == True && preco_atual >= preco_min && preco_atual <= preco_max)
        {
            printf("║ %-5d │ %-35s │ %-30s │ %-12s ║\n",
                   serv.id,
                   serv.nome,
                   serv.desc,
                   serv.preco_s);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum serviço encontrado nessa faixa de preço.                                                              ║\n");
    }

    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de serviços listados: %d\n", contador);

    fclose(arq_servicos);
    pressione_enter();
    getchar();
}
