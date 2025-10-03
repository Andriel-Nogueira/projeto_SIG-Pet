#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "../utilitarios/utilitarios.h"



void m_clientes(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Clientes");

        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar novo cliente                                                          ║\n");
        printf("║          2 - Buscar cliente pelo CPF                                                         ║\n");
        printf("║          3 - Atualizar clientes                                                              ║\n");
        printf("║          4 - Listar clientes                                                                 ║\n");
        printf("║          5 - Excluir cliente                                                                 ║\n");
        printf("║          6 - Cadastrar Pet                                                                   ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        scanf(" %d", &op);
        getchar();
        switch (op)
        {
        case 1:
            cadastrar_cliente();
            break;
        case 2:
            buscar_cliente();
            break;
        case 3:
            atualizar_cliente();
            break;
        case 4:
            listar_clientes();
            break;
        case 5:
            excluir_cliente();
            break;
        case 6:
            cadastrar_pet();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void cadastrar_cliente(void)
{
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];

    exibir_logo();
    exibir_titulo("Cadastrar Cliente");
    input(cpf, 15, "Insira seu cpf");
    input(nome, 50, "Digite o seu nome: ");
    input(data_nascimento, 12, "Digite sua data de nascimento (DD/MM/AAAA): ");
    input(telefone, 20, "Digite seu telefone: ");
    printf("Cliente cadastrado com sucesso!\n");
    printf("Nome: %s.\nCPF: %s.\nData nascimento: %s.\nTelefone: %s.\n", nome, cpf, data_nascimento, telefone);
    
    salvar("clientes/clientes.csv", 4, cpf, nome, data_nascimento, telefone);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_cliente(void)
{
    char cpf_lido[15];
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];
    FILE *arq_clientes;

    exibir_logo();
    exibir_titulo("Buscar Cliente pelo CPF");
    input(cpf_lido, 15, "Digite o CPF do cliente que deseja buscar: ");
    arq_clientes = fopen("clientes/clientes.csv", "rt");
    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        getchar();
        return;
    }

    // Loop para ler o arquivo até o fim, verificando o retorno de fscanf
    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cpf, nome, data_nascimento, telefone) == 4)
    {
        if (strcmp(cpf, cpf_lido) == 0)
        {
            printf("\nCliente encontrado.");
            printf("CPF: %s\n", cpf);
            printf("Nome: %s\n", nome);
            printf("Data de nascimento: %s\n", data_nascimento);
            printf("Telefone: %s\n", telefone);
            printf("Pressione enter para continuar...");
            getchar();
            fclose(arq_clientes);

            return;
        }
   
    }
    fclose(arq_clientes);
    printf("\nCliente com CPF %s não encontrado.\n", cpf_lido);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_cliente(void)
{
 //   char cpf[15];
 //   char nome[50];
 //   char data_nascimento[12];
 //   char telefone[20];
 //   FILE *arq_clientes;
    char cpf_lido[15];

    exibir_logo();
    exibir_titulo("Atualizar Dados do Cliente");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_lido, 15, "Digite o CPF do cliente que deseja atualizar: ");
    printf("\n");
    printf("\nEM DESENVOLVIMENTO!\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_clientes(void)
{
    FILE *arq_clientes;
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];

    exibir_logo();
    exibir_titulo("Listar de Clientes");
    arq_clientes = fopen("clientes/clientes.csv", "rt");

    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }
    // Loop para ler o arquivo até o fim, verificando o retorno de fscanf
    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cpf, nome, data_nascimento, telefone) == 4)
    {
        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
        
        printf("CPF: %s\t║ Nome: %s\t║ Data de nascimento: %s\t║ Telefone: %s\n", cpf, nome, data_nascimento, telefone);

        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
    }
    fclose(arq_clientes);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_cliente(void)
{
    exibir_logo();
    exibir_titulo("Excluir Cliente");
    printf("║      Informe o CPF do cliente que deseja excluir:                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void cadastrar_pet(void)
{
    char cpf[15];
    char cpf_lido[15];
    char nome[50];
    char especie[2]; // G = gato, C = Cachorro, O = outros
    char raca_input[3];
    FILE  *arq_clientes;
    FILE *arq_pets;
    int encontrado = 0;
    char linha[256];

    exibir_logo();
    exibir_titulo("Cadastrar Pet");
    input(cpf_lido, 15, "Digite o CPF do dono do pet: ");
    arq_clientes = fopen("clientes/clientes.csv", "rt");
    
    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        getchar();
        return;
    }

    while (fgets(linha, sizeof(linha), arq_clientes) != NULL) {
        sscanf(linha, "%[^;]", cpf);
        if (strcmp(cpf, cpf_lido) == 0) {
            encontrado = 1;
            break;
        }
    }
    fclose(arq_clientes);


    if (encontrado == 1) {
        printf("\nCliente encontrado.\n");
        input(nome, 50, "Digite o nome do pet: ");
        input(raca_input, 3, "Informe a espécie do seu PET: \n1 - Gato\n2 - Cachorro\n3 - Outro\n\n");
        
        if (strcmp(raca_input, "1") == 0) {
            strcpy(especie, "G");
        } else if (strcmp(raca_input, "2") == 0) {
            strcpy(especie, "C");
        } else {
            strcpy(especie, "O");
        }

        printf("Pet cadastrado com sucesso!\n");
        printf("CPF do cliente: %s.\nNome: %s.\nEspécie: %s.\n", cpf_lido, nome, especie);
        
        ///SALVAR DADOS ///
        arq_pets = fopen("clientes/pets.csv", "at");
        if (arq_pets == NULL) {
            printf("ERRO AO ABRIR ARQUIVO de pets.csv");
            getchar();
            return;
        }
        
        fprintf(arq_pets, "%s;", cpf_lido);
        fprintf(arq_pets, "%s;", nome);
        fprintf(arq_pets, "%s\n", especie);
        fclose(arq_pets);
        ///              ///

    }
    else {
        printf("Cliente com CPF %s não encontrado.\n", cpf_lido);
        printf("É necessário cadastrar o cliente primeiro.\n");
    }

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
