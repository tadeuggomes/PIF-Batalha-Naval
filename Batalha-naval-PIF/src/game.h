#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

// Estrutura que representa um jogador
typedef struct {
    Board* board;       // O tabuleiro do jogador
    Fleet fleet;        // A frota de navios
    char nickname[32];  // Nome do jogador
    int total_shots;    // Estatística: Total de tiros disparados
    int total_hits;     // Estatística: Total de acertos
} Player;

// Estrutura principal do jogo
typedef struct {
    Player p1;
    Player p2;
    int current_turn;   // 1 ou 2
    int game_over;      // Flag de fim de jogo
    int board_size;     // Tamanho do tabuleiro
} Game;

// Configura o jogo e inicializa as estruturas
void game_setup(Game* game, int size);

// Loop principal do jogo (turnos e lógica de tiro)
void game_loop(Game* game);

// Libera toda a memória alocada ao sair
void game_cleanup(Game* game);

#endif