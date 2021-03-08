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
