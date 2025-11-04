#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct produtos
{
    int id;
    char nome[50];
    float preco;
    float quantidade;
    int status;

} Produtos;

// Módulo Principal
void m_produtos(void);

//// Funções de Gerenciamento de Produtos ////
void cadastrar_produto(void);
void buscar_produto(void);
void atualizar_produto(void);
void listar_produtos(void);
void inativar_produto(void);
void excluir_produto_fisico(void);

// Funções de Tela
Produtos* tela_cadastrar_produto(void);
int tela_buscar_produto(void);
int tela_atualizar_produto(void);
int tela_inativar_produto(void);
int tela_excluir_produto_fisico(void);
void exibir_produto(const Produtos* prod);

// Funções de Arquivo
void gravar_produto(const Produtos* prod);
Produtos* buscar_produto_por_id(int id);
void gravar_atualizacao_produto(const Produtos* prod);
int remover_produto_do_arquivo(int id);

#endif