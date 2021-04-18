/**
 * @brief It implements the links module
 *
 * @file links.h
 * @author Enrique Ortega Yegros
 * @version 1.0
 * @date 11-04-2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#ifndef LINKS_H
#define LINKS_H

/**
 * @brief Link ADT to connect spaces
 */
typedef struct _Link Link;

/**
 * @brief Links Status, OPEN or CLOSED
 */
typedef enum {
    OPEN,
    CLOSED
}LINK_ST;



/**
 * @brief Creates a link and returns a pointer to the link. It sets the link Id to -1, the spaces links are set to 0, the name is empty and it status OPEN.
 * @return A pointer to the link created
 */
Link *link_create();
/**
 * @brief Destroys the link given
 * @param l pointer to the link to be destroyed
 */
void link_destroy(Link *l);
/**
 * @brief Sets the Id of the link given
 * @param l pointer to the link which Id will be changed
 * @param id new id of the link
 * @return OK if it works correctly, ERROR in any other case
 */
STATUS link_setId(Link *l, Id id);
/**
 * @brief Changes name of the link given
 * @param l pointer to the link which name will be changed
 * @param name new name of the link
 * @return OK if it works correctly, ERROR in any other case
 */
STATUS link_setName(Link *l, const char *name);
/**
 * @brief Sets the ids connected by the link given
 * @param l pointer to the link to be connected
 * @param id1 Id of the space that will be connected
 * @param id2 Id of the space that will be connected
 * @return OK if it works correctly, ERROR in any other case
 */
STATUS link_setConnections(Link *l, Id id1, Id id2);
/**
 * @brief Sets the status of the link given to OPEN or CLOSED
 * @param l pointer to the link which status will be changed
 * @param st new status of the link (OPEN or CLOSED)
 * @return OK if it works correctly, ERROR in any other case
 */
STATUS link_setStatus(Link *l, LINK_ST st);
/**
 * @brief Gets the Id of the link given
 * @param l pointer to the link which Id will be returned
 * @return Id of the given Link or -1 id there was any error
 */
Id link_getId(Link *l);
/**
 * @brief Gets the name of the link given
 * @param l pointer to the link which name will be returned
 * @return A string copy with the name of the link or NULL if there was any error
 */
char *link_getName(Link *l);
/**
 * @brief Gets the id connected by the link given of the space 2
 * @param l pointer to the link which Spaces Ids will be returned
 * @return Id of the space 2 or -1 is there was any error
 */
Id link_getConnection1(Link *l);
/**
 * @brief Gets the id connected by the link given of the space 2
 * @param l pointer to the link which Spaces Ids will be returned
 * @return Id of the space 1 or -1 is there was any error
 */
Id link_getConnection2(Link *l);
/**
 * @brief Gets the status of the link given, OPEN or CLOSED
 * @param l pointer to the link which status will be returned
 * @return OPEN if the link is open, CLOSED if the link is closed or -1 if there was any error
 */
LINK_ST link_getStatus(Link *l);
/**
 * @brief Prints the link for debugging porpuses
 * @param l pointer to the link that will be printed
 * @return OK if it works correctly, ERROR in any other case
 */
STATUS link_print(Link *l);

#endif
