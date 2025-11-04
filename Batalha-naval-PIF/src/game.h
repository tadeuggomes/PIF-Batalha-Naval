#include "board.h"
#include "fleet.h"

typedef struct {
    Board board;
    Board shots;
    Fleet fleet;
    char nickname[32];
} Player;

typedef struct {
    Player p1, p2;
    int current_player;
    int game_over;
} Game;