/**
 * @brief It defines a space
 *
 * @file object.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

struct _Object {
  Id id;
  char name[WORD_SIZE + 1];
  BOOL object;
};

Object* object_create(Id id) {

  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *) malloc(sizeof (Object));

  if (newObject == NULL) {
    return NULL;
  }
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

STATUS object_destroy(object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

STATUS object_set_name(object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

const char * object_get_name(object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Id object_get_id(object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

STATUS object_print(object* object) {
  Id idaux = NO_ID;

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> object (Id: %ld; Name: %s)\n", object->id, object->name);
  return OK;
}
