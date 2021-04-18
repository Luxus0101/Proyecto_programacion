#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

STATUS game_add_space(Game *game, Space *space);
STATUS game_load_spaces(Game *game, char *filename);
Space *game_get_space(Game *game, Id id);
STATUS game_load_objects(Game *game, char *filename);
STATUS game_add_object(Game *game, Object *object);
STATUS game_load_links(Game *game, char *filename);
