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
        printf("║          1 - Cadastrar novo produto                                                          ║\n");
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
            cadastrar_produto();
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
            inativar_produto();
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

Produtos* tela_cadastrar_produto(void) {
    Produtos* prod;
    prod = (Produtos*) malloc(sizeof(Produtos));
    if (prod == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    exibir_logo();
    exibir_titulo("Cadastrar Produto");
    input(prod->nome, 50, "Nome do Produto: ");
    input(prod->preco, 10, "Preço do Produto: ");
    input(prod->quantidade, 10, "Quantidade em Estoque: ");
    strcpy(prod->id, gerar_id("produtos/produtos.dat"));
    prod->status = True;
    return prod;
}

void gravar_produto(const Produtos* prod) {
    FILE* arq_produtos;
    arq_produtos = fopen("produtos/produtos.dat", "ab");
    if (arq_produtos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    fwrite(prod, sizeof(Produtos), 1, arq_produtos);
    fclose(arq_produtos);
}

void exibir_produto(const Produtos* prod) {
    if (prod == NULL) {
        printf("\nProduto não informado.\n");
        return;
    }
    printf("\n= = = Produto Cadastrado = = =\n");
    printf("Código: %s\n", prod->id);
    printf("Nome: %s\n", prod->nome);
    printf("Preço: R$ %s\n", prod->preco);
    printf("Quantidade em estoque: %s\n", prod->quantidade);
}

void cadastrar_produto(void) {
    Produtos* prod;

    prod = tela_cadastrar_produto();
    if (prod != NULL) {
        gravar_produto(prod);
        exibir_produto(prod);
        free(prod);
    }
    pressione_enter();
}

char* tela_buscar_produto(void) {
    char* id_busca;
    id_busca = (char*) malloc(20 * sizeof(char));
    exibir_logo();
    exibir_titulo("Buscar Produto pelo Código");
    input(id_busca, 20, "Digite o código do produto que deseja buscar: ");
    return id_busca;
}

Produtos* buscar_produto_por_id(const char* id) {
    FILE* arq_produtos;
    Produtos* prod;

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL) {
        return NULL;
    }

    prod = (Produtos*) malloc(sizeof(Produtos));
    while (fread(prod, sizeof(Produtos), 1, arq_produtos)) {
        if ((strcmp(prod->id, id) == 0) && (prod->status == True)) {
            fclose(arq_produtos);
            return prod;
        }
    }
    fclose(arq_produtos);
    free(prod);
    return NULL;
}

void buscar_produto(void) {
    char* id_busca;
    Produtos* prod;

    id_busca = tela_buscar_produto();
    prod = buscar_produto_por_id(id_busca);

    if (prod != NULL) {
        exibir_produto(prod);
        free(prod);
    } else {
        printf("\nNenhum produto encontrado para o código %s.\n", id_busca);
    }
    free(id_busca);
    pressione_enter();
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

char* tela_atualizar_produto(void) {
    char* id_busca;
    id_busca = (char*) malloc(20 * sizeof(char));
    exibir_logo();
    exibir_titulo("Atualizar Produto");
    printf("║      Informe o Código do Produto que deseja atualizar:                                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_busca, 20, "Digite o código do produto que deseja atualizar: ");
    return id_busca;
}

void gravar_atualizacao_produto(const Produtos* prod) {
    FILE* arq_produtos;
    Produtos temp_prod;

    arq_produtos = fopen("produtos/produtos.dat", "r+b");
    if (arq_produtos == NULL) {
        printf("\nErro ao abrir o arquivo para atualização!\n");
        return;
    }

    while (fread(&temp_prod, sizeof(Produtos), 1, arq_produtos)) {
        if (strcmp(temp_prod.id, prod->id) == 0) {
            fseek(arq_produtos, -sizeof(Produtos), SEEK_CUR);
            fwrite(prod, sizeof(Produtos), 1, arq_produtos);
            printf("\nProduto atualizado com sucesso!\n");
            break;
        }
    }
    fclose(arq_produtos);
}

void atualizar_produto(void) {
    char* id_busca;
    Produtos* prod_novo;
    Produtos* prod_antigo;

    id_busca = tela_atualizar_produto();
    prod_antigo = buscar_produto_por_id(id_busca);

    if (prod_antigo == NULL) {
        printf("\nNenhum produto encontrado para o código %s.\n", id_busca);
    } else {
        printf("\nProduto encontrado. Insira os novos dados:\n");
        exibir_produto(prod_antigo);

        // Reutiliza a tela de cadastro para obter os novos dados
        prod_novo = (Produtos*) malloc(sizeof(Produtos));
        input(prod_novo->nome, 50, "Novo nome do Produto: ");
        input(prod_novo->preco, 10, "Novo preço do Produto: ");
        input(prod_novo->quantidade, 10, "Nova quantidade em Estoque: ");
        
        // Mantém o ID e status originais
        strcpy(prod_novo->id, id_busca);
        prod_novo->status = True;

        gravar_atualizacao_produto(prod_novo);
        free(prod_novo);
    }

    free(id_busca);
    free(prod_antigo);
    pressione_enter();
}

char* tela_inativar_produto(void) {
    char* id_busca;
    id_busca = (char*) malloc(20 * sizeof(char));
    exibir_logo();
    exibir_titulo("Inativar Produto");
    printf("║      Informe o Código do Produto que deseja inativar:                                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_busca, 20, "Digite o código do produto que deseja inativar: ");
    return id_busca;
}

void inativar_produto(void) {
    char* id_busca;
    Produtos* prod;

    id_busca = tela_inativar_produto();
    prod = buscar_produto_por_id(id_busca);

    if (prod != NULL) {
        prod->status = False;
        gravar_atualizacao_produto(prod);
        printf("\nProduto com código %s inativado com sucesso!\n", id_busca);
        free(prod);
    } else {
        printf("\nProduto com código %s não encontrado ou já está inativo.\n", id_busca);
    }
    free(id_busca);
    pressione_enter();
}

char* tela_excluir_produto_fisico(void) {
    char* id_busca;
    id_busca = (char*) malloc(20 * sizeof(char));
    exibir_logo();
    exibir_titulo("Excluir Produto Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o código do produto que deseja excluir permanentemente:                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_busca, 20, "Digite o código do produto: ");
    return id_busca;
}

int remover_produto_do_arquivo(const char* id) {
    FILE *arq_produtos, *arq_temp;
    Produtos prod;
    int encontrado = 0;

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL) {
        printf("\nErro ao abrir o arquivo de produtos. A operação não pode ser concluída.\n");
        return -1;
    }

    arq_temp = fopen("produtos/produtos_temp.dat", "wb");
    if (arq_temp == NULL) {
        printf("\nErro ao criar arquivo temporário. A operação não pode ser concluída.\n");
        fclose(arq_produtos);
        return -1;
    }

    while(fread(&prod, sizeof(Produtos), 1, arq_produtos)) {
        if (strcmp(prod.id, id) != 0) {
            fwrite(&prod, sizeof(Produtos), 1, arq_temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_produtos);
    fclose(arq_temp);

    if (encontrado) {
        remove("produtos/produtos.dat");
        rename("produtos/produtos_temp.dat", "produtos/produtos.dat");
    } else {
        remove("produtos/produtos_temp.dat");
    }
    return encontrado;
}

void excluir_produto_fisico(void) {
    char* id_busca;
    int resultado;

    id_busca = tela_excluir_produto_fisico();
    resultado = remover_produto_do_arquivo(id_busca);

    if (resultado == 1) {
        printf("\nProduto com código %s excluído permanentemente com sucesso!\n", id_busca);
    } else if (resultado == 0) {
        printf("\nProduto com código %s não encontrado.\n", id_busca);
    }
    // Se resultado for -1, a mensagem de erro já foi exibida.

    free(id_busca);
    pressione_enter();
}
