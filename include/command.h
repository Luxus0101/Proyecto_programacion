/**
 * @brief It implements the command interpreter
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 2.0
 * @date 13-01-2020
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#define N_CMDT 2
#define N_CMD 12

typedef enum enum_CmdType
{
  CMDS,
  CMDL
} T_CmdType;

typedef enum enum_Command
{
  NO_CMD = -1,
  UNKNOWN,
  EXIT,
  NEXT,
  BACK,
  TAKE,
  DROP,
  ROLL,
  LEFT,
  RIGHT,
  MOVE,
  INSPECT
} T_Command;
char *change_command_to_string(T_Command cmd);
T_Command get_user_input();

#endif
