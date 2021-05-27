#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "space.h"
#include "inventory.h"
#include "set.h"
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
  BOOL illum=FALSE;
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
      strcpy(gdesc[0], "");
      strcpy(gdesc[1], "");
      strcpy(gdesc[2], "");
      strcpy(s_short_desc, "");
      strcpy(s_large_desc, "");
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
      if (toks)
        strcpy(s_short_desc, toks);
      toks = strtok(NULL, "|");
      if (toks)
        strcpy(s_large_desc, toks);
      toks = strtok(NULL, "|");
      if(toks)
        illum=atoi(toks);

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
        space_set_illuminated(space, illum);
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
  BOOL illuminate = FALSE, turnedon = FALSE, movable = FALSE;
  char *toks = NULL;
  Id id = NO_ID, id_space = NO_ID, dependency = NO_ID, open = NO_ID;
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
      if (toks)
        strcpy(desc, toks);
      toks = strtok(NULL, "|");
      movable = atol(toks);
      toks = strtok(NULL, "|");
      dependency = atol(toks);
      toks = strtok(NULL, "|");
      open = atol(toks);
      toks = strtok(NULL, "|");
      illuminate = atoi(toks);
      toks = strtok(NULL, "|");
      turnedon = atoi(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%s|%d|%ld|%ld|%d|%d\n", id, name, id_space, desc, movable, dependency, open, illuminate, turnedon);
#endif
      object = object_create(id);
      if (object != NULL)
      {
        object_set_name(object, name);
        object_set_description(object, desc);
        game_add_object(game, object);
        game_set_object_location(game, id_space, id);
        object_setMovable(object, movable);
        object_setDependency(object, dependency);
        object_setOpen(object, open);
        object_setIlluminate(object, illuminate);
        object_setTurnedon(object, turnedon);
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
STATUS game_load_inv(Game *game, char *filename)
{
  FILE *file = NULL;
  long max_obs=0;
  Id ids=0;

  char line[WORD_SIZE] = "";
  char *toks = NULL;
  STATUS status=OK;
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
    if (strncmp("#i:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      max_obs = atol(toks);
      toks = strtok(NULL, "|");
      ids = atol(toks);
      toks = strtok(NULL, "|");

#ifdef DEBUG
      printf("Leido: %ld|%ld|", max_obs, ids);
#endif
      {
        player_set_inventory_max(game_get_player(game),max_obs);
        player_set_object(game_get_player(game), ids);
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
STATUS game_load_die(Game *game, char *filename)
{
  FILE *file = NULL;
  int max=0;
  int min=0;
  Id id=0;
  int last_roll=0;
  char line[WORD_SIZE] = "";
  char *toks = NULL;
  STATUS status=OK;
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
    if (strncmp("#d:", line, 3) == 0)
    {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      min = atoi(toks);
      toks = strtok(NULL, "|");
      max = atoi(toks);
      toks = strtok(NULL, "|");
      last_roll = atoi(toks);
      toks = strtok(NULL, "|");

#ifdef DEBUG
      printf("Leido: %ld|%d|%d|%d", id, min, max, last_roll);
#endif

      {
        die_set_id(game_get_die(game), id);
        die_set_min(game_get_die(game), min);
        die_set_max(game_get_die(game), max);
        die_set_lastroll(game_get_die(game), last_roll);
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

STATUS game_management_save(Game *game, char *filename)
{
  if (game == NULL)
    return ERROR;

  FILE *f = NULL;
  if (!(f = fopen(filename, "w")))
  {
    return ERROR;
  }

  for (long i = 1; i < MAX_SPACES && game_get_space(game, i) != NULL; i++)
  {
    fprintf(f, "#s:");
    fprintf(f, "%ld|", space_get_id(game_get_space(game, i)));
    fprintf(f, "%s|", space_get_name(game_get_space(game, i)));
    fprintf(f, "%ld|", space_get_north(game_get_space(game, i)));
    fprintf(f, "%ld|", space_get_east(game_get_space(game, i)));
    fprintf(f, "%ld|", space_get_south(game_get_space(game, i)));
    fprintf(f, "%ld", space_get_west(game_get_space(game, i)));
    if (strcmp(space_get_gdesc(game_get_space(game, i), 0), "") != 0)
        {
          fprintf(f,"|");
        }
    for (int j = 0; j < NUM_SHAPES; j++)
    {
      if (strcmp(space_get_gdesc(game_get_space(game, i), j), "") == 0)
      {
        fprintf(f, "\n");
        break;
      }
      fprintf(f, "%s|", space_get_gdesc(game_get_space(game, i), j));
    }
    if (strcmp(space_get_short_description(game_get_space(game, i)), "") != 0)
    {
      fprintf(f, "%s", space_get_short_description(game_get_space(game, i)));
      if (strcmp(space_get_large_description(game_get_space(game, i)), "") != 0)
      {
        fprintf(f, "|%s", space_get_large_description(game_get_space(game, i)));
        if ((game_get_space(game, i + 1) != NULL))
        {
          fprintf(f, "\n");
        }
      }
    }
  }
  for (int i = 0; i < MAX_OBJECTS && game_get_object_inp(game, i) != NULL; i++)
  {
    fprintf(f, "\n#o:");
    fprintf(f, "%ld|", object_get_id(game_get_object_inp(game, i)));
    fprintf(f, "%s|", object_get_name(game_get_object_inp(game, i)));
    fprintf(f, "%ld|", game_get_object_location(game, object_get_id(game_get_object_inp(game, i))));
    fprintf(f, "%s|", object_get_description(game_get_object_inp(game, i)));
    fprintf(f, "%d|", object_isMovable(game_get_object_inp(game, i)));
    fprintf(f, "%ld|", object_getDependency(game_get_object_inp(game, i)));
    fprintf(f, "%ld|", object_getOpen(game_get_object_inp(game, i)));
    fprintf(f, "%d|", object_canIlluminate(game_get_object_inp(game, i)));
    fprintf(f, "%d", object_isTurnedon(game_get_object_inp(game, i)));
  }

  fprintf(f, "\n#p:");
  fprintf(f, "%ld|", player_get_id(game_get_player(game)));
  fprintf(f, "%s|", player_get_name(game_get_player(game)));
  fprintf(f, "%ld|", player_get_location(game_get_player(game)));
  fprintf(f, "%ld|", inventory_num_obs(player_get_inv(game_get_player(game))));

  for (int i = 0; game_get_link_inp(game, i) != NULL && i < MAX_LINKS; i++)
  {
    fprintf(f, "\n#l:");
    fprintf(f, "%ld|", link_getId(game_get_link_inp(game, i)));
    fprintf(f, "%s|", link_getName(game_get_link_inp(game, i)));
    fprintf(f, "%ld|", link_getConnection1(game_get_link_inp(game, i)));
    fprintf(f, "%ld|", link_getConnection2(game_get_link_inp(game, i)));
    fprintf(f, "%d|", link_getStatus(game_get_link_inp(game, i)));
  }
  for (long i = 0; i < inventory_num_obs(player_get_inv(game_get_player(game))) && player_get_inv(game_get_player(game)) != NULL; i++)
  {
    fprintf(f, "\n#i:");
    fprintf(f, "%ld|", inventory_num_obs(player_get_inv(game_get_player(game))));
    fprintf(f, "%ld", inventory_get_id((player_get_inv(game_get_player(game))), i));
  }
  fprintf(f, "\n#d:");
  fprintf(f, "%ld|", die_get_id(game_get_die(game)));
  fprintf(f, "%d|", die_get_min(game_get_die(game)));
  fprintf(f, "%d|", die_get_max(game_get_die(game)));
  fprintf(f, "%d", die_last_roll(game_get_die(game)));

  fclose(f);
  return OK;
}
STATUS game_management_load(Game *game, char *filename)
{
  FILE *f=NULL;
  if (!(f = fopen(filename, "r")) || game == NULL)
  {
    return ERROR;
  }
  fclose(f);
  game_clean(game);
  if (game_create_from_file(game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_load_inv(game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_load_die(game, filename) == ERROR)
  {
    return ERROR;
  }

  return OK;
}
