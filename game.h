/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "player.h"
#include "object.h"
#include "dice.h"
typedef struct _Game Game;
/**
 * @brief creates a game like structure
 * 
 * @param game 
 * @return STATUS 
 */
Game *game_create();
/**
 * @brief creates a game from a read file
 * 
 * @param game 
 * @param filename 
 * @return STATUS 
 */
STATUS game_create_from_file(Game *game, char *filename);
/**
 * @brief updates the games current values with commands
 * 
 * @param game 
 * @param cmd 
 * @return STATUS 
 */
STATUS game_update(Game *game, T_Command cmd);
/**
 * @brief destroys a game like structure
 * 
 * @param game 
 * @return STATUS 
 */
STATUS game_destroy(Game *game);
/**
 * @brief ends the game
 * 
 * @param game 
 * @return BOOL 
 */
BOOL game_is_over(Game *game);
/**
 * @brief prints the values of the game structure
 * 
 * @param game 
 */
void game_print_data(Game *game);
/**
 * @brief finds a space inside of a game structure
 * 
 * @param game 
 * @param id 
 * @return Space* 
 */
Space *game_get_space(Game *game, Id id);
/**
 * @brief locates a player inside of the game
 * 
 * @param game 
 * @return Id 
 */
Id game_get_player_location(Game *game);
/**
 * @brief locates an object inside of the game
 * 
 * @param game 
 * @param id_object 
 * @return Id 
 */
Id game_get_object_location(Game *game, Id id_object);
/**
 * @brief receives the command written by the player
 * 
 * @param game 
 * @return T_Command 
 */
T_Command game_get_last_command(Game *game);
/**
 * @brief stablishes the location of an object inside of a game
 * 
 * @param game 
 * @param id_space 
 * @param id_object 
 * @return STATUS 
 */
STATUS game_set_object_location(Game *game, Id id_space, Id id_object);

/**
 * @brief Mainly oriented towards stablishing the value of the status due to the opacity of the game structure
 * 
 * @param game 
 * @return STATUS 
 */
STATUS game_get_command_status(Game *game);
/**
 * @brief obtains an object in a certain position with a certain i(index)
 * 
 * @param game 
 * @param i 
 * @return Object* 
 */
Object *game_get_object_inp(Game *game, int i);
/**
 * @brief adds an object to the to the list of objects
 * 
 * @param game 
 * @param object 
 * @return STATUS 
 */
STATUS game_add_object(Game *game, Object *object);
/**
 * @brief  adds an object to the to the list of spaces
 * 
 * @param game 
 * @param space 
 * @return STATUS 
 */
STATUS game_add_space(Game *game, Space *space);
/**
 * @brief receives a space from its respective id and a game
 * 
 * @param game 
 * @param id 
 * @return Space* 
 */
Space *game_get_space(Game *game, Id id);
/**
 * @brief receives the player inside of the game structure
 * 
 * @param game 
 * @return Player* 
 */
Player *game_get_player(Game *game);
/**
 * @brief gets a space inside of the list found in game from a game and an index
 * 
 * @param game 
 * @param index 
 * @return Space* 
 */
Space *game_get_space_with_index(Game *game, long index);
/**
 * @brief obtains the dice related to the game
 * 
 * @param game 
 * @return Dice* 
 */
Dice *game_get_dice(Game *game);
STATUS game_set_player_location(Game *game, Id id);
STATUS game_add_player(Game * game, Player * player);
#endif
