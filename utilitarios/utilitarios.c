#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#include "utilitarios.h"

int escolha(void)
{
    int opcao;
    int resultado;

    printf("\n           Escolha a opção desejada: ");
    resultado = scanf("%d", &opcao);

    if (resultado != 1)
    {
        printf("\nOpção inválida! Digite apenas números.\n");
        // Limpa o buffer de entrada em caso de erro
        while (getchar() != '\n')
            ;
        return -1;
    }

    // Limpa o buffer de entrada para consumir o '\n' deixado pelo scanf
    while (getchar() != '\n');
    return opcao;
}

void input(char *nome, int tamanho, char *mensagem)
{
    int tam;
    printf("%s\n", mensagem);
    fgets(nome, tamanho, stdin);
    tam = strlen(nome);
    nome[tam - 1] = '\0';
}

int gerar_id(const char *caminho_arquivo, size_t tamanho_registro)
{
    FILE *arquivo;
    long tamanho_arquivo;
    int num_registros;

    arquivo = fopen(caminho_arquivo, "rb");
    if (arquivo == NULL)
    {
        return 1; // Se o arquivo não existe, o primeiro ID é 1
    }

    fseek(arquivo, 0, SEEK_END);
    tamanho_arquivo = ftell(arquivo);
    fclose(arquivo);
    num_registros = tamanho_arquivo / tamanho_registro;
    return num_registros + 1;
}

void exibir_titulo(const char *titulo) // CRÉDITOS: ajuda da I.A Google Gemini, adpatada pelo dev Jefferson
{
    const int LARGURA_TOTAL = 94;
    int tam_titulo = strlen(titulo);
    int espacos_laterais, espacos_esquerda, espacos_direita;

    // Calcula o espaçamento para centralizar o título
    espacos_laterais = LARGURA_TOTAL - tam_titulo;
    espacos_esquerda = espacos_laterais / 2;
    // Garante que a soma dos espaços seja a correta, mesmo para títulos de tamanho ímpar
    espacos_direita = espacos_laterais - espacos_esquerda;

    printf("║%*s%s%*s║\n", espacos_esquerda, "", titulo, espacos_direita, "");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════╣\n");
}

void exibir_logo(void)
{
    // Comando para limpar a tela que funciona em Windows (cls) e Linux/macOS (clear)
    if (system("cls"))
    {
        system("clear");
    }
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
}

void pressione_enter(void)
{
    printf("\n");
    printf("Pressione <Enter> para continuar...                                        \n");
    // Espera que o usuário pressione Enter
    getchar();
}

