#include "board.h"
#include <stdlib.h> // Para malloc() e free()
#include <stdio.h>  // Para printf() em caso de erro (opcional)

Board* board_inicializar(int rows, int cols) {
    // Aloca memória para a própria estrutura Board
    Board* board = (Board*) malloc(sizeof(Board));

    // Verifica se a alocação falhou
    if (board == NULL) {
        return NULL; 
    }

    //Preenche os campos de linhas e colunas
    board->rows = rows;
    board->cols = cols;

    //Aloca memória para o array de células (rows * cols)
    int total_cells = rows * cols;
    board->cells = (Cell*) malloc(total_cells * sizeof(Cell));

    // Verifica se a alocação das células falhou
    if (board->cells == NULL) {
        // Se a alocação das células falhou,
        // temos que liberar a estrutura 'board' que já tínhamos
        // alocado, senão ela vaza (memory leak).
        free(board); 
        return NULL; // Retorna NULL para indicar falha
    }

    // Inicializa todas as células (se a alocação foi um sucesso)
    for (int i = 0; i < total_cells; i++) {
        board->cells[i].state = CELL_WATER;
        board->cells[i].ship_id = -1;
    }

    // Retorna o ponteiro para o tabuleiro pronto
    return board;
}

void board_free(Board* board) {
    //  Verifica se o ponteiro é nulo (segurança)
    if (board == NULL) {
        return;
    }

    // Libera o array de células
    //    (Também é seguro checar se board->cells é NULL)
    if (board->cells != NULL) {
        free(board->cells);
    }

    // Libera a própria estrutura Board
    // (Deve ser feito DEPOIS de liberar 'cells')
    free(board);
}