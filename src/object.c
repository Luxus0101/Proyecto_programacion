#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"

struct _Object
{
  Id id;
  char name[WORD_SIZE + 1];
  char desc[WORD_SIZE];
  BOOL movable;
  Id dependency;
  Id open;
  BOOL illuminate;
  BOOL turnedon;
};

Object *object_create(Id id)
{
  Object *newObject = NULL;

  if (id == NO_ID)
    return NULL;

  newObject = (Object *)malloc(sizeof(Object));

  if (newObject == NULL)
  {
    return NULL;
  }

  newObject->id = id;

  newObject->name[0] = '\0';

  newObject->movable = FALSE;

  newObject->dependency = NO_ID;

  newObject->open = NO_ID;

  newObject->illuminate = FALSE;

  newObject->turnedon = FALSE;

  return newObject;
}

STATUS object_destroy(Object *object)
{
  if (!object)
  {
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}

STATUS object_set_name(Object *object, char *name)
{
  if (!object || !name)
  {
    return ERROR;
  }

  if (!strcpy(object->name, name))
  {
    return ERROR;
  }

  return OK;
}

const char *object_get_name(Object *object)
{
  if (!object)
  {
    return NULL;
  }
  return object->name;
}
STATUS object_print(Object *object)
{
  if (!object)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);
  return OK;
}

STATUS object_set_id(Object *object, Id id)
{
  if (!object)
  {
    return ERROR;
  }
  if (id < 0)
  {
    return ERROR;
  }
  object->id = id;

  return OK;
}
Id object_get_id(Object *object)
{
  if (!object)
  {
    return NO_ID;
  }
  return object->id;
}

STATUS object_set_description(Object *object, char *desc)
{
  if (!object)
    return ERROR;
  strcpy(object->desc, desc);
  return OK;
}

char *object_get_description(Object *object)
{
  if (!object)
    return NULL;
  return object->desc;
}

BOOL object_isMovable(Object *object)
{
  if (object == NULL)
  {
    return FALSE;
  }

  return object->movable;
}

STATUS object_setMovable(Object *object, BOOL movable)
{
  if (object == NULL)
  {
    return ERROR;
  }

  object->movable = movable;
  return OK;
}

Id object_getDependency(Object *object)
{
  if (object == NULL)
  {
    return NO_ID;
  }

  return object->dependency;
}

STATUS object_setDependency(Object *object, Id object_id)
{
  if (object == NULL || object_id < NO_ID)
  {
    return ERROR;
  }

  object->dependency = object_id;

  return OK;
}

Id object_getOpen(Object *object)
{
  if (object == NULL)
  {
    return NO_ID;
  }

  return object->open;
}

STATUS object_setOpen(Object *object, Id link_id)
{
  if (object == NULL || link_id < NO_ID)
  {
    return ERROR;
  }

  object->open = link_id;

  return OK;
}

BOOL object_canIlluminate(Object *object)
{
  if (object == NULL)
  {
    return FALSE;
  }

  return object->illuminate;
}

STATUS object_setIlluminate(Object *object, BOOL illuminate)
{
  if (object == NULL)
  {
    return ERROR;
  }

  object->illuminate = illuminate;

  return OK;
}

BOOL object_isTurnedon(Object *object)
{
  if (object == NULL)
  {
    return FALSE;
  }

  return object->turnedon;
}

STATUS object_setTurnedon(Object *object, BOOL turned)
{
  if (object == NULL)
  {
    return ERROR;
  }

  object->turnedon = turned;

  return OK;
}
