#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

#include "../clientes/clientes.h" // Para verificar se o cliente existe

typedef struct agendamentos
{
    char cpf[15];
    char nome_pet[30];
    char data[11];
    char hora[6];
    int status;

} Agendamentos;

// Módulo Principal
void m_agendamento(void);

//// Funções de Gerenciamento de Agendamentos ////
void agendar(void);
void buscar_agend(void);
void atualizar_agend(void);
void listar_agend(void);
void inativar_agend(void);
void excluir_agend_fisico(void);

// Funções de Tela
Agendamentos* tela_agendar(void);
char* tela_buscar_agend(void);
char* tela_atualizar_agend(void);
char* tela_inativar_agend(void);
char* tela_excluir_agend_fisico(void);
void exibir_agendamento(const Agendamentos* agend);

#endif
