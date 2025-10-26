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
        printf("║          5 - Inativar serviço                                                                ║\n");
        printf("║          6 - Excluir serviço (Fisicamente)                                                   ║\n");
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
        case 6:
            excluir_servico_fisico();
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
    Servicos *serv;
    FILE *arq_servicos;

    exibir_logo();
    exibir_titulo("Cadastrar Servico");

    serv = (Servicos *)malloc(sizeof(Servicos));
    if (serv == NULL)
    {
        printf("Erro de alocação de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    serv->id = GERAR_ID("servicos/servicos.dat", Servicos);
    printf("ID do serviço gerado automaticamente: %d\n", serv->id);
    input(serv->nome, 50, "Nome do Serviço: ");
    input(serv->desc, 256, "Descrição: ");
    input(serv->preco_s, 32, "Preço (use . como separador): ");
    serv->status = True;

    arq_servicos = fopen("servicos/servicos.dat", "ab");
    if (arq_servicos == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        printf("Pressione <Enter> para voltar...");
        free(serv);
        getchar();
        return;
    }

    fwrite(serv, sizeof(Servicos), 1, arq_servicos);
    fclose(arq_servicos);

    printf("\nCadastro de serviço realizado com sucesso !\n");
    printf("ID: %d\nNome: %s\nDescrição: %s\nPreço: %s\n", serv->id, serv->nome, serv->desc, serv->preco_s);
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(serv);
}

void buscar_servico(void)
{
    Servicos *serv;
    FILE *arq_servicos;
    char id_lido[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Buscar Servico pelo ID");
    input(id_lido, 20, "Informe o ID do serviço que deseja buscar:");

    serv = (Servicos *)malloc(sizeof(Servicos));
    arq_servicos = fopen("servicos/servicos.dat", "rb");
    if (arq_servicos == NULL)
    {
        printf("ERRO AO ABRIR ARQUIVO DE SERVIÇOS\n");
        printf("Pressione <Enter> para voltar...");
        free(serv);
        getchar();
        return;
    }

    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if ((serv->id == atoi(id_lido)) && (serv->status == True))
        {
            encontrado = 1;
            printf("\nServiço encontrado:\n");
            printf("Nome: %s\n", serv->nome);
            printf("Descrição: %s\n", serv->desc);
            printf("Preço: %s\n", serv->preco_s);
            printf("ID: %d\n", serv->id);
            printf("Pressione <Enter> para voltar ao menu principal...                         \n");
            getchar();
            break;
        }
    }
    fclose(arq_servicos);

    if (!encontrado)
    {
        printf("\nServiço com ID %s não encontrado.\n", id_lido);
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(serv);
}

void excluir_servico_fisico(void)
{
    Servicos *serv;
    FILE *arq_servicos;
    FILE *arq_temp;
    char id_busca[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Servico Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o ID do serviço que deseja excluir permanentemente:                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_busca, 20, "Informe o ID do serviço que deseja excluir permanentemente:");

    serv = (Servicos *)malloc(sizeof(Servicos));
    if (serv == NULL)
    {
        printf("Erro de alocação de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_servicos = fopen("servicos/servicos.dat", "rb");
    arq_temp = fopen("servicos/servicos_temp.dat", "wb");

    if (arq_servicos == NULL || arq_temp == NULL)
    {
        printf("Erro ao abrir os arquivos!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(serv);
        if (arq_servicos)
            fclose(arq_servicos);
        if (arq_temp)
            fclose(arq_temp);
        return;
    }

    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv->id != atoi(id_busca))
        {
            fwrite(serv, sizeof(Servicos), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_servicos);
    fclose(arq_temp);
    free(serv);

    remove("servicos/servicos.dat");
    rename("servicos/servicos_temp.dat", "servicos/servicos.dat");

    if (encontrado)
    {
        printf("Serviço com ID %s excluído permanentemente com sucesso!\n", id_busca);
    }
    else
    {
        printf("Serviço com ID %s não encontrado.\n", id_busca);
    }

    printf("\nPressione <Enter> para voltar ao menu principal...\n");
    getchar();
}

void atualizar_servico(void)
{
    Servicos *serv;
    FILE *arq_servicos;
    char id_lido[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Servico");
    printf("║      Informe o ID do serviço que deseja atualizar:                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_lido, 20, "Informe o ID do serviço que deseja atualizar:");

    serv = (Servicos *)malloc(sizeof(Servicos));
    arq_servicos = fopen("servicos/servicos.dat", "r+b");

    if (arq_servicos == NULL)
    {
        printf("\nErro ao abrir arquivo de serviços.\n");
        free(serv);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if ((serv->id == atoi(id_lido)) && (serv->status == True))
        {
            encontrado = 1;
            printf("\nServiço encontrado. Informe os novos dados:\n");
            input(serv->nome, 50, "Nome do Serviço: ");
            input(serv->desc, 256, "Descrição: ");
            input(serv->preco_s, 32, "Preço (use . como separador): ");

            fseek(arq_servicos, -sizeof(Servicos), SEEK_CUR);
            fwrite(serv, sizeof(Servicos), 1, arq_servicos);
            break;
        }
    }

    fclose(arq_servicos);

    if (!encontrado)
    {
        printf("\nServiço com ID %s não encontrado.\n", id_lido);
    }
    else
    {
        printf("\nServiço atualizado com sucesso!\n");
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(serv);
}

void listar_servicos(void)
{
    FILE *arq_servicos;
    Servicos *serv;

    exibir_logo();
    exibir_titulo("Listar Servicos");

    serv = (Servicos *)malloc(sizeof(Servicos));
    arq_servicos = fopen("servicos/servicos.dat", "rb");

    if (arq_servicos == NULL)
    {
        printf("Nenhum serviço cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        free(serv);
        getchar();
        return;
    }
    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv->status == True)
        {
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║                                                                                              ║\n");
            printf("║ Nome: %s\t║ Preço: %s\t║ ID: %d                                       ║\n", serv->nome, serv->preco_s, serv->id);
            printf("║ Descrição: %s   ║\n", serv->desc);
            printf("║                                                                                              ║\n");
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        }
    }
    fclose(arq_servicos);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(serv);
}

void excluir_servico(void)
{
    char id_excluir[20];
    FILE *arq_servicos;
    Servicos *serv;
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Servico");

    input(id_excluir, 20, "Informe o ID do serviço que deseja excluir:");

    serv = (Servicos *)malloc(sizeof(Servicos));
    arq_servicos = fopen("servicos/servicos.dat", "r+b");
    if (arq_servicos == NULL)
    {
        printf("Erro ao abrir arquivo de serviços.\n");
        free(serv);
        getchar();
        return;
    }

    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if ((serv->id == atoi(id_excluir)) && (serv->status == True))
        {
            encontrado = 1;
            serv->status = False; // Exclusão lógica
            fseek(arq_servicos, -sizeof(Servicos), SEEK_CUR);
            fwrite(serv, sizeof(Servicos), 1, arq_servicos);
            break;
        }
    }

    fclose(arq_servicos);

    if (encontrado)
    {
        printf("Serviço com ID %s excluído com sucesso.\n", id_excluir);
    }
    else
    {
        printf("Serviço com ID %s não encontrado.\n", id_excluir);
    }

    printf("\nPressione <Enter> para voltar ao menu principal...\n");
    getchar();
    free(serv);
}