/**
 * @brief It defines a space
 *
 * @file space.h
 * @author Nicolas Pacini and Enrique Ortega
 * @version 3.0
 * @date 14-04-2021
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "links.h"

#define NUM_SHAPES 3

typedef struct _Space Space;

#define MAX_SPACES 100
#define FIRST_SPACE 1

Space *space_create(Id id);
STATUS space_destroy(Space *space);
Id space_get_id(Space *space);
STATUS space_set_name(Space *space, char *name);
const char *space_get_name(Space *space);
STATUS space_set_north(Space *space, Id north);
Id space_get_north(Space *space);
STATUS space_set_south(Space *space, Id south);
Id space_get_south(Space *space);
STATUS space_set_east(Space *space, Id east);
Id space_get_east(Space *space);
STATUS space_set_west(Space *space, Id west);
Id space_get_west(Space *space);
STATUS space_add_object(Space *space, Id object);
STATUS space_del_object(Space *space, Id object);
long space_get_numObjects(Space *space);
STATUS space_print(Space *space);
Id space_get_location(Space *space);
STATUS space_set_location(Space *space, Id location);
BOOL space_isObject(Space *space, Id object);
Id *space_getObjectList(Space *space);
char **space_getDesc(Space *space);
STATUS space_setDesc(Space *space, char *desc, int index);
/**
 * @brief Checks if two spaces are connected by a link or nor
 * @param space1 a pointer to the first space
 * @param space2 a pointer to the second space
 * @return TRUE if they are connected or FALSE otherwise
 */
BOOL space_areConnected(Space *space1, Space *space2);
char *space_get_short_description(Space *space);
STATUS space_set_short_description(Space *space, char *desc);
char *space_get_large_description(Space *space);
STATUS space_set_large_description(Space *space, char *desc);
STATUS space_set_up(Space *space, Id up);
STATUS space_set_down(Space *space, Id down);
Id space_get_up(Space *space);
Id space_get_down(Space *space);
STATUS space_set_illuminated(Space *space, BOOL i);
BOOL space_get_illuminated(Space *space);
char *space_get_gdesc(Space *space, int i);
#endif
