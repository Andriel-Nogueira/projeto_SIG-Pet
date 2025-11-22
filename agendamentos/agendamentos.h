#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H

#include "../clientes/clientes.h" // Para verificar se o cliente existe

typedef struct agendamentos
{
    char cpf[16];
    char id_pet[10]; // Alterado de nome_pet para id_pet
    char id_servico[10];
    char data[11];
    char hora[6];
    int status;

} Agendamentos;

typedef struct no_agendamento
{
    Agendamentos agendamento;
    struct no_agendamento *prox;
} NoAgendamento;

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
Agendamentos *tela_agendar(void);
char *tela_buscar_agend(void);
char *tela_atualizar_agend(void);
char *tela_inativar_agend(void);
char *tela_excluir_agend_fisico(void);
void exibir_agendamento(const Agendamentos *agend);

// Funções de Arquivo
void gravar_agendamento(const Agendamentos *agend);
Agendamentos *buscar_agendamento_por_cpf(const char *cpf);
void gravar_atualizacao_agendamento(const Agendamentos *agend);
int remover_agendamento_do_arquivo(const char *cpf);

#endif
