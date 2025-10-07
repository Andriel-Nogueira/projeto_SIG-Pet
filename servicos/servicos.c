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
    Servicos serv;
    FILE *arq_servicos;

    exibir_logo();
    exibir_titulo("Buscar Serviço pelo ID");
    input(serv.id_lido, 20, "Informe o ID do serviço que deseja buscar:");
    arq_servicos = fopen("servicos/servicos.csv", "rt");
    if (arq_servicos == NULL) 
    {
        printf("ERRO AO ABRIR ARQUIVO DE SERVIÇOS\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_servicos, " %[^;];%[^;];%[^;];%[^\n]", serv.nome, serv.desc, serv.preco_s, serv.id_gerado) == 4)
    {
        if (strcmp(serv.id_gerado, serv.id_lido) == 0) 
        {
            printf("\nServiço encontrado:\n");
            printf("Nome: %s\n", serv.nome);
            printf("Descrição: %s\n", serv.desc);
            printf("Preço: %s\n", serv.preco_s);
            printf("ID: %s\n", serv.id_lido);
            printf("Pressione <Enter> para voltar ao menu principal...                         \n");
            getchar();
            fclose(arq_servicos);

            return;
        }
    }
    fclose(arq_servicos);
    printf("\nServiço com ID %s não encontrado.\n", serv.id_lido);
    
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_servico(void)
{
    Servicos serv;
    FILE *arq_servicos;
    FILE *arq_servicos_temp;
    int encontrado = 0;
    
    exibir_logo();
    exibir_titulo("Atualizar Serviço");
    printf("║      Informe o ID do serviço que deseja atualizar:                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(serv.id_lido, 20, "Informe o ID do serviço que deseja atualizar:");

    arq_servicos = fopen("servicos/servicos.csv", "rt");
    arq_servicos_temp = fopen("servicos/servicos_temp.csv", "wt");

    if (arq_servicos == NULL || arq_servicos_temp == NULL) 
    {
        printf("\nErro ao abrir/criar arquivo de serviços.\n");
        if (arq_servicos) fclose(arq_servicos);
        if (arq_servicos_temp) fclose(arq_servicos_temp);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_servicos, " %[^;];%[^;];%[^;];%[^\n]", serv.nome, serv.desc, serv.preco_s, serv.id_gerado) == 4)
    {
        if (strcmp(serv.id_gerado, serv.id_lido) == 0) 
        {
            encontrado = 1;
            printf("\nServiço encontrado. Informe os novos dados:\n");
            input(serv.nome, 50, "Nome do Serviço: ");
            input(serv.desc, 256, "Descrição: ");
            input(serv.preco_s, 32, "Preço (use . como separador): "); 
            
            fprintf(arq_servicos_temp, "%s;%s;%s;%s\n", serv.nome, serv.desc, serv.preco_s, serv.id_gerado);
        } 
        else 
        {
            fprintf(arq_servicos_temp, "%s;%s;%s;%s\n", serv.nome, serv.desc, serv.preco_s, serv.id_gerado);
        }
    }

    fclose(arq_servicos);
    fclose(arq_servicos_temp);
    remove("servicos/servicos.csv");
    rename("servicos/servicos_temp.csv", "servicos/servicos.csv");

    if (!encontrado) 
    {
        printf("\nServiço com ID %s não encontrado.\n", serv.id_lido);
    } 
    else 
    {
        printf("\nServiço atualizado com sucesso!\n");
    } 


    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_servicos(void)
{
    FILE *arq_servicos;
    Servicos serv;

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
    while (fscanf(arq_servicos, " %[^;];%[^;];%[^;];%[^\n]", serv.nome, serv.desc, serv.preco_s, serv.id_gerado) == 4) 
    {
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║                                                                                              ║\n");
        printf("║ Nome: %s\t║ Preço: %s\t║ ID: %s                                       ║\n", serv.nome, serv.preco_s, serv.id_gerado);
        printf("║ Descrição: %s   ║\n", serv.desc);
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
    char id_excluir[20];
    FILE *arq_servicos, *arq_temp;
    Servicos serv;
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Serviço");

    input(id_excluir, 20, "Informe o ID do serviço que deseja excluir:");

    arq_servicos = fopen("servicos/servicos.csv", "rt");
    if (arq_servicos == NULL) {
        printf("Erro ao abrir arquivo de serviços.\n");
        getchar();
        return;
    }

    arq_temp = fopen("servicos/temp.csv", "wt");
    if (arq_temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arq_servicos);
        getchar();
        return;
    }

    while (fscanf(arq_servicos, " %[^;];%[^;];%[^;];%[^\n]", serv.nome, serv.desc, serv.preco_s, serv.id_gerado) == 4) {
        if (strcmp(serv.id_gerado, id_excluir) != 0) {
            fprintf(arq_temp, "%s;%s;%s;%s\n", serv.nome, serv.desc, serv.preco_s, serv.id_gerado);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_servicos);
    fclose(arq_temp);

    if (encontrado) {
        remove("servicos/servicos.csv");
        rename("servicos/temp.csv", "servicos/servicos.csv");
        printf("Serviço com ID %s excluído com sucesso.\n", id_excluir);
    } else {
        remove("servicos/temp.csv");
        printf("Serviço com ID %s não encontrado.\n", id_excluir);
    }

    printf("\nPressione <Enter> para voltar ao menu principal...\n");
    getchar();
}