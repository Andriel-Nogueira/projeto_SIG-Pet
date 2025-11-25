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
        op = escolha();
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

Produtos *tela_cadastrar_produto(void)
{
    Produtos *prod;
    prod = (Produtos *)malloc(sizeof(Produtos));
    if (prod == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    char preco_str[10];
    char qtd_str[10];

    exibir_logo();
    exibir_titulo("Cadastrar Produto");

    do
    {
        input(prod->nome, 50, "Nome do Produto:");
        if (!validar_nome(prod->nome))
        {
            printf("\nNome inválido! Digite apenas letras e espaços.\n");
        }
    } while (!validar_nome(prod->nome));

    do
    {
        input(preco_str, 10, "Preço do Produto (ex: 25.50):");
    } while (!validar_float(preco_str));
    prod->preco = atof(preco_str);

    do
    {
        input(qtd_str, 10, "Quantidade em Estoque (ex: 10):");
    } while (!validar_float(qtd_str));
    prod->quantidade = atof(qtd_str);

    prod->id = GERAR_ID("produtos/produtos.dat", Produtos);
    prod->status = True;
    return prod;
}

void gravar_produto(const Produtos *prod)
{
    FILE *arq_produtos;
    arq_produtos = fopen("produtos/produtos.dat", "ab");
    if (arq_produtos == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    fwrite(prod, sizeof(Produtos), 1, arq_produtos);
    fclose(arq_produtos);
}

void exibir_produto(const Produtos *prod)
{
    if (prod == NULL)
    {
        printf("\nProduto não informado.\n");
        return;
    }
    printf("\n= = = Produto Cadastrado = = =\n");
    printf("Código: %d\n", prod->id);
    printf("Nome: %s\n", prod->nome);
    printf("Preço: R$ %.2f\n", prod->preco);
    printf("Quantidade em estoque: %.2f\n", prod->quantidade);
}

void cadastrar_produto(void)
{
    Produtos *prod;

    prod = tela_cadastrar_produto();
    if (prod != NULL)
    {
        gravar_produto(prod);
        exibir_produto(prod);
        free(prod);
    }
    pressione_enter();
}

int tela_buscar_produto(void)
{
    char id_str[20];
    int id_busca;
    exibir_logo();
    exibir_titulo("Buscar Produto pelo Código");

    do
    {
        input(id_str, 20, "Digite o código do produto que deseja buscar: ");
    } while (!validar_numero(id_str));

    id_busca = atoi(id_str);
    return id_busca;
}

Produtos *buscar_produto_por_id(int id)
{
    FILE *arq_produtos;
    Produtos *prod;

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        return NULL;
    }

    prod = (Produtos *)malloc(sizeof(Produtos));
    while (fread(prod, sizeof(Produtos), 1, arq_produtos))
    {
        if ((prod->id == id) && (prod->status == True))
        {
            fclose(arq_produtos);
            return prod;
        }
    }
    fclose(arq_produtos);
    free(prod);
    return NULL;
}

void buscar_produto(void)
{
    int id_busca;
    Produtos *prod;

    id_busca = tela_buscar_produto();
    prod = buscar_produto_por_id(id_busca);

    if (prod != NULL)
    {
        exibir_produto(prod);
        free(prod);
    }
    else
    {
        printf("\nNenhum produto encontrado para o código %d.\n", id_busca);
    }
    pressione_enter();
}

void listar_produtos(void)
{
    FILE *arq_produtos;
    Produtos *prod;

    exibir_logo();
    exibir_titulo("Listar Produtos");

    prod = (Produtos *)malloc(sizeof(Produtos));
    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        free(prod);
        getchar();
        return;
    }
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-12s │ %-10s ║\n", "ID", "NOME", "PREÇO (R$)", "ESTOQUE");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    int encontrou = 0, contador = 0;
    while (fread(prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (prod->status == True)
        {
            printf("║ %-5d │ %-35s │ %-12.2f │ %-10.2f ║\n",
                   prod->id,
                   prod->nome,
                   prod->preco,
                   prod->quantidade);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum produto ativo encontrado.                                                                               ║\n");
    }

    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de produtos listados: %d\n", contador);

    fclose(arq_produtos);
    free(prod);

    pressione_enter();
}

int tela_atualizar_produto(void)
{
    char id_str[20];
    int id_busca;
    exibir_logo();
    exibir_titulo("Atualizar Produto");
    printf("║      Informe o Código do Produto que deseja atualizar:                                       ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_str, 20, "Digite o código do produto que deseja atualizar: ");
    id_busca = atoi(id_str);
    return id_busca;
}

void gravar_atualizacao_produto(const Produtos *prod)
{
    FILE *arq_produtos;
    Produtos temp_prod;

    arq_produtos = fopen("produtos/produtos.dat", "r+b");
    if (arq_produtos == NULL)
    {
        printf("\nErro ao abrir o arquivo para atualização!\n");
        return;
    }

    while (fread(&temp_prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (temp_prod.id == prod->id)
        {
            fseek(arq_produtos, -sizeof(Produtos), SEEK_CUR);
            fwrite(prod, sizeof(Produtos), 1, arq_produtos);
            printf("\nProduto atualizado com sucesso!\n");
            break;
        }
    }
    fclose(arq_produtos);
}

void atualizar_produto(void)
{
    int id_busca;
    Produtos *prod_novo;
    Produtos *prod_antigo;

    id_busca = tela_atualizar_produto();
    prod_antigo = buscar_produto_por_id(id_busca);

    if (prod_antigo == NULL)
    {
        printf("\nNenhum produto encontrado para o código %d.\n", id_busca);
    }
    else
    {
        printf("\nProduto encontrado. Insira os novos dados:\n");
        exibir_produto(prod_antigo);

        // Reutiliza a tela de cadastro para obter os novos dados
        prod_novo = (Produtos *)malloc(sizeof(Produtos));
        char preco_str[10];
        char qtd_str[10];

        do
        {
            input(prod_novo->nome, 50, "Novo nome do Produto:");
        } while (!validar_nome(prod_novo->nome));

        do
        {
            input(preco_str, 10, "Novo preço do Produto (ex: 25.50):");
        } while (!validar_float(preco_str));
        prod_novo->preco = atof(preco_str);

        do
        {
            input(qtd_str, 10, "Nova quantidade em Estoque (ex: 10):");
        } while (!validar_float(qtd_str));
        prod_novo->quantidade = atof(qtd_str);

        // Mantém o ID e status originais
        prod_novo->id = id_busca;
        prod_novo->status = True;

        gravar_atualizacao_produto(prod_novo);
        free(prod_novo);
    }

    free(prod_antigo);
    pressione_enter();
}

int tela_inativar_produto(void)
{
    char id_str[20];
    int id_busca;
    exibir_logo();
    exibir_titulo("Inativar Produto");
    printf("║      Informe o Código do Produto que deseja inativar:                                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_str, 20, "Digite o código do produto que deseja inativar: ");
    id_busca = atoi(id_str);
    return id_busca;
}

void inativar_produto(void)
{
    int id_busca;
    Produtos *prod;

    id_busca = tela_inativar_produto();
    prod = buscar_produto_por_id(id_busca);

    if (prod != NULL)
    {
        prod->status = False;
        gravar_atualizacao_produto(prod);
        printf("\nProduto com código %d inativado com sucesso!\n", id_busca);
        free(prod);
    }
    else
    {
        printf("\nProduto com código %d não encontrado ou já está inativo.\n", id_busca);
    }
    pressione_enter();
}

int tela_excluir_produto_fisico(void)
{
    char id_str[20];
    int id_busca;
    exibir_logo();
    exibir_titulo("Excluir Produto Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o código do produto que deseja excluir permanentemente:                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_str, 20, "Digite o código do produto: ");
    id_busca = atoi(id_str);
    return id_busca;
}

int remover_produto_do_arquivo(int id)
{
    FILE *arq_produtos, *arq_temp;
    Produtos prod;
    int encontrado = 0;

    arq_produtos = fopen("produtos/produtos.dat", "rb");
    if (arq_produtos == NULL)
    {
        printf("\nErro ao abrir o arquivo de produtos. A operação não pode ser concluída.\n");
        return -1;
    }

    arq_temp = fopen("produtos/produtos_temp.dat", "wb");
    if (arq_temp == NULL)
    {
        printf("\nErro ao criar arquivo temporário. A operação não pode ser concluída.\n");
        fclose(arq_produtos);
        return -1;
    }

    while (fread(&prod, sizeof(Produtos), 1, arq_produtos))
    {
        if (prod.id != id)
        {
            fwrite(&prod, sizeof(Produtos), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_produtos);
    fclose(arq_temp);

    if (encontrado)
    {
        remove("produtos/produtos.dat");
        rename("produtos/produtos_temp.dat", "produtos/produtos.dat");
    }
    else
    {
        remove("produtos/produtos_temp.dat");
    }
    return encontrado;
}

void excluir_produto_fisico(void)
{
    int id_busca;
    int resultado;

    id_busca = tela_excluir_produto_fisico();
    resultado = remover_produto_do_arquivo(id_busca);

    if (resultado == 1)
    {
        printf("\nProduto com código %d excluído permanentemente com sucesso!\n", id_busca);
    }
    else if (resultado == 0)
    {
        printf("\nProduto com código %d não encontrado.\n", id_busca);
    }
    // Se resultado for -1, a mensagem de erro já foi exibida.

    pressione_enter();
}

NoProduto *carregar_produtos_ordenados(void)
{
    FILE *arq = fopen("produtos/produtos.dat", "rb");
    if (!arq)
    {
        printf("Nenhum produto cadastrado ou erro ao abrir o arquivo.\n");
        return NULL;
    }

    Produtos prod;
    NoProduto *inicio = NULL;

    while (fread(&prod, sizeof(Produtos), 1, arq))
    {
        if (prod.status != True)
            continue;

                NoProduto *novo = malloc(sizeof(NoProduto));
        if (!novo)
        {
            printf("Erro de alocação!\n");
            fclose(arq);
            return inicio;
        }
        novo->produto = prod;
        novo->prox = NULL;

        if (inicio == NULL || prod.preco < inicio->produto.preco)
        {
            novo->prox = inicio;
            inicio = novo;
        }
        else
        {
            NoProduto *aux = inicio;
            while (aux->prox != NULL && aux->prox->produto.preco <= prod.preco)
            {
                aux = aux->prox;
            }
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }

    fclose(arq);
    return inicio;
}
