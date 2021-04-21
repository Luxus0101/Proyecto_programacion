#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"
#include "command.h"
#include "die.h"

#define CHAR_WIDTH

struct _Graphic_engine
{
  Area *map, *descript, *banner, *help, *feedback;
};
typedef enum
{
  Em,
  Le,
  Ri,
  Bo
} link_place;

Graphic_engine *graphic_engine_create()
{
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL)
    return NULL;

  ge->map = screen_area_init(1, 1, 50, 22);
  ge->descript = screen_area_init(55, 1, 30, 9);
  ge->banner = screen_area_init(33, 27, 23, 1);
  ge->help = screen_area_init(5, 29, 78, 2);
  ge->feedback = screen_area_init(5, 24, 78, 3);
  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
  if (!ge)
    return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj[100];
  obj[0] = '\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  link_place lp = Em;
  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID)
  {
    space_act = game_get_space(game, id_act);
    id_back = link_getConnection1(game_get_link(game, (space_get_north(space_act))));
    id_next = link_getConnection2(game_get_link(game, (space_get_south(space_act))));

    if ((space_get_east(game_get_space(game, id_back)) != NO_ID))
    {
      lp = Ri;
      if ((space_get_west(game_get_space(game, id_back)) != NO_ID))
      {
        lp = Bo;
      }
    }
    if ((space_get_west(game_get_space(game, id_back)) != NO_ID))
    {
      lp = Le;
    }

    strcpy(obj, "");
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
      if (game_get_object_location(game, object_get_id(game_get_object_inp(game, i))) == id_back)
        strcat(obj, object_get_name((game_get_object_inp(game, i))));
    }
    if (id_back != NO_ID)
    {
      switch (lp)
      {
      case Bo:
        sprintf(str, "     %ld+-----------+%ld", space_get_west(game_get_space(game, id_back)), space_get_east(game_get_space(game, id_back)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|         %2d|-->%ld", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_back)))), (int)id_back, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, id_back)))));
        screen_area_puts(ge->map, str);
        break;
      case Le:
        sprintf(str, "%ld+-----------+", space_get_west(game_get_space(game, id_back)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|         %2d|", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_back)))), (int)id_back);
        screen_area_puts(ge->map, str);
        break;
      case Ri:
        sprintf(str, "  +-----------+%ld", space_get_east(game_get_space(game, id_back)));
        screen_area_puts(ge->map, str);
        sprintf(str, "  |         %2d|-->%ld", (int)id_back, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, id_back)))));
        screen_area_puts(ge->map, str);
        break;
      default:
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |         %2d|", (int)id_back);
        screen_area_puts(ge->map, str);
        break;
      }

      if (space_getDesc(game_get_space_with_index(game, (id_back - 1)))[0][0] != '\0')
      {
        for (int i = 0; i < NUM_SHAPES; i++)
        {
          sprintf(str, "  |%s|", space_getDesc(game_get_space_with_index(game, (id_back - 1)))[i]);
          screen_area_puts(ge->map, str);
        }
      }
      else
      {
        for (int i = 0; i < NUM_SHAPES; i++)
        {
          sprintf(str, "  |           |");
          screen_area_puts(ge->map, str);
        }
      }

      if (strcmp(obj, "") == 0)
      {
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }
      else
      {
        sprintf(str, "  |%s         |", obj);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^ %ld", id_back);
      screen_area_puts(ge->map, str);
    }
    strcpy(obj, "");
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
      if (game_get_object_location(game, object_get_id(game_get_object_inp(game, i))) == id_act)
        strcat(obj, object_get_name((game_get_object_inp(game, i))));
    }
    lp = Em;
    if ((space_get_east(game_get_space(game, id_act)) != NO_ID))
    {
      lp = Ri;
      if ((space_get_west(game_get_space(game, id_act)) != NO_ID))
      {
        lp = Bo;
      }
    }
    if ((space_get_west(game_get_space(game, id_act)) != NO_ID))
    {
      lp = Le;
    }

    if (id_act != NO_ID)
    {
      switch (lp)
      {
      case Bo:
        sprintf(str, "     %ld+-----------+%ld", space_get_west(game_get_space(game, id_act)), space_get_east(game_get_space(game, id_act)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|:D       %2d|-->%ld", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_act)))), (int)id_act, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, id_act)))));
        screen_area_puts(ge->map, str);
        break;
      case Le:
        sprintf(str, "%ld+-----------+", space_get_west(game_get_space(game, id_act)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|:D       %2d|", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_act)))), (int)id_act);
        screen_area_puts(ge->map, str);
        break;
      case Ri:
        sprintf(str, "  +-----------+%ld", space_get_east(game_get_space(game, id_act)));
        screen_area_puts(ge->map, str);
        sprintf(str, "  |:D       %2d|-->%ld", (int)id_act, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, id_act)))));
        screen_area_puts(ge->map, str);
        break;
      default:
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |:D       %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        break;
      }

      if (space_getDesc(game_get_space_with_index(game, (id_act - 1)))[0][0] != '\0')
      {
        for (int i = 0; i < NUM_SHAPES; i++)
        {
          sprintf(str, "  |%s|", space_getDesc(game_get_space_with_index(game, (id_act - 1)))[i]);
          screen_area_puts(ge->map, str);
        }
      }
      else
      {
        for (int i = 0; i < NUM_SHAPES; i++)
        {
          sprintf(str, "  |           |");
          screen_area_puts(ge->map, str);
        }
      }

      if (strcmp(obj, "") == 0)
      {
        sprintf(str, "  |           |");
        screen_area_puts(ge->map, str);
      }
      else
      {
        sprintf(str, "  |%s         |", obj);
        screen_area_puts(ge->map, str);
      }
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }
    strcpy(obj, "");
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
      if (game_get_object_location(game, object_get_id(game_get_object_inp(game, i))) == id_next)
        strcat(obj, object_get_name((game_get_object_inp(game, i))));
    }
    lp = Em;
    if (id_next != NO_ID)
    {
      sprintf(str, "        v %ld", id_next);
      screen_area_puts(ge->map, str);
      if ((space_get_east(game_get_space(game, id_next)) != NO_ID))
      {
        lp = Ri;
        if ((space_get_west(game_get_space(game, id_next)) != NO_ID))
        {
          lp = Bo;
        }
      }
      if ((space_get_west(game_get_space(game, id_next)) != NO_ID))
      {
        lp = Le;
      }
      switch (lp)
      {
      case Bo:
        sprintf(str, "     %ld+-----------+%ld", space_get_west(game_get_space(game, id_next)), space_get_east(game_get_space(game, id_next)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|         %2d|-->%ld", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_next)))), (int)id_next, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, id_next)))));
        screen_area_puts(ge->map, str);
        break;
      case Le:
        sprintf(str, "%ld+-----------+", space_get_west(game_get_space(game, id_next)));
        screen_area_puts(ge->map, str);
        sprintf(str, "%ld<--|         %2d|", link_getConnection2(game_get_link(game, space_get_west(game_get_space(game, id_next)))), (int)id_next);
        screen_area_puts(ge->map, str);
        break;
      case Ri:
        sprintf(str, "  +-----------+%ld", space_get_east(game_get_space(game, id_next)));
        screen_area_puts(ge->map, str);
        sprintf(str, "  |         %2d|-->%ld", (int)id_next, link_getConnection2(game_get_link(game, space_get_east(game_get_space(game, (int)id_next)))));
        screen_area_puts(ge->map, str);
        break;
      default:
        sprintf(str, "  +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |         %2d|", (int)id_next);
        screen_area_puts(ge->map, str);
        break;

        if (space_getDesc(game_get_space_with_index(game, (id_next - 1)))[0][0] != '\0')
        {
          for (int i = 0; i < NUM_SHAPES; i++)
          {
            sprintf(str, "  |%s|", space_getDesc(game_get_space_with_index(game, (id_next - 1)))[i]);
            screen_area_puts(ge->map, str);
          }
        }
        else
        {
          for (int i = 0; i < NUM_SHAPES; i++)
          {
            sprintf(str, "  |           |");
            screen_area_puts(ge->map, str);
          }
        }

        if (strcmp(obj, "") == 0)
        {
          sprintf(str, "  |           |");
          screen_area_puts(ge->map, str);
        }
        else
        {
          sprintf(str, "  |%s         |", obj);
          screen_area_puts(ge->map, str);
        }
      }
    }

    /* Paint in the description area */
    screen_area_clear(ge->descript);
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
      obj_loc = game_get_object_location(game, object_get_id(game_get_object_inp(game, i)));
      if ((obj_loc != NO_ID))
      {
        sprintf(str, "  Object %d location:%d", i + 1, (int)obj_loc);
        screen_area_puts(ge->descript, str);
      }
    }
    sprintf(str, "  Last roll: %d", die_last_roll(game_get_die(game)));
    screen_area_puts(ge->descript, str);
    char obj_name[100] = "";
    int num;
    for (int i = 0; i < MAX_OBJECTS; i++)
    {
      for (int j = 0; j < inventory_num_obs(player_get_inv(game_get_player(game))); j++)
      {
        if (player_get_object(game_get_player(game), j) == object_get_id(game_get_object_inp(game, i)))
        {
          num = strlen(obj_name);
          sprintf(obj_name + num, "%s", object_get_name(game_get_object_inp(game, i)));
          break;
        }
      }
    }
    num = strlen(obj_name);
    obj_name[num] = '\0';

    sprintf(str, "  Player object: %s", obj_name);
    screen_area_puts(ge->descript, str);

    sprintf(str, "  Descriptions:");
    screen_area_puts(ge->descript, str);

    last_cmd = game_get_last_command(game);
    if (last_cmd == INSPECT)
    {
      sprintf(str, "  %s", game_get_lastDescription(game));
      screen_area_puts(ge->descript, str);
    }

    /* Paint in the banner area */
    screen_area_puts(ge->banner, " The game of the Goose ");

    /* Paint in the help area */
    screen_area_clear(ge->help);
    sprintf(str, " The commands you can use are:");
    screen_area_puts(ge->help, str);
    sprintf(str, "      next or n, back or b, exit or e, d or drop, t or take, rl or roll,             l or left, r or right, m or move, i or inspect");
    screen_area_puts(ge->help, str);

    /* Paint in the feedback area */
    last_cmd = game_get_last_command(game);
    sprintf(str, " %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
    screen_area_puts(ge->feedback, str);

    /* Dump to the terminal */
    screen_paint();
    printf("prompt:> ");
  }
}
