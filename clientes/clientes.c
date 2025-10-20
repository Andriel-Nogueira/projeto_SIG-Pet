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
        printf("║          5 - Inativar cliente                                                                ║\n");
        printf("║          6 - Excluir cliente (Fisicamente)                                                   ║\n");
        printf("║          7 - Cadastrar Pet                                                                   ║\n");
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
            excluir_cliente_fisico();
            break;
        case 7: 
            cadastrar_pet();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

// verifica se um cliente já está cadastrado e ativo
int verif_cli_cadastrado(const char* cpf) {
    FILE* arq_clientes;
    Clientes* cli;
    int encontrado = 0;

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL) {
        return 0; // Se o arquivo não existe, o cliente não pode estar cadastrado
    }

    cli = (Clientes*) malloc(sizeof(Clientes));
    if (cli == NULL) {
        fclose(arq_clientes);
        return 0; // Falha na alocação de memória
    }
    
    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if ((strcmp(cli->cpf, cpf) == 0) && (cli->status == True)) {
            encontrado = 1;
            break;
        }
    }
    fclose(arq_clientes);
    free(cli);
    return encontrado;
}

void cadastrar_cliente(void)
{
    Clientes* cli;
    FILE* arq_clientes;
    cli = (Clientes*) malloc(sizeof(Clientes));

    exibir_logo();
    exibir_titulo("Cadastrar Cliente");


    input(cli->cpf, 15, "Insira seu cpf");

    if (verif_cli_cadastrado(cli->cpf)) {
        printf("\nEste CPF já pertence a um cliente cadastrado.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }

    input(cli->nome, 50, "Digite o seu nome: ");
    input(cli->data_nascimento, 12, "Digite sua data de nascimento (DD/MM/AAAA): ");
    input(cli->telefone, 20, "Digite seu telefone: ");
    cli->status = True;

    arq_clientes = fopen("clientes/clientes.dat", "ab");
    if (arq_clientes == NULL) {
        printf("Erro na abertura do arquivo!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }
    fwrite(cli, sizeof(Clientes), 1, arq_clientes);
    fclose(arq_clientes);

    printf("Cliente cadastrado com sucesso!\n");
    printf("Nome: %s.\nCPF: %s.\nData nascimento: %s.\nTelefone: %s.\n", cli->nome, cli->cpf, cli->data_nascimento, cli->telefone);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    free(cli);
}

void buscar_cliente(void)
{
    Clientes* cli;
    FILE *arq_clientes;
    char cpf_busca[15];

    exibir_logo();
    exibir_titulo("Buscar Cliente pelo CPF");

    input(cpf_busca, 15, "Digite o CPF do cliente que deseja buscar: ");

    if (verif_cli_cadastrado(cpf_busca)) {
        cli = (Clientes*) malloc(sizeof(Clientes));
        arq_clientes = fopen("clientes/clientes.dat", "rb");
        if (arq_clientes == NULL) { // Verificação extra de segurança
            printf("Erro ao abrir o arquivo para leitura.\n");
            free(cli);
            return;
        }
        while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
            if ((strcmp(cli->cpf, cpf_busca) == 0) && (cli->status == True)) {
                printf("\nCliente encontrado:\n");
                printf("CPF: %s\n", cli->cpf);
                printf("Nome: %s\n", cli->nome);
                printf("Data de nascimento: %s\n", cli->data_nascimento);
                printf("Telefone: %s\n", cli->telefone);
            }
        }
        fclose(arq_clientes);
        free(cli);
    } else {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    printf("\nPressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_cliente(void)
{
    Clientes* cli;
    FILE *arq_clientes;
    char cpf_busca[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Dados do Cliente");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente que deseja atualizar: ");

    cli = (Clientes*) malloc(sizeof(Clientes));
    arq_clientes = fopen("clientes/clientes.dat", "r+b");

    if (arq_clientes == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }

    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if ((strcmp(cli->cpf, cpf_busca) == 0) && (cli->status == True)) {
            encontrado = 1;
            printf("\nCliente encontrado:\n");
            printf("CPF: %s\nNome: %s\nData de Nascimento: %s\nTelefone: %s\n\n", cli->cpf, cli->nome, cli->data_nascimento, cli->telefone);
            printf("Digite os novos dados:\n");
            input(cli->nome, 50, "Digite o novo nome: ");
            input(cli->data_nascimento, 12, "Digite a nova data de nascimento (DD/MM/AAAA): ");
            input(cli->telefone, 20, "Digite o novo telefone: ");
            
            fseek(arq_clientes, -sizeof(Clientes), SEEK_CUR);
            fwrite(cli, sizeof(Clientes), 1, arq_clientes);
            printf("\nCliente atualizado com sucesso!\n");
        }
    }

    if (!encontrado) {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    fclose(arq_clientes);
    free(cli);
}

void listar_clientes(void)
{
    FILE* arq_clientes;
    Clientes* cli;

    exibir_logo();
    exibir_titulo("Listar de Clientes");
    
    cli = (Clientes*) malloc(sizeof(Clientes));
    arq_clientes = fopen("clientes/clientes.dat", "rb");

    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }

    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if (cli->status == True) {
            printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
            printf("CPF: %s\t║ Nome: %s\t║ Data de nascimento: %s\t║ Telefone: %s\n", cli->cpf, cli->nome, cli->data_nascimento, cli->telefone);
            printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
        }
    }

    fclose(arq_clientes);
    free(cli);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_cliente(void)
{
    Clientes* cli;
    FILE *arq_clientes;
    char cpf_busca[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Cliente");
    printf("║      Informe o CPF do cliente que deseja excluir:                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente que deseja excluir: ");

    cli = (Clientes*) malloc(sizeof(Clientes));
    arq_clientes = fopen("clientes/clientes.dat", "r+b");

    if (arq_clientes == NULL) {
        printf("\nErro ao abrir o arquivo de clientes. Nenhum cliente cadastrado?\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }

    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if ((strcmp(cli->cpf, cpf_busca) == 0) && (cli->status == True)) {
            encontrado = 1;
            cli->status = False; // Marca como inativo
            fseek(arq_clientes, -sizeof(Clientes), SEEK_CUR);
            fwrite(cli, sizeof(Clientes), 1, arq_clientes);
            printf("\nCliente excluído com sucesso!\n");
        }
    }

    if (!encontrado) {
        printf("\nCliente com CPF %s não encontrado ou já excluído.\n", cpf_busca);
    }

    fclose(arq_clientes);
    free(cli);
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_cliente_fisico(void)
{
    Clientes* cli;
    FILE *arq_clientes;
    FILE *arq_temp;
    char cpf_busca[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Cliente Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o CPF do cliente que deseja excluir permanentemente:                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente: ");

    cli = (Clientes*) malloc(sizeof(Clientes));
    if (cli == NULL) {
        printf("Erro de alocação de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    arq_temp = fopen("clientes/clientes_temp.dat", "wb");

    if (arq_clientes == NULL || arq_temp == NULL) {
        printf("\nErro ao abrir os arquivos. A operação não pode ser concluída.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        if (arq_clientes) fclose(arq_clientes);
        if (arq_temp) fclose(arq_temp);
        return;
    }

    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if (strcmp(cli->cpf, cpf_busca) != 0) {
            fwrite(cli, sizeof(Clientes), 1, arq_temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_clientes);
    fclose(arq_temp);
    free(cli);

    remove("clientes/clientes.dat");
    rename("clientes/clientes_temp.dat", "clientes/clientes.dat");

    if (encontrado) {
        printf("\nCliente com CPF %s excluído permanentemente com sucesso!\n", cpf_busca);
    } else {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void cadastrar_pet(void)
{
    Pets* pet;
    FILE* arq_pets;

    char cpf_busca[15];
    char raca_input[3];

    exibir_logo();
    exibir_titulo("Cadastrar Pet");
    input(cpf_busca, 15, "Digite o CPF do dono do pet: ");

    if (verif_cli_cadastrado(cpf_busca)) {
        printf("\nCliente encontrado.\n");
        pet = (Pets*) malloc(sizeof(Pets));
        if (pet == NULL) {
            printf("Erro de alocação de memória!\n");
            printf("Pressione <Enter> para voltar...");
            getchar();
            return;
        }

        strcpy(pet->cpf, cpf_busca);
        input(pet->nome, 50, "Digite o nome do pet: ");
        input(raca_input, 3, "Informe a espécie do seu PET: \n1 - Gato\n2 - Cachorro\n3 - Outro\n\n");
        
        if (strcmp(raca_input, "1") == 0) { 
            strcpy(pet->especie, "G"); 
        } 
        else if (strcmp(raca_input, "2") == 0) { 
            strcpy(pet->especie, "C"); 
        } 
        else { 
            strcpy(pet->especie, "O"); 
        }
        pet->status = True;

        arq_pets = fopen("clientes/pets.dat", "ab");
        if (arq_pets == NULL) {
            printf("Erro na abertura do arquivo de pets!\n");
        } else {
            fwrite(pet, sizeof(Pets), 1, arq_pets);
            fclose(arq_pets);
        }
        printf("Pet cadastrado com sucesso!\n");
        printf("CPF do cliente: %s.\nNome: %s.\nEspécie: %s.\n", pet->cpf, pet->nome, pet->especie);
        free(pet);
    }
    else {
        printf("Cliente com CPF %s não encontrado.\n", cpf_busca);
        printf("É necessário cadastrar o cliente primeiro.\n");
    }

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
