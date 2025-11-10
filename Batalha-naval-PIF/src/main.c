#include <stdio.h>
#include "io.h"

int main() {
    int menu_choice = 0;

    menu_choice = mostrar_menu();

    switch (menu_choice) {
        case 1:
            printf("Iniciando Novo Jogo...\n");
            // chamar game_create() e game_loop()
            break;
        case 2:
            printf("Configurações (não implementado).\n");
            break;
        case 3:
            printf("Saindo do jogo. Até logo!\n");
            break;
    }

    return 0;
}