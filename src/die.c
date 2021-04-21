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
  int minimum;
  int maximum;
  int last_roll;
};

Die *die_create(Id id){
  if (id<0){
    return NULL;
  }
  Die *d;

  d=(Die *)malloc(sizeof(Die));
  if (d == NULL)
  {
  return NULL;
  }
  d->id = id;
  d->maximum=6;
  d->minimum=1;
  d->last_roll = 0;
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

  die->last_roll = die->minimum + (rand() % die->maximum);

  return OK;
}

STATUS die_print(FILE *f, Die *die){
  if(!die || !f || !(die->last_roll)) return ERROR;

  fprintf(f, "Die %ld:\nMin value: %d\nMax value: %d\nLast value rolled: %d\n", die->id, die->minimum, die->maximum, die->last_roll);

  return OK;
}

int die_get_min(Die *die){
  if(!die) return ERROR;

  return die->minimum;
}

STATUS die_set_min(Die *die, int min){
  if(!die) return ERROR;

  die->minimum = min;

  return OK;
}

int die_get_max(Die *die){
  if(!die) return ERROR;

  return die->maximum;
}
STATUS die_set_max(Die *die, int max){
  if(!die) return ERROR;

  die->maximum = max;

  return OK;
}

Id die_get_id(Die *die){
  if(!die) return ERROR;

  return die->id;
}
STATUS die_set_id(Die *die, Id id){
  if(!die) return ERROR;

  die->id = id;

  return OK;
}

int die_last_roll(Die *die){
  if(!die) return ERROR;

  return die->last_roll;
}
