#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef OBJECT_H
#define OBJECT_H

#define MAX_OBJECTS 15

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
 * @param object Pointer to the object
 * @return STATUS 
 */
STATUS object_destroy(Object *object);
/**
 * @brief gives a certain name to an object structre
 * 
 * @param object Pointer to the object
 * @param name 
 * @return STATUS 
 */
STATUS object_set_name(Object *object, char *name);
/**
 * @brief finds the name for a determined object
 * 
 * @param object Pointer to the object
 * @return const char* 
 */
const char *object_get_name(Object *object);
/**
 * @brief prints the elements of an object like structure on screen
 * 
 * @param object Pointer to the object
 * @return * STATUS 
 */
STATUS object_print(Object *object);
/**
 * @brief sets a determined id for an object
 * 
 * @param object Pointer to the object
 * @param id 
 * @return STATUS 
 */

STATUS object_set_id(Object *object, Id id);
/**
 * @brief finds the id of a certain object
 * 
 * @param object Pointer to the object
 * @return Id 
 */
Id object_get_id(Object *object);

/**
 * @brief gives a certain description to an object structre
 *
 * @param object Pointer to the object
 * @param description
 * @return STATUS
 */
STATUS object_set_description(Object *object, char *desc);

/**
 * @brief finds the description for a determined object
 *
 * @param object Pointer to the object
 * @return const char*
 */
char *object_get_description(Object *object);
/**
 * @brief returns if the object is movable or not
 * 
 * @param object 
 * @return BOOL, TRUE if it is movable, FALSE otherwise
 */
BOOL object_isMovable(Object *object);
/**
 * @brief Stablishes is an object can be moved or not
 * 
 * @param object Pointer to the object
 * @param movable TRUE if can be moved, FALSE if not
 * @return STATUS, OK or ERROR
 */
STATUS object_setMovable(Object *object, BOOL movable);
/**
 * @brief returns the id of an object that the object depends on
 * 
 * @param object Pointer to the object
 * @return Id of the object
 */
Id object_getDependency(Object *object);
/**
 * @brief Stablishes the object dependency of an space
 * 
 * @param object Pointer to the object
 * @param object_id Id of the object
 * @return STATUS, OK or ERROR
 */
STATUS object_setDependency(Object *object, Id object_id);
/**
 * @brief returns the id of a link that object can open
 * 
 * @param object Pointer to the object
 * @return Id of the link
 */
Id object_getOpen(Object *object);
/**
 * @brief Stablishes the link the object can open
 * 
 * @param object Pointer to the object
 * @param link_id Id of the link
 * @return STATUS, OK or ERROR
 */
STATUS object_setOpen(Object *object, Id link_id);
/**
 * @brief returns if the object can illuminate or not
 * 
 * @param object 
 * @return BOOL, TRUE if it can, FALSE otherwise
 */
BOOL object_canIlluminate(Object *object);
/**
 * @brief Stablishes is an object can illuminate or not
 * 
 * @param object Pointer to the object
 * @param movable TRUE if can illuminate, FALSE if not
 * @return STATUS, OK or ERROR
 */
STATUS object_setIlluminate(Object *object, BOOL illuminate);
/**
 * @brief returns if the object is turned on or off
 * 
 * @param object 
 * @return BOOL, TRUE if it is on, FALSE otherwise
 */
BOOL object_isTurnedon(Object *object);
/**
 * @brief Stablishes if an object is truned on or off
 * 
 * @param object Pointer to the object
 * @param movable TRUE if it is on, FALSE if not
 * @return STATUS, OK or ERROR
 */
STATUS object_setTurnedon(Object *object, BOOL turned);


#endif
