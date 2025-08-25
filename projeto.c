//////////////////////////////////////////////////////////////////////////////////////////////////
//    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------. ///
//  ,-.'-  _\  /==/_ /   _.='.'-,  \                    .-`.' ,`.    ,-.--` , \ /==/,  -   , -\ //
// /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \  |==|-  _.-` \==\.-.  - ,-./ //
// \==\  \    |==|  |  /==/ -   .-'   /==/,  -   , -\ |==| _ .=. |  |==|   `.-.  `--`\==\- | /////
//  \==\ -\   |==|- |  |==|_   /_,-.  \==\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \==\_ | ////
//  _\==\ ,\  |==| ,|  |==|  , \_.' )  `--`--------`  |==|-  '..'  |==|    .-'        |==|- | ////
// /==/\/ _ | |==|- |  \==\-  ,    (                  |==|,  |     |==|_  ,`-._       |==|, | ////
// \==\ - , / /==/. /   /==/ _  ,  /                  /==/ - |     /==/ ,     /       /==/ -/ ////
//  `--`---'  `--`-`    `--`------'                   `--`---'     `--`-----``        `--`--` ////
//////////////////////////////////////////////////////////////////////////////////////////////////
///                       Universidade Federal do Rio Grande do Norte                          ///
///                          Centro de Ensino Superior do Seridó                               ///
///                            Disciplina DCT1106 -- Programação                               ///
///                        Projeto Sistema de Atendimento de Pet Shop                          ///
///              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista         ///
//////////////////////////////////////////////////////////////////////////////////////////////////
///                                         Semana 1                                           ///
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// Funções Principais
void m_principal(void);
void t_sobre(void);
void t_equipe(void);

void m_clientes(void);
void t_cadastrar_cliente(void);
void buscar_cliente(void);
void atualizar_cliente(void);
void listar_clientes(void);
void excluir_cliente(void);

void m_servicos(void);
void t_cadastrar_servico(void);

void t_final(void);

//Programa Principal
int main(void) {
    int op; 
    system("clear");
    do {
        system("clear");
        printf("\n");
    printf("╔═════════════════════════════════════╗\n");
    printf("║           Sistema SIG-Pet           ║\n");
    printf("║═════════════════════════════════════║\n");
    printf("║ 1 - Menu Principal                  ║\n");
    printf("║ 2 - Sobre o sistema                 ║\n");
    printf("║ 3 - Equipe de desenvolvimento       ║\n");
    printf("║ 0 - Sair                            ║\n");
    printf("╚═════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha a opção desejada:\n");
    scanf(" %d", &op);
    getchar();
    switch(op){
        case 1:
            m_principal();
            break;
        case 2:
            t_sobre();
            break;
        case 3:
            t_equipe();
            break;
        case 0:
            t_final();
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }   
    } while(op != 0);
    
    
    return 0;
}

