#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agendamentos.h"
#include "utilitarios.h"

void m_agendamento(void)
{
    int op;
    system("clear");
    do
    {
        system("clear");
        printf("\n");
        printf("\n");
        printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
        printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
        printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
        printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
        printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
        printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
        printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
        printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
        printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
        printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║                                   Menu Agendamento                                           ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
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
    
    char cpf[15];
    char data[11];
    char hora[6];
    char nome_pet[30];
    char telefone[20];
    FILE *arq_agendamentos;

    system("clear");
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
    printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
    printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
    printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
    printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
    printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
    printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
    printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
    printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                    Agendar Serviço                                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    input(cpf, 15, "Insira seu CPF:");
    input(nome_pet, 30, "Digite o nome do Pet");
    input(data, 11, "Insira a data desejada: xx/xx");
    input(hora, 6, "Insira o horário desejado: xx:xx\n");
    input(telefone, 20, "Insira seu telefone para contato:");
    
    arq_agendamentos = fopen("agendamentos.csv","at");
    if (arq_agendamentos == NULL){
        printf("ERRO AO ABRIR ARQUIVO");
        return;
    }

    fprintf(arq_agendamentos, "%s;", cpf);
    fprintf(arq_agendamentos, "%s;", nome_pet);
    fprintf(arq_agendamentos, "%s;", data);
    fprintf(arq_agendamentos, "%s;", hora);
    fprintf(arq_agendamentos, "%s\n", telefone);
    fclose(arq_agendamentos);

    printf("\nAgendamento feito com sucesso\n");
    printf("CPF: %s.\nNome do pet: %s.\nData: %s.\nHorário: %s.\nTelefone: %s.", cpf, nome_pet, data, hora, telefone);
   

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_agend(void)
{
    char cpf[15];
    char cpf_lido[20];
    char nome_pet[30];
    char data[20]; 
    char hora[10]; 
    char telefone[20];
    FILE *arq_agendamentos;

    system("clear");
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
    printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
    printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
    printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
    printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
    printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
    printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
    printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
    printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                            Buscar Agendamento pelo CPF                                       ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    
    input(cpf_lido, 15, "Informe o CPF do cliente que fez o agendamento:");

    arq_agendamentos = fopen("agendamentos.csv", "rt");
    if (arq_agendamentos == NULL)
    {
        printf("Nenhum agendamento cadastrado.\n");
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

        if (strcmp(cpf, cpf_lido) == 0)
        {
            printf("\nAgendamento por CPF %s encontrado!:\n", cpf);
            printf("CPF: %s\n", cpf);
            printf("Nome do pet: %s\n", nome_pet);
            printf("Data: %s\n", data);
            printf("Horário: %s\n", hora);
            printf("Telefone: %s\n", telefone);
            printf("Pressione enter para continuar...");
            getchar();
            fclose(arq_agendamentos);

            return;
        }
   
    }
    fclose(arq_agendamentos);
    printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    getchar();
}

void atualizar_agend(void)
{
    system("clear");
    printf("\n");
    // EM DESENVOLVIMENTO!!
    // char cpf[15];
    // char nome[50];
    // char data_nascimento[12];
    // char telefone[20];
    // FILE *arq_clientes;
    char cpf_lido[15];
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
    printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
    printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
    printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
    printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
    printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
    printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
    printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
    printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                 Atualizar Agendamento                                        ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    input(cpf_lido, 15, "Informe o CPF do cliente que fez o agendamento:");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_agend(void)
{
    char cpf[15] = "";
    char nome_pet[30] = "";
    char data[11] = ""; 
    char hora[6] = ""; 
    char telefone[20] = "";
    FILE *arq_agendamentos;

    system("clear");
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
    printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
    printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
    printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
    printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
    printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
    printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
    printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
    printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                 Listar Agendamentos                                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    arq_agendamentos = fopen("agendamentos.csv", "rt");

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
        printf("║ CPF: %s\t║ Nome do Pet: %s\t║ Data: %s\t║ Hora: %s\t║ Telefone: %s  ║\n", cpf , nome_pet, data, hora, telefone);
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
    system("clear");
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------.  ║\n");
    printf("║  ,-.'-  _\\  /==/_ /   _.='.'-,  \\                    .-`.' ,`.    ,-.--` , \\ /==/,  -   , -  ║\n");
    printf("║ /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \\  |==|-  _.-` \\==\\.-.  - ,-.  ║\n");
    printf("║ \\==\\  \\    |==|  |  /==/ -   .-'   /==/,  -   , -\\ |==| _ .=. |  |==|   `.-.  `--`\\==\\-  |   ║\n");
    printf("║  \\==\\ -\\   |==|- |  |==|_   /_,-.  \\==\\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \\==\\_ |   ║\n");
    printf("║  _\\==\\ ,\\  |==| ,|  |==|  , \\_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- |   ║\n");
    printf("║ /==/\\/ _ | |==|- |  \\==\\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, |   ║\n");
    printf("║ \\==\\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/   ║\n");
    printf("║  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--`   ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                 Excluir Agendamento                                          ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o ID do Agendamento que deseja excluir:                                         ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}
