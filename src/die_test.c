/**
 * @brief File to test the functionality of Die module
 *
 * @file die_test.c
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date 15-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"
#include "types.h"

int main(){
  srand(time(NULL));

  Die *die1 = NULL;
  Die *die2 = NULL;

  die1 = die_create(255);
  die2 = die_create(5);

  if(!die1 | !die2) return ERROR;

  die_roll(die1);
  die_print(stdout, die1);
  die_roll(die1);
  die_print(stdout, die1);

  die_roll(die2);
  die_set_id(die2, 45);
  die_print(stdout, die2);
  die_roll(die2);
  die_print(stdout, die2);

  die_destroy(die1);
  die_destroy(die2);


  return OK;
}
