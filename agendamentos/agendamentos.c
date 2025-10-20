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
        printf("║          5 - Inativar agendamento                                                            ║\n");
        printf("║          6 - Excluir agendamento (Fisicamente)                                               ║\n");
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
        case 6:
            excluir_agend_fisico();
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

    FILE *arq_agendamentos;
    Agendamentos *agend;

    exibir_logo();
    exibir_titulo("Agendar Servico");
    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    input(agend->cpf, 15, "Insira seu CPF:");
    input(agend->nome_pet, 30, "Digite o nome do Pet");
    input(agend->data, 11, "Insira a data desejada: xx/xx");
    input(agend->hora, 6, "Insira o horário desejado: xx:xx");
    input(agend->telefone, 20, "Insira seu telefone para contato:");

    agend->status = True;
    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "ab");
    if (arq_agendamentos == NULL)
    {
        printf("Erro na criação ou abertura do arquivo!\n");
        printf("Pressione <Enter> para voltar ao menu principal...                         \n");
        free(agend);
        getchar();
        return;
    }

    fwrite(agend, sizeof(Agendamentos), 1, arq_agendamentos);
    fclose(arq_agendamentos);

    system("clear");
    printf("\nAgendamento realizado com sucesso!\n");
    printf("\nCPF: %s\n", agend->cpf);
    printf("\nNome do Pet: %s\n", agend->nome_pet);
    printf("\nData do Agendamento: %s\n", agend->data);
    printf("\nHorário do Agendamento: %s\n", agend->hora);
    printf("\nTelefone: %s\n", agend->telefone);
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    printf("\n");

    free(agend);
}

void buscar_agend(void)
{
    FILE *arq_agendamentos;
    Agendamentos *agend;
    int encontrado = 0;
    char cpf_lido[15];

    exibir_logo();
    exibir_titulo("Buscar Agendamento pelo CPF");
    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    input(cpf_lido, 15, "Digite o CPF do cliente que realizou o agendamento: ");

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado.\n");
        free(agend);
        getchar();
        return;
    }

    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if ((strcmp(agend->cpf, cpf_lido) == 0) && (agend->status))
        {
            encontrado = 1;
            printf("\nAgendamento encontrado.\n");
            printf("CPF: %s\n", agend->cpf);
            printf("Nome do Pet: %s\n", agend->nome_pet);
            printf("Data do Agendamento: %s\n", agend->data);
            printf("Horário do Agendamento: %s\n", agend->hora);
            printf("Telefone: %s\n", agend->telefone);
            printf("Pressione enter para continuar...");
            getchar();
            return;
        }
    }
    fclose(arq_agendamentos);
    free(agend);

    if (encontrado)
    {
        printf("\nAgendamento encontrado.\n");
    }
    else
    {
        printf("\nAgendamento não encontrado.\n");
    }

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    printf("\n");
}

