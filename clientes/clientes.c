#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "../utilitarios/utilitarios.h"


typedef struct clientes Clientes;
typedef struct pets Pets;

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
    Clientes cli;
    exibir_logo();
    exibir_titulo("Cadastrar Cliente");
    input(cli.cpf, 15, "Insira seu cpf");
    input(cli.nome, 50, "Digite o seu nome: ");
    input(cli.data_nascimento, 12, "Digite sua data de nascimento (DD/MM/AAAA): ");
    input(cli.telefone, 20, "Digite seu telefone: ");
    printf("Cliente cadastrado com sucesso!\n");
    printf("Nome: %s.\nCPF: %s.\nData nascimento: %s.\nTelefone: %s.\n", cli.nome, cli.cpf, cli.data_nascimento, cli.telefone);
    salvar("clientes/clientes.csv", 4, cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_cliente(void)
{
    Clientes cli;
    FILE *arq_clientes;

    exibir_logo();
    exibir_titulo("Buscar Cliente pelo CPF");
    input(cli.cpf_lido, 15, "Digite o CPF do cliente que deseja buscar: ");
    arq_clientes = fopen("clientes/clientes.csv", "rt");
    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        getchar();
        return;
    }
    // Loop para ler o arquivo até o fim, verificando o retorno de fscanf
    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone) == 4)
    {
        if (strcmp(cli.cpf, cli.cpf_lido) == 0)
        {
            printf("\nCliente encontrado.");
            printf("CPF: %s\n", cli.cpf);
            printf("Nome: %s\n", cli.nome);
            printf("Data de nascimento: %s\n", cli.data_nascimento);
            printf("Telefone: %s\n", cli.telefone);
            printf("Pressione enter para continuar...");
            getchar();
            fclose(arq_clientes);

            return;
        }
   
    }
    fclose(arq_clientes);
    printf("\nCliente com CPF %s não encontrado.\n", cli.cpf_lido);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_cliente(void)
{
    Clientes cli;
    FILE *arq_clientes;
    FILE *arq_clientes_temp;
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Dados do Cliente");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cli.cpf_lido, 15, "Digite o CPF do cliente que deseja atualizar: ");

    arq_clientes = fopen("clientes/clientes.csv", "rt");
    arq_clientes_temp = fopen("clientes/clientes_temp.csv", "wt");

    if (arq_clientes == NULL || arq_clientes_temp == NULL) {
        printf("\nErro ao abrir os arquivos!\n");
        if (arq_clientes) fclose(arq_clientes);
        if (arq_clientes_temp) fclose(arq_clientes_temp);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone) == 4) {
        if (strcmp(cli.cpf_lido, cli.cpf) == 0) {
            encontrado = 1;
            printf("\nCliente encontrado:\n");
            printf("CPF: %s\nNome: %s\nData de Nascimento: %s\nTelefone: %s\n\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);
            printf("Digite os novos dados:\n");
            input(cli.nome, 50, "Digite o novo nome: ");
            input(cli.data_nascimento, 12, "Digite a nova data de nascimento (DD/MM/AAAA): ");
            input(cli.telefone, 20, "Digite o novo telefone: ");
            fprintf(arq_clientes_temp, "%s;%s;%s;%s\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);
            printf("\nCliente atualizado com sucesso!\n");
        } else {
            fprintf(arq_clientes_temp, "%s;%s;%s;%s\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);
        }
    }

    fclose(arq_clientes);
    fclose(arq_clientes_temp);
    remove("clientes/clientes.csv");
    rename("clientes/clientes_temp.csv", "clientes/clientes.csv");

    if (!encontrado) {
        printf("\nCliente com CPF %s não encontrado.\n", cli.cpf_lido);
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_clientes(void)
{
    FILE *arq_clientes;
    Clientes cli;

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
    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone) == 4)
    {
        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
        
        printf("CPF: %s\t║ Nome: %s\t║ Data de nascimento: %s\t║ Telefone: %s\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);

        printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
    }
    fclose(arq_clientes);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_cliente(void)
{
    Clientes cli;
    FILE *arq_clientes;
    FILE *arq_clientes_temp;
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Cliente");
    printf("║      Informe o CPF do cliente que deseja excluir:                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cli.cpf_lido, 15, "Digite o CPF do cliente que deseja excluir: ");

    arq_clientes = fopen("clientes/clientes.csv", "rt");
    if (arq_clientes == NULL) {
        printf("\nErro ao abrir o arquivo de clientes. Nenhum cliente cadastrado?\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_clientes_temp = fopen("clientes/clientes_temp.csv", "wt");
    if (arq_clientes_temp == NULL) {
        printf("\nErro ao criar arquivo temporário.\n");
        fclose(arq_clientes);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fscanf(arq_clientes, "%[^;];%[^;];%[^;];%[^\n]\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone) == 4) {
        if (strcmp(cli.cpf_lido, cli.cpf) != 0) {
            fprintf(arq_clientes_temp, "%s;%s;%s;%s\n", cli.cpf, cli.nome, cli.data_nascimento, cli.telefone);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_clientes);
    fclose(arq_clientes_temp);
    remove("clientes/clientes.csv");
    rename("clientes/clientes_temp.csv", "clientes/clientes.csv");

    if (encontrado) {
        printf("\nCliente excluído com sucesso!\n");
    } else {
        printf("\nCliente com CPF %s não encontrado.\n", cli.cpf_lido);
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void cadastrar_pet(void)
{
    Clientes cli;
    Pets pet;
    char raca_input[3];
    FILE  *arq_clientes;
    int encontrado = 0;
    char linha[256];

    exibir_logo();
    exibir_titulo("Cadastrar Pet");
    input(cli.cpf_lido, 15, "Digite o CPF do dono do pet: ");
    arq_clientes = fopen("clientes/clientes.csv", "rt");
    
    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado.\n");
        getchar();
        return;
    }

    // Procura o cliente pelo CPF
    while (fgets(linha, sizeof(linha), arq_clientes) != NULL) {
        sscanf(linha, "%[^;]", cli.cpf);
        if (strcmp(cli.cpf, cli.cpf_lido) == 0) {
            encontrado = 1;
            break;
        }
    }
    fclose(arq_clientes);

    if (encontrado == 1) {
        printf("\nCliente encontrado.\n");
        strcpy(pet.cpf, cli.cpf_lido); // Copia o CPF para a struct do pet
        input(pet.nome, 50, "Digite o nome do pet: ");
        input(raca_input, 3, "Informe a espécie do seu PET: \n1 - Gato\n2 - Cachorro\n3 - Outro\n\n");
        
        if (strcmp(raca_input, "1") == 0) { 

            strcpy(pet.especie, "G"); 
        } 
        else if (strcmp(raca_input, "2") == 0) { 

            strcpy(pet.especie, "C"); 
        } 
        else { 
            
            strcpy(pet.especie, "O"); 
        }

        printf("Pet cadastrado com sucesso!\n");
        printf("CPF do cliente: %s.\nNome: %s.\nEspécie: %s.\n", pet.cpf, pet.nome, pet.especie);
        salvar("clientes/pets.csv", 3, pet.cpf, pet.nome, pet.especie);
    }
    else {
        printf("Cliente com CPF %s não encontrado.\n", cli.cpf_lido);
        printf("É necessário cadastrar o cliente primeiro.\n");
    }

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
