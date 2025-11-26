#include "rnd.h"
#include <stdlib.h>
#include <time.h>

void rnd_init() {
    srand(time(NULL));
}

int rnd_get_int(int min, int max) {
    return min + rand() % (max - min + 1);
}