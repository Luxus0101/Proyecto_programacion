#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "types.h"
#include "space.h"
#include "set.h"
#include "links.h"

struct _Space
{
  Id id;
  char name[WORD_SIZE + 1];
  char *gdesc[NUM_SHAPES];
  char short_desc[WORD_SIZE + 1];
  char large_desc[WORD_SIZE + 1];
  Id north, south, east, west, up, down;
  Set *objects;
  BOOL illuminated;
};

Space *space_create(Id id)
{

  Space *newSpace = NULL;

  if (id == NO_ID)
    return NULL;

  newSpace = (Space *)malloc(sizeof(Space));

  if (newSpace == NULL)
  {
    return NULL;
  }
  newSpace->id = id;

  newSpace->name[0] = '\0';

  for (int i = 0; i < NUM_SHAPES; i++)
  {
    if (!(newSpace->gdesc[i] = (char *)calloc(WORD_SIZE + 1, sizeof(char))))
    {
      free(newSpace);
      return NULL;
    }
    (newSpace->gdesc[i])[0] = '\0';
  }

  strcpy(newSpace->short_desc, "");
  strcpy(newSpace->large_desc, "");

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->up = NO_ID;
  newSpace->down = NO_ID;

  newSpace->illuminated = TRUE;

  newSpace->objects = set_create();
  if (newSpace->objects == NULL)
  {
    return NULL;
  }

  return newSpace;
}

STATUS space_destroy(Space *space)
{
  if (!space)
  {
    return ERROR;
  }
  if (set_destroy(space->objects) == ERROR)
  {
    return ERROR;
  }


  for (int i = 0; i < NUM_SHAPES; i++)
  {
    free(space->gdesc[i]);
  }

  free(space);
  space = NULL;

  return OK;
}
BOOL space_isObject(Space *space, Id object)
{
  if (space == NULL || object < 0)
  {
    return ERROR;
  }

  if (_set_exist_id(space->objects, object) == TRUE)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

STATUS space_set_name(Space *space, char *name)
{
  if (!space || !name)
  {
    return ERROR;
  }

  if (!strcpy(space->name, name))
  {
    return ERROR;
  }

  return OK;
}

STATUS space_set_north(Space *space, Id north)
{
  if (!space || north == NO_ID)
  {
    return ERROR;
  }

  space->north = north;

  return OK;
}

STATUS space_set_south(Space *space, Id south)
{
  if (!space || south == NO_ID)
  {
    return ERROR;
  }

  space->south = south;
  return OK;
}

STATUS space_set_east(Space *space, Id east)
{
  if (!space || east == NO_ID)
  {
    return ERROR;
  }

  space->east = east;
  return OK;
}

STATUS space_set_west(Space *space, Id west)
{
  if (!space || west == NO_ID)
  {
    return ERROR;
  }

  space->west = west;
  return OK;
}

STATUS space_set_up(Space *space, Id up)
{
  if (!space || up == NO_ID)
  {
    return ERROR;
  }

  space->up = up;
  return OK;
}

STATUS space_set_down(Space *space, Id down)
{
  if (!space || down == NO_ID)
  {
    return ERROR;
  }

  space->down = down;
  return OK;
}

const char *space_get_name(Space *space)
{
  if (!space)
  {
    return NULL;
  }
  return space->name;
}

Id space_get_id(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->id;
}

STATUS space_add_object(Space *space, Id object)
{
  if (!space)
  {
    return ERROR;
  }
  if (object < 0)
  {
    return ERROR;
  }
  if (set_add(space->objects, object) == ERROR)
  {
    return ERROR;
  }
  return OK;
}
STATUS space_del_object(Space *space, Id object)
{
  if (!space)
  {
    return ERROR;
  }
  if (object < 0)
  {
    return ERROR;
  }
  if (set_del_id(space->objects, object) == ERROR)
  {
    return ERROR;
  }
  return OK;
}

Id space_get_north(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->north;
}

Id space_get_south(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->south;
}

Id space_get_east(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->east;
}

Id space_get_west(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->west;
}

Id space_get_up(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->up;
}

Id space_get_down(Space *space)
{
  if (!space)
  {
    return NO_ID;
  }
  return space->down;
}

BOOL space_get_object(Space *space)
{
  if (space == NULL)
  {
    return FALSE;
  }

  if (set_get_num_ids(space->objects) > 0)
  {
    return TRUE;
  }

  return FALSE;
}

STATUS space_set_illuminated(Space *space, BOOL i){
  if(!space) return ERROR;
  space->illuminated = i;
  return OK;
}

BOOL space_get_illuminated(Space *space){
  if(!space) return FALSE;
  return space->illuminated;
}

STATUS space_print(Space *space)
{
  Link *laux = NULL;
  if (!space)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);
  fprintf(stdout, "-->Shape:");
  for (int i = 0; i < NUM_SHAPES; i++)
  {
    fprintf(stdout, "\n%s", space->gdesc[i]);
  }

 link_setId(laux, space_get_north(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No north link.\n");
  }

  link_setId(laux, space_get_south(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No south link.\n");
  }

  link_setId(laux, space_get_east(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No east link.\n");
  }

  link_setId(laux, space_get_west(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No west link.\n");
  }

  link_setId(laux, space_get_up(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No up link.\n");
  }

  link_setId(laux, space_get_down(space));
  if (NULL != laux)
  {
    link_print(laux);
  }
  else
  {
    fprintf(stdout, "---> No down link.\n");
  }

  if (space_get_object(space) == 1)
  {

    fprintf(stdout, "---> Objects in the space.\n");
  }
  else
  {
    fprintf(stdout, "---> No object in the space.\n");
  }

  fprintf(stdout, "Illuminated? %hd\n", space->illuminated);

  return OK;
}
Id *space_getObjectList(Space *space)
{
  if (!space)
  {
    return FALSE;
  }
  return set_getVectors(space->objects);
}
long space_get_numObjects(Space *space)
{
  if (space == NULL)
  {
    return -1;
  }
  return set_get_num_ids(space->objects);
}

char **space_getDesc(Space *space)
{
  if (space == NULL)
  {
    return NULL;
  }

  return space->gdesc;
}

STATUS space_setDesc(Space *space, char *desc, int index)
{
  if (space == NULL || desc == NULL || index < 0)
  {
    return ERROR;
  }

  if (strcpy(space->gdesc[index], desc) == NULL)
  {
    return ERROR;
  }
  return OK;
}

BOOL space_areConnected(Space *space1, Space *space2)
{
  if (space1 == NULL || space2 == NULL)
  {
    return 0;
  }

  if (space1->north == space2->south)
  {
    return 1;
  }
  if (space1->east == space2->west)
  {
    return 1;
  }
  if (space1->south == space2->north)
  {
    return 1;
  }
  if (space1->west == space2->east)
  {
    return 1;
  }
  return 0;
}

STATUS space_set_short_description(Space *space, char *desc){
  if(!space || desc == NULL) return ERROR;
  strcpy(space->short_desc, desc);
  return OK;
}

char *space_get_short_description(Space *space){
  if(!space) return NULL;
  return space->short_desc;
}

STATUS space_set_large_description(Space *space, char *desc){
  if(!space || desc == NULL) return ERROR;
  strcpy(space->large_desc, desc);
  return OK;
}

char *space_get_large_description(Space *space){
  if(!space) return NULL;
  return space->large_desc;
}
char *space_get_gdesc(Space *space, int i)
{
  if (space == NULL || i < 0||i>NUM_SHAPES)
  {
    return NULL;
  }
  return space->gdesc[i];
}
