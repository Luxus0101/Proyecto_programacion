/**
 * @brief It defines a space
 *
 * @file space.c
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date  25-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  Id object;
};

Space* space_create(Id id) {

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->object = FALSE;

  return newSpace;
}

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  free(space);
  space = NULL;

  return OK;
}

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }

  return OK;
}

/* Movement of the player*/

STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

STATUS space_set_object(Space* space, Id value) {
  if (!space) {
    return ERROR;
  }
  space->object = value;
  return OK;
}

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

/* */

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Id space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  return space->object;
}

STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  if (space_get_object(space)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
