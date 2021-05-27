#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "game.h"

#ifndef DIALOGUE_H
#define DIALOGUE_H

typedef struct _Dialogue Dialogue;
Dialogue * dialogue_init();
STATUS dialogue_free(Dialogue *d);
char * dialogue_get_arg(Dialogue *d);
char * dialogue_get_dial(Dialogue *d);
STATUS dialogue_set_arg(Dialogue *d, char *a);
STATUS dialogue_set_dial(Dialogue *d, char *a);
STATUS dialogue_switch(Dialogue *d, int commId, STATUS st);

#endif
