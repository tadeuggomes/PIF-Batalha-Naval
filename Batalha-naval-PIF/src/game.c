#include "game.h"
#include "rnd.h"
#include "io.h"
#include <stdio.h>
#include <string.h>

// --- Funções Auxiliares (Privadas) ---

// Verifica se um navio pode ser colocado na posição (Validação)
int _can_place_ship(Board* board, int len, int r, int c, int orient) {
    // 1. Verifica limites do tabuleiro
    if (orient == 0) { // Horizontal
        if (c + len > board->cols) return 0; // Sai do tabuleiro
    } else { // Vertical
        if (r + len > board->rows) return 0; // Sai do tabuleiro
    }

    // 2. Verifica sobreposição (se já existe navio ali)
    for (int i = 0; i < len; i++) {
        int rr = r + (orient == 1 ? i : 0);
        int cc = c + (orient == 0 ? i : 0);
        int idx = rr * board->cols + cc;
        if (board->cells[idx].state != CELL_WATER) return 0; // Já ocupado
    }
    return 1;
}

// Aplica o navio no tabuleiro (assume que validação passou)
void _apply_ship(Board* board, Ship* ship, int r, int c, int orient) {
    for (int i = 0; i < ship->length; i++) {
        int rr = r + (orient == 1 ? i : 0);
        int cc = c + (orient == 0 ? i : 0);
        int idx = rr * board->cols + cc;
        board->cells[idx].state = CELL_SHIP;
    }
}

// Tenta posicionar navio aleatoriamente (Para o Bot ou posicionamento auto)
int _try_place_ship_auto(Board* board, Ship* ship) {
    int r = rnd_get_int(0, board->rows - 1);
    int c = rnd_get_int(0, board->cols - 1);
    int orient = rnd_get_int(0, 1); 

    if (_can_place_ship(board, ship->length, r, c, orient)) {
        _apply_ship(board, ship, r, c, orient);
        return 1;
    }
    return 0;
}

// Lógica de Posicionamento Manual
void _place_ships_manual(Player* p) {
    printf("\n--- Posicionamento Manual: %s ---\n", p->nickname);
    io_print_board(p->board, 1); // Mostra o tabuleiro atual

    for (int i = 0; i < p->fleet.count; i++) {
        Ship* ship = &p->fleet.ships[i];
        int placed = 0;
        int r, c, orient;

        while (!placed) {
            printf("\nPosicione: %s (Tamanho: %d)\n", ship->name, ship->length);
            
            if (!io_read_placement_input(&r, &c, &orient)) {
                printf("[ERRO] Formato invalido! Tente novamente.\n");
                continue;
            }

            // Validação rigorosa
            if (r < 0 || r >= p->board->rows || c < 0 || c >= p->board->cols) {
                printf("[ERRO] Coordenada fora do tabuleiro!\n");
            } else if (_can_place_ship(p->board, ship->length, r, c, orient)) {
                _apply_ship(p->board, ship, r, c, orient);
                placed = 1;
                printf(">> %s posicionado com sucesso!\n", ship->name);
                io_print_board(p->board, 1); // Atualiza visualização
            } else {
                printf("[ERRO] Posicao invalida! Sobreposicao ou fora dos limites.\n");
            }
        }
    }
}

void _place_ships_auto_loop(Player* p) {
    for (int i = 0; i < p->fleet.count; i++) {
        while (!_try_place_ship_auto(p->board, &p->fleet.ships[i]));
    }
}

// --- Funções Públicas ---

