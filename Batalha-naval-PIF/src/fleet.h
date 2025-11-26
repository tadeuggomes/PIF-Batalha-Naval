#ifndef FLEET_H
#define FLEET_H

typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    char name[20];
    int length;
    int hits;
} Ship;

typedef struct {
    Ship *ships;
    int count;
    int ships_afloat; 
} Fleet;

void fleet_init(Fleet* fleet);

void fleet_free(Fleet* fleet);

#endif