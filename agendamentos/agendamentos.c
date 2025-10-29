#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "../utilitarios/utilitarios.h"
#include "../clientes/clientes.h"

// Funções internas
void gravar_agendamento(const Agendamentos *agend);
Agendamentos *buscar_agendamento_por_cpf(const char *cpf);
void gravar_atualizacao_agendamento(const Agendamentos *agend);
int remover_agendamento_do_arquivo(const char *cpf);
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
        op = escolha();
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
            inativar_agend();
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

Agendamentos *tela_agendar(void)
{
    Agendamentos *agend;

    exibir_logo();
    exibir_titulo("Agendar Servico");
    agend = (Agendamentos *)malloc(sizeof(Agendamentos));

    do
    {
        input(agend->cpf, 15, "Insira o CPF do cliente (pode conter '.' e '-'):");
        if (!validar_cpf(agend->cpf))
        {
            printf("\nCPF inválido! Deve conter 11 dígitos numéricos.\n");
        }
    } while (!validar_cpf(agend->cpf));

    if (!verificar_cliente_cadastrado(agend->cpf))
    {
        printf("\nCliente com CPF %s não encontrado. É necessário cadastrar o cliente primeiro.\n", agend->cpf);
        free(agend);
        return NULL;
    }

    do
    {
        input(agend->nome_pet, 30, "Digite o nome do Pet:");
        if (!validar_nome(agend->nome_pet))
        {
            printf("\nNome inválido! Digite um nome para o pet.\n");
        }
    } while (!validar_nome(agend->nome_pet));

    int dia, mes, ano;
    printf("Digite a data do agendamento:\n");
    ler_data(&dia, &mes, &ano);
    sprintf(agend->data, "%02d/%02d/%04d", dia, mes, ano);

    input(agend->hora, 6, "Insira o horário desejado (HH:MM):");

    agend->status = True;
    return agend;
}

void agendar(void)
{
    Agendamentos *agend = tela_agendar();
    if (agend != NULL)
    {
        gravar_agendamento(agend);
        printf("\nAgendamento realizado com sucesso!\n");
        exibir_agendamento(agend);
        free(agend);
    }
    pressione_enter();
}

char *tela_buscar_agend(void)
{
    char *cpf_busca = (char *)malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Buscar Agendamento pelo CPF");
    input(cpf_busca, 15, "Digite o CPF do cliente que realizou o agendamento:");
    return cpf_busca;
}

void buscar_agend(void)
{
    char *cpf_busca = tela_buscar_agend();
    Agendamentos *agend = buscar_agendamento_por_cpf(cpf_busca);

    if (agend != NULL)
    {
        printf("\nAgendamento encontrado:\n");
        exibir_agendamento(agend);
        free(agend);
    }
    else
    {
        printf("\nNenhum agendamento ativo encontrado para o CPF %s.\n", cpf_busca);
    }
    free(cpf_busca);
    pressione_enter();
}

char *tela_atualizar_agend(void)
{
    char *cpf_busca = (char *)malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Atualizar Agendamento");
    printf("║         Informe o CPF agendado que deseja atualizar:                                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do agendamento que deseja atualizar:");
    return cpf_busca;
}

void atualizar_agend(void)
{
    char *cpf_busca = tela_atualizar_agend();
    Agendamentos *agend_antigo = buscar_agendamento_por_cpf(cpf_busca);

    if (agend_antigo == NULL)
    {
        printf("\nAgendamento para o CPF %s não encontrado ou inativo.\n", cpf_busca);
    }
    else
    {
        printf("\nAgendamento encontrado. Insira os novos dados:\n");
        Agendamentos *agend_novo = (Agendamentos *)malloc(sizeof(Agendamentos));

        strcpy(agend_novo->cpf, agend_antigo->cpf); // Mantém o CPF original

        do
        {
            input(agend_novo->nome_pet, 30, "Digite o nome do Pet:");
        } while (!validar_nome(agend_novo->nome_pet));

        int dia, mes, ano;
        printf("Digite a nova data do agendamento:\n");
        ler_data(&dia, &mes, &ano);
        sprintf(agend_novo->data, "%02d/%02d/%04d", dia, mes, ano);

        input(agend_novo->hora, 6, "Insira o novo horário desejado (HH:MM):");
        agend_novo->status = True;

        gravar_atualizacao_agendamento(agend_novo);
        printf("\nAgendamento atualizado com sucesso!\n");
        free(agend_novo);
    }
    free(agend_antigo);
    free(cpf_busca);
    pressione_enter();
}

void listar_agend(void)
{
    FILE *arq_agendamentos;
    Agendamentos agend;

    exibir_logo();
    exibir_titulo("Listar Agendamentos");

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado ou erro ao abrir o arquivo.\n");
    }
    else
    {
        while (fread(&agend, sizeof(Agendamentos), 1, arq_agendamentos))
        {
            if (agend.status == True)
            {
                printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
                exibir_agendamento(&agend);
                printf("════════════════════════════════════════════════════════════════════════════════════════════════\n");
            }
        }
        fclose(arq_agendamentos);
    }
    pressione_enter();
}

