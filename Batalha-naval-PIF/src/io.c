#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mostrar_menu(void) {
    int opcao = 0;
    // Loop para garantir entrada válida
    do {
        printf("\n======================\n");
        printf("   BATALHA NAVAL\n");
        printf("======================\n");
        printf("1. Novo Jogo\n");
        printf("2. Sair\n"); // Simplifiquei para focar no fluxo principal
        printf("----------------------\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer se digitar letra
            while(getchar() != '\n');
            opcao = 0;
        }
    } while (opcao < 1 || opcao > 2);
    return opcao;
}

void io_print_board(Board* board, int show_ships) {
    printf("\n   ");
    // Imprime cabeçalho das colunas (A, B, C...)
    for (int j = 0; j < board->cols; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < board->rows; i++) {
        printf("%2d ", i + 1); // Número da linha
        for (int j = 0; j < board->cols; j++) {
            int index = i * board->cols + j;
            Cell c = board->cells[index];
            char symbol = '.';

            // Define o símbolo baseado no estado da célula
            if (c.state == CELL_HIT) symbol = 'X';      // Acerto
            else if (c.state == CELL_MISS) symbol = 'O'; // Erro/Água
            else if (c.state == CELL_SHIP) {
                // Se deve mostrar navios, mostra 'S', senão esconde '.'
                symbol = (show_ships) ? 'S' : '.'; 
            }

            printf("%c ", symbol);
        }
        printf("\n");
    }
}

int io_read_coordinate(int* row, int* col) {
    char input[10];
    printf(">> Digite coordenada (ex: A1): ");
    scanf("%s", input);

    int len = strlen(input);
    if (len < 2) return 0; // Entrada muito curta

    // Processa a letra da coluna
    char c = toupper(input[0]);
    if (c < 'A' || c > 'Z') return 0;
    *col = c - 'A';

    // Processa o número da linha
    if (sscanf(input + 1, "%d", row) != 1) return 0;
    *row = *row - 1; // Ajusta para índice 0 (usuário vê 1, array é 0)

    return 1;
}

int io_read_placement_input(int* row, int* col, int* orientation) {
    // Primeiro pede a coordenada
    if (!io_read_coordinate(row, col)) return 0;

    // Depois pede a orientação
    char orient_char;
    printf(">> Orientacao (H para Horizontal, V para Vertical): ");
    // O espaço antes de %c ignora whitespaces anteriores
    scanf(" %c", &orient_char);
    orient_char = toupper(orient_char);

    if (orient_char == 'H') *orientation = 0; // 0 = Horizontal
    else if (orient_char == 'V') *orientation = 1; // 1 = Vertical
    else return 0; // Inválido

    return 1;
}

void io_show_game_over(Player* winner, Player* loser) {
    printf("\n\n");
    printf("########################################\n");
    printf("#             FIM DE JOGO              #\n");
    printf("########################################\n");
    printf("VENCEDOR: %s !!!\n\n", winner->nickname);

    // Cálculo de precisão
    float prec_w = (winner->total_shots > 0) ? ((float)winner->total_hits / winner->total_shots) * 100.0 : 0.0;
    float prec_l = (loser->total_shots > 0) ? ((float)loser->total_hits / loser->total_shots) * 100.0 : 0.0;

    printf("--- ESTATISTICAS ---\n");
    printf("%s (Vencedor):\n", winner->nickname);
    printf("  Tiros: %d | Acertos: %d | Precisao: %.1f%%\n", winner->total_shots, winner->total_hits, prec_w);
    
    printf("\n%s (Perdedor):\n", loser->nickname);
    printf("  Tiros: %d | Acertos: %d | Precisao: %.1f%%\n", loser->total_shots, loser->total_hits, prec_l);

    printf("\n--- ESTADO FINAL DOS TABULEIROS ---\n");
    printf("Tabuleiro do %s:\n", winner->nickname);
    io_print_board(winner->board, 1); // Mostra tudo

    printf("\nTabuleiro do %s:\n", loser->nickname);
    io_print_board(loser->board, 1); // Mostra tudo
    printf("\n");
}