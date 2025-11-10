#include "io.h"
# include <stdio.h>

int mostrar_menu(void) {
    int opcao = 0;
    int escolha_validacao = 0;

    do {
        printf("\n");
        printf("======================\n");
        printf("   BATALHA NAVAL\n");
        printf("======================\n");
        printf("1. Novo Jogo\n");
        printf("2. Configurações\n");
        printf("3. Sair\n");
        printf("----------------------\n");
        printf("Escolha uma opção: ");

        escolha_validacao = scanf("%d", &opcao);

        if (escolha_validacao != 1) {
            printf("\n[ERRO] Entrada inválida. Por favor, digite um número.\n");

            while (getchar() != '\n');
            
            opcao = 0;
        } else if (opcao < 1 || opcao > 3) {

            printf("\n[ERRO] Opção inválida. Escolha 1, 2 ou 3.\n");
        }

    } while (opcao < 1 || opcao > 3);

    return opcao;
}