#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "../utilitarios/utilitarios.h"
#include "../pets/pets.h"

void m_clientes(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Clientes");

        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar novo cliente                                                          ║\n");
        printf("║          2 - Buscar cliente pelo CPF                                                         ║\n");
        printf("║          3 - Atualizar clientes                                                              ║\n");
        printf("║          4 - Listar clientes                                                                 ║\n");
        printf("║          5 - Inativar cliente                                                                ║\n");
        printf("║          6 - Excluir cliente (Fisicamente)                                                   ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        op = escolha();
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
            inativar_cliente();
            break;
        case 6:
            excluir_cliente_fisico();
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
    Clientes *cli;

    cli = tela_cadastrar_cliente();
    if (cli == NULL)
    {
        return;
    }
    gravar_cliente(cli);
    printf("Cliente cadastrado com sucesso!\n");
    exibir_cliente(cli);
    pressione_enter();
    free(cli);
}

void buscar_cliente(void)
{
    char cpf_busca[16];
    Clientes *cli = NULL;

    exibir_logo();
    exibir_titulo("Buscar Cliente pelo CPF");

    ler_cpf(cpf_busca);

    cli = buscar_cliente_por_cpf(cpf_busca);

    if (cli != NULL)
    {
        printf("\nCliente encontrado:\n");
        exibir_cliente(cli);
        free(cli);
    }
    else
    {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    pressione_enter();
}

void atualizar_cliente(void)
{
    char *cpf_busca;
    Clientes *cli;

    cpf_busca = tela_atualizar_cliente();

    if (!verificar_cliente_cadastrado(cpf_busca))
    {
        printf("\nCliente com CPF %s não encontrado ou inativo.\n", cpf_busca);
    }
    else
    {
        cli = tela_cadastrar_cliente();
        if (cli != NULL)
        {
            strcpy(cli->cpf, cpf_busca);
            gravar_atualizacao_cliente(cli);
            free(cli);
        }
    }
    free(cpf_busca);
    pressione_enter();
}

void listar_clientes(void)
{
    FILE *arq_clientes;
    Clientes *cli;

    exibir_logo();
    exibir_titulo("Listagem de Clientes");

    cli = (Clientes *)malloc(sizeof(Clientes));
    arq_clientes = fopen("clientes/clientes.dat", "rb");

    if (arq_clientes == NULL)
    {
        printf("Nenhum cliente cadastrado ou erro ao abrir o arquivo.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }

    printf("╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-15s │ %-35s │ %-12s │ %-15s ║\n", "CPF", "NOME", "NASCIMENTO", "TELEFONE");
    printf("╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    int encontrou = 0;
    while (fread(cli, sizeof(Clientes), 1, arq_clientes))
    {
        if (cli->status == True)
        {
            printf("║ %-15s │ %-35s │ %-12s │ %-15s ║\n",
                   cli->cpf,
                   cli->nome,
                   cli->data_nascimento,
                   cli->telefone);
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum cliente ativo encontrado.                                                                                     ║\n");
    }

    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    fclose(arq_clientes);
    free(cli);

    pressione_enter();
}

void inativar_cliente(void)
{
    Clientes *cli;
    char *cpf_busca;

    cpf_busca = tela_inativar_cliente();
    cli = buscar_cliente_por_cpf(cpf_busca);

    if (cli == NULL)
    {
        printf("\nCliente com CPF %s não encontrado ou já está inativo.\n", cpf_busca);
    }
    else
    {
        cli->status = False;
        gravar_atualizacao_cliente(cli);
        printf("\nCliente inativado com sucesso!\n");
    }
    free(cli);
    free(cpf_busca);
    pressione_enter();
}

void excluir_cliente_fisico(void)
{
    char *cpf_busca;
    int encontrado = 0;

    cpf_busca = tela_excluir_cliente_fisico();
    if (cpf_busca == NULL)
    {
        return;
    }

    encontrado = remover_cliente_do_arquivo(cpf_busca);

    if (encontrado == 1)
    {
        printf("\nCliente com CPF %s excluído permanentemente com sucesso!\n", cpf_busca);
    }
    else if (encontrado == 0)
    {
        printf("\nCliente com CPF %s não encontrado.\n", cpf_busca);
    }

    free(cpf_busca);
    pressione_enter();
}

Clientes *buscar_cliente_por_cpf(const char *cpf)
{
    FILE *arq_clientes;
    Clientes *cli;

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        return NULL;
    }

    cli = (Clientes *)malloc(sizeof(Clientes));
    while (fread(cli, sizeof(Clientes), 1, arq_clientes))
    {
        if ((strcmp(cli->cpf, cpf) == 0) && (cli->status == True))
        {
            fclose(arq_clientes);
            return cli;
        }
    }

    fclose(arq_clientes);
    free(cli);
    return NULL;
}

Clientes *tela_cadastrar_cliente(void)
{
    Clientes *cli;
    cli = (Clientes *)malloc(sizeof(Clientes));

    exibir_logo();
    exibir_titulo("Cadastrar Cliente");

    ler_cpf(cli->cpf);

    if (verificar_cliente_cadastrado(cli->cpf))
    {
        printf("\nEste CPF já pertence a um cliente cadastrado.\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return NULL;
    }

    do
    {
        input(cli->nome, 50, "Digite o seu nome:");
        if (!validar_nome(cli->nome))
        {
            printf("\nNome inválido! Digite apenas letras e espaços.\n");
        }
    } while (!validar_nome(cli->nome));

    // Validação da data de nascimento
    int dia, mes, ano;
    printf("Digite sua data de nascimento:\n");
    ler_data(&dia, &mes, &ano);
    sprintf(cli->data_nascimento, "%02d/%02d/%04d", dia, mes, ano);

    do
    {
        input(cli->telefone, 20, "Digite seu telefone (10 ou 11 dígitos, com DDD):");
        if (!validar_telefone(cli->telefone))
        {
            printf("\nTelefone inválido! Deve conter 10 ou 11 dígitos numéricos.\n");
        }
    } while (!validar_telefone(cli->telefone));

    cli->status = True;
    return cli;
}

char *tela_atualizar_cliente(void)
{
    char *cpf_busca;
    cpf_busca = (char *)malloc(16 * sizeof(char));
    exibir_logo();
    exibir_titulo("Atualizar Dados do Cliente");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    ler_cpf(cpf_busca);
    return cpf_busca;
}

void exibir_cliente(const Clientes *cli)
{
    if (cli == NULL)
    {
        return;
    }
    printf("CPF: %s\n", cli->cpf);
    printf("Nome: %s\n", cli->nome);
    printf("Data de nascimento: %s\n", cli->data_nascimento);
    printf("Telefone: %s\n", cli->telefone);
}

void gravar_cliente(Clientes *cli)
{
    FILE *arq_clientes;
    arq_clientes = fopen("clientes/clientes.dat", "ab");
    if (arq_clientes == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        printf("Pressione <Enter> para voltar...");
        getchar();
        free(cli);
        return;
    }
    fwrite(cli, sizeof(Clientes), 1, arq_clientes);
    fclose(arq_clientes);
}

void gravar_atualizacao_cliente(const Clientes *cli)
{
    FILE *arq_clientes;
    arq_clientes = fopen("clientes/clientes.dat", "r+b");
    if (arq_clientes == NULL)
    {
        printf("Erro ao abrir o arquivo para atualização.\n");
        return;
    }

    Clientes temp_cli;
    while (fread(&temp_cli, sizeof(Clientes), 1, arq_clientes))
    {
        if ((strcmp(temp_cli.cpf, cli->cpf) == 0) && (temp_cli.status == True))
        {
            fseek(arq_clientes, -sizeof(Clientes), SEEK_CUR);
            fwrite(cli, sizeof(Clientes), 1, arq_clientes);
            printf("\nCliente atualizado com sucesso!\n");
            break;
        }
    }
    fclose(arq_clientes);
}

int remover_cliente_do_arquivo(const char *cpf_busca)
{
    FILE *arq_clientes, *arq_temp;
    Clientes cli;
    int encontrado = 0;

    // se retornar -1 significa erro de arquivo

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        printf("\nNenhum cliente cadastrado. A operação não pode ser concluída.\n");
        return -1;
    }

    arq_temp = fopen("clientes/clientes_temp.dat", "wb");
    if (arq_temp == NULL)
    {
        printf("\nErro ao criar arquivo temporário. A operação não pode ser concluída.\n");
        fclose(arq_clientes);
        return -1;
    }

    while (fread(&cli, sizeof(Clientes), 1, arq_clientes))
    {
        if (strcmp(cli.cpf, cpf_busca) != 0)
        {
            fwrite(&cli, sizeof(Clientes), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_clientes);
    fclose(arq_temp);

    if (encontrado)
    {
        remove("clientes/clientes.dat");
        rename("clientes/clientes_temp.dat", "clientes/clientes.dat");
    }
    else
    {
        remove("clientes/clientes_temp.dat");
    }

    return encontrado;
}

char *tela_inativar_cliente(void)
{
    char *cpf_busca;
    cpf_busca = (char *)malloc(16 * sizeof(char));
    exibir_logo();
    exibir_titulo("Inativar Cliente (Exclusão Lógica)");
    printf("║      Informe o CPF do cliente que deseja inativar:                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    ler_cpf(cpf_busca);
    return cpf_busca;
}

char *tela_excluir_cliente_fisico(void)
{

    char *cpf_busca;
    cpf_busca = (char *)malloc(16 * sizeof(char));
    if (cpf_busca == NULL)
    {
        printf("Erro de alocação de memória!\n");
        pressione_enter();
        return NULL;
    }
    exibir_logo();
    exibir_titulo("Excluir Cliente Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o CPF do cliente que deseja excluir permanentemente:                            ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    ler_cpf(cpf_busca);
    return cpf_busca;
}

int verificar_cliente_cadastrado(const char *cpf)
{
    FILE *arq_clientes;
    Clientes *cli;
    int encontrado = 0;

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        return 0; // Se o arquivo não existe, o cliente não pode estar cadastrado
    }

    cli = (Clientes *)malloc(sizeof(Clientes));
    if (cli == NULL)
    {
        fclose(arq_clientes);
        return 0; // Falha na alocação de memória
    }

    while (fread(cli, sizeof(Clientes), 1, arq_clientes))
    {
        if ((strcmp(cli->cpf, cpf) == 0) && (cli->status == True))
        {
            encontrado = 1;
            break;
        }
    }
    fclose(arq_clientes);
    free(cli);
    return encontrado;
}

int cliente_tem_pets(const char *cpf)
{
    FILE *arq_pets;
    Pets pet;
    int tem_pets = 0;

    arq_pets = fopen("pets/pets.dat", "rb");
    if (arq_pets == NULL)
    {
        return 0; // Se o arquivo não existe, não há pets
    }

    while (fread(&pet, sizeof(Pets), 1, arq_pets))
    {
        if (pet.status == True && strcmp(pet.cpf, cpf) == 0)
        {
            tem_pets = 1;
            break; // Encontrou pelo menos um, já pode parar
        }
    }

    fclose(arq_pets);
    return tem_pets;
}

NoCliente *carregar_clientes_lista(void)
{
    FILE *arq_clientes;
    Clientes cli;
    NoCliente *lista = NULL;
    NoCliente *ultimo = NULL;

    arq_clientes = fopen("clientes/clientes.dat", "rb");
    if (arq_clientes == NULL)
    {
        return NULL; // Nenhum cliente cadastrado
    }

    while (fread(&cli, sizeof(Clientes), 1, arq_clientes))
    {
        NoCliente *novo_no = (NoCliente *)malloc(sizeof(NoCliente));
        if (novo_no == NULL)
        {
            fclose(arq_clientes);
            // Liberar a lista já criada em caso de falha
            NoCliente *atual = lista;
            while (atual != NULL)
            {
                NoCliente *temp = atual;
                atual = atual->prox;
                free(temp);
            }
            return NULL; // Falha na alocação de memória
        }
        novo_no->cliente = cli;
        novo_no->prox = NULL;

        if (lista == NULL)
        {
            lista = novo_no;
        }
        else
        {
            ultimo->prox = novo_no;
        }
        ultimo = novo_no;
    }

    fclose(arq_clientes);
    return lista;
}