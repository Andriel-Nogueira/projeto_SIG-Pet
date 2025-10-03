#ifndef CLIENTES_H
#define CLIENTES_H

void m_clientes(void);
void cadastrar_cliente(void);
void buscar_cliente(void);
void atualizar_cliente(void);
void listar_clientes(void);
void excluir_cliente(void);
void cadastrar_pet(void);


struct clientes
{
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];

    char cpf_lido[15];
    char status;
};

struct pets
{
    char cpf[15];
    char nome[50];
    char especie[2];
};



#endif