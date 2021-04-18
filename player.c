#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "player.h"
#include "inventory.h"
struct _Player
{
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Inventory *I;
};

Player *player_create(Id id)
{
  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *)malloc(sizeof(Player));

  if (newPlayer == NULL)
  {
    return NULL;
  }

  newPlayer->id = id;

  newPlayer->name[0] = '\0';

  newPlayer->location = NO_ID;

  newPlayer->I = Inventory_create();

  return newPlayer;
}

STATUS player_set_id(Player *player, Id id)
{
  if (!player)
  {
    return ERROR;
  }
  if (id < 0)
  {
    return ERROR;
  }
  player->id = id;

  return OK;
}

Id player_get_id(Player *player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->id;
}

STATUS player_set_name(Player *player, char *name)
{
  if (!player || !name)
  {
    return ERROR;
  }

  if (!strcpy(player->name, name))
  {
    return ERROR;
  }

  return OK;
}
const char *player_get_name(Player *player)
{
  if (!player)
  {
    return NULL;
  }
  return player->name;
}
STATUS player_set_location(Player *player, Id location)
{
  if (!player)
  {
    return ERROR;
  }
  player->location = location;
  return OK;
}
Id player_get_location(Player *player)
{
  if (!player)
  {
    return NO_ID;
  }
  return player->location;
}

STATUS player_set_object(Player *player, Id object)
{
  if (!player)
  {
    return ERROR;
  }
  Inventory_add_id(player->I, object);
  return OK;
}

Id player_get_object(Player *player, int i)
{
  if (!player)
  {
    return NO_ID;
  }
  return inventory_get_id(player->I, i);
}
Id player_get_object_from_id(Player *player, Id id)
{

  if ((!player) || (id < 0))
  {
    return -1;
  }
  for (int i = 0; i < inventory_num_obs(player->I); i++)
  {
    if (id == inventory_get_id(player->I, i))
    {
      return id;
    }
  }
  return -1;
}

STATUS player_print(Player *player)
{
  if (!player)
  {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld)\n", player->id, player->name, player->location);
  Inventory_print(player->I);
  return OK;
}

STATUS player_destroy(Player *player)
{
  if (!player)
  {
    return ERROR;
  }

  Inventory_destroy(player->I);
  free(player);
  player = NULL;

  return OK;
}
Inventory *player_get_inv(Player *player)
{
  if (player == NULL)
  {
    return NULL;
  }
  return player->I;
}
long player_num_objs(Player *player)
{
  if (player == NULL)
  {
    return -1;
  }
  return inventory_num_obs(player->I);
}
BOOL player_object_exist(Player *player, Id id)
{
  if (player == NULL || id < 0)
  {
    return FALSE;
  }
  if (Inventory_check_object(player->I, id) == TRUE)
  {
    return TRUE;
  }
  return FALSE;
}
STATUS player_sub_object(Player *player, Id id)
{
  if (player == NULL || id < 0)
  {
    return ERROR;
  }

  Inventory_sub_id(player->I, id);
  return OK;
}
STATUS player_set_inventory_max(Player *player, long i)
{

  if (inventory_set_max_obs(player->I, i))
  {
    return ERROR;
  }
  return OK;
}