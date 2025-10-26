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

void m_clientes(void);
void cadastrar_cliente(void);
void buscar_cliente(void);
void atualizar_cliente(void);
void listar_clientes(void);
void inativar_cliente(void);
void excluir_cliente_fisico(void);
void cadastrar_pet(void);
void inativar_pet(void);
void excluir_pet_fisico(void);
Clientes* tela_cadastrar_cliente(void);
char* tela_excluir_cliente_fisico(void);
int remover_cliente_do_arquivo(const char* cpf);
void gravar_cliente(Clientes*);


#endif