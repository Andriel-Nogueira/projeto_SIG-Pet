#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct clientes
{
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];
    int status;
} Clientes;

typedef struct pets
{
    char cpf[15];
    char nome[50];
    char especie[2];
    int status;
} Pets;

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

// Funções de Arquivo (Cliente)
void gravar_cliente(Clientes*);
int remover_cliente_do_arquivo(const char* cpf);
void gravar_atualizacao_cliente(const Clientes* cli);
int verificar_cliente_cadastrado(const char* cpf);
Clientes* buscar_cliente_por_cpf(const char* cpf);
void exibir_cliente(const Clientes* cli);

//// Funções de Gerenciamento de Pets ////
void cadastrar_pet(void);
void inativar_pet(void);
void excluir_pet_fisico(void);

// Funções de Tela (Pet)
Pets* tela_cadastrar_pet(void);
void tela_inativar_pet(char* cpf_busca, char* nome_pet_busca);
void tela_excluir_pet_fisico(char* cpf_busca, char* nome_pet_busca);

// Funções de Arquivo e Lógica (Pet)
void gravar_pet(Pets* pet);
void gravar_atualizacao_pet(const Pets* pet);
int remover_pet_do_arquivo(const char* cpf, const char* nome);
Pets* buscar_pet(const char* cpf, const char* nome);
void exibir_pet(const Pets* pet);

#endif