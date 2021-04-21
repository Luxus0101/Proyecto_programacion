#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef SET_H
#define SET_H

#define ID_SIZE 4000

typedef struct _Set Set;
/**
 * @brief creates a set like structure
 * 
 * @return Set* 
 */
Set *set_create();
/**
 * @brief Destroys a set like structure
 * 
 * @param s 
 * @return STATUS 
 */
STATUS set_destroy(Set *s);
/**
 * @brief adds an id to the set
 * 
 * @param s 
 * @param id 
 * @return STATUS 
 */
STATUS set_add(Set *s, Id id);
/**
 * @brief deletes an id from the set
 * 
 * @param s 
 * @param id 
 * @return STATUS 
 */
STATUS set_del_id(Set *s, Id id);
/**
 * @brief checks if an id is found inside of a set
 * 
 * @param s 
 * @param id 
 * @return BOOL 
 */
BOOL _set_exist_id(Set *s, Id id);
/**
 * @brief obtains the number of ids stored in a set
 * 
 * @param s 
 * @return long 
 */
long set_get_num_ids(Set *s);
/**
 * @brief prints the elements contained inside of a set
 * 
 * @param s 
 * @return STATUS 
 */
STATUS set_print(Set *s);
/**
 * @brief Gets an array with the Ids stored in a Set
 *
 * @param s A pointer to the set
 *
 * @return A pointer to the Ids
 */
long *set_getVectors(Set *s);


long set_get_id(Set *s, int i);


#endif