#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "../utilitarios/utilitarios.h"

typedef struct produtos Produtos;

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
    Produtos* prod;
    FILE* arq_produtos;

    exibir_logo();
    exibir_titulo("Adicionar Produto");

    prod = (Produtos*) malloc(sizeof(Produtos));
    if (prod == NULL) {
        printf("Erro de alocação de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    input(prod->nome, 50, "Nome do Produto: ");
    input(prod->preco, 10, "Preço do Produto: ");
    input(prod->quantidade, 10, "Quantidade em Estoque: ");
    strcpy(prod->id, gerar_id("produtos/produtos.dat"));
    prod->status = '1';

    arq_produtos = fopen("produtos/produtos.dat", "ab");
    fwrite(prod, sizeof(Produtos), 1, arq_produtos);
    fclose(arq_produtos);

    printf("\nProduto cadastrado com sucesso!\n");
    printf("Código: %s\n", prod->id);
    printf("Nome: %s\n", prod->nome);
    printf("Preço: %s\n", prod->preco);
    printf("Quantidade em estoque: %s\n", prod->quantidade);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(prod);
}

void buscar_produto(void)
{
    Produtos* prod;
    FILE *arq_produtos;
    char id_lido[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Buscar Produto pelo Código");
    input(id_lido, 20, "Digite o id do produto que deseja buscar: ");

    prod = (Produtos*) malloc(sizeof(Produtos));
    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("Nenhum produto cadastrado.\n");
        printf("Pressione <Enter> para voltar...");
        free(prod);
        getchar();
        return;
    }

    while (fread(prod, sizeof(Produtos), 1, arq_produtos))
    {
        if ((strcmp(prod->id, id_lido) == 0) && (prod->status == '1'))
        {
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            printf("ID: %s\n", prod->id);
            printf("Nome: %s\n", prod->nome);
            printf("Preço: %s\n", prod->preco);
            printf("Quantidade: %s\n", prod->quantidade);
            break;
        }
    }
    fclose(arq_produtos);
    free(prod);
    if (!encontrado) {
        printf("\nNenhum produto encontrado para o ID %s.\n", id_lido);
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_produto(void)
{
    Produtos* prod;
    FILE* arq_produtos;
    char id_lido[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Produto");
    printf("║      Informe o Código do Produto que deseja atualizar:                                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_lido, 20, "Digite o id do produto que deseja atualizar: ");

    prod = (Produtos*) malloc(sizeof(Produtos));
    arq_produtos = fopen("produtos/produtos.dat", "r+b");
    if (arq_produtos == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(prod);
        return;
    }

    while (fread(prod, sizeof(Produtos), 1, arq_produtos))
    {
        if ((strcmp(prod->id, id_lido) == 0) && (prod->status == '1'))
        {
            encontrado = 1;
            printf("\nProduto encontrado:\n");
            printf("ID: %s\n", prod->id);
            printf("Nome: %s\n", prod->nome);
            printf("Preço do produto: %s\n", prod->preco);
            printf("Quantidade em estoque: %s\n", prod->quantidade);
            printf("\n");
            printf("Digite os novos dados do produto:\n");
            input(prod->nome, 50, "Nome do Produto: ");
            input(prod->preco, 10, "Preço do Produto: ");
            input(prod->quantidade, 10, "Quantidade em Estoque: ");
            fseek(arq_produtos, -sizeof(Produtos), SEEK_CUR);
            fwrite(prod, sizeof(Produtos), 1, arq_produtos);
            printf("\nProduto atualizado com sucesso!\n");
            break;
        }
    }
    fclose(arq_produtos);
    free(prod);
    if (!encontrado) {
        printf("\nNenhum produto encontrado para o ID %s.\n", id_lido);
    }
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_produtos(void)
{
    FILE *arq_produtos;
    Produtos prod;

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
    while (fscanf(arq_produtos, "%[^;];%[^;];%[^;];%[^\n]\n", prod.id, prod.nome, prod.preco, prod.quantidade) == 4)
    {

        printf("id: %s\t║ Nome: %s\t║ Preço: %s\t║ Quantidade em estoque: %s\n", prod.id, prod.nome, prod.preco, prod.quantidade);

        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
    }
    fclose(arq_produtos);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_produto(void)
{
    Produtos prod;
    FILE *arq_produtos;
    FILE *arq_produtos_temp;
    exibir_logo();
    exibir_titulo("Excluir Produto");
    printf("║      Informe o Código do Produto que deseja excluir:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(prod.id_lido, 20, "Digite o id do produto que deseja excluir: ");

    arq_produtos = fopen("produtos/produtos.csv", "rt");
    if (arq_produtos == NULL)
    {
        printf("\nErro ao abrir o arquivo de produtos. Nenhum produto cadastrado?\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_produtos_temp = fopen("produtos/produtos_temp.csv", "wt");
    if (arq_produtos_temp == NULL)
    {
        printf("\nErro ao criar arquivo temporário.\n");
        fclose(arq_produtos);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_produtos, "%[^;];%[^;];%[^;];%[^\n]\n", prod.id, prod.nome, prod.preco, prod.quantidade) == 4){
     if (strcmp(prod.id_lido, prod.id) != 0){
        fprintf(arq_produtos_temp, "%s;%s;%s;%s\n", prod.id, prod.nome, prod.preco, prod.quantidade);
     }
    }
    fclose(arq_produtos);
    fclose(arq_produtos_temp);
    remove("produtos/produtos.csv");
    rename("produtos/produtos_temp.csv", "produtos/produtos.csv");
    printf("\nProduto excluído com sucesso!\n");
    getchar();
}