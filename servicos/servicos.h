#ifndef SERVICOS_H
#define SERVICOS_H

typedef struct servicos
{
    char nome[50];
    char desc[256];
    char preco_s[32];
    int id;
    int status;
} Servicos;

// Módulo Principal
void m_servicos(void);

//// Funções de Gerenciamento de Serviços ////
void cadastrar_servico(void);
void buscar_servico(void);
void atualizar_servico(void);
void listar_servicos(void);
void inativar_servico(void);
void excluir_servico_fisico(void);

// Funções de Tela
Servicos* tela_cadastrar_servico(void);
int tela_buscar_servico(void);
int tela_atualizar_servico(void);
int tela_inativar_servico(void);
int tela_excluir_servico_fisico(void);
void exibir_servico(const Servicos* serv);

// Funções de Arquivo e Lógica
void gravar_servico(const Servicos* serv);
Servicos* buscar_servico_por_id(int id);
void gravar_atualizacao_servico(const Servicos* serv);
int remover_servico_do_arquivo(int id);

#endif
