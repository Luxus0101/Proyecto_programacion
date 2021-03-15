/**
 * @brief File to test the functionality of Set module
 *
 * @file set_test.c
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date 08-03-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include "set.h"
#include "types.h"

int main(){
  Set *set = NULL;
  Id id1 = 0, id2 = 7, id3 = 8;
  set = set_create();

  set_add(set, -1);
  set_add(set, id1);
  set_add(set, id3);
  set_add(set, id2);

  set_print(stdout, set);

  set_del(set, id2);
  set_del(set, 40);

  set_print(stdout, set);

  set_destroy(set);

  return OK;
}
