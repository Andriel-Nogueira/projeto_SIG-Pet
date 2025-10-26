#ifndef SERVICOS_H
#define SERVICOS_H

void m_servicos(void);
void cadastrar_servico(void);
void buscar_servico(void);
void atualizar_servico(void);
void listar_servicos(void);
void excluir_servico(void);
void excluir_servico_fisico(void);

struct servicos
{
    char nome[50];
    char desc[256];
    char preco_s[32];
    char id_gerado[20];
    int status;

};

#endif
