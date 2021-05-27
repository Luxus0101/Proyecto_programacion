#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "space.h"

STATUS game_load_spaces(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char s_short_desc[WORD_SIZE] = "";
  char s_large_desc[WORD_SIZE] = "";
  char *gdesc[NUM_SHAPES];
  for (int i = 0; i < NUM_SHAPES; i++)
  {
    if (!(gdesc[i] = (char *)calloc(WORD_SIZE + 1, sizeof(char))))
    {
      strncpy(gdesc[i], "", WORD_SIZE);
      return ERROR;
    };
  }
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#s:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      for (int i = 0; i < NUM_SHAPES; i++)
      {
        toks = strtok(NULL, "|");
        if (toks)
        {
          strcpy(gdesc[i], toks);
          gdesc[i][WORD_SIZE] = '\0';
        }
        else
        {
          while (i >= 0)
          {
            gdesc[i][0] = '\0';
            i--;
          }
          break;
        }
      }
      toks = strtok(NULL, "|");
      if(toks)
      strcpy(s_short_desc, toks);
      toks = strtok(NULL, "|");
      if(toks)
      strcpy(s_large_desc, toks);


#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%s|%s|%s\n", id, name, north, east, south, west, gdesc[0], gdesc[1], gdesc[2]);
#endif
      space = space_create(id);
      if (space != NULL)
      {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_setDesc(space, gdesc[0], 0);
        space_setDesc(space, gdesc[1], 1);
        space_setDesc(space, gdesc[2], 2);
        space_set_short_description(space, s_short_desc);
        space_set_large_description(space, s_large_desc);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);
  for (int i = 0; i < NUM_SHAPES; i++)
  {
    free(gdesc[i]);
  }

  return status;
}

STATUS game_load_objects(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char desc[WORD_SIZE] = "\0";
  char *toks = NULL;
  Id id = NO_ID, id_space = NO_ID;
  Object *object = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#o:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_space = atol(toks);
      toks = strtok(NULL, "|");
      if(toks)
      strcpy(desc, toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld\n", id, name, id_space);
#endif
      object = object_create(id);
      if (object != NULL)
      {
        object_set_name(object, name);
        object_set_description(object, desc);
        game_add_object(game, object);
        game_set_object_location(game, id_space, id);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}
STATUS game_load_player(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, id_player = NO_ID;
  int inv_size;
  Player *player = NULL;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#p:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_player = atol(toks);
      toks = strtok(NULL, "|");
      inv_size = atol(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%d\n", id, name, id_player, inv_size);
#endif
      player = player_create(id);
      if (player != NULL)
      {
        player_set_name(player, name);
        player_set_inventory_max(player, inv_size);
        game_add_player(game, player);
        game_set_player_location(game, id_player);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}
STATUS game_load_links(Game *game, char *filename)
{
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, id_space1 = NO_ID, id_space2 = NO_ID;
  Link *link = NULL;
  LINK_ST Lst = OPEN;
  STATUS status = OK;

  if (!filename)
  {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL)
  {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file))
  {
    if (strncmp("#l:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      id_space1 = atol(toks);
      toks = strtok(NULL, "|");
      id_space2 = atol(toks);
      toks = strtok(NULL, "|");
      Lst = atoi(toks);

#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%d\n", id, name, id_space1, id_space2, Lst);
#endif
      link = link_create();
      if (link != NULL)
      {
        link_setName(link, name);
        link_setId(link, id);
        link_setConnections(link, id_space1, id_space2);
        link_setStatus(link, Lst);
        game_add_link(game, link);
      }
    }
  }

  if (ferror(file))
  {
    status = ERROR;
  }

  fclose(file);

  return status;
}
