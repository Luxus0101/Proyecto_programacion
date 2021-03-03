/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file graphic_engine.h
 * @author Paloma Ruiz Matesanz
 * @version 1.0
 * @date 10-02-2021
 * @copyright GNU Public License
 */

#ifndef __GRAPHIC_ENGINE__
#define __GRAPHIC_ENGINE__

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine *ge);
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);
void graphic_engine_write_command(Graphic_engine *ge, char *str);

#endif
