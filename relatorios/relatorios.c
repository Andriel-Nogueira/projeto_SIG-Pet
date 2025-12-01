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
        exibir_titulo("Menu Relatorios");

        printf("║                                                                                              ║\n");
        printf("║          1 - Relatorios de Clientes                                                          ║\n");
        printf("║          2 - Relatorios de Pets                                                              ║\n");
        printf("║          3 - Relatorios de Produtos                                                          ║\n");
        printf("║          4 - Relatorios de Serviços                                                          ║\n");
        printf("║          5 - Relatorios de Vendas                                                            ║\n");
        printf("║          6 - Relatorios de Agendamentos                                                      ║\n");
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
        case 3:
            relatorio_produtos();
            break;
        case 4:
            relatorio_servicos();
            break;
        case 5:
            relatorio_vendas();
            break;
        case 6:
            relatorio_agendamentos();
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
        exibir_titulo("Relatorios de Clientes");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de clientes                                                      ║\n");
        printf("║          2 - Listagem de clientes por idade                                                  ║\n");
        printf("║          3 - Listagem Ordenada por nome                                                      ║\n");
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
        case 3:
            relatorio_clientes_ordenados();
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
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listagem de Clientes por Idade");

    int idade_filtro = tela_obter_idade();

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        printf("\nNenhum cliente cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-35s │ %-12s │ %-13s │ %-5s ║\n", "CPF", "NOME", "NASCIMENTO", "TELEFONE", "IDADE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&cli, sizeof(Clientes), 1, arq_clientes))
    {
        if (cli.status == True)
        {
            int idade = calcular_idade(cli.data_nascimento);
            if (idade == idade_filtro)
            {
                printf("║ %-15s │ %-35s │ %-12s │ %-13s │ %-5d ║\n",
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

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de clientes com %d anos: %d\n", idade_filtro, contador);

    fclose(arq_clientes);
    pressione_enter();
}

int tela_obter_idade(void)
{
    char idade_str[10];
    do
    {
        input(idade_str, 10, "Digite a idade que deseja filtrar:");
    } while (!validar_numero(idade_str));
    return atoi(idade_str);
}

void relatorio_pets(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatorios de Pets");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de pets                                                          ║\n");
        printf("║          2 - Listagem por espécie                                                            ║\n");
        printf("║          3 - Listagem por cliente (CPF do dono)                                              ║\n");
        printf("║          4 - Listagem geral de pet por cliente                                               ║\n");
        printf("║          5 - Listagem ordenada por nome do pet                                               ║\n");
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
            listar_pets_por_cpf_tela();
            break;
        case 4:
            relatorio_pets_por_clientes();
            break;
        case 5:
            relatorio_pets_ordenados();
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
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-30s │ %-10s  │ %-38s ║\n", "ID", "NOME DO PET", "ESPÉCIE", "CPF DO DONO");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&pet, sizeof(Pets), 1, arq))
    {
        if (pet.status == True)
        {
            printf("║ %-5d │ %-30s │ %-10s │ %-38s ║\n",
                   pet.id,
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
        printf("║ Nenhum pet ativo encontrado.                                                                                   ║\n");
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

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
    exibir_titulo("Listar Pets por Especie");

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║               LEGENDA: C - Cachorro | G - Gato | P - Pássaro | O - Outro                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n\n");

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

    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║ %-15s │ %-30s │ %-42s ║\n", "CPF DO DONO", "NOME DO PET", "ESPÉCIE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&pet, sizeof(Pets), 1, fp) == 1)
    {
        if (pet.status == True && toupper(pet.especie[0]) == especie_busca)
        {
            printf("║ %-15s │ %-30s │ %-41s ║\n", pet.cpf, pet.nome, pet.especie);
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum pet encontrado para a espécie '%c'.                         ║\n", especie_busca);
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    fclose(fp);
    printf("\nPressione ENTER para voltar...");
    getchar();
    getchar();
}

void listar_pets_por_cpf_tela(void)
{
    char cpf_busca[16];
    exibir_logo();
    exibir_titulo("Listagem de Pets por CPF do Dono");

    ler_cpf(cpf_busca);

    if (!verificar_cliente_cadastrado(cpf_busca))
    {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
        pressione_enter();
        return;
    }

    listar_pets_por_cpf(cpf_busca);
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
        printf("║          3 - Listagem ordenada por preço                                                     ║\n");
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
        case 3:
            relatorio_servicos_ordenados();
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
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listar Serviços por Faixa de Preço");

    float preco_min = tela_obter_preco_minimo();
    float preco_max = tela_obter_preco_maximo();

    arq_servicos = fopen("servicos/servicos.dat", "rb");
    if (arq_servicos == NULL)
    {
        printf("Nenhum serviço cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-30s │ %-12s ║\n", "ID", "NOME", "DESCRIÇÃO", "PREÇO (R$)");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    while (fread(&serv, sizeof(Servicos), 1, arq_servicos))
    {
        float preco_atual = atof(serv.preco_s); // converte o preço armazenado como string para float
        preco_atual = atof(serv.preco_s);       // converte o preço armazenado como string para float

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

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de serviços listados: %d\n", contador);

    fclose(arq_servicos);
    pressione_enter();
}

void relatorio_produtos(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatorios de Produtos");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de produtos                                                      ║\n");
        printf("║          2 - Listagem por faixa de preço                                                     ║\n");
        printf("║          3 - Listagem ordenada por preços                                                    ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_produtos_geral();
            break;
        case 2:
            listar_produtos_por_faixa_de_preco();
            break;
        case 3:
            relatorio_produtos_ordenados();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void listar_produtos_geral(void)
{
    FILE *arq_produtos;
    Produtos prod;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listagem Geral de Produtos");

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("\nNenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-12s │ %-32s ║\n", "ID", "NOME", "PREÇO (R$)", "ESTOQUE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    while (fread(&prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (prod.status == True)
        {
            printf("║ %-5d │ %-35s │ %-12.2f │ %-31.2f ║\n", prod.id, prod.nome, prod.preco, prod.quantidade);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum produto ativo encontrado.                                                               ║\n");
    }
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de produtos listados: %d\n", contador);

    fclose(arq_produtos);
    pressione_enter();
}

void listar_produtos_por_faixa_de_preco(void)
{
    FILE *arq_produtos;
    Produtos prod;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listar Produtos por Faixa de Preco");

    float preco_min = tela_obter_preco_minimo();
    float preco_max = tela_obter_preco_maximo();

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("\nNenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-12s │ %-32s ║\n", "ID", "NOME", "PREÇO (R$)", "ESTOQUE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    while (fread(&prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (prod.status == True && prod.preco >= preco_min && prod.preco <= preco_max)
        {
            printf("║ %-5d │ %-35s │ %-12.2f │ %-31.2f ║\n", prod.id, prod.nome, prod.preco, prod.quantidade);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
        printf("║ Nenhum produto encontrado nessa faixa de preço.                                          ║\n");

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de produtos na faixa de preço: %d\n", contador);

    fclose(arq_produtos);
    pressione_enter();
}

void relatorio_agendamentos(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatorios de Agendamentos");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de agendamentos                                                  ║\n");
        printf("║          2 - Listagem de agendamentos por data (filtro)                                      ║\n");
        printf("║          3 - Listagem de agendamentos ordenada por data                                      ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_agendamentos_geral();
            break;
        case 2:
            listar_agendamentos_por_data();
            break;
        case 3:
            relatorio_agendamentos_ordenados();
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void listar_agendamentos_geral(void)
{
    FILE *arq_agendamentos;
    Agendamentos agend;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listagem Geral de Agendamentos");

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        printf("\nNenhum agendamento cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-25s │ %-20s │ %-20s │ %-12s │ %-8s ║\n",
           "CPF", "PET (ID)", "NOME DO PET", "SERVIÇO", "DATA", "HORA");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    while (fread(&agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (agend.status == True)
        {
            // Buscar PET
            Pets *pet = buscar_pet_id(atoi(agend.id_pet));
            char nome_pet_temp[31] = "Pet não encontrado";
            if (pet != NULL)
            {
                strncpy(nome_pet_temp, pet->nome, 30);
                free(pet);
            }

            // Buscar SERVIÇO
            Servicos *serv = buscar_servico_por_id(atoi(agend.id_servico));
            char nome_serv_temp[41] = "Serviço não encontrado";
            if (serv != NULL)
            {
                strncpy(nome_serv_temp, serv->nome, 40);
                free(serv);
            }

            printf("║ %-15s │ %-25s │ %-20s │ %-20s │ %-12s │ %-8s ║\n",
                   agend.cpf,
                   agend.id_pet,
                   nome_pet_temp,
                   nome_serv_temp,
                   agend.data,
                   agend.hora);

            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
        printf("║ Nenhum agendamento ativo encontrado.                                                                            ║\n");

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de agendamentos listados: %d\n", contador);

    fclose(arq_agendamentos);
    pressione_enter();
}

void relatorio_vendas(void)
{
    int op;
    do
    {
        system("clear");
        exibir_logo();
        exibir_titulo("Relatorios de Vendas");

        printf("║                                                                                              ║\n");
        printf("║          1 - Listagem geral de vendas                                                        ║\n");
        printf("║          2 - Listagem por faixa de preço                                                     ║\n");
        printf("║          3 - Relatório de vendas completo                                                    ║\n");
        printf("║          4 - Listagem ordenada por data (crescente)                                            ║\n");
        printf("║          5 - Listagem de venda decrescente (lista invertida)                                  ║\n");
        printf("║          0 - Voltar                                                                          ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

        op = escolha();

        switch (op)
        {
        case 1:
            listar_vendas_geral();
            break;
        case 2:
            listar_vendas_por_faixa_de_preco();
            break;
        case 3:
            relatorio_vendas_detalhado();
            break;
        case 4:
            relatorio_vendas_ordenadas();
            break;
        case 5:
            relatorio_vendas_decrescente();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void listar_vendas_geral(void)
{
    FILE *arq_vendas;
    Venda venda;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listagem Geral de Vendas");

    arq_vendas = fopen("vendas/vendas.dat", "rb");
    if (arq_vendas == NULL)
    {
        printf("Nenhuma venda registrada ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-15s │ %-30s | %-12s │ %-18s ║\n", "ID", "CPF CLIENTE", "NOME CLIENTE", "DATA", "VALOR TOTAL (R$)");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    while (fread(&venda, sizeof(Venda), 1, arq_vendas))
    {
        if (venda.status == True)
        {
            Clientes *cli = buscar_cliente_por_cpf(venda.cpf_cliente);
            printf("║ %-5d │ %-15s │ %-30s | %-12s │ %-18.2f ║\n", venda.id, venda.cpf_cliente, cli->nome, venda.data, venda.valor_total);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
        printf("║ Nenhuma venda ativa encontrada.                                                                               ║\n");

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de vendas listadas: %d\n", contador);

    fclose(arq_vendas);
    pressione_enter();
}

void listar_vendas_por_faixa_de_preco(void)
{
    FILE *arq_vendas;
    Venda venda;
    int encontrou = 0, contador = 0;

    exibir_logo();
    exibir_titulo("Listar Vendas por Faixa de Preco");

    float preco_min = tela_obter_preco_minimo();
    float preco_max = tela_obter_preco_maximo();

    arq_vendas = fopen("vendas/vendas.dat", "rb");
    if (arq_vendas == NULL)
    {
        printf("Nenhuma venda cadastrada ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-15s │ %-30s | %-12s │ %-18s ║\n", "ID", "CPF CLIENTE", "NOME CLIENTE", "DATA", "VALOR TOTAL (R$)");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    while (fread(&venda, sizeof(Venda), 1, arq_vendas))
    {
        if (venda.status == True && venda.valor_total >= preco_min && venda.valor_total <= preco_max)
        {
            Clientes *cli = buscar_cliente_por_cpf(venda.cpf_cliente);
            printf("║ %-5d │ %-15s │ %-30s | %-12s │ %-18.2f ║\n", venda.id, venda.cpf_cliente, cli->nome, venda.data, venda.valor_total);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
        printf("║ Nenhuma venda encontrada nessa faixa de preço.                                               ║\n");

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de vendas na faixa de preço: %d\n", contador);

    fclose(arq_vendas);
    pressione_enter();
}

float tela_obter_preco_minimo(void)
{
    char preco_str[20];
    do
    {
        input(preco_str, 20, "Informe o preço mínimo:");
    } while (!validar_float(preco_str));
    return atof(preco_str);
}

float tela_obter_preco_maximo(void)
{
    char preco_str[20];
    do
    {
        input(preco_str, 20, "Informe o preço máximo:");
    } while (!validar_float(preco_str));
    return atof(preco_str);
}

int tela_obter_mes(void)
{
    char mes_str[4]; // Aumentado para comportar 2 dígitos, \n e \0
    int mes;
    do
    {
        input(mes_str, 4, "Informe o mês (1-12):");
        if (!validar_numero(mes_str) || (mes = atoi(mes_str)) < 1 || mes > 12)
        {
            printf("\nMês inválido! Por favor, digite um número entre 1 e 12.\n");
            mes = 0; // Força a repetição do loop
        }
    } while (mes == 0);
    return mes;
}

void listar_agendamentos_por_data(void)
{
    FILE *arq_agendamentos;
    Agendamentos agend;
    int encontrou = 0, contador = 0;
    int mes_busca = tela_obter_mes();

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int ano_atual = tm.tm_year + 1900;

    exibir_logo();
    exibir_titulo("Listar agendamentos por data");

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        printf("\nNenhum agendamento cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    // Verificação prévia para saber se existe algum agendamento no mês/ano
    int existe_agendamento_no_mes = 0;
    while (fread(&agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (agend.status == True)
        {
            int mes_agend, ano_agend;
            sscanf(agend.data, "%*d/%d/%d", &mes_agend, &ano_agend);
            if (mes_agend == mes_busca && ano_agend == ano_atual)
            {
                existe_agendamento_no_mes = 1;
                break;
            }
        }
    }

    // Se não encontrou, exibe a mensagem e sai
    if (!existe_agendamento_no_mes)
    {
        printf("\nNenhum agendamento encontrado para o mês %d do ano %d.\n", mes_busca, ano_atual);
        fclose(arq_agendamentos);
        pressione_enter();
        return;
    }

    // Se encontrou, rebobina o arquivo para listar
    rewind(arq_agendamentos);

    printf("\n╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-10s │ %-25s │ %-12s │ %-8s ║\n", "CPF", "ID PET", "NOME DO PET", "DATA", "HORA");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    while (fread(&agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (agend.status == True)
        {
            int mes_agend, ano_agend;
            // Extrai mês e ano da data do agendamento
            sscanf(agend.data, "%*d/%d/%d", &mes_agend, &ano_agend);

            if (mes_agend == mes_busca && ano_agend == ano_atual)
            {
                Pets *pet = buscar_pet_id(atoi(agend.id_pet));
                char nome_pet_temp[31] = "Pet não encontrado";
                if (pet != NULL)
                {
                    strncpy(nome_pet_temp, pet->nome, 30);
                    free(pet);
                }
                printf("║ %-15s │ %-10s │ %-25s │ %-12s │ %-8s ║\n",
                       agend.cpf,
                       agend.id_pet,
                       nome_pet_temp,
                       agend.data,
                       agend.hora);
                encontrou = 1;
                contador++;
            }
        }
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
    {
        printf("\nTotal de agendamentos encontrados: %d\n", contador);
    }

    fclose(arq_agendamentos);
    pressione_enter();
}

void relatorio_vendas_detalhado(void)
{
    exibir_logo();
    exibir_titulo("Relatorio Detalhado de Vendas");

    NoVenda *lista = carregar_vendas_lista();

    if (!lista)
    {
        printf("Nenhuma venda registrada.\n");
        pressione_enter();
        return;
    }

    NoVenda *atual = lista;

    while (atual != NULL)
    {
        Venda *venda = &atual->venda;

        Clientes *cli = buscar_cliente_por_cpf(venda->cpf_cliente);

        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ VENDA %-5d                                                                                  ║\n", venda->id);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

        printf("║ Cliente: %-83s ║\n", cli ? cli->nome : "Cliente não encontrado");
        printf("║ Data: %-86s ║\n", venda->data);

        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ %-5s │ %-45s │ %-10s │ %-10s  │ %-10s ║\n",
               "ID", "PRODUTO", "QTD", "UNITÁRIO", "SUBTOTAL");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

        float total_geral = 0.0;

        for (int i = 0; i < venda->num_itens; i++)
        {
            ItemVenda *item = &venda->itens[i];
            Produtos *prod = buscar_produto_por_id(item->id_produto);

            if (!prod)
            {
                printf("║ %-5d │ %-45s │ %-10.2f │ %-12s │ %-12s ║\n",
                       item->id_produto, "Produto não encontrado",
                       item->quantidade, "---", "---");
                continue;
            }

            float unit = prod->preco;
            float subtotal = unit * item->quantidade;
            total_geral += subtotal;

            printf("║ %-5d │ %-45s │ %-10.2f │ %-10.2f │ %-10.2f ║\n",
                   prod->id, prod->nome, item->quantidade, unit, subtotal);

            free(prod);
        }

        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ VALOR TOTAL DA VENDA: R$ %-67.2f ║\n", total_geral);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

        if (cli)
            free(cli);

        atual = atual->prox;
    }

    // liberar lista
    atual = lista;
    while (atual != NULL)
    {
        NoVenda *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    pressione_enter();
}

void relatorio_pets_por_clientes(void)
{
    exibir_logo();
    exibir_titulo("Listagem de Pets por Clientes");

    NoCliente *lista_clientes = carregar_clientes_lista();

    if (!lista_clientes)
    {
        printf("Nenhum cliente cadastrado.\n");
        pressione_enter();
        return;
    }

    NoCliente *cliente_atual = lista_clientes;
    while (cliente_atual != NULL)
    {
        Clientes *cli = &cliente_atual->cliente;

        if (cli->status == True)
        {
            printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
            printf("║ Cliente: %-84s║\n", cli->nome);
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            listar_pets_por_cpf(cli->cpf);
            printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
        }
        cliente_atual = cliente_atual->prox;
    }

    // Liberar a memória da lista de clientes
    while (lista_clientes != NULL)
    {
        NoCliente *temp = lista_clientes;
        lista_clientes = lista_clientes->prox;
        free(temp);
    }
    pressione_enter();
}

void relatorio_clientes_ordenados(void)
{
    exibir_logo();
    exibir_titulo("Relatorio de Clientes Ordenados por Nome");

    NoCliente *lista = carregar_clientes_ordenados_nome();

    if (lista == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        pressione_enter();
        return;
    }

    NoCliente *p = lista;

    while (p != NULL)
    {
        Clientes *c = &p->cliente;

        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ Nome: %-87s║\n", c->nome);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ CPF: %-88s║\n", c->cpf);
        printf("║ Data de Nascimento: %-73s║\n", c->data_nascimento);
        printf("║ Telefone: %-83s║\n", c->telefone);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

        p = p->prox;
    }

    // liberar memória
    p = lista;
    while (p != NULL)
    {
        NoCliente *tmp = p;
        p = p->prox;
        free(tmp);
    }

    pressione_enter();
}

void relatorio_pets_ordenados(void)
{
    exibir_logo();
    exibir_titulo("Relatório de Pets Ordenados por Especie");

    NoPet *lista = carregar_pets_ordenados_nome();

    if (lista == NULL)
    {
        printf("Nenhum pet cadastrado.\n");
        pressione_enter();
        return;
    }

    NoPet *p = lista;

    while (p != NULL)
    {
        Pets *pet = &p->pet;

        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║ Nome do Pet: %-80s║\n", pet->nome);
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║ Espécie: %-84s║\n", pet->especie);
        printf("║ ID: %-89d║\n", pet->id);
        printf("║ CPF do Dono: %-80s║\n", pet->cpf);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");

        p = p->prox;
    }

    // liberar memória
    p = lista;
    while (p != NULL)
    {
        NoPet *tmp = p;
        p = p->prox;
        free(tmp);
    }

    pressione_enter();
}

void relatorio_produtos_ordenados(void)
{
    exibir_logo();
    exibir_titulo("Produtos do Menor Preco para o Maior");

    NoProduto *lista = carregar_produtos_ordenados();
    if (!lista)
    {
        printf("\nNenhum produto ativo encontrado.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-12s │ %-32s ║\n", "ID", "NOME", "PREÇO (R$)", "ESTOQUE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    NoProduto *aux = lista;
    int contador = 0;

    while (aux != NULL)
    {
        printf("║ %-5d │ %-35s │ %-12.2f │ %-31.2f ║\n",
               aux->produto.id,
               aux->produto.nome,
               aux->produto.preco,
               aux->produto.quantidade);

        aux = aux->prox;
        contador++;
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nTotal de produtos listados: %d\n", contador);

    aux = lista;
    while (aux != NULL)
    {
        NoProduto *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    pressione_enter();
}


void relatorio_agendamentos_ordenados(void)
{
    exibir_logo();
    exibir_titulo("Agendamentos Ordenados por Data");

    NoAgendamento *lista = carregar_agendamentos_ordenados();
    if (!lista)
    {
        printf("\nNenhum agendamento cadastrado.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-25s │ %-10s │ %-25s │ %-12s │ %-8s ║\n",
           "CLIENTE", "ID PET", "NOME DO PET", "DATA", "HORA");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    NoAgendamento *aux = lista;
    int contador = 0;

    while (aux != NULL)
    {
        Pets *pet = buscar_pet_id(atoi(aux->agendamento.id_pet));
        char nome_pet[31] = "Pet não encontrado";
        if (pet != NULL)
        {
            strncpy(nome_pet, pet->nome, 30);
            free(pet);
        }

        Clientes *cli = buscar_cliente_por_cpf(aux->agendamento.cpf);
        char nome_cli[51] = "Cliente não encontrado";
        if (cli != NULL)
        {
            strncpy(nome_cli, cli->nome, 50);
            free(cli);
        }

        printf("║ %-25s │ %-10s │ %-25s │ %-12s │ %-8s ║\n",
               nome_cli,
               aux->agendamento.id_pet,
               nome_pet,
               aux->agendamento.data,
               aux->agendamento.hora);

        aux = aux->prox;
        contador++;
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nTotal de agendamentos listados: %d\n", contador);

    aux = lista;
    while (aux != NULL)
    {
        NoAgendamento *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    pressione_enter();
}

void relatorio_vendas_decrescente(void){
    exibir_logo();
    exibir_titulo("Vendas decrescente");

    NoVenda *lista = carregar_vendas_decrescente();
    if (!lista){
        printf("\nNenhuma venda cadastrada.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-15s │ %-35s │ %-12s │ %-12s  ║\n", 
           "ID", "CPF CLIENTE", "NOME CLIENTE", "DATA", "VALOR (R$)");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    NoVenda *aux = lista;
    int contador = 0;

    while (aux != NULL)
    {
        Clientes *cli = buscar_cliente_por_cpf(aux->venda.cpf_cliente);
        char nome_cliente[36] = "Cliente não encontrado";
        if (cli != NULL)
        {
            strncpy(nome_cliente, cli->nome, 35);
            free(cli);
        }

        printf("║ %-5d │ %-15s │ %-35s │ %-12s │ %-12.2f  ║\n",
               aux->venda.id,
               aux->venda.cpf_cliente,
               nome_cliente,
               aux->venda.data,
               aux->venda.valor_total);

        aux = aux->prox;
        contador++;
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nTotal de vendas listadas: %d\n", contador);

    aux = lista;
    while (aux != NULL)
    {
        NoVenda *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    pressione_enter();

}

void relatorio_vendas_ordenadas(void)
{
    exibir_logo();
    exibir_titulo("Vendas Ordenadas por Data");

    NoVenda *lista = carregar_vendas_ordenadas();
    if (!lista)
    {
        printf("\nNenhuma venda cadastrada.\n");
        pressione_enter();
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-15s │ %-35s │ %-12s │ %-12s  ║\n", 
           "ID", "CPF CLIENTE", "NOME CLIENTE", "DATA", "VALOR (R$)");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    NoVenda *aux = lista;
    int contador = 0;

    while (aux != NULL)
    {
        Clientes *cli = buscar_cliente_por_cpf(aux->venda.cpf_cliente);
        char nome_cliente[36] = "Cliente não encontrado";
        if (cli != NULL)
        {
            strncpy(nome_cliente, cli->nome, 35);
            free(cli);
        }

        printf("║ %-5d │ %-15s │ %-35s │ %-12s │ %-12.2f  ║\n",
               aux->venda.id,
               aux->venda.cpf_cliente,
               nome_cliente,
               aux->venda.data,
               aux->venda.valor_total);

        aux = aux->prox;
        contador++;
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nTotal de vendas listadas: %d\n", contador);

    aux = lista;
    while (aux != NULL)
    {
        NoVenda *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    pressione_enter();
}

void relatorio_servicos_ordenados(void)
{
    exibir_logo();
    exibir_titulo("Serviços do Menor para o Maior Preço");

    NoServico *lista = carregar_servicos_ordenados();
    if (!lista)
    {
        printf("\nNenhum serviço cadastrado.\n");
        pressione_enter();
        return;
    }

    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-30s │ %-12s ║\n", 
           "ID", "NOME", "DESCRIÇÃO", "PREÇO (R$)");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    NoServico *aux = lista;
    int contador = 0;

    while (aux != NULL)
    {
        printf("║ %-5d │ %-35s │ %-30s │ %-12s ║\n",
               aux->servico.id,
               aux->servico.nome,
               aux->servico.desc,
               aux->servico.preco_s);

        aux = aux->prox;
        contador++;
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\nTotal de serviços listados: %d\n", contador);

    aux = lista;
    while (aux != NULL)
    {
        NoServico *temp = aux;
        aux = aux->prox;
        free(temp);
    }

    pressione_enter();
}