#define True 1;
#define False 0;

void m_agendamento(void);
void agendar(void);
void buscar_agend(void);
void atualizar_agend(void);
void listar_agend(void);
void excluir_agend(void);

struct agendamentos
{
    char cpf[15];
    char nome_pet[30];
    char data[11];
    char hora[6];
    char telefone[20];
    char status;

};

typedef struct agendamentos Agendamentos;