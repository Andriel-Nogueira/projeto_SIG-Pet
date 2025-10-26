#ifndef VENDAS_H
#define VENDAS_H

#include "../clientes/clientes.h"
#include "../produtos/produtos.h"

#define MAX_ITENS 10

typedef struct {
    int id_produto;
    float preco_unitario;
    float quantidade;
} ItemVenda;

typedef struct {
    int id;
    char cpf_cliente[15];
    char data[11];
    ItemVenda itens[MAX_ITENS];
    int num_itens;
    float valor_total;
    int status;
} Venda;

// Módulo Principal
void m_vendas(void);

void realizar_venda(void);
char* tela_identificar_cliente(void);
void adicionar_itens_venda(Venda* venda);
void cancelar_venda(void);
int tela_cancelar_venda(void);
Venda* buscar_venda_por_id(int id);
void restaurar_estoque(const Venda* venda);
void gravar_venda(const Venda* venda);
void gravar_atualizacao_venda(const Venda* venda);
void exibir_venda(const Venda* venda);
void listar_vendas(void);

#endif