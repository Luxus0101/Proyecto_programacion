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
#include "die.h"
#include "dialogue.h"
typedef struct _Game Game;
/**
 * @brief creates a game like structure
 *
 * @param game Pointer to the game
 * @return STATUS
 */
Game *game_create();
/**
 * @brief creates a game from a read file
 *
 * @param game Pointer to the game
 * @param filename
 * @return STATUS
 */
STATUS game_create_from_file(Game *game, char *filename);
/**
 * @brief updates the games current values with commands
 *
 * @param game Pointer to the game
 * @param cmd
 * @return STATUS
 */
STATUS game_update(Game *game, T_Command cmd);
/**
 * @brief destroys a game like structure
 *
 * @param game Pointer to the game
 * @return STATUS
 */
STATUS game_destroy(Game *game);
/**
 * @brief ends the game
 *
 * @param game Pointer to the game
 * @return BOOL
 */
BOOL game_is_over(Game *game);
/**
 * @brief prints the values of the game structure
 *
 * @param game Pointer to the game
 */
void game_print_data(Game *game);
/**
 * @brief finds a space inside of a game structure
 *
 * @param game Pointer to the game
 * @param id
 * @return Space*
 */
Space *game_get_space(Game *game, Id id);
/**
 * @brief locates a player inside of the game
 *
 * @param game Pointer to the game
 * @return Id
 */
Id game_get_player_location(Game *game);
/**
 * @brief locates an object inside of the game
 *
 * @param game Pointer to the game
 * @param id_object
 * @return Id
 */
Id game_get_object_location(Game *game, Id id_object);
/**
 * @brief receives the command written by the player
 *
 * @param game Pointer to the game
 * @return T_Command
 */
T_Command game_get_last_command(Game *game);
/**
 * @brief stablishes the location of an object inside of a game
 *
 * @param game Pointer to the game
 * @param id_space
 * @param id_object
 * @return STATUS
 */
STATUS game_set_object_location(Game *game, Id id_space, Id id_object);

/**
 * @brief Mainly oriented towards stablishing the value of the status due to the opacity of the game structure
 *
 * @param game Pointer to the game
 * @return STATUS
 */
STATUS game_get_command_status(Game *game);
/**
 * @brief obtains an object in a certain position with a certain i(index)
 *
 * @param game Pointer to the game
 * @param i
 * @return Object*
 */
Object *game_get_object_inp(Game *game, int i);
/**
 * @brief adds an object to the to the list of objects
 *
 * @param game Pointer to the game
 * @param object
 * @return STATUS
 */
STATUS game_add_object(Game *game, Object *object);
/**
 * @brief  adds an object to the to the list of spaces
 *
 * @param game Pointer to the game
 * @param space
 * @return STATUS
 */
STATUS game_add_space(Game *game, Space *space);
/**
 * @brief receives a space from its respective id and a game
 *
 * @param game Pointer to the game
 * @param id
 * @return Space*
 */
Space *game_get_space(Game *game, Id id);
/**
 * @brief receives the player inside of the game structure
 *
 * @param game Pointer to the game
 * @return Player*
 */
Player *game_get_player(Game *game);
/**
 * @brief gets a space inside of the list found in game from a game and an index
 *
 * @param game Pointer to the game
 * @param index
 * @return Space*
 */
Space *game_get_space_with_index(Game *game, long index);
/**
 * @brief obtains the die related to the game
 *
 * @param game Pointer to the game
 * @return die*
 */
Die *game_get_die(Game *game);
STATUS game_set_player_location(Game *game, Id id);
STATUS game_add_player(Game * game, Player * player);
Link* game_get_link(Game *game, Id id);
STATUS game_add_link(Game *game, Link *link);
char *game_get_lastDescription(Game *game);
/**
 * @brief Returns if an object can be taken or not based on its dependencies
 * 
 * @param game Pointer to the game
 * @param object Pointer to the object 
 * @return BOOL, TRUE if it can be taken, FALSE otherwise
 */
BOOL game_object_canBeTaken(Game *game, Object *object);
STATUS game_set_dial(Game *game, Dialogue *d);
Dialogue *game_get_dial(Game *game);
/**
 * @brief obtains the pointer to the link with an id given
 * 
 * @param game Pointer to the game
 * @param id of the link
 * @return Link* 
 */
Link *game_get_link_with_id(Game *game, Id id);
Link *game_get_link_inp(Game *game, int index);
STATUS game_clean(Game *game);
#endif