void excluir_agend_fisico(void)
{
    FILE *arq_agendamentos;
    FILE *arq_temp;
    Agendamentos *agend;
    char cpf_busca[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Agendamento Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o CPF do agendamento que deseja excluir permanentemente:                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do agendamento que deseja excluir permanentemente: ");

    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    if (agend == NULL)
    {
        printf("\nErro de memória!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    arq_temp = fopen("agendamentos/agendamentos_temp.dat", "wb");

    if (arq_agendamentos == NULL || arq_temp == NULL)
    {
        printf("\nErro ao abrir os arquivos!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(agend);
        if (arq_agendamentos)
            fclose(arq_agendamentos);
        if (arq_temp)
            fclose(arq_temp);
        return;
    }

    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (strcmp(agend->cpf, cpf_busca) != 0)
        {
            fwrite(agend, sizeof(Agendamentos), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_agendamentos);
    fclose(arq_temp);
    free(agend);

    remove("agendamentos/agendamentos.dat");
    rename("agendamentos/agendamentos_temp.dat", "agendamentos/agendamentos.dat");

    if (encontrado)
    {
        printf("\nAgendamento com CPF %s excluído permanentemente com sucesso!\n", cpf_busca);
    }
    else
    {
        printf("\nAgendamento com CPF %s não encontrado.\n", cpf_busca);
    }
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_agend(void)
{
    FILE *arq_agendamentos;
    Agendamentos *agend;
    char cpf_lido[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Atualizar Agendamento");
    printf("║         Informe o CPF agendado que deseja atualizar:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    input(cpf_lido, 15, "Digite o CPF do agendamento que deseja atualizar: ");

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "r+b");
    if (arq_agendamentos == NULL)
    {
        printf("\nErro ao abrir o arquivo de agendamentos.\n");
        free(agend);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if ((strcmp(agend->cpf, cpf_lido) == 0) && (agend->status))
        {
            encontrado = 1;
            printf("Agendamento encontrado.\n");
            printf("CPF: %s\nNome do Pet: %s\nData: %s\nHorário: %s\nTelefone: %s\n", cpf_lido, agend->nome_pet, agend->data, agend->hora, agend->telefone);
            printf("Insira os novos dados do agendamento:\n");
            input(agend->nome_pet, 30, "Digite o nome do Pet");
            input(agend->data, 11, "Insira a nova data desejada: xx/xx");
            input(agend->hora, 6, "Insira o novo horário desejado: xx:xx");
            input(agend->telefone, 20, "Insira seu telefone para contato:");

            fseek(arq_agendamentos, (-1) * sizeof(Agendamentos), SEEK_CUR);
            fwrite(agend, sizeof(Agendamentos), 1, arq_agendamentos);
        }
    }

    fclose(arq_agendamentos);
    free(agend);

    if (encontrado)
    {
        printf("\nAgendamento atualizado com sucesso!\n");
    }
    else
    {
        printf("\nCPF do agendamento não encontrado.\n");
    }
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_agend(void)
{
    FILE *arq_agendamentos;
    Agendamentos *agend;

    exibir_logo();
    exibir_titulo("Listar Agendamentos");

    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    if (agend == NULL)
    {
        printf("Erro de memória.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado ou erro ao abrir o arquivo.\n");
        free(agend);
        printf("Pressione <Enter> para voltar...");
        getchar();
        return;
    }

    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos) == 1)
    {
        if (agend->status)
        {
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
            printf("║                                                                                              ║\n");
            printf("║ CPF: %s\t║ Nome do Pet: %s\t║ Data: %s\t║ Hora: %s\t║ Telefone: %s  ║\n", agend->cpf, agend->nome_pet, agend->data, agend->hora, agend->telefone);
            printf("║                                                                                              ║\n");
            printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        }
    }

    fclose(arq_agendamentos);
    free(agend);

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void excluir_agend(void)
{
    FILE *arq_agendamentos;
    Agendamentos *agend;
    char cpf_lido[15];
    int encontrado = 0;

    exibir_logo();
    exibir_titulo("Excluir Agendamento");
    printf("║      Informe o CPF referente ao agendamento que deseja excluir:                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_lido, 15, "Digite o CPF referente ao agendamento que deseja excluir: ");

    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "r+b");
    if (arq_agendamentos == NULL)
    {
        printf("\nErro ao abrir o arquivo de clientes. Nenhum cliente cadastrado?\n");
        printf("Pressione <Enter> para voltar...");
        free(agend);
        getchar();
        return;
    }

    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if ((strcmp(agend->cpf, cpf_lido) == 0) && (agend->status))
        {
            encontrado = 1;
            agend->status = False; // Exclusão lógica
            fseek(arq_agendamentos, (-1) * sizeof(Agendamentos), SEEK_CUR);
            fwrite(agend, sizeof(Agendamentos), 1, arq_agendamentos);
        }
    }

    fclose(arq_agendamentos);
    free(agend);

    if (encontrado)
    {
        printf("\nAgendamento excluído com sucesso!\n");
    }
    else
    {
        printf("\nAgendamento com CPF %s não encontrado.\n", cpf_lido);
    }

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