void game_setup(Game* game, int size) {
    game->board_size = size;
    game->game_over = 0;
    game->current_turn = 1;

    // --- Jogador 1 ---
    strcpy(game->p1.nickname, "Jogador 1");
    game->p1.board = board_inicializar(size, size);
    game->p1.total_shots = 0;
    game->p1.total_hits = 0;
    fleet_init(&game->p1.fleet);

    // --- Jogador 2 ---
    strcpy(game->p2.nickname, "Jogador 2 (CPU)");
    game->p2.board = board_inicializar(size, size);
    game->p2.total_shots = 0;
    game->p2.total_hits = 0;
    fleet_init(&game->p2.fleet);

    // Seleção de Modo de Posicionamento para P1
    int mode = 0;
    while(mode != 1 && mode != 2) {
        printf("\nComo deseja posicionar sua frota?\n");
        printf("1. Automatico (Aleatorio)\n");
        printf("2. Manual\n");
        printf("Opcao: ");
        scanf("%d", &mode);
    }

    if (mode == 1) {
        printf("Posicionando navios do Jogador 1 automaticamente...\n");
        _place_ships_auto_loop(&game->p1);
    } else {
        _place_ships_manual(&game->p1);
    }

    // P2 (CPU) sempre posiciona automático
    printf("Posicionando navios do Jogador 2 (CPU)...\n");
    _place_ships_auto_loop(&game->p2);
}

int _process_shot(Player* shooter, Player* target, int r, int c) {
    if (r < 0 || r >= target->board->rows || c < 0 || c >= target->board->cols) return -1;
    
    int idx = r * target->board->cols + c;
    Cell* cell = &target->board->cells[idx];

    // Validação: não pode atirar onde já atirou
    if (cell->state == CELL_HIT || cell->state == CELL_MISS) return -1;

    shooter->total_shots++; // Computa estatística

    if (cell->state == CELL_SHIP) {
        cell->state = CELL_HIT;
        shooter->total_hits++; // Computa estatística
        return 1; // Acerto
    } else {
        cell->state = CELL_MISS;
        return 0; // Água
    }
}

int _check_loss(Player* p) {
    // Verifica se ainda existe alguma célula de navio não atingida
    int total = p->board->rows * p->board->cols;
    for(int i=0; i<total; i++) {
        if (p->board->cells[i].state == CELL_SHIP) return 0; // Ainda vivo
    }
    return 1; // Perdeu (tudo afundado)
}

void game_loop(Game* game) {
    int r, c;
    
    while (!game->game_over) {
        Player* curr = (game->current_turn == 1) ? &game->p1 : &game->p2;
        Player* opp  = (game->current_turn == 1) ? &game->p2 : &game->p1;

        // Se for turno da CPU (P2), faz jogada automática simples
        if (game->current_turn == 2) {
            printf("\n>>> Turno da CPU <<<\n");
            int valid = 0;
            while(!valid) {
                // Inteligência básica: tiro aleatório
                r = rnd_get_int(0, game->board_size - 1);
                c = rnd_get_int(0, game->board_size - 1);
                int res = _process_shot(curr, opp, r, c);
                if (res != -1) {
                    if (res == 1) printf("CPU ACERTOU em %c%d!\n", 'A'+c, r+1);
                    else printf("CPU errou (Agua) em %c%d.\n", 'A'+c, r+1);
                    valid = 1;
                }
            }
        } else {
            // Turno do Jogador Humano
            printf("\n>>> Turno de %s <<<\n", curr->nickname);
            printf("Tabuleiro do Inimigo:\n");
            io_print_board(opp->board, 0); // 0 = esconde navios

            int valid_shot = 0;
            while (!valid_shot) {
                if (!io_read_coordinate(&r, &c)) {
                    printf("Coordenada invalida!\n");
                    continue;
                }

                int res = _process_shot(curr, opp, r, c);
                if (res == -1) printf("Voce ja atirou ai ou fora dos limites!\n");
                else {
                    if (res == 1) printf("\n[ X ] ACERTOU EM CHEIO!\n");
                    else printf("\n[ O ] AGUA!\n");
                    valid_shot = 1;
                }
            }
        }

        // Verifica condição de vitória
        if (_check_loss(opp)) {
            io_show_game_over(curr, opp); // Exibe relatório final
            game->game_over = 1;
        } else {
            // Troca turno
            game->current_turn = (game->current_turn == 1) ? 2 : 1;
        }
    }
}

void game_cleanup(Game* game) {
    board_free(game->p1.board);
    fleet_free(&game->p1.fleet);
    board_free(game->p2.board);
    fleet_free(&game->p2.fleet);
    printf("Memoria liberada. Jogo encerrado.\n");
}