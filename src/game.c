/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"
#include "set.h"
#include "die.h"
#include "inventory.h"
#include "dialogue.h"
#define N_CALLBACK 12
struct _Game
{
  Player *player;
  Object *object[MAX_OBJECTS + 1];
  Space *spaces[MAX_SPACES + 1];
  T_Command last_cmd;
  Die *die;
  Dialogue *dial;
  STATUS stat_last_cmd;
  Link *links[MAX_LINKS + 1];
  char last_description[WORD_SIZE + 1];
};

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game *game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game *game);
void game_callback_exit(Game *game);
void game_callback_take(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_move(Game *game);
void game_callback_inspect(Game *game);
void game_callback_turn_on(Game *game);
void game_callback_turn_off(Game *game);
void game_callback_open(Game *game);
void game_callback_save(Game *game);
void game_callback_load(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_move,
    game_callback_inspect,
    game_callback_turn_on,
    game_callback_turn_off,
    game_callback_open,
    game_callback_save,
    game_callback_load};

/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);
STATUS game_set_player_location(Game *game, Id id);

/**
   Game interface implementation
*/

Game *game_create()
{
  Game *game;
  if (!(game = (Game *)malloc(sizeof(Game))))
  {

    return NULL;
  }

  int i;

  for (i = 0; i < MAX_SPACES; i++)
  {
    game->spaces[i] = NULL;
  }

  game->player = NULL;
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    game->object[i] = NULL;
  }
  for (i = 0; i < MAX_LINKS; i++)
  {
    game->links[i] = NULL;
  }
  game->last_cmd = NO_CMD;
  if ((game->die = die_create(69)) == NULL)
  {
    free(game);
    return NULL;
  }
  game->stat_last_cmd = OK;

  game->dial = dialogue_init();

  strcpy(game->last_description, "");

  return game;
}

