/** 
 * @brief It implements the command interpreter
 * 
 * @file command.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 13-01-2020 
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include "command.h"
#include <stdlib.h>


#define CMD_LENGHT 30

char *cmd_to_str[N_CMD][N_CMDT] =
	{
		{"", "No command"},
		{"", "Unknown"},
		{"e", "Exit"},
		{"n", "Next"},
		{"b", "Back"},
		{"t", "Take"},
		{"d", "Drop"},
		{"rl", "Roll"},
		{"r", "Right"},
		{"l", "Left"}};

T_Command get_user_input()
{
	T_Command cmd = NO_CMD;
	char input[CMD_LENGHT] = "";
	int i = UNKNOWN - NO_CMD + 1;
	if (scanf("%s", input) > 0)
	{
		cmd = UNKNOWN;
		while (cmd == UNKNOWN && i < N_CMD)
		{
			if (!strcasecmp(input, cmd_to_str[i][CMDS]) || !strcasecmp(input, cmd_to_str[i][CMDL]))
			{
				cmd = i + NO_CMD;
			}
			else
			{
				i++;
			}
		}
	}
	return cmd;
}
char *change_command_to_string(T_Command cmd)
{
	char *cmd_str_new=NULL;
	if (!(cmd_str_new=(char*)calloc(__WORDSIZE,sizeof(char))))
		{
			return NULL;
		}
	if (strcpy(cmd_str_new, cmd_to_str[cmd-NO_CMD][CMDL]))
	{
		return cmd_str_new;
	}
	else
	{
		return NULL;
	}
}