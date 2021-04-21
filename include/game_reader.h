#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


  /**
 * @brief tokenises the values found in data.dat introducing them into their respective spaces
 * 
 * @param game 
 * @param filename 
 * @return STATUS 
 */
STATUS game_load_spaces(Game *game, char *filename);

 /**
 * @brief interprets the data.dat file and introduces objcts into a set foumd in the interior of the game structure
 * 
 * @param game 
 * @param filename 
 * @return STATUS 
 */
STATUS game_load_objects(Game *game, char *filename);
STATUS game_load_player(Game *game, char *filename);
STATUS game_load_links(Game *game, char *filename);