STATUS game_create_from_file(Game *game, char *filename)
{
  if (game_load_player(game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  if (game_load_objects(game, filename) == ERROR)
  {
    return ERROR;
  }
  if (game_load_links(game, filename) == ERROR)
  {
    return ERROR;
  }

  game_set_player_location(game, game_get_player_location(game));

  return OK;
}

STATUS game_destroy(Game *game)
{
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
  {
    space_destroy(game->spaces[i]);
  }
  for (i = 0; (i < MAX_OBJECTS) && (game->object[i] != NULL); i++)
  {
    object_destroy(game->object[i]);
  }
  for (i = 0; (i < MAX_LINKS) && (game->links[i] != NULL); i++)
  {
    link_destroy(game->links[i]);
  }
  player_destroy(game->player);
  die_destroy(game->die);
  dialogue_free(game->dial);
  free(game);
  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{

  if (position < 0 || position >= MAX_SPACES)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

STATUS game_set_player_location(Game *game, Id id)
{

  if (id == NO_ID)
  {
    return ERROR;
  }

  player_set_location(game->player, id);

  return OK;
}
STATUS game_set_dial(Game *game, Dialogue *d)
{
  if (game == NULL || d == NULL)
    return ERROR;
  game->dial = d;
  return OK;
}

Dialogue *game_get_dial(Game *game)
{
  if (game == NULL)
    return NULL;
  return game->dial;
}
STATUS game_set_object_location(Game *game, Id id_space, Id id_object)
{

  if (id_space == NO_ID || id_object == NO_ID || game == NULL)
  {
    return ERROR;
  }

  for (int i = 0; i < MAX_SPACES; i++)
  {
    if (space_get_id(game->spaces[i]) == id_space)
    {
      space_add_object(game->spaces[i], id_object);
      return OK;
    }
  }
  return ERROR;
}

Id game_get_player_location(Game *game)
{
  return player_get_location(game->player);
}

Id game_get_object_location(Game *game, Id id_object)
{
  if (game == NULL || id_object < 0)
  {
    return ERROR;
  }

  Id *arr = NULL;
  for (int i = 0; i < MAX_SPACES; i++)
  {

    arr = space_getObjectList(game->spaces[i]);

    for (int j = 0; j < space_get_numObjects(game->spaces[i]); j++)
    {
      if (arr[j] == id_object)
      {
        free(arr);
        return space_get_id(game->spaces[i]);
      }
    }
    free(arr);
  }
  return ERROR;
}

STATUS game_update(Game *game, T_Command cmd)
{
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game *game)
{
  return game->last_cmd;
}

void game_print_data(Game *game)
{
  int i = 0, j = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Objects location: \n");
  for (j = 0; j < MAX_OBJECTS && game->object[j] != NULL; j++)
  {
    printf(" %s  ", object_get_name(game->object[j]));
  }

  printf("=> Player location: %d\n", (int)game_get_player_location(game));

  printf("=> Die last value: %d\n", die_last_roll(game->die));

  printf("prompt:> ");
}

BOOL game_is_over(Game *game)
{
  return FALSE;
}

STATUS game_get_command_status(Game *game)
{
  if (game == NULL)
  {
    return ERROR;
  }
  return game->stat_last_cmd;
}
Object *game_get_object_inp(Game *game, int i)
{
  if (i < 0 || game == NULL)
  {
    return NULL;
  }
  return game->object[i];
}
STATUS game_add_object(Game *game, Object *object)
{
  int i = 0;

  if (object == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_OBJECTS) && (game->object[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->object[i] = object;

  return OK;
}
STATUS game_add_space(Game *game, Space *space)
{
  int i = 0;

  if (space == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_SPACES) && (game->spaces[i] != NULL))
  {
    i++;
  }

  if (i >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}
Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}
Player *game_get_player(Game *game)
{
  if (game == NULL)
  {
    return NULL;
  }
  return game->player;
}
Space *game_get_space_with_index(Game *game, long index)
{
  if (game == NULL || index < 0)
  {
    return NULL;
  }
  return game->spaces[index];
}
Die *game_get_die(Game *game)
{
  if (game == NULL)
  {
    return NULL;
  }
  return game->die;
}
STATUS game_add_player(Game *game, Player *player)
{
  if (player == NULL)
  {
    return ERROR;
  }

  game->player = player;
  return OK;
}
Link *game_get_link(Game *game, Id id)
{
  if (game == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < MAX_LINKS && (game->links[i] != NULL); i++)
  {

    if (link_getId(game->links[i]) == id)
    {
      return game->links[i];
    }
  }
  return NULL;
}

STATUS game_add_link(Game *game, Link *link)
{
  int i = 0;

  if (link == NULL)
  {
    return ERROR;
  }

  while ((i < MAX_LINKS) && (game->links[i] != NULL))
  {
    i++;
  }
  game->links[i] = link;

  if (i >= MAX_LINKS)
  {
    return ERROR;
  }

  return OK;
}

char *game_get_lastDescription(Game *game)
{
  if (game == NULL)
  {
    return NULL;
  }

  return game->last_description;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game *game)
{
  game->stat_last_cmd = ERROR;
}
void game_callback_exit(Game *game)
{
  game->stat_last_cmd = OK;
}
void game_callback_move(Game *game)
{
  Id space_id = NO_ID;
  int i = 0;
  Id current_id;
  char direction[100];

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  /*----------------------------*/
  scanf("%s", direction);
  dialogue_set_arg(game->dial, direction);

  if (strcmp("west", direction) == 0 || strcmp("w", direction) == 0)
  {
    space_id = game_get_player_location(game);
    if (space_id == NO_ID)
    {
      game->stat_last_cmd = ERROR;
      return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = link_getConnection2(game_get_link(game, space_get_west(game->spaces[i])));

        if (current_id != NO_ID && (link_getStatus(game_get_link(game, space_get_west(game->spaces[i]))) == Open))
        {
          game_set_player_location(game, current_id);
          game->stat_last_cmd = OK;
        }
        else
        {
          game->stat_last_cmd = ERROR;
          return;
        }
        strcpy(game->last_description, space_get_short_description(game_get_space(game, current_id)));
        return;
      }
    }
    game->stat_last_cmd = ERROR;
  }
  else if (strcmp("south", direction) == 0 || strcmp("s", direction) == 0)
  {
    space_id = game_get_player_location(game);
    if (space_id == NO_ID)
    {
      game->stat_last_cmd = ERROR;
      return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = link_getConnection2(game_get_link(game, space_get_south(game->spaces[i])));
        if (current_id != NO_ID && (link_getStatus(game_get_link(game, space_get_south(game->spaces[i]))) == Open))
        {
          game_set_player_location(game, current_id);
          game->stat_last_cmd = OK;
        }
        else
        {
          game->stat_last_cmd = ERROR;
          return;
        }
        strcpy(game->last_description, space_get_short_description(game_get_space(game, current_id)));
        return;
      }
    }
    game->stat_last_cmd = ERROR;
  }
  else if (strcmp("north", direction) == 0 || strcmp("n", direction) == 0)
  {
    space_id = game_get_player_location(game);

    if (NO_ID == space_id)
    {
      game->stat_last_cmd = ERROR;
      return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = link_getConnection1(game_get_link(game, space_get_north(game->spaces[i])));
        if (current_id != NO_ID && (link_getStatus(game_get_link(game, space_get_north(game->spaces[i]))) == Open))
        {
          game_set_player_location(game, current_id);
          game->stat_last_cmd = OK;
        }
        else
        {
          game->stat_last_cmd = ERROR;
          return;
        }
        strcpy(game->last_description, space_get_short_description(game_get_space(game, current_id)));
        return;
      }
    }
    game->stat_last_cmd = ERROR;
  }

  else if (strcmp("east", direction) == 0 || strcmp("e", direction) == 0)
  {
    space_id = game_get_player_location(game);
    if (space_id == NO_ID)
    {
      game->stat_last_cmd = ERROR;
      return;
    }

    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      current_id = space_get_id(game->spaces[i]);
      if (current_id == space_id)
      {
        current_id = link_getConnection2(game_get_link(game, space_get_east(game->spaces[i])));
        if (current_id != NO_ID && (link_getStatus(game_get_link(game, space_get_east(game->spaces[i]))) == Open))
        {
          game_set_player_location(game, current_id);
          game->stat_last_cmd = OK;
        }
        else
        {
          game->stat_last_cmd = ERROR;
          return;
        }
        strcpy(game->last_description, space_get_short_description(game_get_space(game, current_id)));
        return;
      }
    }
    game->stat_last_cmd = ERROR;
  }
  else
  {
    game->stat_last_cmd = ERROR;
    return;
  }
}
void game_callback_take(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  Id object_loc_id = NO_ID;
  BOOL canBeTaken = FALSE;
  char object_desc[100];
  if (Inventory_get_set_num_ids(player_get_inv(game_get_player(game))) != inventory_num_obs(player_get_inv(game_get_player(game))))
  {
    scanf("%s", object_desc);

    dialogue_set_arg(game->dial, object_desc);

    if ((object_id = strtol(object_desc, NULL, 10)) == 0)
    {
      for (int i = 0; game->object[i] != NULL; i++)
      {
        if (strcmp(object_get_name(game->object[i]), object_desc) == 0)
        {
          object_id = object_get_id(game->object[i]);
          canBeTaken = game_object_canBeTaken(game, game->object[i]);
          break;
        }
      }
    }

    player_id = game_get_player_location(game);
    if (object_id == NO_ID)
    {
      game->stat_last_cmd = ERROR;
      return;
    }

    object_loc_id = game_get_object_location(game, object_id);
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
    {
      current_id = space_get_id(game->spaces[i]);

      if (current_id == object_loc_id && player_id == current_id && player_object_exist(game->player, object_id) == FALSE && canBeTaken)
      {

        player_set_object(game->player, object_id);
        space_del_object(game->spaces[i], object_id);
        game->stat_last_cmd = OK;

        return;
      }
    }
  }
  game->stat_last_cmd = ERROR;
  return;
}
void game_callback_drop(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id player_id = NO_ID;
  Id object_id = NO_ID;
  char object_desc[100];
  Id obj_dep = NO_ID;
  player_id = game_get_player_location(game);

  if (NO_ID == player_id)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  scanf("%s", object_desc);
  dialogue_set_arg(game->dial, object_desc);

  if ((object_id = strtol(object_desc, NULL, 10)) == 0)
  {
    for (int i = 0; game->object[i] != NULL; i++)
    {
      if (strcmp(object_get_name(game->object[i]), object_desc) == 0)
      {
        object_id = object_get_id(game->object[i]);
        obj_dep = object_getDependency(game->object[i]);
        printf("objid: %ld\n", object_id);
        break;
      }
    }
  }

  if (object_id == NO_ID)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  if (Inventory_check_object(player_get_inv(game->player), object_id) == FALSE)
  {
    game->stat_last_cmd = ERROR;
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_id)
    {
      if (obj_dep != NO_ID)
      {
        space_add_object(game->spaces[i], obj_dep);
        player_sub_object(game->player, obj_dep);
        space_add_object(game->spaces[i], object_id);
        player_sub_object(game->player, object_id);
        game->stat_last_cmd = OK;
        return;
      }
      else
      {
        space_add_object(game->spaces[i], object_id);
        player_sub_object(game->player, object_id);
        game->stat_last_cmd = OK;
        return;
      }
    }
  }
  game->stat_last_cmd = ERROR;
}
void game_callback_roll(Game *game)
{
  if (die_roll(game->die) < 0)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  game->stat_last_cmd = OK;
  return;
}
void game_callback_inspect(Game *game)
{
  Id space_id = NO_ID, object_id = NO_ID;
  int i;
  BOOL object_found = FALSE;
  char desc[WORD_SIZE];

  space_id = game_get_player_location(game);
  if (space_id == NO_ID)
  {
    game->stat_last_cmd = ERROR;
    return;
  }

  scanf("%s", desc);

  if (space_get_illuminated(game_get_space(game, game_get_player_location(game))))
  {
    /*Return space description*/
    if (strcmp("space", desc) == 0 || strcmp("s", desc) == 0)
    {

      strcpy(game->last_description, space_get_large_description(game_get_space(game, space_id)));
      printf("%s", space_get_short_description(game_get_space(game, space_id)));
      game->stat_last_cmd = OK;
      return;
    }

    /*Return object description*/
    else
    {
      for (i = 0; game->object[i] != NULL; i++)
      {
        if (strcmp(object_get_name(game->object[i]), desc) == 0)
        {
          object_id = object_get_id(game->object[i]);
          object_found = TRUE;
          break;
        }
      }
      if ((object_found && game_get_object_location(game, object_get_id(game->object[i])) == game_get_player_location(game)) || Inventory_check_object(player_get_inv(game_get_player(game)), object_id))
      {
        strcpy(game->last_description, object_get_description(game->object[i]));
        game->stat_last_cmd = OK;
        return;
      }
      else if (object_found)
      {
        strcpy(game->last_description, "The object isn't here");
        game->stat_last_cmd = OK;
        return;
      }
      else
      {
        strcpy(game->last_description, "That object doesn't exist");
        game->stat_last_cmd = OK;
        return;
      }
    }
  }
  else
  {
    strcpy(game->last_description, space_get_short_description(game_get_space(game, space_id)));
    game->stat_last_cmd = OK;
    return;
  }
}

