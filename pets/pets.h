#ifndef PETS_H
#define PETS_H

#include "../clientes/clientes.h"

typedef struct pets
{
    char cpf[15];
    char nome[50];
    char especie[2];
    int status;
    int id;
} Pets;

// Módulo Principal
void m_pets(void);

//// Funções de Gerenciamento de Pets ////
void cadastrar_pet(void);
void inativar_pet(void);
void excluir_pet_fisico(void);

// Funções de Tela (Pet)
Pets *tela_cadastrar_pet(void);
void tela_inativar_pet(char *cpf_busca, char *nome_pet_busca);
void tela_excluir_pet_fisico(char *cpf_busca, char *nome_pet_busca);
void exibir_pet(const Pets *pet);

// Funções de Arquivo (Pet)
void gravar_pet(Pets *pet);
void gravar_atualizacao_pet(const Pets *pet);
int remover_pet_do_arquivo(const char *cpf, const char *nome);
Pets *buscar_pet(const char *cpf, const char *nome);

#endif