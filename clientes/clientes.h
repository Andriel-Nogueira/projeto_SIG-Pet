#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct clientes
{
    char cpf[16];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];
    int status;
} Clientes;

// Módulo Principal
void m_clientes(void);

//// Funções de Gerenciamento de Clientes ////
void cadastrar_cliente(void);
void buscar_cliente(void);
void atualizar_cliente(void);
void listar_clientes(void);
void inativar_cliente(void);
void excluir_cliente_fisico(void);

// Funções de Tela (Cliente)
Clientes* tela_cadastrar_cliente(void);
char* tela_atualizar_cliente(void);
char* tela_inativar_cliente(void);
char* tela_excluir_cliente_fisico(void);
void exibir_cliente(const Clientes* cli);

// Funções de Arquivo (Cliente)
void gravar_cliente(Clientes*);
int remover_cliente_do_arquivo(const char* cpf);
void gravar_atualizacao_cliente(const Clientes* cli);
int verificar_cliente_cadastrado(const char* cpf);
Clientes* buscar_cliente_por_cpf(const char* cpf);

#endif