char *tela_inativar_agend(void)
{
    char *cpf_busca = (char *)malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Inativar Agendamento");
    printf("║      Informe o CPF referente ao agendamento que deseja excluir:                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF referente ao agendamento que deseja inativar:");
    return cpf_busca;
}

void inativar_agend(void)
{
    char *cpf_busca = tela_inativar_agend();
    Agendamentos *agend = buscar_agendamento_por_cpf(cpf_busca);

    if (agend != NULL)
    {
        agend->status = False;
        gravar_atualizacao_agendamento(agend);
        printf("\nAgendamento inativado com sucesso!\n");
        free(agend);
    }
    else
    {
        printf("\nAgendamento com CPF %s não encontrado ou já inativo.\n", cpf_busca);
    }
    free(cpf_busca);
    pressione_enter();
}

char *tela_excluir_agend_fisico(void)
{
    char *cpf_busca = (char *)malloc(15 * sizeof(char));
    exibir_logo();
    exibir_titulo("Excluir Agendamento Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o CPF do agendamento que deseja excluir permanentemente:                        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_busca, 15, "Digite o CPF do agendamento que deseja excluir permanentemente:");
    return cpf_busca;
}

void excluir_agend_fisico(void)
{
    char *cpf_busca = tela_excluir_agend_fisico();
    int encontrado = remover_agendamento_do_arquivo(cpf_busca);

    if (encontrado == 1)
    {
        printf("\nAgendamento com CPF %s excluído permanentemente com sucesso!\n", cpf_busca);
    }
    else if (encontrado == 0)
    {
        printf("\nAgendamento com CPF %s não encontrado.\n", cpf_busca);
    }
    free(cpf_busca);
    pressione_enter();
}

void exibir_agendamento(const Agendamentos *agend)
{
    if (agend == NULL)
    {
        return;
    }
    printf("CPF do Cliente: %s\n", agend->cpf);
    printf("Nome do Pet: %s\n", agend->nome_pet);
    printf("Data: %s\n", agend->data);
    printf("Hora: %s\n", agend->hora);
}

void gravar_agendamento(const Agendamentos *agend)
{
    FILE *arq_agendamentos = fopen("agendamentos/agendamentos.dat", "ab");
    if (arq_agendamentos == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    fwrite(agend, sizeof(Agendamentos), 1, arq_agendamentos);
    fclose(arq_agendamentos);
}

Agendamentos *buscar_agendamento_por_cpf(const char *cpf)
{
    FILE *arq_agendamentos;
    Agendamentos *agend;

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        return NULL;
    }

    agend = (Agendamentos *)malloc(sizeof(Agendamentos));
    while (fread(agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if ((strcmp(agend->cpf, cpf) == 0) && (agend->status == True))
        {
            fclose(arq_agendamentos);
            return agend;
        }
    }
    fclose(arq_agendamentos);
    free(agend);
    return NULL;
}

void gravar_atualizacao_agendamento(const Agendamentos *agend_atualizado)
{
    FILE *arq_agendamentos;
    Agendamentos agend_lido;

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "r+b");
    if (arq_agendamentos == NULL)
    {
        printf("\nErro ao abrir o arquivo de agendamentos para atualização.\n");
        return;
    }

    while (fread(&agend_lido, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (strcmp(agend_lido.cpf, agend_atualizado->cpf) == 0)
        {
            fseek(arq_agendamentos, -sizeof(Agendamentos), SEEK_CUR);
            fwrite(agend_atualizado, sizeof(Agendamentos), 1, arq_agendamentos);
            break;
        }
    }
    fclose(arq_agendamentos);
}

int remover_agendamento_do_arquivo(const char *cpf)
{
    FILE *arq_agendamentos, *arq_temp;
    Agendamentos agend;
    int encontrado = 0;

    arq_agendamentos = fopen("agendamentos/agendamentos.dat", "rb");
    if (arq_agendamentos == NULL)
    {
        return -1;
    }

    arq_temp = fopen("agendamentos/agendamentos_temp.dat", "wb");
    if (arq_temp == NULL)
    {
        fclose(arq_agendamentos);
        return -1;
    }

    while (fread(&agend, sizeof(Agendamentos), 1, arq_agendamentos))
    {
        if (strcmp(agend.cpf, cpf) != 0)
        {
            fwrite(&agend, sizeof(Agendamentos), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_agendamentos);
    fclose(arq_temp);

    if (encontrado)
    {
        remove("agendamentos/agendamentos.dat");
        rename("agendamentos/agendamentos_temp.dat", "agendamentos/agendamentos.dat");
    }
    else
    {
        remove("agendamentos/agendamentos_temp.dat");
    }

    return encontrado;
}
