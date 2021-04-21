#include "command.h"
#include "space.h"
#include "object.h"
#include "dice.h"

#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct _Inventory Inventory;

Inventory *Inventory_create();
STATUS Inventory_destroy(Inventory *I);
STATUS Inventory_add_id(Inventory *I,Id id);
Id inventory_get_id(Inventory *I,int i);
STATUS Inventory_print(Inventory *I);
long inventory_num_obs(Inventory *I);
BOOL Inventory_check_object(Inventory *I, Id id);
STATUS Inventory_sub_id(Inventory *I, Id id);
STATUS inventory_set_max_obs(Inventory *I, long num);
long Inventory_get_set_num_ids(Inventory *I);
#endif