/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2020
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "command.h"
#include "game.h"

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *f1);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[])
{
  Game *game=NULL;
  Graphic_engine *gengine;
  FILE *f1 = NULL;
  if (argc < 2)
  {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  if ((argc >= 3) && ((strcmp(argv[2], "-l") == 0)))
  {
    if (argv[3])
    {

      if (!(f1 = fopen(argv[3], "w")))
      {
        return 1;
      }
    }

    else
    {

      fprintf(stderr, "Use: %s %s -l <log_file>\n", argv[0], argv[1]);
      return 1;
    }
  }
  game=game_create();
  
  if (!game_loop_init(game, &gengine, argv[1]))
  {
    game_loop_run(game, gengine, f1);
    game_loop_cleanup(game, gengine);
  }
  if (f1 != NULL)
  {
    fclose(f1);
  }
  
  return 0;
}

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
  if (game_create_from_file(game, file_name) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    return 1;
  }

  return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *f1)
{
  T_Command command = NO_CMD;

  while ((command != EXIT) && !game_is_over(game))
  {
    char *strcmd;
    graphic_engine_paint_game(gengine, game);
    command = get_user_input();
    game_update(game, command);
    /* there´s quite an important change here, related to the swap performed in the Game stuct */
    if ((game_get_command_status(game) == OK) && (f1 != NULL))
    {
      fprintf(f1, "%s : OK\n", strcmd = change_command_to_string(command));
      free(strcmd);
    }
    else if (f1 != NULL)
    {
      fprintf(f1, "%s : ERROR\n", strcmd = change_command_to_string(command));
      free(strcmd);
    }
  }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
  game_destroy(game);
  graphic_engine_destroy(gengine);

}
