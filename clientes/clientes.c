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
        printf("║          5 - Inativar cliente                                                                ║\n");
        printf("║          6 - Excluir cliente (Fisicamente)                                                   ║\n");
        printf("║          7 - Cadastrar pet                                                                   ║\n");
        printf("║          8 - Inativar pet                                                                    ║\n");
        printf("║          9 - Excluir pet (Fisicamente)                                                       ║\n");
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
            inativar_cliente();
            break;
        case 6: 
            excluir_cliente_fisico();
            break;
        case 7: 
            cadastrar_pet();
            break;
        case 8: 
            inativar_pet();
            break;
        case 9:
            excluir_pet_fisico();
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
    Clientes* cli;

    cli = tela_cadastrar_cliente();
    if (cli == NULL) {
        return;
    }
    gravar_cliente(cli);
    printf("Cliente cadastrado com sucesso!\n");
    exibir_cliente(cli);
    pressione_enter();
    free(cli);
}

void buscar_cliente(void)
{
    char cpf_busca[15];
    Clientes* cli = NULL;

    exibir_logo();
    exibir_titulo("Buscar Cliente pelo CPF");

    input(cpf_busca, 15, "Digite o CPF do cliente que deseja buscar: ");

    cli = buscar_cliente_por_cpf(cpf_busca);

    if (cli != NULL) {
        printf("\nCliente encontrado:\n");
        exibir_cliente(cli);
        free(cli);
    } else {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    pressione_enter();
}

void atualizar_cliente(void)
{
    char* cpf_busca;
    Clientes* cli;

    cpf_busca = tela_atualizar_cliente();
    
    if (!verificar_cliente_cadastrado(cpf_busca)) {
        printf("\nCliente com CPF %s não encontrado ou inativo.\n", cpf_busca);
    } else {
        cli = tela_cadastrar_cliente();
        if (cli != NULL) {
            strcpy(cli->cpf, cpf_busca);
            gravar_atualizacao_cliente(cli);
            free(cli);
        }
    }
    free(cpf_busca);
    pressione_enter();
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

    pressione_enter();
}

void inativar_cliente(void)
{
    Clientes* cli;
    char* cpf_busca;

    cpf_busca = tela_inativar_cliente();
    cli = buscar_cliente_por_cpf(cpf_busca);

    if (cli == NULL) {
        printf("\nCliente com CPF %s não encontrado ou já está inativo.\n", cpf_busca);
    } else {
        cli->status = False;
        gravar_atualizacao_cliente(cli);
        printf("\nCliente inativado com sucesso!\n");
    }
    free(cli);
    free(cpf_busca);
    pressione_enter();
}

void excluir_cliente_fisico(void)
{
    char* cpf_busca;
    int encontrado = 0;

    cpf_busca = tela_excluir_cliente_fisico();
    if (cpf_busca == NULL) {
        return;
    }

    encontrado = remover_cliente_do_arquivo(cpf_busca);

    if (encontrado == 1) {
        printf("\nCliente com CPF %s excluído permanentemente com sucesso!\n", cpf_busca);
    } else if (encontrado == 0) {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    free(cpf_busca);
    pressione_enter();
}



Clientes* buscar_cliente_por_cpf(const char* cpf) {
    FILE* arq_clientes;
    Clientes* cli;

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL) {
        return NULL;
    }

    cli = (Clientes*) malloc(sizeof(Clientes));
    while(fread(cli, sizeof(Clientes), 1, arq_clientes)) {
        if ((strcmp(cli->cpf, cpf) == 0) && (cli->status == True)) {
            fclose(arq_clientes);
            return cli;
        }
    }

    fclose(arq_clientes);
    free(cli); 
    return NULL; 
}


Clientes* tela_cadastrar_cliente(void){
    Clientes* cli;
    cli = (Clientes*) malloc(sizeof(Clientes));

    exibir_logo();
    exibir_titulo("Cadastrar Cliente");

    do {
        input(cli->cpf, 15, "Insira seu CPF (apenas números):");
        if (!validar_numero(cli->cpf)) {
            printf("\nCPF inválido! Digite apenas números.\n");
        }
    } while (!validar_numero(cli->cpf));

    if (verificar_cliente_cadastrado(cli->cpf)) {
        printf("\nEste CPF já pertence a um cliente cadastrado.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return NULL;
    }

    input(cli->nome, 50, "Digite o seu nome: ");
    input(cli->data_nascimento, 12, "Digite sua data de nascimento (DD/MM/AAAA): ");
    
    do {
        input(cli->telefone, 20, "Digite seu telefone (10 ou 11 dígitos, com DDD):");
        if (!validar_telefone(cli->telefone)) {
            printf("\nTelefone inválido! Deve conter 10 ou 11 dígitos numéricos.\n");
        }
    } while (!validar_telefone(cli->telefone));

    cli->status = True;
    return cli;
}

char* tela_atualizar_cliente(void) {
    char* cpf_busca;
    cpf_busca = (char*) malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Atualizar Dados do Cliente");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente que deseja atualizar: ");
    return cpf_busca;
}

void exibir_cliente(const Clientes* cli)
{
    if (cli == NULL) {
        return;
    }
    printf("CPF: %s\n", cli->cpf);
    printf("Nome: %s\n", cli->nome);
    printf("Data de nascimento: %s\n", cli->data_nascimento);
    printf("Telefone: %s\n", cli->telefone);
}

void gravar_cliente(Clientes* cli){
    FILE* arq_clientes;
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
}





void tela_inativar_pet(char* cpf_busca, char* nome_pet_busca) {
    exibir_logo();
    exibir_titulo("Inativar Pet (Exclusão Lógica)");
    printf("║      Informe os dados do pet que deseja inativar:                                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do dono: ");
    input(nome_pet_busca, 50, "Digite o nome do pet: ");
}

void tela_excluir_pet_fisico(char* cpf_busca, char* nome_pet_busca) {
    exibir_logo();
    exibir_titulo("Excluir Pet Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe os dados do pet que deseja excluir permanentemente:                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do dono: ");
    input(nome_pet_busca, 50, "Digite o nome do pet: ");
}

Pets* tela_cadastrar_pet(void)
{
    Pets* pet;
    char cpf_busca[15];
    char raca_input[3];

    exibir_logo();
    exibir_titulo("Cadastrar Pet");
    input(cpf_busca, 15, "Digite o CPF do dono do pet: ");

    if (!verificar_cliente_cadastrado(cpf_busca)) {
        printf("Cliente com CPF %s não encontrado.\n", cpf_busca);
        printf("É necessário cadastrar o cliente primeiro.\n");
        return NULL;
    }

    printf("\nCliente encontrado.\n");
    pet = (Pets*) malloc(sizeof(Pets));
    if (pet == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }

    strcpy(pet->cpf, cpf_busca);
    input(pet->nome, 50, "Digite o nome do pet: ");
    input(raca_input, 3, "Informe a espécie do seu PET: \n1 - Gato\n2 - Cachorro\n3 - Outro\n\n");
    
    if (strcmp(raca_input, "1") == 0) { 
        strcpy(pet->especie, "G"); 
    } else if (strcmp(raca_input, "2") == 0) { 
        strcpy(pet->especie, "C"); 
    } else { 
        strcpy(pet->especie, "O"); 
    }
    pet->status = True;
    return pet;
}

Pets* buscar_pet(const char* cpf, const char* nome) {
    FILE* arq_pets;
    Pets* pet;

    arq_pets = fopen("clientes/pets.dat", "rb");
    if (arq_pets == NULL) {
        return NULL;
    }

    pet = (Pets*) malloc(sizeof(Pets));
    while(fread(pet, sizeof(Pets), 1, arq_pets)) {
        if ((strcmp(pet->cpf, cpf) == 0) && (strcmp(pet->nome, nome) == 0) && (pet->status == True)) {
            fclose(arq_pets);
            return pet;
        }
    }
    fclose(arq_pets);
    free(pet);
    return NULL;
}

void gravar_atualizacao_pet(const Pets* pet_atualizado) {
    FILE* arq_pets;
    Pets pet_lido;

    arq_pets = fopen("clientes/pets.dat", "r+b");
    if (arq_pets == NULL) {
        printf("\nErro ao abrir o arquivo de pets para atualização.\n");
        return;
    }

    while(fread(&pet_lido, sizeof(Pets), 1, arq_pets)) {
        if ((strcmp(pet_lido.cpf, pet_atualizado->cpf) == 0) && (strcmp(pet_lido.nome, pet_atualizado->nome) == 0)) {
            fseek(arq_pets, -sizeof(Pets), SEEK_CUR);
            fwrite(pet_atualizado, sizeof(Pets), 1, arq_pets);
            break;
        }
    }
    fclose(arq_pets);
}

void gravar_atualizacao_cliente(const Clientes* cli) {
    FILE* arq_clientes;
    arq_clientes = fopen("clientes/clientes.dat", "r+b");
    if (arq_clientes == NULL) {
        printf("Erro ao abrir o arquivo para atualização.\n");
        return;
    }

    Clientes temp_cli;
    while(fread(&temp_cli, sizeof(Clientes), 1, arq_clientes)) {
        if ((strcmp(temp_cli.cpf, cli->cpf) == 0) && (temp_cli.status == True)) {
            fseek(arq_clientes, -sizeof(Clientes), SEEK_CUR);
            fwrite(cli, sizeof(Clientes), 1, arq_clientes);
            printf("\nCliente atualizado com sucesso!\n");
            break;
        }
    }
    fclose(arq_clientes);
}

void inativar_pet(void)
{
    Pets* pet;
    char cpf_busca[15];
    char nome_pet_busca[50];

    tela_inativar_pet(cpf_busca, nome_pet_busca);
    pet = buscar_pet(cpf_busca, nome_pet_busca);

    if (pet != NULL) {
        pet->status = False;
        gravar_atualizacao_pet(pet);
        printf("\nPet '%s' inativado com sucesso!\n", nome_pet_busca);
        free(pet);
    } else {
        printf("\nPet '%s' do cliente com CPF %s não encontrado ou já está inativo.\n", nome_pet_busca, cpf_busca);
    }
    pressione_enter();
}


int remover_pet_do_arquivo(const char* cpf, const char* nome) {
    FILE *arq_pets, *arq_temp;
    Pets pet;
    int encontrado = 0;

    arq_pets = fopen("clientes/pets.dat", "rb");
    if (arq_pets == NULL) return -1;

    arq_temp = fopen("clientes/pets_temp.dat", "wb");
    if (arq_temp == NULL) {
        fclose(arq_pets);
        return -1;
    }

    while(fread(&pet, sizeof(Pets), 1, arq_pets)) {
        if (!((strcmp(pet.cpf, cpf) == 0) && (strcmp(pet.nome, nome) == 0))) {
            fwrite(&pet, sizeof(Pets), 1, arq_temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_pets);
    fclose(arq_temp);

    if (encontrado) {
        remove("clientes/pets.dat");
        rename("clientes/pets_temp.dat", "clientes/pets.dat");
    } else {
        remove("clientes/pets_temp.dat");
    }
    return encontrado;
}

int remover_cliente_do_arquivo(const char* cpf_busca) {
    FILE *arq_clientes, *arq_temp;
    Clientes cli;
    int encontrado = 0;

    // se retornar -1 significa erro de arquivo

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL) {
        printf("\nNenhum cliente cadastrado. A operação não pode ser concluída.\n");
        return -1; 
    }

    arq_temp = fopen("clientes/clientes_temp.dat", "wb");
    if (arq_temp == NULL) {
        printf("\nErro ao criar arquivo temporário. A operação não pode ser concluída.\n");
        fclose(arq_clientes);
        return -1;
    }

    while(fread(&cli, sizeof(Clientes), 1, arq_clientes)) {
        if (strcmp(cli.cpf, cpf_busca) != 0) {
            fwrite(&cli, sizeof(Clientes), 1, arq_temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq_clientes);
    fclose(arq_temp);

    if (encontrado) {
        remove("clientes/clientes.dat");
        rename("clientes/clientes_temp.dat", "clientes/clientes.dat");
    } else {
        remove("clientes/clientes_temp.dat");
    }

    return encontrado;
}

void excluir_pet_fisico(void) {
    char cpf_busca[15];
    char nome_pet_busca[50];
    int encontrado = 0;

    tela_excluir_pet_fisico(cpf_busca, nome_pet_busca);
    encontrado = remover_pet_do_arquivo(cpf_busca, nome_pet_busca);

    if (encontrado) {
        printf("\nPet '%s' excluído permanentemente com sucesso!\n", nome_pet_busca);
    } else {
        printf("\nPet '%s' do cliente com CPF %s não encontrado.\n", nome_pet_busca, cpf_busca);
    }
    pressione_enter();
}

char* tela_inativar_cliente(void) {
    char* cpf_busca;
    cpf_busca = (char*) malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Inativar Cliente (Exclusão Lógica)");
    printf("║      Informe o CPF do cliente que deseja inativar:                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente: ");
    return cpf_busca;
}

char* tela_excluir_cliente_fisico(void) {

    char* cpf_busca;
    cpf_busca = (char*) malloc(15 * sizeof(char));
    if (cpf_busca == NULL) {
        printf("Erro de alocação de memória!\n");
        pressione_enter();
        return NULL;
    }
    exibir_logo();
    exibir_titulo("Excluir Cliente Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o CPF do cliente que deseja excluir permanentemente:                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do cliente: ");
    return cpf_busca;
}



void gravar_pet(Pets* pet) {
    FILE* arq_pets;
    arq_pets = fopen("clientes/pets.dat", "ab");
    if (arq_pets == NULL) {
        printf("Erro na abertura do arquivo de pets!\n");
        return;
    }
    fwrite(pet, sizeof(Pets), 1, arq_pets);
    fclose(arq_pets);
}

void exibir_pet(const Pets* pet) {
    if (pet == NULL) {
        return;
    }
    printf("CPF do cliente: %s\n", pet->cpf);
    printf("Nome do pet: %s\n", pet->nome);
    printf("Espécie: %s\n", pet->especie);
}

void cadastrar_pet(void)
{
    Pets* pet;

    pet = tela_cadastrar_pet();
    if (pet != NULL) {
        gravar_pet(pet);
        printf("\nPet cadastrado com sucesso!\n");
        exibir_pet(pet);
        free(pet);
    }

    pressione_enter();
}


int verificar_cliente_cadastrado(const char* cpf) {
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