BOOL game_object_canBeTaken(Game *game, Object *object)
{
  if (object == NULL || game == NULL)
  {
    return FALSE;
  }

  Id dep_obj = object_getDependency(object);

  if (Inventory_check_object(player_get_inv(game->player), dep_obj) == TRUE || dep_obj == NO_ID)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void game_callback_turn_on(Game *game)
{
  if (game == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  char obj_name[WORD_SIZE] = "";
  STATUS done = OK;
  scanf("%s", obj_name);

  for (int i = 0; game->object[i] != NULL; i++)
  {
    if (!(strcmp(object_get_name(game->object[i]), obj_name)))
    {
      if (object_isTurnedon(game->object[i]) == TRUE)
      {
        done = ERROR;
        break;
      }
      object_setTurnedon(game->object[i], TRUE);
      if (!space_get_illuminated(game_get_space(game, game_get_player_location(game))))
      {
        space_set_illuminated(game_get_space(game, game_get_player_location(game)), TRUE);
        done = OK;
        break;
      }
      else
      {
        done = OK;
        break;
      }
    }
  }
  if (done == OK)
  {
    game->stat_last_cmd = OK;
    return;
  }
  else
  {
    game->stat_last_cmd = ERROR;
    return;
  }
}

void game_callback_turn_off(Game *game)
{
  if (game == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  char obj_name[WORD_SIZE] = "";
  STATUS done = OK;
  scanf("%s", obj_name);

  for (int i = 0; game->object[i] != NULL; i++)
  {
    if (!(strcmp(object_get_name(game->object[i]), obj_name)))
    {
      if (object_isTurnedon(game->object[i]) == FALSE)
      {
        done = ERROR;
        break;
      }
      object_setTurnedon(game->object[i], FALSE);
      if (!space_get_illuminated(game_get_space(game, game_get_player_location(game))))
      {
        space_set_illuminated(game_get_space(game, game_get_player_location(game)), FALSE);
        done = OK;
        break;
      }
      else
      {
        done = OK;
        break;
      }
    }
  }
  if (done == OK)
  {
    game->stat_last_cmd = OK;
    return;
  }
  else
  {
    game->stat_last_cmd = ERROR;
    return;
  }
}
void game_callback_open(Game *game)
{
  if (game == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  char desc[WORD_SIZE] = "";
  char *lnk_name = NULL;
  char *with = NULL;
  char *obj_name = NULL;
  Id current_id = NO_ID;

  current_id = game_get_player_location(game);

  fgets(desc, WORD_SIZE, stdin);
  lnk_name = strtok(desc, " ");
  with = strtok(NULL, " ");
  obj_name = strtok(NULL, " ");
  if (obj_name == NULL)
  {
    game->stat_last_cmd = ERROR;
    dialogue_set_arg(game->dial, "this");
    return;
  }
  obj_name[strlen(obj_name) - 1] = '\0';
  dialogue_set_arg(game->dial, lnk_name);
  if (lnk_name == NULL || with == NULL || obj_name == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }

  for (long i = 0; i < MAX_OBJECTS; i++)
  {
    if (!(strcmp(object_get_name(game->object[i]), obj_name)))
    {

      if (Inventory_check_object(player_get_inv(game->player), object_get_id(game->object[i])))
      {

        for (int j = 0; game->links[j] != NULL; j++)
        {
          if ((!(strcmp(link_getName(game->links[j]), lnk_name))) && (link_getConnection1(game->links[j]) == current_id || link_getConnection2(game->links[j]) == current_id))
          {
            if (object_getOpen(game->object[i]) == link_getId(game->links[j]))
            {

              if (link_getStatus(game->links[j]) == Open)
              {
                game->stat_last_cmd = ERROR;
                return;
              }
              link_setStatus(game->links[j], Open);
              game->stat_last_cmd = OK;
              return;
            }
          }
        }
      }
    }
  }

  game->stat_last_cmd = ERROR;
  return;
}

void game_callback_save(Game *game)
{
  char filename[WORD_SIZE] = "";
  scanf("%s", filename);
  if (filename == NULL || game == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  dialogue_set_arg(game->dial, filename);
  if (game_management_save(game, filename) == OK)
  {
    game->stat_last_cmd = OK;
    return;
  }
  game->stat_last_cmd = ERROR;
  return;
}
void game_callback_load(Game *game)
{

  char filename[WORD_SIZE] = "";
  FILE *f;
   scanf("%s", filename);
  
  if (filename == NULL || game == NULL)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  dialogue_set_arg(game->dial, filename);
  if (game_management_load(game, filename) == ERROR)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  game->stat_last_cmd = OK;
  return;
}

Link *game_get_link_with_id(Game *game, Id id)
{
  if (id < 0 || game == NULL)
  {
    return NULL;
  }

  for (int i = 0; i < MAX_LINKS && game->links[i] != NULL; i++)
  {
    if (link_getId(game->links[i]) == id)
    {
      return game->links[i];
    }
  }
  return NULL;
}

Link *game_get_link_inp(Game *game, int index)
{
  if (game == NULL || index < NO_ID)
  {
    return NULL;
  }
  return game->links[index];
}

STATUS game_clean(Game *game)
{
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++)
  {
    space_destroy(game->spaces[i]);
    game->spaces[i] = NULL;
  }
  for (i = 0; (i < MAX_OBJECTS) && (game->object[i] != NULL); i++)
  {
    object_destroy(game->object[i]);
    game->object[i] = NULL;
  }
  for (i = 0; (i < MAX_LINKS) && (game->links[i] != NULL); i++)
  {
    link_destroy(game->links[i]);
    game->links[i] = NULL;
  }
  player_destroy(game->player);

  return OK;
}
