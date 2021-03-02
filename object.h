/**
 * @brief It defines a space
 *
 * @file object.h
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

Object* object_create(Id id);
STATUS object_destroy(Object* Object);
Id object_get_id(Object* object);
STATUS object_set_name(Object* object, char* name);
const char* object_get_name(Object* object);
STATUS object_print(Object* object);

#endif
