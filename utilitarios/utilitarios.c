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