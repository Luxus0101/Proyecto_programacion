#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dialogue.h"
#include "game_reader.h"
#include "game.h"
#include "command.h"

struct _Dialogue
{
  int cont;
  char *arg;
  char *dial;
  int ult;
  char *lastArg;
};

Dialogue *dialogue_init()
{
  Dialogue *d;
  d = (Dialogue *)malloc(sizeof(Dialogue));
  d->arg = (char *)malloc(sizeof(char) * 100);
  strcpy(d->arg, " ");
  d->dial = (char *)malloc(sizeof(char) * 300);
  strcpy(d->dial, " ");
  d->cont = 0;
  d->ult = 5;
  d->lastArg = (char *)malloc(sizeof(char) * 100);
  strcpy(d->lastArg, "n");
  return d;
}

STATUS dialogue_free(Dialogue *d)
{
  if (d == NULL)
    return ERROR;
  free(d->lastArg);
  free(d->arg);
  free(d->dial);
  free(d);
  d = NULL;
  return OK;
}

char *dialogue_get_arg(Dialogue *d)
{
  if (d == NULL)
    return NULL;
  return d->arg;
}

char *dialogue_get_lastArg(Dialogue *d)
{
  if (d == NULL)
    return NULL;
  return d->lastArg;
}

char *dialogue_get_dial(Dialogue *d)
{
  if (d == NULL)
    return NULL;
  return d->dial;
}

int dialogue_get_cont(Dialogue *d)
{
  if (d == NULL)
    return -1;
  return d->cont;
}

STATUS dialogue_set_cont(Dialogue *d, int cont)
{
  if (d == NULL)
    return ERROR;
  d->cont = cont;
  return OK;
}

int dialogue_get_ult(Dialogue *d)
{
  if (d == NULL)
    return -1;
  return d->ult;
}

STATUS dialogue_set_ult(Dialogue *d, int ult)
{
  if (d == NULL)
    return ERROR;
  d->ult = ult;
  return OK;
}

STATUS dialogue_set_arg(Dialogue *d, char *a)
{
  if (d == NULL || a == NULL)
    return ERROR;
  strcpy(d->arg, a);
  return OK;
}

STATUS dialogue_set_lastArg(Dialogue *d, char *a)
{
  if (d == NULL || a == NULL)
    return ERROR;
  strcpy(d->lastArg, a);
  return OK;
}

STATUS dialogue_set_dial(Dialogue *d, char *a)
{
  if (d == NULL || a == NULL)
    return ERROR;
  strcpy(d->dial, a);
  return OK;
}

STATUS dialogue_switch(Dialogue *d, int commId, STATUS st)
{
  if (d == NULL)
    return ERROR;
  char aux[300];
  sprintf(aux, "%s", d->arg);
  if (st == ERROR && d->ult == commId && strcmp(aux, d->lastArg) == 0)
  {
    d->cont++;
  }
  else
  {
    d->cont = 0;
  }
  strcpy(d->lastArg, aux);
  d->ult = commId;
  if (d->cont > 1 && st == ERROR && strcmp(aux, d->lastArg) == 0)
  {
    sprintf(aux, "You have tried %d times before, try another command", d->cont);
  }
  else
  {
    switch (commId)
    {
    case 1: // exit
      printf("Bye bye :P\n");
    case 2: //take
      if (st == ERROR || d->cont >= 1)
      {
        sprintf(aux, "You haven't been able to take any object");
      }
      else
      {
        sprintf(aux, "You just took the object %s", d->arg);
      }
      break;
    case 3: //drop
      if (st == ERROR || d->cont >= 1)
      {
        sprintf(aux, "You haven't been able to drop any object");
      }
      else
      {
        sprintf(aux, "You have drop the object %s", d->arg);
      }
      break;
    case 4: //roll
      sprintf(aux, "You have rolled the dice");
      break;
    case 5: //move
      if (st == ERROR || d->cont >= 1)
      {
        sprintf(aux, "You haven't been able to move %s", d->arg);
      }
      else
      {
        sprintf(aux, "You have moved %s", d->arg);
      }
      break;
    case 6: //inspect
      sprintf(aux, "You have read the description");
      break;
    case 7: //turn on
      sprintf(aux, "You have turn on the light");
      break;
    case 8: //turn off
      sprintf(aux, "You have turn off the light");
      break;
    case 9: //open
      if (st == ERROR || d->cont >= 1)
      {
        sprintf(aux, "You haven't been able to open %s", d->arg);
      }
      else
      {
        sprintf(aux, "You have opened %s", d->arg);
      }
      break;
      case 10: //save
      if (st == ERROR)
      {
        sprintf(aux, "Error saving");
      }
      else
      {
        sprintf(aux, "Saved file %s", d->arg);
      }
      break;
      case 11: //load
      if (st == ERROR)
      {
        sprintf(aux, "Error loading");
      }
      else
      {
        sprintf(aux, "Loaded file %s", d->arg);
      }
      break;
    default: //Unknown
      sprintf(aux, "This is not a valid action, try again");
      break;
    }
  }
  strcpy(d->dial, aux);
  return OK;
}
