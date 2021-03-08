/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Paloma Ruiz Matesanz
 * @version 1.0
 * @date 27-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "object.h"
#include "player.h"
#include "space.h"
#include "command.h"
#include "game_reader.h"
#include "graphic_engine.h"
#include "screen.h"
#include "types.h"

#define N_CALLBACK 7


//Define the function type for the callbacks

typedef void (*callback_fn)(Game* game);

//List of callbacks for each command in the game

void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_next(Game* game);
void game_callback_back(Game* game);
void game_callback_take(Game* game);
void game_callback_drop(Game* game);
void game_callback_jump(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_next,
  game_callback_back,
  game_callback_take,
  game_callback_drop,
  game_callback_jump};

//Private functions

STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);

//Game interface implementation

STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game-> player = player_create(PLAYER_ID);
  game-> object = object_create(OBJECT_ID);
  game-> last_cmd = NO_CMD;

  return OK;
}

STATUS game_create_from_file(Game* game, char* filename) {

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;

  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }
  object_destroy(game->object);
  player_destroy(game->player);
  return OK;
}

STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ((i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}

Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }
  return space_get_id(game->spaces[position]);
}

Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }
  return NULL;
}

STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  player_set_location(game->player, id);

  return OK;
}

STATUS game_set_object_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }
  int i=0;
  while (i<MAX_SPACES && game->spaces[i] != NULL){
    if (space_get_id(game->spaces[i])== id){
      space_set_object(game->spaces[i], id);
      return OK;
    }
    i++;
  }
  return ERROR;
}

Id game_get_player_location(Game* game) {
  return player_get_location(game->player);
}

Id game_get_object_location(Game* game) {
  int i=0;
  Id id;
  id=object_get_id(game->object);
  for(i=0;i<MAX_SPACES && game->spaces[i] != NULL; i++){
    if (space_get_object(game->spaces[i])==id){
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID;
}

STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int) game_get_object_location(game));
  printf("=> Player location: %d\n", (int) game_get_player_location(game));
  printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
  return FALSE;
}

//Callbacks implementation for each action

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}

void game_callback_next(Game* game) {
  int i = 0;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    Id current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      Id current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_back(Game* game) {
  int i = 0;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    Id current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      Id current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_take(Game* game) {
  int i = 0;
  Id player_id = NO_ID;

  player_id = game_get_player_location(game);

  if (NO_ID == player_id) {
    return;
  }
  for (i=0; i<MAX_SPACES && game->spaces[i] != NULL; i++){
    if (player_id==space_get_id(game->spaces[i])){
      break;
    }
  }
  if (space_get_object(game->spaces[i]) == NO_ID){
    return;
  }
  player_set_object (game->player, space_get_object(game->spaces[i]));
  space_set_object(game->spaces[i], NO_ID);
  return;
}

void game_callback_drop(Game* game) {
  int i = 0;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }
  for (i=0; i<MAX_SPACES && game->spaces[i] != NULL; i++){
    if (space_id==space_get_id(game->spaces[i])){
      break;
    }
  }
  if (space_get_object(game->spaces[i]) != NO_ID){
    return;
  }
  space_set_object(game->spaces[i], player_get_object(game->player));
  player_set_object(game->player, NO_ID);
  return;
}


void game_callback_jump(Game* game) {
  int i = 0;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    Id current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      Id current_id = space_get_east(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}
