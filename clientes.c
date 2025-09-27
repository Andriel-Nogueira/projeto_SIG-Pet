#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "utilitarios.h"

void m_clientes(void)
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
        printf("║                                      Menu Clientes                                           ║\n");
        printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar novo cliente                                                          ║\n");
        printf("║          2 - Buscar cliente pelo CPF                                                         ║\n");
        printf("║          3 - Atualizar clientes                                                              ║\n");
        printf("║          4 - Listar clientes e pets                                                          ║\n");
        printf("║          5 - Excluir cliente                                                                 ║\n");
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
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

void cadastrar_cliente(void)
{
    system("clear");
    printf("\n");
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];
    FILE  *arq_cliente;
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
    printf("║                                   Cadastrar Cliente                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf, 15, "Insira seu cpf");
    input(nome, 50, "Digite o seu nome: ");
    input(data_nascimento, 12, "Digite sua data de nascimento (DD/MM/AAAA): ");
    input(telefone, 20, "Digite seu telefone: ");
    printf("Cliente cadastrado com sucesso!\n");
    printf("Nome: %s.\nCPF: %s.\nData nascimento: %s.\nTelefone: %s.\n", nome, cpf, data_nascimento, telefone);
    
                ///SALVAR DADOS ///
    arq_cliente = fopen("clientes.csv","at");
    if (arq_cliente == NULL){
        printf("ERRO AO ABRIR ARQUIVO");
        return;
    }
    fprintf(arq_cliente, "%s;", cpf);
    fprintf(arq_cliente, "%s;", nome);
    fprintf(arq_cliente, "%s;", data_nascimento);
    fprintf(arq_cliente, "%s\n", telefone);
    fclose(arq_cliente);
                ///              ///

    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void buscar_cliente(void)
{
    system("clear");
    printf("\n");
    char cpf_lido[15];
    char cpf[15];
    char nome[50];
    char data_nascimento[12];
    char telefone[20];
    FILE *arq_clientes;
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
    printf("║                                 Buscar Cliente pelo CPF                                      ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    
    input(cpf_lido, 15, "Digite o CPF do cliente que deseja buscar: ");
    arq_clientes = fopen("clientes.csv", "rt");
    if (arq_clientes == NULL)
    {
        printf("Nenhum agendamento cadastrado.\n");
        getchar();
        return;
    }

    while (!feof(arq_clientes))
    {
        fscanf(arq_clientes, "%[^;]", cpf);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^;]", nome);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^;]", data_nascimento);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^\n]", telefone);
        fgetc(arq_clientes);

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
    printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);

    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void atualizar_cliente(void)
{
    system("clear");
    printf("\n");
 //   char cpf[15];
 //   char nome[50];
 //   char data_nascimento[12];
 //   char telefone[20];
 //   FILE *arq_clientes;
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
    printf("║                                Atualizar Dados do Cliente                                    ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(cpf_lido, 15, "Digite o CPF do cliente que deseja atualizar: ");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void listar_clientes(void)
{
    system("clear");
    printf("\n");
    FILE *arq_clientes;
    char cpf[15] = "";
    char nome[50] = "";
    char data_nascimento[12] = "";
    char telefone[20] = "";

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
    printf("║                                       Listar de Clientes                                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    arq_clientes = fopen("clientes.csv", "rt");

    while (!feof(arq_clientes))
    {
        fscanf(arq_clientes, "%[^;]", cpf);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^;]", nome);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^;]", data_nascimento);
        fgetc(arq_clientes);
        fscanf(arq_clientes, "%[^\n]", telefone);
        fgetc(arq_clientes);


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
    printf("║                                    Excluir Cliente                                           ║\n");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o CPF do cliente que deseja excluir:                                            ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}