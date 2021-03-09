#ifndef DIE_H
#define DIE_H

#include "types.h"

#define FACES_DIE 6

typedef struct _Die Die;

Die *die_create(Id id);
STATUS die_destroy(Die *die);
STATUS die_roll(Die *die);
STATUS die_print(Die *die);

int die_getMin(Die *die);
STATUS die_setMin(Die *die, int min);

int die_getMax(Die *die);
STATUS die_setMin(Die *die, int max);

Id die_getId(Die *die)
STATUS die_setMin(Die *die, Id id);

int die_getLastState(Die *die);


#endif
