#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servicos.h"
#include "../utilitarios/utilitarios.h"

void m_servicos(void)
{
    int op;
    system("clear");
    do
    {
        exibir_logo();
        exibir_titulo("Menu Servicos");

        printf("║                                                                                              ║\n");
        printf("║          1 - Cadastrar novo serviço                                                          ║\n");
        printf("║          2 - Buscar serviço pelo código                                                      ║\n");
        printf("║          3 - Atualizar serviço                                                               ║\n");
        printf("║          4 - Listar serviços                                                                 ║\n");
        printf("║          5 - Inativar serviço                                                                ║\n");
        printf("║          6 - Excluir serviço (Fisicamente)                                                   ║\n");
        printf("║          0 - Voltar ao menu principal                                                        ║\n");
        printf("║                                                                                              ║\n");
        printf("║          Escolha uma opção:                                                                  ║\n");
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
        op = escolha();

        switch (op)
        {
        case 1:
            cadastrar_servico();
            break;
        case 2:
            buscar_servico();
            break;
        case 3:
            atualizar_servico();
            break;
        case 4:
            listar_servicos();
            break;
        case 5:
            inativar_servico();
            break;
        case 6:
            excluir_servico_fisico();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 0);
}

Servicos *tela_cadastrar_servico(void)
{
    Servicos *serv;

    exibir_logo();
    exibir_titulo("Cadastrar Servico");

    serv = (Servicos *)malloc(sizeof(Servicos));
    if (serv == NULL)
    {
        printf("Erro de alocação de memória!\n");
        pressione_enter();
        return NULL;
    }

    serv->id = GERAR_ID("servicos/servicos.dat", Servicos);
    printf("ID do serviço gerado automaticamente: %d\n", serv->id);

    do
    {
        input(serv->nome, 50, "Nome do Serviço: ");
        if (!validar_nome(serv->nome))
        {
            printf("\nNome inválido! Digite um nome para o serviço.\n");
        }
    } while (!validar_nome(serv->nome));

    input(serv->desc, 256, "Descrição: ");

    do
    {
        input(serv->preco_s, 32, "Preço (use . como separador): ");
        if (!validar_float(serv->preco_s))
        {
            printf("\nPreço inválido! Digite um valor numérico (ex: 50.00).\n");
        }
    } while (!validar_float(serv->preco_s));

    serv->status = True;
    return serv;
}

void cadastrar_servico(void)
{
    Servicos *serv = tela_cadastrar_servico();
    if (serv != NULL)
    {
        gravar_servico(serv);
        printf("\nCadastro de serviço realizado com sucesso!\n");
        exibir_servico(serv);
        free(serv);
    }
    pressione_enter();
}

int tela_buscar_servico(void)
{
    char id_lido[20];
    exibir_logo();
    exibir_titulo("Buscar Servico pelo ID");
    input(id_lido, 20, "Informe o ID do serviço que deseja buscar:");
    if (!validar_numero(id_lido))
    {
        return -1; // Retorna -1 para indicar ID inválido
    }
    return atoi(id_lido);
}

void buscar_servico(void)
{
    int id_busca = tela_buscar_servico();
    if (id_busca == -1)
    {
        printf("\nID inválido. Por favor, digite apenas números.\n");
        pressione_enter();
        return;
    }

    Servicos *serv = buscar_servico_por_id(id_busca);

    if (serv != NULL)
    {
        printf("\nServiço encontrado:\n");
        exibir_servico(serv);
        free(serv);
    }
    else
    {
        printf("\nServiço com ID %d não encontrado ou inativo.\n", id_busca);
    }
    pressione_enter();
}

int tela_atualizar_servico(void)
{
    char id_lido[20];
    exibir_logo();
    exibir_titulo("Atualizar Servico");
    printf("║      Informe o ID do serviço que deseja atualizar:                                           ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_lido, 20, "Informe o ID do serviço que deseja atualizar:");
    if (!validar_numero(id_lido))
    {
        return -1;
    }
    return atoi(id_lido);
}

void atualizar_servico(void)
{
    int id_busca = tela_atualizar_servico();
    if (id_busca == -1)
    {
        printf("\nID inválido. Por favor, digite apenas números.\n");
        pressione_enter();
        return;
    }

    Servicos *serv_existente = buscar_servico_por_id(id_busca);
    if (serv_existente == NULL)
    {
        printf("\nServiço com ID %d não encontrado ou inativo.\n", id_busca);
    }
    else
    {
        free(serv_existente); // Libera o que foi retornado pela busca
        printf("\nServiço encontrado. Informe os novos dados:\n");
        Servicos *serv_novo = (Servicos *)malloc(sizeof(Servicos));

        do
        {
            input(serv_novo->nome, 50, "Nome do Serviço: ");
            if (!validar_nome(serv_novo->nome))
            {
                printf("\nNome inválido! Digite um nome para o serviço.\n");
            }
        } while (!validar_nome(serv_novo->nome));

        input(serv_novo->desc, 256, "Descrição: ");

        do
        {
            input(serv_novo->preco_s, 32, "Preço (use . como separador): ");
            if (!validar_float(serv_novo->preco_s))
            {
                printf("\nPreço inválido! Digite um valor numérico (ex: 50.00).\n");
            }
        } while (!validar_float(serv_novo->preco_s));

        serv_novo->id = id_busca;
        serv_novo->status = True;
        gravar_atualizacao_servico(serv_novo);
        printf("\nServiço atualizado com sucesso!\n");
        free(serv_novo);
    }
    pressione_enter();
}

void listar_servicos(void)
{
    FILE *arq_servicos;
    Servicos serv;

    exibir_logo();
    exibir_titulo("Listagem de Serviços");

    arq_servicos = fopen("servicos/servicos.dat", "rb");

    if (arq_servicos == NULL)
    {
        printf("Nenhum serviço cadastrado ou erro ao abrir o arquivo.\n");
        pressione_enter();
        return;
    }

    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-5s │ %-35s │ %-30s │ %-12s ║\n", "ID", "NOME", "DESCRIÇÃO", "PREÇO (R$)");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    int encontrou = 0, contador = 0;
    while (fread(&serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv.status == True)
        {
            printf("║ %-5d │ %-35s │ %-30s │ %-12.2s ║\n",
                   serv.id,
                   serv.nome,
                   serv.desc,
                   serv.preco_s);
            encontrou = 1;
            contador++;
        }
    }

    if (!encontrou)
    {
        printf("║ Nenhum serviço ativo encontrado.                                                                              ║\n");
    }

    printf("╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");

    if (encontrou)
        printf("\nTotal de serviços listados: %d\n", contador);

    fclose(arq_servicos);
    pressione_enter();
}

int tela_inativar_servico(void)
{
    char id_lido[20];
    exibir_logo();
    exibir_titulo("Inativar Servico (Exclusão Lógica)");
    input(id_lido, 20, "Informe o ID do serviço que deseja inativar:");
    if (!validar_numero(id_lido))
    {
        return -1;
    }
    return atoi(id_lido);
}

void inativar_servico(void)
{
    int id_busca = tela_inativar_servico();
    if (id_busca == -1)
    {
        printf("\nID inválido. Por favor, digite apenas números.\n");
        pressione_enter();
        return;
    }

    Servicos *serv = buscar_servico_por_id(id_busca);

    if (serv != NULL)
    {
        serv->status = False;
        gravar_atualizacao_servico(serv);
        printf("\nServiço com ID %d inativado com sucesso.\n", id_busca);
        free(serv);
    }
    else
    {
        printf("\nServiço com ID %d não encontrado ou já está inativo.\n", id_busca);
    }
    pressione_enter();
}

int tela_excluir_servico_fisico(void)
{
    char id_lido[20];
    exibir_logo();
    exibir_titulo("Excluir Servico Fisicamente");
    printf("║      ATENÇÃO: Esta ação é irreversível!                                                      ║\n");
    printf("║      Informe o ID do serviço que deseja excluir permanentemente:                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    input(id_lido, 20, "Informe o ID do serviço que deseja excluir permanentemente:");
    if (!validar_numero(id_lido))
    {
        return -1;
    }
    return atoi(id_lido);
}

void excluir_servico_fisico(void)
{
    int id_busca = tela_excluir_servico_fisico();
    if (id_busca == -1)
    {
        printf("\nID inválido. Por favor, digite apenas números.\n");
        pressione_enter();
        return;
    }

    int encontrado = remover_servico_do_arquivo(id_busca);

    if (encontrado == 1)
    {
        printf("\nServiço com ID %d excluído permanentemente com sucesso!\n", id_busca);
    }
    else if (encontrado == 0)
    {
        printf("\nServiço com ID %d não encontrado.\n", id_busca);
    }
    pressione_enter();
}

void exibir_servico(const Servicos *serv)
{
    if (serv == NULL)
    {
        return;
    }
    printf("ID: %d\n", serv->id);
    printf("Nome: %s\n", serv->nome);
    printf("Descrição: %s\n", serv->desc);
    printf("Preço: R$ %s\n", serv->preco_s);
}

void gravar_servico(const Servicos *serv)
{
    FILE *arq_servicos = fopen("servicos/servicos.dat", "ab");
    if (arq_servicos == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
        pressione_enter();
        return;
    }
    fwrite(serv, sizeof(Servicos), 1, arq_servicos);
    fclose(arq_servicos);
}

void gravar_atualizacao_servico(const Servicos *serv_atualizado)
{
    FILE *arq_servicos;
    Servicos serv_lido;

    arq_servicos = fopen("servicos/servicos.dat", "r+b");
    if (arq_servicos == NULL)
    {
        printf("\nErro ao abrir o arquivo de serviços para atualização.\n");
        return;
    }

    while (fread(&serv_lido, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv_lido.id == serv_atualizado->id)
        {
            fseek(arq_servicos, -sizeof(Servicos), SEEK_CUR);
            fwrite(serv_atualizado, sizeof(Servicos), 1, arq_servicos);
            break;
        }
    }
    fclose(arq_servicos);
}

int remover_servico_do_arquivo(int id)
{
    FILE *arq_servicos, *arq_temp;
    Servicos serv;
    int encontrado = 0;

    arq_servicos = fopen("servicos/servicos.dat", "rb");
    if (arq_servicos == NULL)
    {
        printf("\nNenhum serviço cadastrado. A operação não pode ser concluída.\n");
        return -1;
    }

    arq_temp = fopen("servicos/servicos_temp.dat", "wb");
    if (arq_temp == NULL)
    {
        printf("\nErro ao criar arquivo temporário. A operação não pode ser concluída.\n");
        fclose(arq_servicos);
        return -1;
    }

    while (fread(&serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv.id != id)
        {
            fwrite(&serv, sizeof(Servicos), 1, arq_temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(arq_servicos);
    fclose(arq_temp);

    if (encontrado)
    {
        remove("servicos/servicos.dat");
        rename("servicos/servicos_temp.dat", "servicos/servicos.dat");
    }
    else
    {
        remove("servicos/servicos_temp.dat");
    }

    return encontrado;
}

Servicos *buscar_servico_por_id(int id)
{
    FILE *arq_servicos;
    Servicos *serv = malloc(sizeof(Servicos));

    arq_servicos = fopen("servicos/servicos.dat", "rb");
    if (arq_servicos == NULL)
    {
        free(serv);
        return NULL;
    }

    while (fread(serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv->id == id && serv->status == True)
        {
            fclose(arq_servicos);
            return serv;
        }
    }

    fclose(arq_servicos);
    free(serv);
    return NULL;
}

void listar_servicos_simples(void)
{
    FILE *arq_servicos;
    Servicos serv;

    arq_servicos = fopen("servicos/servicos.dat", "rb");

    if (arq_servicos == NULL)
    {
        printf("\nNenhum serviço cadastrado.\n");
        return;
    }

    printf("\n--- Serviços Disponíveis ---\n");
    printf("%-5s │ %-30s │ %-10s\n", "ID", "NOME", "PREÇO");

    while (fread(&serv, sizeof(Servicos), 1, arq_servicos))
    {
        if (serv.status == True)
        {
            printf("%-5d │ %-30s │ R$ %s\n",
                   serv.id, serv.nome, serv.preco_s);
        }
    }

    fclose(arq_servicos);
}
