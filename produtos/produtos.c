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
        printf("║          5 - Inativar produto                                                                ║\n");
        printf("║          6 - Excluir produto (Fisicamente)                                                   ║\n");
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
        case 6:
            excluir_produto_fisico();
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
    prod->status = True;

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
    exibir_titulo("Buscar Produto pelo Codigo");
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
        if ((strcmp(prod->id, id_lido) == 0) && (prod->status == True))
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

void excluir_produto_fisico(void)
{
    Produtos* prod;
    FILE *arq_produtos;
    FILE *arq_temp;
    char id_busca[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Produto Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o código do produto que deseja excluir permanentemente:                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_busca, 20, "Digite o código do produto: ");

    prod = (Produtos*) malloc(sizeof(Produtos));
    if (prod == NULL) {
        printf("Erro de alocação de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    arq_temp = fopen("produtos/produtos_temp.dat", "wb");

    if (arq_produtos == NULL || arq_temp == NULL) {
        printf("\nErro ao abrir os arquivos. A operação não pode ser concluída.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(prod);
        if (arq_produtos) fclose(arq_produtos);
        if (arq_temp) fclose(arq_temp);
        return;
    }

    while(fread(prod, sizeof(Produtos), 1, arq_produtos)) {
        if (strcmp(prod->id, id_busca) != 0) {
            fwrite(prod, sizeof(Produtos), 1, arq_temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_produtos);
    fclose(arq_temp);
    free(prod);

    remove("produtos/produtos.dat");
    rename("produtos/produtos_temp.dat", "produtos/produtos.dat");

    if (encontrado) {
        printf("\nProduto com código %s excluído permanentemente com sucesso!\n", id_busca);
    } else {
        printf("\nProduto com código %s não encontrado.\n", id_busca);
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
        if ((strcmp(prod->id, id_lido) == 0) && (prod->status == True))
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
    Produtos* prod;

    exibir_logo();
    exibir_titulo("Listar Produtos");

    prod = (Produtos*) malloc(sizeof(Produtos));
    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        free(prod);
        getchar();
        return;
    }
    while (fread(prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (prod->status == True) {
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║ ID: %-10s ║ Nome: %-20s ║ Preço: R$ %-10s ║ Estoque: %-5s ║\n", prod->id, prod->nome, prod->preco, prod->quantidade);
        }
    }
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    fclose(arq_produtos);
    free(prod);
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_produto(void)
{
    Produtos* prod;
    FILE* arq_produtos;
    char id_lido[20];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Produto");
    printf("║      Informe o Código do Produto que deseja excluir:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_lido, 20, "Digite o id do produto que deseja excluir: ");

    prod = (Produtos*) malloc(sizeof(Produtos));
    arq_produtos = fopen("produtos/produtos.dat", "r+b");
    if (arq_produtos == NULL)
    {
        printf("\nErro ao abrir o arquivo de produtos. Nenhum produto cadastrado?\n");
        printf("Pressione <Enter> para voltar...");
        free(prod);
        getchar();
        return;
    }

    while (fread(prod, sizeof(Produtos), 1, arq_produtos)) {
        if ((strcmp(prod->id, id_lido) == 0) && (prod->status == True)) {
            encontrado = 1;
            prod->status = False; // Exclusão lógica
            fseek(arq_produtos, -sizeof(Produtos), SEEK_CUR);
            fwrite(prod, sizeof(Produtos), 1, arq_produtos);
            printf("\nProduto com ID %s excluído com sucesso!\n", id_lido);
            break;
        }
    }
    fclose(arq_produtos);
    free(prod);
    if (!encontrado) {
        printf("\nProduto com ID %s não encontrado ou já foi excluído.\n", id_lido);
    }
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}