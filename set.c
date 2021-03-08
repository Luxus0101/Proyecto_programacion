#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include "types.h"

struct _Set{
  Id *id_vector;
  int number_of_ids;
};

Set *set_create(){
  Set *set = NULL;
  Id *id_vector;
  int i;
  set = (Set *)malloc(sizeof(Set));
  id_vector = (Id *)malloc(SET_MAX_SIZE*sizeof(Id));

  set->id_vector = id_vector;

  if(!set) return NULL;

  for(i = 0; i < SET_MAX_SIZE; i++){
    set->id_vector[i] = NO_ID;
  }

  set->number_of_ids = 0;

  return set;
}

STATUS set_destroy(Set *set){
  if(!set) return ERROR;

  free(set);
  set = NULL;

  return OK;
}

STATUS set_add(Set *set, Id id){
  int i;

  if(!set || id == NO_ID) return ERROR;

  for(i = 0; i < set->number_of_ids; i++){
  if(set->id_vector[i] == id) {
    return ERROR;
    }
  }

  set->id_vector[set->number_of_ids] = id;
  set->number_of_ids++;

  return OK;
}

STATUS set_del(Set *set, Id id){
  int i;
  short id_found = 0;

  if(!set || id < 0) return ERROR;

  for(i = 0; i < set->number_of_ids; i++){
    if(set->id_vector[i] == id) {
      id_found = 1;
    }
    if(id_found && i < SET_MAX_SIZE-1) set->id_vector[i] = set->id_vector[i+1];
    else if(id_found) set->id_vector[i] = NO_ID;
  }
  if(!id_found) return ERROR;

  set->number_of_ids--;

  return OK;

}

STATUS set_print(FILE *f, Set *set){
  int i;

  if(!set || !f) return ERROR;

  fprintf(f, "Set: ");
  for(i = 0; i < set->number_of_ids; i++){
    fprintf(f, "%ld ", set->id_vector[i]);
  }
  fprintf(f, "\n");

  return OK;
}
