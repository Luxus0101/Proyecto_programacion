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
#include "inventory.h"
#define N_CALLBACK 9
struct _Game
{
  Player *player;
  Object *object[MAX_OBJECTS + 1];
  Space *spaces[MAX_SPACES + 1];
  T_Command last_cmd;
  Dice *dice;
  STATUS stat_last_cmd;
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
void game_callback_next(Game *game);
void game_callback_back(Game *game);
void game_callback_take(Game *game);
void game_callback_drop(Game *game);
void game_callback_roll(Game *game);
void game_callback_right(Game *game);
void game_callback_left(Game *game);

static callback_fn game_callback_fn_list[N_CALLBACK] = {
    game_callback_unknown,
    game_callback_exit,
    game_callback_next,
    game_callback_back,
    game_callback_take,
    game_callback_drop,
    game_callback_roll,
    game_callback_right,
    game_callback_left,
};

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
  game->last_cmd = NO_CMD;
  if ((game->dice = dice_create(69)) == NULL)
  {
    free(game);
    return NULL;
  }
  game->stat_last_cmd = OK;

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
  game_set_player_location(game, game_get_space_id_at(game, 0));

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
  };
  player_destroy(game->player);
  dice_destroy(game->dice);
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

  printf("=> Dice last value: %d\n", dice_last_roll(game->dice));

  printf("prompt:> ");
}

BOOL game_is_over(Game *game)
{
  return FALSE;
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

void game_callback_next(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

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
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game->stat_last_cmd = OK;
      }
      else
      {
        game->stat_last_cmd = ERROR;
      }
      return;
    }
  }
  game->stat_last_cmd = ERROR;
}

void game_callback_back(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

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
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game->stat_last_cmd = OK;
      }
      else
      {
        game->stat_last_cmd = ERROR;
      }
      return;
    }
  }
  game->stat_last_cmd = ERROR;
}

void game_callback_take(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id object_id = NO_ID;
  char *toks;
  Id player_id = NO_ID;
  Id object_loc_id = NO_ID;
  char object_desc[100];
  if (Inventory_get_set_num_ids(player_get_inv(game_get_player(game))) != inventory_num_obs(player_get_inv(game_get_player(game))))
  {
    scanf("%s", object_desc);

    if (strncmp("O", object_desc, 1) == 0 || strncmp("o", object_desc, 1) == 0)
    {
      toks = strtok(object_desc + 1, "");
      object_id = atol(toks);
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

      if (current_id == object_loc_id && player_id == current_id && player_object_exist(game->player, object_id) == FALSE)
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
  char *toks;
  Id player_id = NO_ID;
  Id object_id = NO_ID;
  char object_desc[100];
  player_id = game_get_player_location(game);

  if (NO_ID == player_id)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  scanf("%s", object_desc);

  if (strncmp("O", object_desc, 1) == 0 || strncmp("o", object_desc, 1) == 0)
  {
    toks = strtok(object_desc + 1, "");
    object_id = atol(toks);
  }
  if (object_id == NO_ID)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++)
  {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == player_id)
    {
      space_add_object(game->spaces[i], object_id);
      player_sub_object(game->player, object_id);
      game->stat_last_cmd = OK;
      return;
    }
  }
  game->stat_last_cmd = ERROR;
}
void game_callback_roll(Game *game)
{
  if (dice_roll(game->dice) < 0)
  {
    game->stat_last_cmd = ERROR;
    return;
  }
  game->stat_last_cmd = OK;
  return;
}
void game_callback_left(Game *game)
{
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

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
      current_id = space_get_west(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game->stat_last_cmd = OK;
      }
      else
      {
        game->stat_last_cmd = ERROR;
      }
      return;
    }
  }
  game->stat_last_cmd = ERROR;
}
void game_callback_right(Game *game)
{

  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

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
      current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID)
      {
        game_set_player_location(game, current_id);
        game->stat_last_cmd = OK;
      }
      else
      {
        game->stat_last_cmd = ERROR;
      }
      return;
    }
  }
  game->stat_last_cmd = ERROR;
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
Dice *game_get_dice(Game *game)
{
  if (game == NULL)
  {
    return NULL;
  }
  return game->dice;
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