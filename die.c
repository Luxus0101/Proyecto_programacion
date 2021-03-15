/**
 * @brief Code for Die module
 *
 * @file die.c
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date  25-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"
#include "types.h"

struct _Die{
  Id id;
  int min_val;
  int max_val;
  int last_state;
};

Die *die_create(Id id, int min, int max){
  Die *d = NULL;

  if(id == NO_ID || !(max)|| !(min)) return NULL;

  d = (Die *) malloc(sizeof(Die));

  if(!d) return NULL;

  d->id = id;
  d->min_val = min;
  d->max_val = max;
  d->last_state = NO_LAST_STATE;

  return d;
}

STATUS die_destroy(Die *die){
  if(!die) return ERROR;

  free(die);
  die = NULL;

  return OK;
}

STATUS die_roll(Die *die){
  if(!die) return ERROR;

  die->last_state = die->min_val + (rand() % die->max_val);

  return OK;
}

STATUS die_print(FILE *f, Die *die){
  if(!die || !f || !(die->last_state)) return ERROR;

  fprintf(f, "Die %ld:\nMin value: %d\nMax value: %d\nLast value rolled: %d\n", die->id, die->min_val, die->max_val, die->last_state);

  return OK;
}

int die_getMin(Die *die){
  if(!die) return ERROR;

  return die->min_val;
}

STATUS die_setMin(Die *die, int min){
  if(!die) return ERROR;

  die->min_val = min;

  return OK;
}

int die_getMax(Die *die){
  if(!die) return ERROR;

  return die->max_val;
}
STATUS die_setMax(Die *die, int max){
  if(!die) return ERROR;

  die->max_val = max;

  return OK;
}

Id die_getId(Die *die){
  if(!die) return ERROR;

  return die->id;
}
STATUS die_setId(Die *die, Id id){
  if(!die) return ERROR;

  die->id = id;

  return OK;
}

int die_getLastState(Die *die){
  if(!die) return ERROR;

  return die->last_state;
}