int eh_digito(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validar_numero(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!eh_digito(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validar_telefone(const char *telefone)
{
    int i = 0;
    while (telefone[i] != '\0')
    {
        if (!eh_digito(telefone[i]))
        {
            return 0;
        }
        i++;
    }
    if (i < 10 || i > 11)
    {
        return 0;
    }
    return 1;
}

int eh_bissexto(int ano)
{
    if ((ano % 4 == 0) && (ano % 100 != 0))
    {
        return 1;
    }
    else if (ano % 400 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ler_data_agendamento(int *dia, int *mes, int *ano)
{
    char dia_str[4], mes_str[4], ano_str[6];
    int data_valida;

    do
    {
        printf("Digite a data:\n");
        input(dia_str, 4, "Dia (DD):");
        input(mes_str, 4, "Mês (MM):");
        input(ano_str, 6, "Ano (AAAA):");

        *dia = atoi(dia_str);
        *mes = atoi(mes_str);
        *ano = atoi(ano_str);

        data_valida = validar_data_agendamento(*dia, *mes, *ano);
        if (!data_valida)
        {
            printf("\nData inválida! Por favor, insira uma data correta.\n");
        }
    } while (!data_valida);
}

int validar_data_agendamento(int dia, int mes, int ano)
{
    int maior_dia;
    if (ano < 1900 || ano < 2025 || mes < 1 || mes > 12 || dia < 1)
    {
        return 0;
    }
    if (mes == 2)
    { // Fevereiro
        maior_dia = eh_bissexto(ano) ? 29 : 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    { // Meses com 30 dias
        maior_dia = 30;
    }
    else
    { // Meses com 31 dias
        maior_dia = 31;
    }
    if (dia > maior_dia)
    {
        return 0;
    }
    return 1; // Data válida
}

int validar_data(int dia, int mes, int ano)
{
    int maior_dia;
    if (ano < 1900 || ano > 2025 || mes < 1 || mes > 12 || dia < 1)
    {
        return 0;
    }
    if (mes == 2)
    { // Fevereiro
        maior_dia = eh_bissexto(ano) ? 29 : 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    { // Meses com 30 dias
        maior_dia = 30;
    }
    else
    { // Meses com 31 dias
        maior_dia = 31;
    }
    if (dia > maior_dia)
    {
        return 0;
    }
    return 1; // Data válida
}

void ler_data(int *dia, int *mes, int *ano)
{
    char dia_str[4], mes_str[4], ano_str[6];
    int data_valida;

    do
    {
        printf("Digite a data:\n");
        input(dia_str, 4, "Dia (DD):");
        input(mes_str, 4, "Mês (MM):");
        input(ano_str, 6, "Ano (AAAA):");

        *dia = atoi(dia_str);
        *mes = atoi(mes_str);
        *ano = atoi(ano_str);

        data_valida = validar_data(*dia, *mes, *ano);
        if (!data_valida)
        {
            printf("\nData inválida! Por favor, insira uma data correta.\n");
        }
    } while (!data_valida);
}

int eh_letra(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validar_nome(const char *nome)
{
    // Verifica se o nome não está vazio
    if (nome[0] == '\0')
    {
        return 0;
    }
    for (int i = 0; nome[i] != '\0'; i++)
    {
        // Permite letras e espaços
        if (!eh_letra(nome[i]) && nome[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int validar_cpf(const char *cpf)
{
    char cpf_apenas_digitos[12];
    int i, j = 0;

    // 1. Cria uma string temporária contendo apenas os dígitos do CPF
    for (i = 0; cpf[i] != '\0'; i++)
    {
        if (eh_digito(cpf[i]))
        {
            if (j < 11) { // Evita estouro de buffer se a entrada for muito longa
                cpf_apenas_digitos[j] = cpf[i]; // Copia o dígito
                j++;                            // Move para a próxima posição
            }
        }
        else if (cpf[i] != '.' && cpf[i] != '-')
        {
            return 0; // Encontrou um caractere inválido
        }
    }
    cpf_apenas_digitos[j] = '\0'; // Finaliza a string de dígitos

    // 2. Verifica se o CPF tem exatamente 11 dígitos
    if (strlen(cpf_apenas_digitos) != 11)
    {
        return 0;
    }

    // 3. Verifica se todos os 11 dígitos são iguais (ex: 11111111111)
    for (i = 1; i < 11; i++)
    {
        if (cpf_apenas_digitos[i] != cpf_apenas_digitos[0]) break;
    }
    if (i == 11) return 0; // Se o loop terminou, todos são iguais

    return 1; // Se passou por todas as verificações, o CPF é considerado válido
}

int validar_float(const char *str)
{
    int dot_count = 0;
    if (str[0] == '\0')
    {
        return 0; // String vazia não é válida
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '.')
        {
            dot_count++;
        }
        else if (!eh_digito(str[i]))
        {
            return 0; // Não é dígito nem ponto
        }
    }
    // Permite no máximo um ponto decimal
    return dot_count <= 1;
}

void obter_data_atual(char *data_str)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data_str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void ler_cpf(char *cpf_destino)
{
    char cpf_input[20]; // Buffer para a entrada bruta do usuário
    int valido = 0;

    do
    {
        // 1. Lê a entrada do usuário (com pontos e traços)
        input(cpf_input, 20, "Insira o CPF (pode conter '.' e '-'):");

        // 2. Limpa a string, mantendo apenas os dígitos
        char cpf_limpo[12];
        int j = 0;
        for (int i = 0; cpf_input[i] != '\0'; i++)
        {
            if (isdigit(cpf_input[i]))
            {
                if (j < 11)
                {
                    cpf_limpo[j++] = cpf_input[i];
                }
            }
        }
        cpf_limpo[j] = '\0'; // Finaliza a string limpa

        // 3. Valida o CPF limpo
        if (validar_cpf(cpf_limpo))
        {
            strcpy(cpf_destino, cpf_limpo); // Copia o CPF limpo e válido para o destino
            valido = 1;
        }
        else
        {
            printf("\nCPF inválido! O CPF deve conter 11 dígitos. Tente novamente.\n");
        }
    } while (!valido);
}
