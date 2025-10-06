#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "../utilitarios/utilitarios.h"

typedef struct agendamentos Agendamentos;

void m_agendamento(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Agendamento");

        printf("║                                                                                              ║\n");
        printf("║          1 - Agendar serviço                                                                 ║\n");
        printf("║          2 - Buscar agendamento pelo cliente                                                 ║\n");
        printf("║          3 - Atualizar agendamento                                                           ║\n");
        printf("║          4 - Listar agendamentos                                                             ║\n");
        printf("║          5 - Excluir agendamento                                                             ║\n");
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
            agendar();
            break;
        case 2:
            buscar_agend();
            break;
        case 3:
            atualizar_agend();
            break;
        case 4:
            listar_agend();
            break;
        case 5:
            excluir_agend();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void agendar(void)
{
    Agendamentos agend;
    exibir_logo();
    exibir_titulo("Agendar Serviço");
    input(agend.cpf, 15, "Insira seu CPF:");
    input(agend.nome_pet, 30, "Digite o nome do Pet");
    input(agend.data, 11, "Insira a data desejada: xx/xx");
    input(agend.hora, 6, "Insira o horário desejado: xx:xx\n");
    input(agend.telefone, 20, "Insira seu telefone para contato:");
    printf("\nAgendamento feito com sucesso\n");
    printf("CPF: %s.\nNome do pet: %s.\nData: %s.\nHorário: %s.\nTelefone: %s.", agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone);
    salvar("agendamentos/agendamentos.csv", 5, agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_agend(void)
{
    Agendamentos agend;
    FILE *arq_agendamentos;

    exibir_logo();
    exibir_titulo("Buscar Agendamento pelo CPF");
    input(agend.cpf_lido, 15, "Digite o CPF do cliente que realizou o agendamento: ");
    arq_agendamentos = fopen("agendamentos/agendamentos.csv", "rt");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado.\n");
        getchar();
        return;
    }
    // Loop para ler o arquivo até o fim, verificando o retorno de fscanf
    while (fscanf(arq_agendamentos, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone) == 5)
    {
        if (strcmp(agend.cpf, agend.cpf_lido) == 0)
        {
            printf("\nAgendamento encontrado.");
            printf("CPF: %s\n", agend.cpf);
            printf("Nome do Pet: %s\n", agend.nome_pet);
            printf("Data do Agendamento: %s\n", agend.data);
            printf("Horário do Agendamento: %s\n", agend.hora);
            printf("Telefone: %s\n", agend.telefone);
            printf("Pressione enter para continuar...");
            getchar();
            fclose(arq_agendamentos);

            return;
        }
   
    }
    fclose(arq_agendamentos);
    printf("\nAgendamento com CPF %s não encontrado.\n", agend.cpf_lido);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_agend(void)
{
    Agendamentos agend;
    FILE *arq_agendamentos;
    FILE *arq_agendamentos_temp;
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Agendamento");
    printf("║         Informe o CPF agendado que deseja atualizar:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(agend.cpf_lido, 15, "Digite o CPF do agendamento que deseja atualizar: ");

    arq_agendamentos = fopen("agendamentos/agendamentos.csv", "rt");
    arq_agendamentos_temp = fopen("agendamentos/agendamentos_temp.csv", "wt");

    if (arq_agendamentos_temp == NULL || arq_agendamentos == NULL)
    {
        printf("Erro ao abrir os arquivos!\n");
        if(arq_agendamentos) fclose(arq_agendamentos);
        if(arq_agendamentos_temp) fclose(arq_agendamentos_temp);
        fclose(arq_agendamentos);
        getchar();
        return;
    }

    while (fscanf(arq_agendamentos, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", agend.cpf, agend.data, agend.hora, agend.nome_pet, agend.telefone) == 5)
    {
        if (strcmp(agend.cpf_lido, agend.cpf) == 0)
        {
            encontrado = 1;
            printf("Agendamento encontrado.\n");
            printf("CPF: %s\nNome do Pet: %s\nData: %s\nHorário: %s\nTelefone: %s\n", agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone);
            printf("Insira os novos dados do agendamento:\n");
            input(agend.nome_pet, 30, "Digite o nome do Pet");
            input(agend.data, 11, "Insira a nova data desejada: xx/xx");
            input(agend.hora, 6, "Insira o novo horário desejado: xx:xx\n");
            input(agend.telefone, 20, "Insira seu telefone para contato:");
            fprintf(arq_agendamentos_temp, "%s;%s;%s;%s;%s\n", agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone);
        }
        else
        {
            fprintf(arq_agendamentos_temp, "%s;%s;%s;%s;%s\n", agend.cpf, agend.nome_pet, agend.data, agend.hora, agend.telefone);
        }
    }

    fclose(arq_agendamentos);
    fclose(arq_agendamentos_temp);
    remove("agendamentos/agendamentos.csv");
    rename("agendamentos/agendamentos_temp.csv", "agendamentos/agendamentos.csv");

    if (!encontrado)
    {
        printf("Agendamento com CPF %s não encontrado.\n", agend.cpf_lido);
    }
    
    printf("Dados do agendamento alterados com sucesso!\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
}

void listar_agend(void)
{
    char cpf[15] = "";
    char nome_pet[30] = "";
    char data[11] = "";
    char hora[6] = "";
    char telefone[20] = "";
    FILE *arq_agendamentos;

    exibir_logo();
    exibir_titulo("Listar Agendamentos");
    arq_agendamentos = fopen("agendamentos/agendamentos.csv", "rt");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }
    while (!feof(arq_agendamentos))
    {
        fscanf(arq_agendamentos, "%[^;]", cpf);
        fgetc(arq_agendamentos);
        fscanf(arq_agendamentos, "%[^;]", nome_pet);
        fgetc(arq_agendamentos);
        fscanf(arq_agendamentos, "%[^;]", data);
        fgetc(arq_agendamentos);
        fscanf(arq_agendamentos, "%[^;]", hora);
        fgetc(arq_agendamentos);
        fscanf(arq_agendamentos, "%[^\n]", telefone);
        fgetc(arq_agendamentos);

        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║                                                                                              ║\n");
        printf("║ CPF: %s\t║ Nome do Pet: %s\t║ Data: %s\t║ Hora: %s\t║ Telefone: %s  ║\n", cpf, nome_pet, data, hora, telefone);
        printf("║                                                                                              ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    }
    fclose(arq_agendamentos);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_agend(void)
{
    // EM DESENVOLVIMENTO!!
    exibir_logo();
    exibir_titulo("Excluir Agendamento");
    printf("║      Informe o CPF do Agendamento que deseja excluir:                                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
