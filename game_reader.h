/**
 * @brief Read the game module
 * for each command
 *
 * @file game_reader.h
 * @author Paloma Ruiz Matesanz
 * @version 1.0
 * @date  27-02-2021
 * @copyright GNU Public License
 */

#ifndef GREAD_H
#define GREAD_H

#include "types.h"
#include "game.h"

STATUS game_load_spaces(Game* game, char* filename);
#endif
