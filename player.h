/**
 * @brief It defines a space
 *
 * @file player.c
 * @author Paloma Ruiz Matesanz
 * @version 1.0
 * @date  25-02-2021
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

#define PLAYER_ID 102

typedef struct _Player Player;

Player* player_create(Id id);
STATUS player_destroy(Player* player);
Id player_get_id(Player* player);
STATUS player_set_name(Player* player, char* name);
const char* player_get_name(Player* player);
STATUS player_set_location(Player* player, Id id);
Id player_get_object(Player* player);
Id player_get_location(Player* player);
STATUS player_set_object(Player* player, Id id);
STATUS player_print(Player* player);

#endif
