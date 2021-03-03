/**
 * @brief It defines a space
 *
 * @file player.c
 * @author María Paloma Ruiz Matesanz
 * @version 1.0
 * @date  25-02-2021
 * @copyright GNU Public License
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"

struct _Player {
  Id id;
  char name[WORD_SIZE + 1];
  Id location;
  Id object;
};

Player* player_create(Id id) {

  Player *newPlayer = NULL;

  if (id == NO_ID)
    return NULL;

  newPlayer = (Player *) malloc(sizeof (Player));

  if (newPlayer == NULL) {
    return NULL;
  }
  newPlayer->id = id;

  newPlayer->name[0] = '\0';

  newPlayer->location= NO_ID;
  newPlayer->object = NO_ID;

  return newPlayer;
}

STATUS player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}

STATUS player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

//Movement of the player

STATUS player_set_location(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->location = id;
  return OK;
}

STATUS player_set_object(Player* player, Id id) {
  if (!player || id == NO_ID) {
    return ERROR;
  }
  player->object = id;
  return OK;
}

const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Id player_get_object(Player* player) {
  if (!player) {
    return FALSE;
  }
  return player-> object;
}

Id player_get_location(Player* player) {
  if (!player) {
    return ERROR;
  }
  return player-> location;
}

STATUS player_print(Player* player) {
  Id idaux = NO_ID;

  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  idaux = player_get_location(player);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Location link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No location link.\n");
  }

  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the player.\n");
  } else {
    fprintf(stdout, "---> No object in the player.\n");
  }

  return OK;
}
