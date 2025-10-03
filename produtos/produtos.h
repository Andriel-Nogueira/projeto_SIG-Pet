#ifndef PRODUTOS_H
#define PRODUTOS_H

void m_produtos(void);
void adicionar_produto(void);
void buscar_produto(void);
void atualizar_produto(void);
void listar_produtos(void);
void excluir_produto(void);

struct produtos
{
    char id[20];
    char nome[50];
    char preco[10];
    char quantidade[10];
    char id_lido[20];
};

#endif