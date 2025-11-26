#include "fleet.h"
#include <stdlib.h>
#include <string.h>

void fleet_init(Fleet* fleet) {
    fleet->count = 5;
    fleet->ships_afloat = 5;
    fleet->ships = (Ship*) malloc(fleet->count * sizeof(Ship));

    strcpy(fleet->ships[0].name, "Porta-avioes");
    fleet->ships[0].length = 5;
    fleet->ships[0].hits = 0;

    strcpy(fleet->ships[1].name, "Encouracado");
    fleet->ships[1].length = 4;
    fleet->ships[1].hits = 0;

    strcpy(fleet->ships[2].name, "Cruzador");
    fleet->ships[2].length = 3;
    fleet->ships[2].hits = 0;

    strcpy(fleet->ships[3].name, "Submarino");
    fleet->ships[3].length = 3;
    fleet->ships[3].hits = 0;

    strcpy(fleet->ships[4].name, "Destroyer");
    fleet->ships[4].length = 2;
    fleet->ships[4].hits = 0;
}

void fleet_free(Fleet* fleet) {
    if (fleet->ships != NULL) {
        free(fleet->ships);
    }
}