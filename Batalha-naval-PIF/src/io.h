#ifndef IO_H
#define IO_H

#include "board.h"
#include "game.h" // Necessário para acessar struct Player no relatório

// Exibe o menu principal e retorna a opção escolhida
int mostrar_menu(void);

// Exibe o tabuleiro. 
// show_ships = 1 (mostra navios - para posicionamento ou fim de jogo)
// show_ships = 0 (esconde navios - para jogabilidade)
void io_print_board(Board* board, int show_ships);

// Lê uma coordenada (ex: "A5")
int io_read_coordinate(int* row, int* col);

// Lê dados para posicionamento manual (Coordenada + Orientação)
// Retorna 1 se sucesso, 0 se entrada inválida
int io_read_placement_input(int* row, int* col, int* orientation);

// Exibe o relatório final com estatísticas
void io_show_game_over(Player* winner, Player* loser);

#endif