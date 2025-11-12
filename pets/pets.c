#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pets.h"
#include "../utilitarios/utilitarios.h"
#include "../clientes/clientes.h"

void m_pets(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Pets");

        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar pet                                                                   ║\n");
        printf("║          2 - Inativar pet                                                                    ║\n");
        printf("║          3 - Excluir pet (Fisicamente)                                                       ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        op = escolha();
        switch (op)
        {
        case 1:
            cadastrar_pet();
            break;
        case 2:
            inativar_pet();
            break;
        case 3:
            excluir_pet_fisico();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void tela_inativar_pet(char *cpf_busca, char *nome_pet_busca)
{
    exibir_logo();
    exibir_titulo("Inativar Pet (Exclusão Lógica)");
    printf("║      Informe os dados do pet que deseja inativar:                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do dono: ");
    input(nome_pet_busca, 50, "Digite o nome do pet: ");
}

void tela_excluir_pet_fisico(char *cpf_busca, char *nome_pet_busca)
{
    exibir_logo();
    exibir_titulo("Excluir Pet Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe os dados do pet que deseja excluir permanentemente:                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do dono: ");
    input(nome_pet_busca, 50, "Digite o nome do pet: ");
}

Pets *tela_cadastrar_pet(void)
{
    Pets *pet;
    char cpf_busca[15];
    char raca_input[3];

    exibir_logo();
    exibir_titulo("Cadastrar Pet");

    do
    {
        input(cpf_busca, 15, "Digite o CPF do dono do pet (apenas números):");
        if (!validar_numero(cpf_busca))
        {
            printf("\nCPF inválido! Digite apenas números.\n");
        }
    } while (!validar_numero(cpf_busca));

    if (!verificar_cliente_cadastrado(cpf_busca))
    {
        printf("Cliente com CPF %s não encontrado.\n", cpf_busca);
        printf("É necessário cadastrar o cliente primeiro.\n");
        return NULL;
    }

    printf("\nCliente encontrado.\n");
    pet = (Pets *)malloc(sizeof(Pets));
    if (pet == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    strcpy(pet->cpf, cpf_busca);

    do
    {
        input(pet->nome, 50, "Digite o nome do pet:");
        if (!validar_nome(pet->nome))
        {
            printf("\nNome inválido! Digite apenas letras e espaços.\n");
        }
    } while (!validar_nome(pet->nome));

    do
    {
        input(raca_input, 3, "Informe a espécie do seu PET: \n1 - Gato\n2 - Cachorro\n3 - Outro\n\n");
        if (strcmp(raca_input, "1") != 0 && strcmp(raca_input, "2") != 0 && strcmp(raca_input, "3") != 0)
        {
            printf("\nOpção inválida! Por favor, escolha 1, 2 ou 3.\n");
        }
    } while (strcmp(raca_input, "1") != 0 && strcmp(raca_input, "2") != 0 && strcmp(raca_input, "3") != 0);

    if (strcmp(raca_input, "1") == 0)
    {
        strcpy(pet->especie, "G");
    }
    else if (strcmp(raca_input, "2") == 0)
    {
        strcpy(pet->especie, "C");
    }
    else
    {
        strcpy(pet->especie, "O");
    }
    pet->status = True;
    return pet;
}

Pets *buscar_pet(const char *cpf, const char *nome)
{
    FILE *arq_pets;
    Pets *pet;

    arq_pets = fopen("clientes/pets.dat", "rb");
    if (arq_pets == NULL)
    {
        return NULL;
    }

    pet = (Pets *)malloc(sizeof(Pets));
    while (fread(pet, sizeof(Pets), 1, arq_pets))
    {
        if ((strcmp(pet->cpf, cpf) == 0) && (strcmp(pet->nome, nome) == 0) && (pet->status == True))
        {
            fclose(arq_pets);
            return pet;
        }
    }
    fclose(arq_pets);
    free(pet);
    return NULL;
}

void gravar_atualizacao_pet(const Pets *pet_atualizado)
{
    FILE *arq_pets;
    Pets pet_lido;

    arq_pets = fopen("clientes/pets.dat", "r+b");
    if (arq_pets == NULL)
    {
        printf("\nErro ao abrir o arquivo de pets para atualização.\n");
        return;
    }

    while (fread(&pet_lido, sizeof(Pets), 1, arq_pets))
    {
        if ((strcmp(pet_lido.cpf, pet_atualizado->cpf) == 0) && (strcmp(pet_lido.nome, pet_atualizado->nome) == 0))
        {
            fseek(arq_pets, -sizeof(Pets), SEEK_CUR);
            fwrite(pet_atualizado, sizeof(Pets), 1, arq_pets);
            break;
        }
    }
    fclose(arq_pets);
}

void inativar_pet(void)
{
    Pets *pet;
    char cpf_busca[15];
    char nome_pet_busca[50];

    tela_inativar_pet(cpf_busca, nome_pet_busca);
    pet = buscar_pet(cpf_busca, nome_pet_busca);

    if (pet != NULL)
    {
        pet->status = False;
        gravar_atualizacao_pet(pet);
        printf("\nPet '%s' inativado com sucesso!\n", nome_pet_busca);
        free(pet);
    }
    else
    {
        printf("\nPet '%s' do cliente com CPF %s não encontrado ou já está inativo.\n", nome_pet_busca, cpf_busca);
    }
    pressione_enter();
}

int remover_pet_do_arquivo(const char *cpf, const char *nome)
{
    FILE *arq_pets, *arq_temp;
    Pets pet;
    int encontrado = 0;

    arq_pets = fopen("clientes/pets.dat", "rb");
    if (arq_pets == NULL)
        return -1;

    arq_temp = fopen("clientes/pets_temp.dat", "wb");
    if (arq_temp == NULL)
    {
        fclose(arq_pets);
        return -1;
    }

    while (fread(&pet, sizeof(Pets), 1, arq_pets))
    {
        if (!((strcmp(pet.cpf, cpf) == 0) && (strcmp(pet.nome, nome) == 0)))
        {
            fwrite(&pet, sizeof(Pets), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_pets);
    fclose(arq_temp);

    if (encontrado)
    {
        remove("clientes/pets.dat");
        rename("clientes/pets_temp.dat", "clientes/pets.dat");
    }
    else
    {
        remove("clientes/pets_temp.dat");
    }
    return encontrado;
}

void excluir_pet_fisico(void)
{
    char cpf_busca[15];
    char nome_pet_busca[50];
    int encontrado = 0;

    tela_excluir_pet_fisico(cpf_busca, nome_pet_busca);
    encontrado = remover_pet_do_arquivo(cpf_busca, nome_pet_busca);

    if (encontrado)
    {
        printf("\nPet '%s' excluído permanentemente com sucesso!\n", nome_pet_busca);
    }
    else
    {
        printf("\nPet '%s' do cliente com CPF %s não encontrado.\n", nome_pet_busca, cpf_busca);
    }
    pressione_enter();
}

void gravar_pet(Pets *pet)
{
    FILE *arq_pets;
    arq_pets = fopen("clientes/pets.dat", "ab");
    if (arq_pets == NULL)
    {
        printf("Erro na abertura do arquivo de pets!\n");
        return;
    }
    fwrite(pet, sizeof(Pets), 1, arq_pets);
    fclose(arq_pets);
}

void exibir_pet(const Pets *pet)
{
    if (pet == NULL)
    {
        return;
    }
    printf("CPF do cliente: %s\n", pet->cpf);
    printf("Nome do pet: %s\n", pet->nome);
    printf("Espécie: %s\n", pet->especie);
}

void cadastrar_pet(void)
{
    Pets *pet;

    pet = tela_cadastrar_pet();
    if (pet != NULL)
    {
        gravar_pet(pet);
        printf("\nPet cadastrado com sucesso!\n");
        exibir_pet(pet);
        free(pet);
    }

    pressione_enter();
}