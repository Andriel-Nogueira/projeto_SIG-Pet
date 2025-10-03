#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
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

void salvar(const char* nome_arquivo, int num_args, ...) {
    FILE* arquivo = fopen(nome_arquivo, "at");
    if (arquivo == NULL) {
        printf("Erro na criação ou abertura do arquivo!\n");
        return;
    }

    va_list args;
    va_start(args, num_args);

    // Escreve os dados no arquivo, separados por ";"
    for (int i = 0; i < num_args; i++) {
        fprintf(arquivo, "%s", va_arg(args, char*));
        if (i < num_args - 1) {
            fprintf(arquivo, ";");  // Adiciona o separador ";"
        }
    }

    va_end(args);

    fprintf(arquivo, "\n");
    fclose(arquivo);
}

char* gerar_id(const char* caminho_arquivo)
{
    int id = 0;
    static char id_str[20];
    char linha[255];
    FILE *arquivo;

    arquivo = fopen(caminho_arquivo, "rt");
    if (arquivo == NULL)
    {
        return "1";
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        id++;  
    }

    fclose(arquivo);
    sprintf(id_str, "%d", id + 1);
    
    return id_str;
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

}
