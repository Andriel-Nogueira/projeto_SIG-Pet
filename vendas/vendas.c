#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "../clientes/clientes.h"
#include "../produtos/produtos.h"
#include "../utilitarios/utilitarios.h"

void m_vendas(void) {
    int op;
    do {
        exibir_logo();
        exibir_titulo("Menu Vendas");
        printf("║                                                                                              ║\n");
        printf("║          1 - Realizar Nova Venda                                                             ║\n");
        printf("║          2 - Listar Vendas                                                                   ║\n");
        printf("║          3 - Cancelar Venda                                                                  ║\n");
        printf("║          0 - Voltar ao Menu Principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        op = escolha();

        switch (op) {
            case 1:
                realizar_venda();
                break;
            case 2:
                listar_vendas();
                break;
            case 3:
                cancelar_venda();
                break;
        }
    } while (op != 0);
}

char* tela_identificar_cliente(void) {
    Clientes* cliente;
    char* cpf_busca = (char*) malloc(15 * sizeof(char));

    do {
        input(cpf_busca, 15, "CPF do Cliente (apenas números):");
        cliente = buscar_cliente_por_cpf(cpf_busca);
        if (cliente == NULL) {
            printf("\nCliente não encontrado. Tente novamente.\n");
        }
    } while (cliente == NULL);

    free(cliente);
    return cpf_busca;
}

void tela_adicionar_itens(Venda* venda) {
    char continuar;
    char qtd_str[10];
    float quantidade_desejada;

    do {
        printf("\nAdicionando produto à venda...\n");
        int id_produto = tela_buscar_produto();
        
        // A busca do produto deve ser feita aqui, na tela,
        // pois é uma interação direta com a entrada do usuário.
        Produtos* prod = NULL;
        if (id_produto != -1) {
            prod = buscar_produto_por_id(id_produto);
        }

        if (prod != NULL) {
            printf("Produto encontrado: %s | Estoque: %.2f\n", prod->nome, prod->quantidade);
            
            do {
                input(qtd_str, 10, "Digite a quantidade desejada:");
            } while (!validar_float(qtd_str));
            quantidade_desejada = atof(qtd_str);

            if (quantidade_desejada > 0 && quantidade_desejada <= prod->quantidade) {
                // Adiciona o item à venda
                ItemVenda* item = &venda->itens[venda->num_itens];
                item->id_produto = prod->id;
                item->preco_unitario = prod->preco;
                item->quantidade = quantidade_desejada;
                
                venda->valor_total += (prod->preco * quantidade_desejada);
                venda->num_itens++;

                // Atualiza o estoque do produto
                prod->quantidade -= quantidade_desejada;
                gravar_atualizacao_produto(prod);

                printf("\nItem adicionado com sucesso!\n");
            } else {
                printf("\nQuantidade inválida ou insuficiente em estoque.\n");
            }
            free(prod);
        } else {
            printf("\nProduto com código %d não encontrado.\n", id_produto);
        }
        
        printf("\nDeseja adicionar outro item? (S/N): ");
        scanf(" %c", &continuar);
        getchar();

    } while ((continuar == 'S' || continuar == 's') && venda->num_itens < MAX_ITENS);
}

void gravar_venda(const Venda* venda) {
    FILE* arq_vendas = fopen("vendas/vendas.dat", "ab");
    if (arq_vendas != NULL) {
        fwrite(venda, sizeof(Venda), 1, arq_vendas);
        fclose(arq_vendas);
    } else {
        printf("\nErro ao salvar a venda!\n");
    }
}

void gravar_atualizacao_venda(const Venda* venda) {
    FILE* arq_vendas;
    Venda temp_venda;

    arq_vendas = fopen("vendas/vendas.dat", "r+b");
    if (arq_vendas == NULL) {
        printf("\nErro ao abrir o arquivo de vendas para atualização!\n");
        return;
    }

    while (fread(&temp_venda, sizeof(Venda), 1, arq_vendas)) {
        if (temp_venda.id == venda->id) {
            fseek(arq_vendas, -sizeof(Venda), SEEK_CUR);
            fwrite(venda, sizeof(Venda), 1, arq_vendas);
            break;
        }
    }
    fclose(arq_vendas);
}

void realizar_venda(void) {
    Venda* venda = (Venda*) malloc(sizeof(Venda));
    venda->num_itens = 0;
    venda->valor_total = 0.0;

    exibir_logo();
    exibir_titulo("Realizar Venda");

    char* cpf_cliente = tela_identificar_cliente();
    strcpy(venda->cpf_cliente, cpf_cliente);
    free(cpf_cliente);

    tela_adicionar_itens(venda);

    if (venda->num_itens > 0) {
        venda->id = GERAR_ID("vendas/vendas.dat", Venda);
        venda->status = True;
        obter_data_atual(venda->data);

        gravar_venda(venda);
        printf("\n----- Venda Finalizada -----\n");
        exibir_venda(venda);
    } else {
        printf("\nNenhum item na venda. Venda cancelada.\n");
    }

    free(venda);
    pressione_enter();
}

int tela_cancelar_venda(void) {
    char id_str[10];
    exibir_logo();
    exibir_titulo("Cancelar Venda");
    do {
        input(id_str, 10, "Digite o ID da venda que deseja cancelar:");
    } while (!validar_numero(id_str));
    return atoi(id_str);
}

Venda* buscar_venda_por_id(int id) {
    FILE* arq_vendas;
    Venda* venda;

    arq_vendas = fopen("vendas/vendas.dat", "rb");
    if (arq_vendas == NULL) {
        return NULL;
    }

    venda = (Venda*) malloc(sizeof(Venda));
    while (fread(venda, sizeof(Venda), 1, arq_vendas)) {
        if (venda->id == id && venda->status == True) {
            fclose(arq_vendas);
            return venda;
        }
    }
    fclose(arq_vendas);
    free(venda);
    return NULL;
}

void restaurar_estoque(const Venda* venda) {
    for (int i = 0; i < venda->num_itens; i++) {
        const ItemVenda* item = &venda->itens[i];
        Produtos* prod = buscar_produto_por_id(item->id_produto);
        if (prod != NULL) {
            prod->quantidade += item->quantidade;
            gravar_atualizacao_produto(prod);
            free(prod);
        }
    }
}

void cancelar_venda(void) {
    int id_venda = tela_cancelar_venda();
    Venda* venda = buscar_venda_por_id(id_venda);

    if (venda == NULL) {
        printf("\nVenda com ID %d não encontrada ou já cancelada.\n", id_venda);
    } else {
        char confirmacao;
        printf("\nDeseja realmente cancelar a venda #%d? (S/N): ", id_venda);
        scanf(" %c", &confirmacao);
        getchar();

        if (confirmacao == 'S' || confirmacao == 's') {
            // 1. Marca a venda como inativa (cancelada)
            venda->status = False;
            
            // 2. Restaura o estoque dos produtos
            restaurar_estoque(venda);

            // 3. Grava a atualização do status da venda
            gravar_atualizacao_venda(venda);

            printf("\nVenda #%d cancelada com sucesso e estoque restaurado!\n", id_venda);
        } else {
            printf("\nOperação de cancelamento abortada.\n");
        }
    }

    free(venda);
    pressione_enter();
}


void exibir_venda(const Venda* venda) {
    printf("ID da Venda: %d\n", venda->id);
    printf("Data: %s\n", venda->data);
    printf("CPF do Cliente: %s\n", venda->cpf_cliente);
    printf("Itens na venda: %d\n", venda->num_itens);
    printf("Valor Total: R$ %.2f\n", venda->valor_total);
    if (venda->status == False) {
        printf("Status: CANCELADA\n");
    }
    printf("----------------------------\n");
    printf("Itens:\n");
    for (int i = 0; i < venda->num_itens; i++) {
        printf("  - Produto ID: %d | Qtd: %.2f | Preço Un.: R$ %.2f\n", 
               venda->itens[i].id_produto, venda->itens[i].quantidade, venda->itens[i].preco_unitario);
    }
}

void listar_vendas(void) {
    FILE* arq_vendas;
    Venda venda;

    exibir_logo();
    exibir_titulo("Histórico de Vendas");

    arq_vendas = fopen("vendas/vendas.dat", "rb");
    if (arq_vendas == NULL) {
        printf("\nNenhuma venda registrada.\n");
        pressione_enter();
        return;
    }

    while(fread(&venda, sizeof(Venda), 1, arq_vendas)) {
        exibir_venda(&venda);
    }

    fclose(arq_vendas);
    pressione_enter();
}