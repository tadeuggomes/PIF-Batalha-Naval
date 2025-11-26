#include <stdio.h>
#include "io.h"
#include "game.h"
#include "rnd.h"

int main() {
    rnd_init(); // Inicializa semente aleatória
    int menu_choice = 0;

    do {
        menu_choice = mostrar_menu();

        switch (menu_choice) {
            case 1: {
                printf("\n--- CONFIGURACAO INICIAL ---\n");
                Game game;
                int size = 10; 
                
                printf("Tamanho do tabuleiro (min 5, max 15): ");
                if (scanf("%d", &size) != 1) size = 10; // Fallback
                
                // Limites de segurança
                if (size < 5) size = 5;
                if (size > 15) size = 15;

                game_setup(&game, size); // Configura e posiciona
                game_loop(&game);        // Roda o jogo
                game_cleanup(&game);     // Limpa memória
                break;
            }
            case 2:
                printf("Saindo do jogo... Ate logo!\n");
                break;
        }
    } while (menu_choice != 2);

    return 0;
}