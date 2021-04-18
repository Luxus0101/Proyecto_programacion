#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef OBJECT_H
#define OBJECT_H

#define MAX_OBJECTS 4

#include "types.h"

typedef struct _Object Object;
/**
 * @brief creates an object like structure
 * 
 * @param id 
 * @return Object* 
 */
Object *object_create(Id id);
 /**
 * @brief destroys a selected object
 * 
 * @param object 
 * @return STATUS 
 */
STATUS object_destroy(Object *object);
/**
 * @brief gives a certain name to an object structre
 * 
 * @param object 
 * @param name 
 * @return STATUS 
 */
STATUS object_set_name(Object *object, char *name);
/**
 * @brief finds the name for a determined object
 * 
 * @param object 
 * @return const char* 
 */
const char *object_get_name(Object *object);
/**
 * @brief prints the elements of an object like structure on screen
 * 
 * @param object 
 * @return * STATUS 
 */
STATUS object_print(Object *object);
 /**
 * @brief sets a determined id for an object
 * 
 * @param object 
 * @param id 
 * @return STATUS 
 */
 
STATUS object_set_id(Object *object, Id id);
/**
 * @brief finds the id of a certain object
 * 
 * @param object 
 * @return Id 
 */
Id object_get_id(Object *object);

#endif