void m_principal(void) {
    int op;
    system("clear");
    do {
        system("clear");
        printf("\n");
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                         Semana 1                                             ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          1 - Módulo Clientes                                                                 ║\n");
    printf("║          2 - Módulo Serviços                                                                 ║\n");
    printf("║          3 - Módulo Produtos                                                                 ║\n");
    printf("║          4 - Módulo Vendas                                                                   ║\n");
    printf("║          5 - Módulo Relatórios                                                               ║\n");
    printf("║          0 - Sair                                                                            ║\n");
    printf("║                                                                                              ║\n");
    printf("║          Escolha uma opção:                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    scanf(" %d", &op);
    getchar();
    switch(op){
        case 1:
            m_clientes();
            break;
        case 2:
            m_servicos();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while(op != 0);
    
}

void m_clientes(void) {
    int op;
    system("clear");
    do {
        system("clear");
        printf("\n");
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                      Menu Clientes                                           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          1 - Cadastrar novo cliente                                                          ║\n");
    printf("║          2 - Buscar cliente pelo CPF                                                         ║\n");
    printf("║          3 - Atualizar clientes                                                              ║\n");
    printf("║          4 - Listar clientes e pets                                                          ║\n");
    printf("║          5 - Excluir cliente                                                                 ║\n");
    printf("║          0 - Voltar ao menu principal                                                        ║\n");
    printf("║                                                                                              ║\n");
    printf("║          Escolha uma opção:                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    scanf(" %d", &op);
    getchar();
    switch(op){
        case 1:
            t_cadastrar_cliente();
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
            excluir_cliente();
            break;
        case 0:
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            
        }
    } while(op != 0);
    
}

void t_cadastrar_cliente(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                   Cadastrar Cliente                                          ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Nome Completo:                                                                          ║\n");
    printf("║      CPF:                                                                                    ║\n");
    printf("║      Pet (Nome/Raça):                                                                        ║\n");
    printf("║      Telefone:                                                                               ║\n");
    printf("║      Endereço:                                                                               ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    
}

void buscar_cliente(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                 Buscar Cliente pelo CPF                                      ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o CPF do cliente:                                                               ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    
}

void atualizar_cliente(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                Atualizar Dados do Cliente                                    ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o CPF do cliente que deseja atualizar:                                          ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    
}

void listar_clientes(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                   Listar Clientes e Pets                                     ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Lista de Clientes e seus respectivos Pets:                                              ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    
}

void excluir_cliente(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                    Excluir Cliente                                           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Informe o CPF do cliente que deseja excluir:                                            ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
    
}

void m_servicos(void) {
    int op;
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                    Menu Serviços                                             ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          1 - Cadastrar novo serviço                                                          ║\n");
    printf("║          2 - Buscar serviço pelo código                                                      ║\n");
    printf("║          3 - Atualizar serviço                                                               ║\n");
    printf("║          4 - Listar serviços                                                                 ║\n");
    printf("║          5 - Excluir serviço                                                                 ║\n");
    printf("║          0 - Voltar ao menu principal                                                        ║\n");
    printf("║                                                                                              ║\n");
    printf("║          Escolha uma opção:                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    scanf(" %d", &op);
    getchar();
}

void t_cadastrar_servico(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                   Cadastrar Serviço                                          ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║      Nome do Serviço:                                                                        ║\n");
    printf("║      Descrição:                                                                              ║\n");
    printf("║      Preço:                                                                                  ║\n");
    printf("║      ID do Serviço:                                                                          ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                     "Pressione <Enter> para voltar ao menu principal...                         \n");
    getchar();
}

void t_sobre(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                         Semana 1                                             ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          Este é um sistema de atendimento para Pet Shop, desenvolvido como parte de uma      ║\n");
    printf("║          atividade acadêmica. O sistema é dividido em módulos que permitem o gerenciamento   ║\n");
    printf("║          de clientes, serviços, produtos, vendas, estoque e relatórios.                      ║\n");
    printf("║          O objetivo é proporcionar uma experiência de aprendizado prática e funcional,       ║\n");
    printf("║          permitindo que os usuários gerenciem eficientemente as operações de um Pet Shop.    ║\n");
    printf("║                                                                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                        "Pressione <Enter> para voltar ao menu principal...\n");
    getchar();
    
}

void t_equipe(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                         Semana 1                                             ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          Equipe de Desenvolvimento:                                                          ║\n");
    printf("║          - Andriel Nogueira                                                                  ║\n");
    printf("║            Email: andriel.pereiraufrn@gmail.com                                              ║\n");
    printf("║            GitHub: @Andriel-Nogueira                                                         ║\n");
    printf("║          - Carlos Henrique de Oliveira Batista                                               ║\n");
    printf("║            Email: carlos.oliveira.714@ufrn.com.br                                            ║\n");
    printf("║            GitHub: @Carlos-Henrique-de-Oliveira-Batista                                      ║\n");
    printf("║          - Repositório da Equipe: https://github.com/Andriel-Nogueira/projeto_SIG-Pet.git    ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf(                        "Pressione <Enter> para voltar ao menu principal...\n");
    getchar();
    
}

void t_final(void) {
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
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                       Universidade Federal do Rio Grande do Norte                            ║\n");
    printf("║                          Centro de Ensino Superior do Seridó                                 ║\n");
    printf("║                            Disciplina DCT1106 -- Programação                                 ║\n");
    printf("║                        Projeto Sistema de Atendimento de Pet Shop                            ║\n");
    printf("║              Developed by @Andriel-Nogueira & @Carlos-Henrique-de-Oliveira-Batista           ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                         Semana 1                                             ║\n");
    printf("║══════════════════════════════════════════════════════════════════════════════════════════════║\n");
    printf("║                                                                                              ║\n");
    printf("║          Obrigado por utilizar o Sistema SIG-Pet!                                            ║\n");
    printf("║          Esperamos ter proporcionado uma ótima experiência!                                  ║\n");
    printf("║          Volte Sempre!                                                                       ║\n");
    printf("║            __    __                                                ||      _,,,---,,_        ║\n");
    printf("║          o-''))_____\\                                        ZzZzz /,`.-'`'    -.  ;-;;,_    ║\n");
    printf("║          z--__/ * * * )                                           |,4-  ) )-,_. ,/ (  `'-'   ║\n");
    printf("║          c_c__/-c____/                                           '---''(_/--'  `-'/_)        ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
}
