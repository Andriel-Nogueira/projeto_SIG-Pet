#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#define True 1
#define False 0

void input(char *nome, int tamanho, char *mensagem);
int escolha(void);

void salvar(const char *nome_arquivo, int num_args, ...);

int gerar_id(const char *caminho_arquivo, size_t tamanho_registro);
#define GERAR_ID(caminho, tipo) gerar_id(caminho, sizeof(tipo))

void exibir_logo(void);
void exibir_titulo(const char *titulo);
void pressione_enter(void);

int validar_numero(const char *str);
int validar_cpf(const char *cpf);
int validar_telefone(const char *telefone);
int eh_digito(char c);
int eh_bissexto(int ano);
int validar_data(int dia, int mes, int ano);
void ler_data(int *dia, int *mes, int *ano);
int eh_letra(char c);
int validar_nome(const char *nome);
int validar_float(const char *str);
void obter_data_atual(char *data_str);
int validar_data_agendamento(int dia, int mes, int ano);
void ler_data_agendamento(int *dia, int *mes, int *ano);
void ler_cpf(char *cpf_destino);
int validar_hora(const char *hora);
void ler_hora(char *hora);

#endif
