#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servicos.h"
#include "../utilitarios/utilitarios.h"

typedef struct servicos Servicos;

void m_servicos(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Servicos");

        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar novo serviço                                                          ║\n");
        printf("║          2 - Buscar serviço pelo código                                                      ║\n");
        printf("║          3 - Atualizar serviço                                                               ║\n");
        printf("║          4 - Listar serviços                                                                 ║\n");
        printf("║          5 - Excluir serviço                                                                 ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        scanf(" %d", &op);
        getchar();
        switch (op)
        {
        case 1:
            cadastrar_servico();
            break;
        case 2:
            buscar_servico();
            break;
        case 3:
            atualizar_servico();
            break;
        case 4:
            listar_servicos();
            break;
        case 5:
            excluir_servico();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void cadastrar_servico(void)
{
    Servicos serv;
    exibir_logo();
    exibir_titulo("Cadastrar Serviço");
    
    // Gera o ID automaticamente
    strcpy(serv.id_gerado, gerar_id("servicos/servicos.csv"));
    
    printf("ID do serviço gerado automaticamente: %s\n", serv.id_gerado);
    input(serv.nome, 50, "Nome do Serviço: ");
    input(serv.desc, 256, "Descrição: ");
    input(serv.preco_s, 32, "Preço (use . como separador): "); 
    
    salvar("servicos/servicos.csv", 4, serv.nome, serv.desc, serv.preco_s, serv.id_gerado);
    printf("\nCadastro de serviço realizado com sucesso !\n");
    printf("ID: %s\nNome: %s\nDescrição: %s\nPreço: %s\n", serv.id_gerado, serv.nome, serv.desc, serv.preco_s);
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_servico(void)
{
    char nome[50];
    char desc[256];
    char preco_s[32];
    char id[20];
    char id_lido[20];
    FILE *arq_servicos;

    exibir_logo();
    exibir_titulo("Buscar Serviço pelo ID");
    printf("║                            Serviços pré-cadastrados no sistema:                              ║\n");
    printf("║         ID-1: Banho                                                                          ║\n");
    printf("║         ID-2: Tosa                                                                           ║\n");
    printf("║         ID-3: Cuidados complementares                                                        ║\n");
    printf("║         ID-4: Banho Premium                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    input(id_lido, 20, "Informe o ID do serviço que deseja buscar:");

    arq_servicos = fopen("servicos/servicos.csv", "rt");
    if (arq_servicos == NULL) 
    {
        printf("ERRO AO ABRIR ARQUIVO DE SERVIÇOS\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (!feof(arq_servicos)) 
    {
        fscanf(arq_servicos, "%[^;]", nome);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^;]", desc);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^;]", preco_s);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^\n]", id);
        fgetc(arq_servicos);

        if (strcmp(id, id_lido) == 0) 
        {
            printf("\nServiço encontrado:\n");
            printf("Nome: %s\n", nome);
            printf("Descrição: %s\n", desc);
            printf("Preço: %s\n", preco_s);
            printf("ID: %s\n", id);
            fclose(arq_servicos);
            printf("\n");
            printf("Pressione <Enter> para voltar ao menu principal...                         \n");
            getchar();
            return;
        }
    }
    fclose(arq_servicos);
    printf("\nServiço com ID %s não encontrado.\n", id_lido);
    
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    getchar();
}

void atualizar_servico(void)
{
    //EM DESENVOLVIMENTO!!
    char id[20];

    exibir_logo();
    exibir_titulo("Atualizar Serviço");
    input(id, 20, "Informe o ID do serviço que deseja atualizar:");
    printf("\nEM DESENVOLVIMENTO!\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_servicos(void)
{
    char nome[50] = "";
    char desc[256] = "";
    char preco_s[32] = "";
    char id[20] = "";
    FILE *arq_servicos;

    exibir_logo();
    exibir_titulo("Listar Serviços");
    arq_servicos = fopen("servicos/servicos.csv", "rt");
    if (arq_servicos == NULL)
    {
        printf("Nenhum serviço cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }
    while (!feof(arq_servicos)) 
    {
        fscanf(arq_servicos, "%[^;]", nome);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^;]", desc);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^;]", preco_s);
        fgetc(arq_servicos);
        fscanf(arq_servicos, "%[^\n]", id);
        fgetc(arq_servicos);

        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║                                                                                              ║\n");
        printf("║ Nome: %s\t║ Preço: %s\t║ ID: %s                                       ║\n", nome, preco_s, id);
        printf("║ Descrição: %s   ║\n", desc);
        printf("║                                                                                              ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    }
    fclose(arq_servicos);


    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_servico(void)
{

}