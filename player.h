#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "inventory.h"

#ifndef PLAYER_H
#define PLAYER_H
typedef struct _Player Player;
/**
 * @brief creates a player with a certain id
 * 
 * @param id 
 * @return Player* 
 */
Player *player_create(Id id);
/**
 * @brief destroys a player like structure
 * 
 * @param player 
 * @return STATUS 
 */
STATUS player_destroy(Player *player);
/**
 * @brief stablishes the id for a certain playerl or even change it
 * 
 * @param player 
 * @param id 
 * @return STATUS 
 */
STATUS player_set_name(Player *player, char *name);
 /**
 * @brief finds the name for a certain player
 * 
 * @param player 
 * @return const char* 
 */
const char *player_get_name(Player *player);
/**
 * @brief prints on screen the different values found inside of the player structure
 * 
 * @param player 
 * @return STATUS 
 */
STATUS player_print(Player *player);
/**
 * @brief stablishes the id for a player
 * 
 * @param player 
 * @param id 
 * @return STATUS 
 */
STATUS player_set_id(Player *player, Id id);
/**
 * @brief receives a player id
 * 
 * @param player 
 * @return Id 
 */
Id player_get_id(Player *player);
/**
 * @brief finds the location of a player
 * 
 * @param player 
 * @return Id 
 */
Id player_get_location(Player *player);
/**
 * @brief stablishes the location of a player
 * 
 * @param player 
 * @param location 
 * @return STATUS 
 */
STATUS player_set_location(Player *player, Id location);
/**
 * @brief finds an object stored by the player
 * 
 * @param player 
 * @return Id 
 */
Id player_get_object(Player *player,int i);
/**
 * @brief gives an object to a certain player
 * 
 * @param player 
 * @param object 
 * @return STATUS 
 */
STATUS player_set_object(Player *player, Id object);
Inventory *player_get_inv(Player *player);
Id player_get_object_from_id(Player *player, Id id);
long player_num_objs(Player *player);
BOOL player_object_exist(Player *player, Id id);
STATUS player_sub_object(Player *player, Id id);
STATUS player_set_inventory_max(Player *player, long i);
#endif
