#ifndef PRODUTOS_H
#define PRODUTOS_H

struct produtos
{
    int id;
    char nome[50];
    float preco;
    float quantidade;
    int status;
};

typedef struct produtos Produtos;


// Módulo Principal
void m_produtos(void);

//// Funções de Gerenciamento de Produtos ////
void cadastrar_produto(void);
void buscar_produto(void);
void atualizar_produto(void);
void listar_produtos(void);
void inativar_produto(void);
void excluir_produto_fisico(void);

// Funções de Tela e Lógica (Produto)
Produtos* tela_cadastrar_produto(void);
char* tela_buscar_produto(void);
char* tela_atualizar_produto(void);
char* tela_inativar_produto(void);
char* tela_excluir_produto_fisico(void);
void exibir_produto(const Produtos* prod);
void gravar_produto(const Produtos* prod);
void gravar_atualizacao_produto(const Produtos* prod);
Produtos* buscar_produto_por_id(const char* id);
int remover_produto_do_arquivo(const char* id);

#endif