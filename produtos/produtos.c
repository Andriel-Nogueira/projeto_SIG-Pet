#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "../utilitarios/utilitarios.h"

void m_produtos(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Produtos");

        printf("║                                                                                              ║\n");
        printf("║          1 - Adicionar novo produto                                                          ║\n");
        printf("║          2 - Buscar produto pelo código                                                      ║\n");
        printf("║          3 - Atualizar produto                                                               ║\n");
        printf("║          4 - Listar produtos                                                                 ║\n");
        printf("║          5 - Excluir produto                                                                 ║\n");
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
            adicionar_produto();
            break;
        case 2:
            buscar_produto();
            break;
        case 3:
            atualizar_produto();
            break;
        case 4:
            listar_produtos();
            break;
        case 5:
            excluir_produto();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void adicionar_produto(void)
{
    char nome[50];
    char preco[10];
    char quantidade[10];    
    char id_gerado[20];

    exibir_logo();
    exibir_titulo("Adicionar Produto");
    input(nome, 50, "Nome do Produto: ");
    input(preco, 50, "Preço do Produto: ");
    input(quantidade, 50, "Quantidade em Estoque: ");
    strcpy(id_gerado, gerar_id("produtos/produtos.csv"));

    printf("\nProduto cadastrado com sucesso!\n");
    printf("Código: %s\n", id_gerado);
    printf("Nome: %s\n", nome);
    printf("Preço: %s\n", preco);
    printf("Quantidade em estoque: %s\n", quantidade);
    
    salvar("produtos/produtos.csv", 4, id_gerado, nome, preco, quantidade);


    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_produto(void)
{
    char id[10];
    char id_lido[10];
    char nome[50];
    char preco[10];
    char quantidade[10];
    FILE *arq_produtos;

    exibir_logo();
    exibir_titulo("Buscar Produto pelo Código");
    input(id_lido, 15, "Digite o id do produto que deseja buscar: ");

    arq_produtos = fopen("produtos/produtos.csv", "rt");
    if (arq_produtos == NULL)
    {
        printf("Nenhum produto cadastrado.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_produtos, "%[^;];%[^;];%[^;];%[^\n]\n", id, nome, preco, quantidade) == 4)
    {
        if (strcmp(id, id_lido) == 0)
        {
            printf("\nProduto encontrado:\n");
            printf("ID: %s\n", id);
            printf("Nome: %s\n", nome);
            printf("Preço: %s\n", preco);
            printf("Quantidade: %s\n", quantidade);
            fclose(arq_produtos);
            printf("\nPressione <Enter> para continuar...");
            getchar();
            return;
        }
    }
    fclose(arq_produtos);
    printf("\nNenhum produto encontrado para o ID %s.\n", id_lido);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_produto(void)
{
    exibir_logo();
    exibir_titulo("Atualizar Produto");
    printf("║      Informe o Código do Produto que deseja atualizar:                                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("EM DESENVOLVIMENTO!\nPressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_produtos(void)
{
    FILE *arq_produtos;
    char id [10];
    char nome[50];
    char preco[10];
    char quantidade[10];

    exibir_logo();
    exibir_titulo("Listar Produtos");
    arq_produtos = fopen("produtos/produtos.csv", "rt");
    if (arq_produtos == NULL)
    {
        printf("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }
    while (fscanf(arq_produtos, "%[^;];%[^;];%[^;];%[^\n]\n", id, nome, preco, quantidade) == 4)
    {

        printf("id: %s\t║ Nome: %s\t║ Preço: %s\t║ Quantidade em estoque: %s\n", id, nome, preco, quantidade);

        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
    }
    fclose(arq_produtos);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_produto(void)
{
    exibir_logo();
    exibir_titulo("Excluir Produto");
    printf("║      Informe o Código do Produto que deseja excluir:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
