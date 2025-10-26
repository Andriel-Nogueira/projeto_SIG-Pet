#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#define True 1
#define False 0

void input(char *nome, int tamanho, char *mensagem);
int escolha(void);

void salvar(const char* nome_arquivo, int num_args, ...) ;

char* gerar_id(const char* caminho_arquivo);

void exibir_logo(void);
void exibir_titulo(const char* titulo);
void pressione_enter(void);

int validar_numero(const char* str);
int validar_telefone(const char* telefone);
int eh_digito(char c);
int eh_bissexto(int ano);
int validar_data(int dia, int mes, int ano);
void ler_data(int* dia, int* mes, int* ano);

#endif
