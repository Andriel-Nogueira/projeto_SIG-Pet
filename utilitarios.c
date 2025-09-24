#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
