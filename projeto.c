//////////////////////////////////////////////////////////////////////////////////////////////////
//    ,-,--.    .=-.-.       _,---.                        _ __         ,----.   ,--.--------. ///
//  ,-.'-  _\  /==/_ /   _.='.'-,  \                    .-`.' ,`.    ,-.--` , \ /==/,  -   , -\ //
// /==/_ ,_.' |==|, |   /==.'-     /   ,--.--------.   /==/, -   \  |==|-  _.-` \==\.-.  - ,-./ //
// \==\  \    |==|  |  /==/ -   .-'   /==/,  -   , -\ |==| _ .=. |  |==|   `.-.  `--`\==\- \ /////
//  \==\ -\   |==|- |  |==|_   /_,-.  \==\.-.  - ,-./ |==| , '=',| /==/_ ,    /       \==\_ \ ////
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
void m_sobre(void);

//Programa Principal
int main(void) {
    int op; 
    system("clear || cls");
    do {
    printf("╔═════════════════════════════════════╗\n");
    printf("║           Sistema SIG-Pet           ║\n");
    printf("║═════════════════════════════════════║\n");
    printf("║ 1 - Menu Principal                  ║\n");
    printf("║ 2 - Sobre o sistema                 ║\n");
    printf("║ 0 - Sair                            ║\n");
    printf("╚═════════════════════════════════════╝\n");
    printf("\n");
    printf("Escolha a opção desejada:\n");
    scanf("%d", &op);
    switch(op){
        case 1:
            m_principal();
            break;
        case 2:
            m_sobre();
            break;
        case 0:
            printf("Obrigado por usar o SIG-Pet!\n");
            printf("Pressione <Enter> para sair...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }   
    } while(op != 0);
    getchar();
    
    return 0;
}

void m_principal(void) {
    char op;
    system("clear || cls");
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
    printf("║          5 - Módulo Estoque                                                                  ║\n");
    printf("║          6 - Módulo Relatórios                                                               ║\n");
    printf("║          0 - Sair                                                                            ║\n");
    printf("║                                                                                              ║\n");
    printf("║          Escolha uma opção:                                                                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    scanf(" %c", &op);
    getchar();

}


void m_sobre(void) {
    char op;
    system("clear || cls");
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
    scanf(                        "Pressione <Enter> para voltar ao menu principal...\n");
    getchar();
}