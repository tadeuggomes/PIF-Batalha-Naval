#include "board.h"
#include <stdlib.h> 
#include <stdio.h>  

Board* board_inicializar(int rows, int cols) {
    Board* board = (Board*) malloc(sizeof(Board));

    if (board == NULL) {
        return NULL; 
    }

    board->rows = rows;
    board->cols = cols;

    int total_cells = rows * cols;
    board->cells = (Cell*) malloc(total_cells * sizeof(Cell));

    if (board->cells == NULL) {
        free(board); 
        return NULL; 
    }

    for (int i = 0; i < total_cells; i++) {
        board->cells[i].state = CELL_WATER;
        board->cells[i].ship_id = -1;
    }

    return board;
}

void board_free(Board* board) {
    if (board == NULL) {
        return;
    }

    if (board->cells != NULL) {
        free(board->cells);
    }

    free(board);
}