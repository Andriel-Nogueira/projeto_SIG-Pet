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
        while (getchar() != '\n')
            ;
        return -1;
    }

    getchar();
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



int gerar_id(const char* caminho_arquivo, size_t tamanho_registro)
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

void exibir_titulo(const char* titulo) //CRÉDITOS: ajuda da I.A Google Gemini, adpatada pelo dev Jefferson 
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
    if (system("cls")) {
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
    printf("Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

int eh_digito(char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int validar_numero(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!eh_digito(str[i])) {
            return 0; 
        }
    }
    return 1; 
}

int validar_telefone(const char* telefone) {
    int i = 0;
    while (telefone[i] != '\0') {
        if (!eh_digito(telefone[i])) {
            return 0;
        }
        i++;
    }
    if (i < 10 || i > 11) {
        return 0;
    }
    return 1;
}

int eh_bissexto(int ano) {
    if ((ano % 4 == 0) && (ano % 100 != 0)) {
        return 1;
    } else if (ano % 400 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int validar_data(int dia, int mes, int ano) {
    int maior_dia;
    if (ano < 1900 || ano > 2024 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }
    if (mes == 2) { // Fevereiro
        maior_dia = eh_bissexto(ano) ? 29 : 28;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Meses com 30 dias
        maior_dia = 30;
    } else { // Meses com 31 dias
        maior_dia = 31;
    }
    if (dia > maior_dia) {
        return 0;
    }
    return 1; // Data válida
}

void ler_data(int* dia, int* mes, int* ano) {
    char dia_str[4], mes_str[4], ano_str[6];
    int data_valida;

    do {
        printf("Digite a data:\n");
        input(dia_str, 4, "Dia (DD):");
        input(mes_str, 4, "Mês (MM):");
        input(ano_str, 6, "Ano (AAAA):");

        *dia = atoi(dia_str);
        *mes = atoi(mes_str);
        *ano = atoi(ano_str);

        data_valida = validar_data(*dia, *mes, *ano);
        if (!data_valida) {
            printf("\nData inválida! Por favor, insira uma data correta.\n");
        }
    } while (!data_valida);
}

int eh_letra(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    } else {
        return 0;
    }
}

int validar_nome(const char* nome) {
    // Verifica se o nome não está vazio
    if (nome[0] == '\0') {
        return 0;
    }
    for (int i = 0; nome[i] != '\0'; i++) {
        // Permite letras e espaços
        if (!eh_letra(nome[i]) && nome[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int validar_float(const char* str) {
    int dot_count = 0;
    if (str[0] == '\0') {
        return 0; // String vazia não é válida
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dot_count++;
        } else if (!eh_digito(str[i])) {
            return 0; // Não é dígito nem ponto
        }
    }
    // Permite no máximo um ponto decimal
    return dot_count <= 1;
}

void obter_data_atual(char* data_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data_str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}
