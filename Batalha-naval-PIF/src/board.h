typedef enum { CELL_WATER, CELL_SHIP, CELL_HIT, CELL_MISS } CellState;

typedef struct {
    CellState state;
    int ship_id;
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells;
} Board;